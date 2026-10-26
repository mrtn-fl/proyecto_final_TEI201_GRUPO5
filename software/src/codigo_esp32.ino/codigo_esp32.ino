#include <DHT.h>

// ---------- Pines (ESP32-S3 Super Mini) ----------
const int PIN_DHT    = 4;
const int PIN_MQ     = 1;
const int PIN_BUZZER = 5;
const int PIN_R      = 6;
const int PIN_G      = 8;
const int PIN_B      = 9;
const int PIN_BTN    = 0;   // botón BOOT (provisorio). Con pulsador real: 7

// ---------- Opciones de hardware ----------
const bool BUZZER_ACTIVO   = true;   // true: activo (suena con HIGH). false: pasivo (usa tone)
const bool LED_ANODO_COMUN = false;  // KY-016 normal: false

// ---------- Parámetros (ajustables) ----------
const int  T_ALERTA   = 1500;      // umbral alerta (valor ADC 0-4095)
const int  T_ALARMA   = 2500;      // umbral alarma
const int  HIST       = 200;       // histéresis
const int  CONFIRMAR  = 3;         // lecturas seguidas para cambiar de nivel
const unsigned long WARMUP_MS   = 20000;   // equipo real: minutos
const unsigned long SILENCIO_MS = 30000;   // equipo real: 300000 (5 min)
const unsigned long MUESTREO_MS = 1000;
const unsigned long DHT_MS      = 2000;

DHT dht(PIN_DHT, DHT22);

enum Estado { WARMUP, NORMAL, ALERTA, ALARMA, FALLA };
Estado estado = WARMUP;

int  nivel = 0, candidato = 0, conf = 0;
int  rawMQ = 0, fallasADC = 0, fallasDHT = 0;
float temp = NAN, hum = NAN;
unsigned long tMuestreo = 0, tDHT = 0, silencioHasta = 0;
bool buzzerSonando = false;

// ---------- Salidas ----------
void setColor(bool r, bool g, bool b) {
  if (LED_ANODO_COMUN) { r = !r; g = !g; b = !b; }
  digitalWrite(PIN_R, r);
  digitalWrite(PIN_G, g);
  digitalWrite(PIN_B, b);
}

void buzzerOn()  { if (BUZZER_ACTIVO) digitalWrite(PIN_BUZZER, HIGH); else tone(PIN_BUZZER, 2000); }
void buzzerOff() { if (BUZZER_ACTIVO) digitalWrite(PIN_BUZZER, LOW);  else noTone(PIN_BUZZER); }

// ---------- Lectura del sensor de gas (promedio de 4) ----------
int leerMQ() {
  long suma = 0;
  for (int i = 0; i < 4; i++) suma += analogRead(PIN_MQ);
  return suma / 4;
}

// ---------- Nivel objetivo con histéresis ----------
int objetivo(int raw, int actual) {
  if (raw >= T_ALARMA) return 2;
  if (actual == 2 && raw >= T_ALARMA - HIST) return 2;
  if (raw >= T_ALERTA) return 1;
  if (actual >= 1 && raw >= T_ALERTA - HIST) return 1;
  return 0;
}

// ---------- Botón: silencia, no desactiva ----------
void revisarBoton() {
  static bool ultimo = HIGH;
  static unsigned long tCambio = 0;
  bool lectura = digitalRead(PIN_BTN);
  if (lectura != ultimo && millis() - tCambio > 50) {
    tCambio = millis();
    ultimo = lectura;
    if (lectura == LOW && (estado == ALERTA || estado == ALARMA || estado == FALLA)) {
      silencioHasta = millis() + SILENCIO_MS;
      Serial.println(">> Alarma silenciada");
    }
  }
}

// ---------- Salidas según estado ----------
void actualizarSalidas() {
  unsigned long t = millis();
  bool led = false, buz = false;

  switch (estado) {
    case WARMUP: led = (t % 400) < 200; break;
    case NORMAL: led = (t % 3000) < 80; break;            // latido
    case ALERTA: { unsigned long p = t % 1000; led = buz = (p < 200); } break;
    case ALARMA: led = buz = true; break;
    case FALLA:  { unsigned long p = t % 2000;
                   led = buz = (p < 150) || (p >= 300 && p < 450); } break;
  }

  bool silenciado = (long)(silencioHasta - t) > 0;
  if (silenciado) buz = false;

  if (!led) setColor(0, 0, 0);
  else switch (estado) {
    case WARMUP: setColor(0, 0, 1); break;   // azul
    case NORMAL: setColor(0, 1, 0); break;   // verde
    case ALERTA: setColor(1, 1, 0); break;   // amarillo
    case ALARMA: setColor(1, 0, 0); break;   // rojo
    case FALLA:  setColor(1, 0, 1); break;   // magenta
  }

  if (buz && !buzzerSonando)      { buzzerOn();  buzzerSonando = true; }
  else if (!buz && buzzerSonando) { buzzerOff(); buzzerSonando = false; }
}

void setup() {
  Serial.begin(115200);
  pinMode(PIN_R, OUTPUT);
  pinMode(PIN_G, OUTPUT);
  pinMode(PIN_B, OUTPUT);
  pinMode(PIN_BUZZER, OUTPUT);
  pinMode(PIN_BTN, INPUT_PULLUP);
  setColor(0, 0, 0);
  buzzerOff();
  analogSetPinAttenuation(PIN_MQ, ADC_11db);
  dht.begin();
  Serial.println("Calentando...");
}

void loop() {
  unsigned long t = millis();
  revisarBoton();

  // --- DHT22 cada 2 s ---
  if (t - tDHT >= DHT_MS) {
    tDHT = t;
    float h = dht.readHumidity();
    float c = dht.readTemperature();
    if (isnan(h) || isnan(c)) fallasDHT++;
    else { fallasDHT = 0; hum = h; temp = c; }
    Serial.printf("MQ=%d | T=%.1f C | H=%.1f %% | estado=%d | DHT_fallas=%d\n",
                  rawMQ, temp, hum, (int)estado, fallasDHT);
  }

  // --- Sensor de gas cada 1 s ---
  if (t - tMuestreo >= MUESTREO_MS) {
    tMuestreo = t;
    rawMQ = leerMQ();
    if (rawMQ == 0) fallasADC++; else fallasADC = 0;

    int obj = objetivo(rawMQ, nivel);
    if (obj != nivel) {
      if (obj == candidato) conf++;
      else { candidato = obj; conf = 1; }
      if (conf >= CONFIRMAR) { nivel = obj; conf = 0; }
    } else {
      conf = 0;
    }
    if (nivel == 0) silencioHasta = 0;
  }

  // --- Estado final ---
  if (t < WARMUP_MS) estado = WARMUP;
  else if (nivel == 2) estado = ALARMA;
  else if (nivel == 1) estado = ALERTA;
  else if (fallasADC >= 5 || fallasDHT >= 3) estado = FALLA;
  else estado = NORMAL;

  actualizarSalidas();
}