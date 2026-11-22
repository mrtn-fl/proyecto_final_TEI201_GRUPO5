// =====================================================================
//  CoStop - Detector de CO con alerta por Telegram + base de datos en la nube
//  ESP32 -> Telegram (alertas a un tercero)
//  ESP32 -> Railway (API) -> Aiven PostgreSQL (registro de datos)
//  Respaldo local en LittleFS (por si no hay WiFi)
// =====================================================================
#include <LittleFS.h>
#include <DHT.h>
#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <HTTPClient.h>
#include "secrets.h"   // WIFI_SSID, WIFI_PASS, TG_TOKEN, TG_CHAT, SERVER_URL, API_KEY (no se sube a GitHub)

// ---------- PINES (ajusta a tu cableado) ----------
#define PIN_MQ7     1     // salida analógica AO del MQ-7 (usa GPIO 1-10 = ADC1, funciona con WiFi)
#define PIN_DHT     4
#define PIN_R       8     // LED KY-016
#define PIN_G       9
#define PIN_B       10
#define PIN_BUZZER  5
#define PIN_BTN     7

// ---------- UMBRALES MQ-7 (CALIBRAR) ----------
// Lectura cruda del ADC: 0 a 4095 (12 bits, 0 a 3,3 V).
// Cómo calibrar:
//   1) Encender en aire limpio, esperar a que la lectura se estabilice
//      (mínimo 10 minutos de precalentamiento) y anotar el valor -> MQ7_BASE.
//   2) Acercar una fuente de CO controlada (con supervisión, en un lugar ventilado) y anotar cómo sube.
//   3) Ajustar ALERTA y PELIGRO por sobre la base.
// Referencia de alarmas comerciales (norma UL 2034):
//   70 ppm por 1-4 h, 150 ppm por 10-50 min, 400 ppm por 4-15 min.
#define MQ7_BASE         800    // lectura en aire limpio (medir y reemplazar)
#define UMBRAL_ALERTA    2000   // LED amarillo
#define UMBRAL_PELIGRO   3000   // LED rojo + buzzer + Telegram
#define HISTERESIS       150    // margen para que la alarma no parpadee justo en el umbral
#define TIEMPO_CALENTAMIENTO  20000UL // Tiempo de calentamiento

// ---------- TIEMPOS ----------
#define INTERVALO_LECTURA  2000UL    // lee sensores cada 2 s
#define INTERVALO_LOG      10000UL   // guarda/envía cada 10 s (para probar; usar 60000 en uso real)
#define REINTENTO_WIFI     15000UL   // si se cae el WiFi, reintenta cada 15 s
#define USAR_WIFI          true

#define SILENCIO_MS        300000UL  // el botón silencia el buzzer 5 min (la alarma y el LED siguen)

// ---------- CREDENCIALES ----------
// WiFi, Telegram y nube están en secrets.h (copiar secrets_example.h -> secrets.h y completar).
const char* DISPOSITIVO = "costop-1";

// =====================================================================
DHT dht(PIN_DHT, DHT11);
unsigned long ultimoLog = 0, ultimaLectura = 0, ultimoIntentoWiFi = 0;
int coRaw = 0;
float temp = NAN, hum = NAN;
int nivel = 0;               // 0 = normal, 1 = alerta, 2 = peligro
bool alertaEnviada = false;
unsigned long inicioCalentamiento = 0;
bool calentando = true;
bool silenciado = false;
unsigned long inicioSilencio = 0;
bool btnAnterior = HIGH;
unsigned long ultimoCambioBtn = 0;

void setColor(bool r, bool g, bool b) {
  digitalWrite(PIN_R, r); digitalWrite(PIN_G, g); digitalWrite(PIN_B, b);
}

bool hayWiFi() {
  return USAR_WIFI && WiFi.status() == WL_CONNECTED;
}

// ---------- WiFi: reconexión sin bloquear ----------
void revisarWiFi() {
  if (!USAR_WIFI || WiFi.status() == WL_CONNECTED) return;
  if (millis() - ultimoIntentoWiFi < REINTENTO_WIFI) return;
  ultimoIntentoWiFi = millis();
  Serial.println("[wifi] reconectando...");
  WiFi.disconnect();
  WiFi.begin(WIFI_SSID, WIFI_PASS);
}

