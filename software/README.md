# Software – Documentación

Firmware y servidor de **COStop**, alarma doméstica de monóxido de carbono (CO).

El firmware corre en un **ESP32-S3 Super Mini**: lee el sensor **MQ-7** (CO) y el **DHT11** (temperatura/humedad), avisa con LED RGB y buzzer, manda alertas por **Telegram** a un tercero y registra las lecturas en una base de datos **PostgreSQL (Aiven)** a través de una API en **Railway**. Si no hay WiFi, la alarma local sigue funcionando y los datos quedan respaldados en la memoria flash (LittleFS).

## Contenido

| Carpeta | Descripción |
|---|---|
| `src/costop/` | Firmware (`costop.ino`) y plantilla de credenciales (`secrets_example.h`) |
| `servidor/` | API Node.js (Railway) + esquema de la base de datos PostgreSQL (Aiven) |
| `librerias/` | Dependencias y versiones |
| `docs/` | Funciones, flujo de datos, diagramas y troubleshooting |

---

## Arquitectura

```
                 ┌───────────────► Telegram (alerta a un familiar/vecino)
 MQ-7 ─┐         │
 DHT11 ─┼─► ESP32-S3 ──WiFi──► API Railway (Node.js) ──► PostgreSQL Aiven
 Botón ─┘    │   │
             │   └──► LittleFS /datos.csv (respaldo local, sin WiFi)
             └──► LED RGB + buzzer (aviso local, funciona siempre)
```

## Stack tecnológico

- **Firmware:** C/C++ (Arduino framework), Arduino IDE 2.x, núcleo ESP32 de Espressif
- **Librerías firmware:** DHT sensor library, Adafruit Unified Sensor, y del núcleo ESP32: WiFi, WiFiClientSecure, HTTPClient, LittleFS
- **Servidor:** Node.js 18+, Express, pg
- **Base de datos:** PostgreSQL en Aiven
- **Hosting de la API:** Railway
- **Alertas:** Telegram Bot API

Versiones en [`librerias/README.md`](librerias/README.md).

---

## Instalación del firmware

1. Instalar Arduino IDE 2.x y el soporte **esp32 by Espressif** (URL del gestor de tarjetas: `https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json`).
2. Instalar **DHT sensor library** y **Adafruit Unified Sensor** desde el Gestor de bibliotecas.
3. En `src/costop/`, copiar `secrets_example.h` como **`secrets.h`** y completar WiFi, token y chat_id de Telegram, URL del servidor y API key. `secrets.h` está en `.gitignore` y **no se sube**.
4. Abrir `src/costop/costop.ino`, elegir placa **ESP32S3 Dev Module** y el puerto.
5. Compilar y subir. Monitor Serie a **115200 baudios**.

> El WiFi del ESP32 solo funciona en redes de **2,4 GHz**.

## Instalación del servidor y la base de datos

Ver [`servidor/README.md`](servidor/README.md).

---

## Parámetros ajustables (inicio de `costop.ino`)

```cpp
#define PIN_MQ7     1     // AO del MQ-7 (ADC1, compatible con WiFi)
#define PIN_DHT     4
#define PIN_R       8     // LED KY-016
#define PIN_G       9
#define PIN_B       10
#define PIN_BUZZER  5
#define PIN_BTN     7     // pulsador de silencio (a GND)

#define MQ7_BASE         800    // lectura en aire limpio (calibrar)
#define UMBRAL_ALERTA    2000   // LED amarillo
#define UMBRAL_PELIGRO   3000   // LED rojo + buzzer + Telegram
#define HISTERESIS       150
#define TIEMPO_CALENTAMIENTO  20000UL

#define INTERVALO_LECTURA  2000UL   // lectura de sensores
#define INTERVALO_LOG      10000UL  // registro flash + nube (uso real: 60000)
#define REINTENTO_WIFI     15000UL
#define SILENCIO_MS        300000UL // silencio del buzzer (5 min)
#define USAR_WIFI          true     // false = modo solo local
```

---

## Estados del sistema

| Estado | LED RGB | Buzzer | Telegram |
|---|---|---|---|
| Calentamiento | Azul intermitente | Apagado | "CoStop listo" al terminar |
| Normal | Verde fijo | Apagado | "niveles normales otra vez" si venía de peligro |
| Alerta (≥ 2000) | Amarillo fijo | Apagado | — |
| Peligro (≥ 3000) | Rojo fijo | Continuo (silenciable 5 min) | Alerta al tercero (una vez por evento) |

- **Histéresis (150):** baja de peligro a alerta bajo 2850, y a normal bajo 1850, para que no parpadee en el umbral.
- **Botón:** en peligro apaga el buzzer por `SILENCIO_MS`; el LED sigue rojo. Si el nivel baja, el silencio se cancela.
- **Sin WiFi:** LED, buzzer y respaldo en flash siguen funcionando; reintenta conectarse cada 15 s sin bloquear la alarma.

---

## Datos

| Destino | Qué guarda | Cada cuánto |
|---|---|---|
| PostgreSQL (vía API) | Una fila por sensor: `co`, `temperatura`, `humedad` | `INTERVALO_LOG` |
| LittleFS `/datos.csv` | `seg,co_raw,temp,hum` | `INTERVALO_LOG` |

Comandos por Monitor Serie: `d` descarga el CSV, `i` cuenta registros, `b` borra el archivo.

---

## Seguridad

- Las credenciales van en `secrets.h`, fuera del repositorio.
- La API exige el header `x-api-key` para escribir.
- El ESP32 usa HTTPS con `setInsecure()` (no verifica el certificado del servidor): aceptable para el prototipo, mejorable cargando el certificado raíz.

## Limitaciones

- Umbrales en valores crudos del ADC, **no en ppm**; el MQ-7 requiere calibración.
- El DHT11 solo se registra; no influye en la alarma.
- `TIEMPO_CALENTAMIENTO` está reducido para pruebas.
- **No reemplaza un detector de CO certificado.**
