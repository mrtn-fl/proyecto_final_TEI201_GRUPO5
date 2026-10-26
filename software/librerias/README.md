# Librerías

## Librerías Estándar (Arduino IDE)

El código solo incluye una librería directamente (`#include <DHT.h>`):

1. **DHT sensor library** (Adafruit) – v[ x ]
   - Propósito: leer temperatura y humedad del DHT11 (`dht.readTemperature()`, `dht.readHumidity()`).
   - Instalación: `Herramientas > Administrar bibliotecas` y buscar "DHT sensor library".

2. **Adafruit Unified Sensor** – v[ x ]
   - Propósito: dependencia que requiere la librería DHT.
   - Instalación: buscar "Adafruit Unified Sensor" (el IDE suele ofrecer instalarla junto con DHT).


---

## Soporte de placa

- **esp32 by Espressif Systems** – v[x] (Gestor de tarjetas). Aporta `analogRead`, `analogSetPinAttenuation`, `tone`/`noTone` y `Serial.printf`.
- Placa a seleccionar: **ESP32S3 Dev Module** (o equivalente para el Super Mini).

---

## Librerías Personalizadas/Modificadas

El proyecto **no usa librerías personalizadas ni modificadas**; esta carpeta no necesita código adicional.

---

## Dependencias Completas

| Librería | Versión | Fuente | Obligatoria |
|----------|---------|--------|-------------|
| esp32 (Espressif) | [x] | Gestor de tarjetas de Arduino IDE | Si |
| DHT sensor library | [x] | Arduino Library Manager (Adafruit) | Si |
| Adafruit Unified Sensor | [x] | Arduino Library Manager (Adafruit) | Si |
| WiFi / Bluetooth | — | No por ahora

Declarar también las librerías en [`FUENTES.md`](../../FUENTES.md), en la raíz del repositorio.