// ---------- Telegram: mensaje al tercero ----------
void enviarTelegram(const String& msg) {
  if (!hayWiFi()) return;
  WiFiClientSecure cliente; cliente.setInsecure();
  HTTPClient http;
  http.begin(cliente, String("https://api.telegram.org/bot") + TG_TOKEN + "/sendMessage");
  http.addHeader("Content-Type", "application/json");
  String body = String("{\"chat_id\":\"") + TG_CHAT + "\",\"text\":\"" + msg + "\"}";
  Serial.printf("[telegram] codigo %d\n", http.POST(body));
  http.end();
}

// ---------- Nube: una fila por sensor ----------
void enviarNube(const char* sensor, float valor) {
  if (!hayWiFi() || isnan(valor)) return;   // NaN no viaja (el servidor respondería 400)
  WiFiClientSecure cliente; cliente.setInsecure();
  HTTPClient http;
  http.begin(cliente, SERVER_URL);
  http.addHeader("Content-Type", "application/json");
  http.addHeader("x-api-key", API_KEY);
  char body[120];
  snprintf(body, sizeof(body),
           "{\"dispositivo\":\"%s\",\"sensor\":\"%s\",\"valor\":%.2f}",
           DISPOSITIVO, sensor, valor);
  Serial.printf("[nube] %s -> %d\n", sensor, http.POST(body));
  http.end();
}

// ---------- Respaldo local ----------
void guardarFlash() {
  File f = LittleFS.open("/datos.csv", "a");
  if (f) {
    f.printf("%lu,%d,%.1f,%.1f\n", millis() / 1000, coRaw, temp, hum);
    f.close();
    Serial.printf("[guardado] seg=%lu\n", millis() / 1000);
  } else Serial.println("[ERROR] no se pudo escribir");
}

void descargar() {
  File f = LittleFS.open("/datos.csv", "r");
  Serial.println("===== INICIO DATOS =====");
  Serial.println("seg,co_raw,temp,hum");
  while (f && f.available()) Serial.write(f.read());
  if (f) f.close();
  Serial.println("===== FIN DATOS =====");
}

void info() {
  File f = LittleFS.open("/datos.csv", "r");
  if (!f) { Serial.println("[info] archivo vacio o inexistente"); return; }
  int lineas = 0;
  while (f.available()) if (f.read() == '\n') lineas++;
  Serial.printf("[info] %d registros, %d bytes\n", lineas, f.size());
  f.close();
}

// ---------- Alarma con histéresis ----------
void evaluarAlarma() {
  int nuevo = nivel;
  if (coRaw >= UMBRAL_PELIGRO)                       nuevo = 2;
  else if (coRaw >= UMBRAL_ALERTA)                   nuevo = (nivel == 2 && coRaw > UMBRAL_PELIGRO - HISTERESIS) ? 2 : 1;
  else if (coRaw < UMBRAL_ALERTA - HISTERESIS)       nuevo = 0;
  else if (nivel == 2)                               nuevo = 1;   // banda de histéresis: de peligro baja a alerta

  nivel = nuevo;
  if (nivel == 2) {
    setColor(1, 0, 0);
    if (silenciado && millis() - inicioSilencio < SILENCIO_MS) noTone(PIN_BUZZER);
    else { silenciado = false; tone(PIN_BUZZER, 2000); }
    if (!alertaEnviada) {
      enviarTelegram("ALERTA CoStop: CO peligroso (lectura " + String(coRaw) + "). Ventile y salga del lugar.");
      alertaEnviada = true;
    }
  } else if (nivel == 1) {
    silenciado = false;
    setColor(1, 1, 0); noTone(PIN_BUZZER);
  } else {
    silenciado = false;
    setColor(0, 1, 0); noTone(PIN_BUZZER);
    if (alertaEnviada) {
      enviarTelegram("CoStop: niveles de CO normales otra vez (lectura " + String(coRaw) + ").");
      alertaEnviada = false;
    }
  }
}

