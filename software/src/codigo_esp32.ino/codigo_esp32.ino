/*
 * COStop - Alarma doméstica de monóxido de carbono (CO)
 * Taller de Diseño en Ingeniería (TEI201) - Universidad Adolfo Ibáñez
 *
 * Plataforma: ESP32-S3 Super Mini
 * Sensores:   MQ-7 (gas, entrada analógica) y DHT11 (temperatura y humedad)
 * Salidas:    LED RGB KY-016 y buzzer pasivo
 *
 * Funcionamiento general:
 *  - Mide el gas con el MQ-7 una vez por segundo y decide un "nivel" (0, 1 o 2).
 *  - Para evitar falsas alarmas, el nivel solo cambia tras varias lecturas seguidas
 *    (confirmación) y vuelve a bajar con histéresis.
 *  - A partir del nivel y de las fallas de sensores se define el estado del sistema:
 *    WARMUP, NORMAL, ALERTA, ALARMA o FALLA, y cada uno tiene su patrón de LED y buzzer.
 *  - El botón silencia el buzzer, pero no apaga la alarma ni el LED.
 *
 * Librería requerida: DHT sensor library (Adafruit) + Adafruit Unified Sensor.
 */

#include <DHT.h>

// ---------- Pines (ESP32-S3 Super Mini) ----------
const int PIN_DHT    = 4;   // datos del DHT11
const int PIN_MQ     = 1;   // salida analógica del MQ-7 (debe ser un pin con ADC)
const int PIN_BUZZER = 5;   // buzzer
const int PIN_R      = 6;   // LED RGB - rojo
const int PIN_G      = 8;   // LED RGB - verde
const int PIN_B      = 9;   // LED RGB - azul
const int PIN_BTN    = 0;   // botón BOOT (provisorio). Con pulsador real: 7

// ---------- Opciones de hardware ----------
const bool BUZZER_ACTIVO   = false;  // true: activo (suena con HIGH). false: pasivo (usa tone)
const bool LED_ANODO_COMUN = false;  // KY-016 normal: false

// ---------- Parámetros (ajustables) ----------
// Los umbrales están en valores crudos del ADC (0-4095), no en ppm.
const int  T_ALERTA   = 1500;      // umbral alerta (valor ADC 0-4095)
const int  T_ALARMA   = 2500;      // umbral alarma
const int  HIST       = 200;       // histéresis: se baja de nivel solo si la lectura cae HIST bajo el umbral
const int  CONFIRMAR  = 3;         // lecturas seguidas para cambiar de nivel
const unsigned long WARMUP_MS   = 20000;   // calentamiento del MQ-7; equipo real: minutos
const unsigned long SILENCIO_MS = 30000;   // duración del silencio; equipo real: 300000 (5 min)
const unsigned long MUESTREO_MS = 1000;    // cada cuánto se lee el sensor de gas
const unsigned long DHT_MS      = 2000;    // cada cuánto se lee el DHT11

// Objeto del sensor de temperatura y humedad (tipo DHT11)
DHT dht(PIN_DHT, DHT11);

// Estados posibles del sistema
enum Estado { WARMUP, NORMAL, ALERTA, ALARMA, FALLA };
Estado estado = WARMUP;

// Variables de control del nivel de gas
int  nivel = 0, candidato = 0, conf = 0;   // nivel vigente (0/1/2), nivel candidato y lecturas que lo confirman
int  rawMQ = 0, fallasADC = 0, fallasDHT = 0;  // última lectura del MQ y contadores de fallas seguidas
float temp = NAN, hum = NAN;               // última temperatura y humedad válidas
unsigned long tMuestreo = 0, tDHT = 0, silencioHasta = 0;  // marcas de tiempo (ms)
bool buzzerSonando = false;                // evita reenviar la orden al buzzer en cada ciclo

// ---------- Salidas ----------

/*
 * Enciende el LED RGB. Cada parámetro es 1 (encendido) o 0 (apagado).
 * Si el LED es de ánodo común, se invierte la lógica.
 */
