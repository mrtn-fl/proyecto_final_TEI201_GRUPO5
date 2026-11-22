# Librerías

## Firmware (Arduino IDE)

| Librería | Versión | Fuente | Uso en el código |
|---|---|---|---|
| esp32 by Espressif Systems (núcleo) | 3.3.12 | Gestor de tarjetas | Placa, ADC, `tone` |
| DHT sensor library (Adafruit) | 1.4.7 | Gestor de bibliotecas | `#include <DHT.h>` – lectura DHT11 |
| Adafruit Unified Sensor | 1.1.15 | Gestor de bibliotecas | Dependencia de DHT |
| WiFi | incluida en el núcleo esp32 | — | `#include <WiFi.h>` – conexión |
| WiFiClientSecure | incluida en el núcleo esp32 | — | HTTPS a Telegram y Railway |
| HTTPClient | incluida en el núcleo esp32 | — | Peticiones POST |
| LittleFS | incluida en el núcleo esp32 | — | Respaldo `/datos.csv` en flash |


**Instalación:** `Herramientas > Administrar bibliotecas`, buscar "DHT sensor library" e instalar con sus dependencias.

## Servidor (Node.js)

Definidas en [`../servidor/package.json`](../servidor/package.json) y se instalan con `npm install`:

| Paquete | Versión | Uso |
|---|---|---|
| express | ^4.21.0 | Servidor HTTP y rutas de la API |
| pg | ^8.13.0 | Conexión a PostgreSQL (Aiven) |

## Librerías personalizadas

No se usan librerías personalizadas ni modificadas.

Todas están declaradas en [`FUENTES.md`](../../FUENTES.md).
   