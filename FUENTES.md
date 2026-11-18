# Fuentes

Origen de todo lo que no fue escrito o diseñado íntegramente por el equipo, y referencias técnicas que respaldan las decisiones del proyecto **COStop**.

## Código y proyecto de origen

| Elemento | Origen | Uso |
| Firmware `software/src/costop/costop.ino` | Escrito por el equipo (Grupo 5) | Código del prototipo |
| Servidor `software/servidor/` | Escrito por el equipo (Grupo 5) | API y base de datos |
| Estructura de carpetas y esqueleto de los README | Plantilla [sebasdv/proyecto_final_TEI201](https://github.com/sebasdv/proyecto_final_TEI201) | Organización del repositorio |
| Referencia de formato | [ferjomendez/Repo-Ejemplo-TEI201](https://github.com/ferjomendez/Repo-Ejemplo-TEI201) | Guía de qué documentar |
| Apoyo de IA | Claude | Se uso como apoyo para completar archivos segun nuestra informacion, ademas se utilizo su apoyo para el codigo |

## Librerías de software

| Librería | Dónde se usa | Licencia | Sitio |
| DHT sensor library (Adafruit) | Lectura del DHT11 (`#include <DHT.h>`) | MIT | https://github.com/adafruit/DHT-sensor-library |
| Adafruit Unified Sensor | Dependencia de la librería DHT | Apache-2.0 | https://github.com/adafruit/Adafruit_Sensor |
| Arduino core para ESP32 (Espressif), incluye WiFi, WiFiClientSecure, HTTPClient y LittleFS | ADC, `tone`, conexión WiFi, HTTPS y respaldo en flash | LGPL-2.1 | https://github.com/espressif/arduino-esp32 |
| Express | Servidor de la API | MIT | https://expressjs.com |
| node-postgres (`pg`) | Conexión a PostgreSQL | MIT | https://node-postgres.com |

## Servicios externos

| Servicio | Uso | Sitio |
| Telegram Bot API | Envío de alertas a un tercero | https://core.telegram.org/bots/api |
| Railway | Hosting de la API | https://railway.com |
| Aiven for PostgreSQL | Base de datos en la nube | https://aiven.io/postgresql |

Versiones exactas en [software/librerias/README.md](software/librerias/README.md).


## Datos y contexto del problema

- Diario Usach (2024, 24 de junio). *Advierte aumento de intoxicaciones por monóxido de carbono al interior de las casas.* https://www.diariousach.cl
- Cuerpo de Bomberos de Punta Arenas (2019, 6 de mayo). *Intoxicación por monóxido de carbono.* https://www.bomberospuntaarenas.cl/2019/05/06/intoxicacion-por-monoxido-de-carbono/
- Ministerio de Energía (2026). Registro de certificación de estufas a kerosene.
- Precios del BOM: ver tabla de referencias en [hardware/bom/README.md](hardware/bom/README.md).

## Herramientas

Arduino IDE 2.x (firmware), Autodesk Fusion 360 (modelo 3D, planos y renders) 