void setColor(bool r, bool g, bool b) {
  if (LED_ANODO_COMUN) { r = !r; g = !g; b = !b; }
  digitalWrite(PIN_R, r);
  digitalWrite(PIN_G, g);
  digitalWrite(PIN_B, b);
}

// Buzzer activo: basta con poner el pin en HIGH. Pasivo: necesita un tono (2000 Hz).
void buzzerOn()  { if (BUZZER_ACTIVO) digitalWrite(PIN_BUZZER, HIGH); else tone(PIN_BUZZER, 2000); }
void buzzerOff() { if (BUZZER_ACTIVO) digitalWrite(PIN_BUZZER, LOW);  else noTone(PIN_BUZZER); }

// ---------- Lectura del sensor de gas (promedio de 4) ----------
// Promediar varias lecturas reduce el ruido del ADC y evita saltos por una lectura aislada.
int leerMQ() {
  long suma = 0;
  for (int i = 0; i < 4; i++) suma += analogRead(PIN_MQ);
  return suma / 4;
}

// ---------- Nivel objetivo con histéresis ----------
/*
 * Devuelve el nivel que corresponde a una lectura: 0 normal, 1 alerta, 2 alarma.
 * Con histéresis: si ya se está en un nivel alto, se mantiene hasta que la lectura
 * baje HIST unidades por debajo del umbral. Así no oscila cuando el valor está
 * justo en el límite.
 */
int objetivo(int raw, int actual) {
  if (raw >= T_ALARMA) return 2;
  if (actual == 2 && raw >= T_ALARMA - HIST) return 2;   // mantiene alarma hasta bajar bien
  if (raw >= T_ALERTA) return 1;
  if (actual >= 1 && raw >= T_ALERTA - HIST) return 1;   // mantiene alerta hasta bajar bien
  return 0;
}

// ---------- Botón: silencia, no desactiva ----------
/*
 * Lee el botón con antirrebote de 50 ms. Al presionarlo (LOW, por el pull-up) en
 * ALERTA, ALARMA o FALLA, silencia el buzzer durante SILENCIO_MS. El LED sigue activo.
 */
void revisarBoton() {
  static bool ultimo = HIGH;            // última lectura estable del botón
  static unsigned long tCambio = 0;     // momento del último cambio aceptado
  bool lectura = digitalRead(PIN_BTN);
  if (lectura != ultimo && millis() - tCambio > 50) {   // ignora rebotes menores a 50 ms
    tCambio = millis();
    ultimo = lectura;
    if (lectura == LOW && (estado == ALERTA || estado == ALARMA || estado == FALLA)) {
      silencioHasta = millis() + SILENCIO_MS;
      Serial.println(">> Alarma silenciada");
    }
  }
}

// ---------- Salidas según estado ----------
/*
 * Define el patrón de LED y buzzer de cada estado usando millis() (sin delay(),
 * para no bloquear la lectura de sensores):
 *   WARMUP  azul parpadeando (200 ms de cada 400 ms), sin sonido
 *   NORMAL  verde, destello de 80 ms cada 3 s ("latido": indica que el equipo funciona)
 *   ALERTA  amarillo y pitido de 200 ms cada 1 s
 *   ALARMA  rojo fijo y sonido continuo
 *   FALLA   magenta con doble pitido de 150 ms cada 2 s
 */