// ---------- Botón de silencio (antirrebote 50 ms) ----------
// Solo apaga el buzzer en PELIGRO; el LED rojo sigue y el Telegram ya se envió.
void revisarBoton() {
  bool lectura = digitalRead(PIN_BTN);
  if (lectura != btnAnterior && millis() - ultimoCambioBtn > 50) {
    ultimoCambioBtn = millis();
    btnAnterior = lectura;
    if (lectura == LOW && nivel == 2) {
      silenciado = true;
      inicioSilencio = millis();
      noTone(PIN_BUZZER);
      Serial.println("[boton] buzzer silenciado");
    }
  }
}

void actualizarCalentamiento() {
  if (!calentando) return;
  if (millis() - inicioCalentamiento < TIEMPO_CALENTAMIENTO) {
    setColor(0, 0, (millis() / 500) % 2);
    noTone(PIN_BUZZER);
  } else {
    calentando = false;
    setColor(0, 1, 0);
    Serial.println("[ok] calentamiento listo");
    enviarTelegram("CoStop listo, vigilando CO");
  }
}

void setup() {
  Serial.begin(115200);
  delay(1500);
  pinMode(PIN_R, OUTPUT); pinMode(PIN_G, OUTPUT); pinMode(PIN_B, OUTPUT);
  pinMode(PIN_BUZZER, OUTPUT);
  pinMode(PIN_BTN, INPUT_PULLUP);   // botón a GND: presionado = LOW
  dht.begin();

  if (LittleFS.begin(true)) Serial.println("[ok] LittleFS montado");
  else                      Serial.println("[ERROR] LittleFS no monto");

  if (USAR_WIFI) {
    WiFi.mode(WIFI_STA);

    // --- DIAGNÓSTICO: qué redes ve la placa ---
    int n = WiFi.scanNetworks();
    Serial.printf("[scan] %d redes encontradas:\n", n);
    for (int i = 0; i < n; i++) {
      Serial.printf("   '%s'  señal %d\n", WiFi.SSID(i).c_str(), WiFi.RSSI(i));
    }

    // --- Conexión ---
    WiFi.begin(WIFI_SSID, WIFI_PASS);
    WiFi.setTxPower(WIFI_POWER_8_5dBm);
    unsigned long t0 = millis();
    while (WiFi.status() != WL_CONNECTED && millis() - t0 < 20000) delay(500);
    Serial.printf("[wifi] estado = %d\n", WiFi.status());
    Serial.println(hayWiFi() ? "[ok] WiFi" : "[aviso] sin WiFi");
  }

  Serial.println("CoStop listo. Comandos: d=descargar  i=info  b=borrar");
  enviarTelegram("CoStop encendido");
  inicioCalentamiento = millis();
}

void loop() {
  revisarWiFi();
  actualizarCalentamiento();
  revisarBoton();
  // --- Lectura de sensores ---
  if (millis() - ultimaLectura >= INTERVALO_LECTURA) {
    ultimaLectura = millis();
    coRaw = analogRead(PIN_MQ7);
    float t = dht.readTemperature(), h = dht.readHumidity();
    if (!isnan(t)) temp = t;
    if (!isnan(h)) hum = h;
    Serial.printf("[lectura] CO=%d  T=%.1f  H=%.1f  nivel=%d\n", coRaw, temp, hum, nivel);
    if (!calentando) evaluarAlarma();
  }

  // --- Registro: flash (respaldo) + nube ---
  if (!calentando && millis() - ultimoLog >= INTERVALO_LOG) {
    ultimoLog = millis();
    guardarFlash();
    enviarNube("co", coRaw);
    enviarNube("temperatura", temp);
    enviarNube("humedad", hum);
  }

  // --- Comandos por Monitor Serie ---
  if (Serial.available()) {
    char c = Serial.read();
    if (c == 'd') descargar();
    if (c == 'i') info();
    if (c == 'b') { LittleFS.remove("/datos.csv"); Serial.println("[ok] datos borrados"); }
  }
}
