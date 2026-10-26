# Software – Documentacion

Esta carpeta contiene el firmware y la documentación técnica de **COStop**, la alarma doméstica de monóxido de carbono (CO) de bajo costo para hogares del sur de Chile con calefacción a combustión.

El firmware corre en un **ESP32-S3 Super Mini**, lee un sensor de gas MQ y un sensor DHT22 (temperatura/humedad), y comunica el estado del ambiente con un LED RGB y un buzzer.

## Contenido

| Carpeta | Descripción |
| `src/` | Código fuente del firmware (`src/codigo_esp32/codigo_esp32.ino`) |
| `librerias/` | Dependencias del proyecto y guía de instalación |
| `docs/` | Diagramas de flujo, documentación de funciones, manuales y troubleshooting |

---

## Stack Tecnológico

- **Plataforma:** ESP32-S3 Super Mini (Espressif)
- **Lenguaje:** C/C++ (Arduino framework)
- **IDE:** Arduino IDE 2.x
- **Librerías principales:**
  - DHT sensor library (Adafruit) – v[x]
  - Adafruit Unified Sensor – v[x]
  - Soporte de placas ESP32 (Espressif) – v[x]

El detalle completo está en [`librerias/README.md`](librerias/README.md).

---

## Instalación y Configuración

### 1. Instalar Arduino IDE
Descargar Arduino IDE 2.x desde https://www.arduino.cc/en/software e instalarlo.

### 2. Instalar el soporte para ESP32
1. Abrir `Archivo > Preferencias`.
2. En *Gestor de URLs adicionales de tarjetas* agregar:
   `https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json`
3. Ir a `Herramientas > Placa > Gestor de tarjetas`, buscar **esp32** (Espressif Systems) e instalar.

### 3. Instalar las librerías
`Herramientas > Administrar bibliotecas` e instalar **DHT sensor library** y **Adafruit Unified Sensor** (ver `librerias/README.md`).

### 4. Cargar el código
1. Abrir `src/codigo_esp32/codigo_esp32.ino`.
2. Seleccionar la placa **ESP32S3 Dev Module** (o la equivalente para el Super Mini) y el puerto COM correspondiente.
3. Compilar y subir.
4. Abrir el Monitor Serie a **115200 baudios** para ver las lecturas.

> Conexiones eléctricas en `hardware/README.md`.

---

## Configuración de Parámetros

Los parámetros ajustables están al inicio del código:

```cpp
// Pines (ESP32-S3 Super Mini)
const int PIN_DHT    = 4;   // Datos del DHT22
const int PIN_MQ     = 1;   // Entrada analógica del sensor MQ
const int PIN_BUZZER = 5;   // Buzzer
const int PIN_R      = 6;   // LED RGB - rojo
const int PIN_G      = 8;   // LED RGB - verde
const int PIN_B      = 9;   // LED RGB - azul
const int PIN_BTN    = 0;   // Botón de silencio (BOOT, provisorio; con pulsador real: 7)

// Umbrales y tiempos
const int T_ALERTA = 1500;                 // umbral de alerta (ADC 0-4095)
const int T_ALARMA = 2500;                 // umbral de alarma
const int HIST = 200;                      // histéresis
const int CONFIRMAR = 3;                   // lecturas seguidas para cambiar de nivel
const unsigned long WARMUP_MS = 20000;     // calentamiento (prototipo; equipo real: minutos)
const unsigned long SILENCIO_MS = 30000;   // silencio (prototipo; equipo real: 300000 = 5 min)
```

---

## Arquitectura del Software

El firmware funciona como una **máquina de estados** que se ejecuta de forma continua. Prioridad de evaluación: calentamiento → alarma → alerta → falla → normal.

```
Encendido → CALENTAMIENTO → NORMAL ⇄ ALERTA ⇄ ALARMA
                              │
                              └──→ FALLA DE SENSOR (solo si no hay alerta ni alarma de gas)
```

### Módulos principales
1. **Inicialización (`setup`)** – Configura pines, serial (115200), ADC del sensor MQ y DHT22; el calentamiento corre durante los primeros `WARMUP_MS`.
2. **Lectura de sensores** – MQ cada 1 s (promedio de 4 lecturas) y DHT22 cada 2 s.
3. **Procesamiento** – Compara con los umbrales usando **histéresis** y **confirmación de 3 lecturas consecutivas** para evitar falsas alarmas.
4. **Actuación** – Controla el LED RGB y el buzzer según el estado.


### Estados del sistema

| Estado | LED RGB | Buzzer |
| Calentamiento (warm-up) | Azul intermitente | Apagado |
| Normal | Verde (destello breve cada 3 s) | Apagado |
| Alerta | Amarillo intermitente | Pitidos cortos |
| Alarma | Rojo fijo | Continuo |
| Falla de sensor | Magenta intermitente | Doble pitido |

> Diagrama de flujo y documentación de funciones: ver `docs/`.

---

## Comunicación

El prototipo actual **no usa WiFi ni Bluetooth**: funciona de forma autónoma y local, de modo que no depende de conexión a internet. Esto es intencional, ya que los hogares objetivo (zonas rurales del sur de Chile) pueden no tener conectividad estable. Por eso no se incluye API/endpoints.