void actualizarSalidas() {
  unsigned long t = millis();
  bool led = false, buz = false;   // led: encendido en este instante; buz: buzzer debe sonar

  switch (estado) {
    case WARMUP: led = (t % 400) < 200; break;
    case NORMAL: led = (t % 3000) < 80; break;            // latido
    case ALERTA: { unsigned long p = t % 1000; led = buz = (p < 200); } break;
    case ALARMA: led = buz = true; break;
    case FALLA:  { unsigned long p = t % 2000;
                   led = buz = (p < 150) || (p >= 300 && p < 450); } break;   // dos pitidos
  }

  // Si el botón silenció la alarma, el buzzer queda apagado hasta que termine el tiempo
  bool silenciado = (long)(silencioHasta - t) > 0;
  if (silenciado) buz = false;

  // Color del LED según el estado (o apagado en la parte "off" del parpadeo)
  if (!led) setColor(0, 0, 0);
  else switch (estado) {
    case WARMUP: setColor(0, 0, 1); break;   // azul
    case NORMAL: setColor(0, 1, 0); break;   // verde
    case ALERTA: setColor(1, 1, 0); break;   // amarillo
    case ALARMA: setColor(1, 0, 0); break;   // rojo
    case FALLA:  setColor(1, 0, 1); break;   // magenta
  }

  // Solo se activa o desactiva el buzzer cuando cambia su situación
  if (buz && !buzzerSonando)      { buzzerOn();  buzzerSonando = true; }
  else if (!buz && buzzerSonando) { buzzerOff(); buzzerSonando = false; }
}

// Inicialización: puerto serial, pines, ADC y sensor DHT
void setup() {
  Serial.begin(115200);
  pinMode(PIN_R, OUTPUT);
  pinMode(PIN_G, OUTPUT);
  pinMode(PIN_B, OUTPUT);
  pinMode(PIN_BUZZER, OUTPUT);
  pinMode(PIN_BTN, INPUT_PULLUP);   // botón a tierra: presionado = LOW
  setColor(0, 0, 0);
  buzzerOff();
  analogSetPinAttenuation(PIN_MQ, ADC_11db);   // permite leer hasta ~3,3 V en el ADC
  dht.begin();
  Serial.println("Calentando...");
}

// Ciclo principal: lee sensores, calcula el estado y actualiza las salidas
void loop() {
  unsigned long t = millis();
  revisarBoton();

  // --- DHT11 cada 2 s ---
  // Solo informa temperatura y humedad por serial; su único efecto en el estado es detectar su propia falla.
  if (t - tDHT >= DHT_MS) {
    tDHT = t;
    float h = dht.readHumidity();
    float c = dht.readTemperature();
    if (isnan(h) || isnan(c)) fallasDHT++;               // lectura inválida: cuenta una falla
    else { fallasDHT = 0; hum = h; temp = c; }           // lectura válida: reinicia el contador
    Serial.printf("MQ=%d | T=%.1f C | H=%.1f %% | estado=%d | DHT_fallas=%d\n",
                  rawMQ, temp, hum, (int)estado, fallasDHT);
  }

  // --- Sensor de gas cada 1 s ---
  if (t - tMuestreo >= MUESTREO_MS) {
    tMuestreo = t;
    rawMQ = leerMQ();
    if (rawMQ == 0) fallasADC++; else fallasADC = 0;     // lectura 0 sostenida = sensor desconectado

    // Confirmación: el nivel solo cambia si el nuevo valor se repite CONFIRMAR veces seguidas
    int obj = objetivo(rawMQ, nivel);
    if (obj != nivel) {
      if (obj == candidato) conf++;                      // mismo candidato: suma una confirmación
      else { candidato = obj; conf = 1; }                // candidato distinto: empieza de nuevo
      if (conf >= CONFIRMAR) { nivel = obj; conf = 0; }  // confirmado: cambia el nivel
    } else {
      conf = 0;                                          // se mantiene el nivel: no hay cambio pendiente
    }
    if (nivel == 0) silencioHasta = 0;   // si el gas volvió a normal, se cancela el silencio
  }

  // --- Estado final ---
  // Prioridad: calentamiento > alarma > alerta > falla de sensor > normal.
  // Una alerta o alarma de gas siempre tiene prioridad sobre una falla.
  if (t < WARMUP_MS) estado = WARMUP;
  else if (nivel == 2) estado = ALARMA;
  else if (nivel == 1) estado = ALERTA;
  else if (fallasADC >= 5 || fallasDHT >= 3) estado = FALLA;
  else estado = NORMAL;

  actualizarSalidas();
}
