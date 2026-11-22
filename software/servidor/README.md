# Servidor y base de datos – COStop

API en Node.js (desplegada en **Railway**) que recibe las lecturas del ESP32 y las guarda en **PostgreSQL (Aiven)**.

## Servidor desplegado

**URL base:** https://proyectofinaltei201grupo5-production.up.railway.app

| Ruta | Enlace |
|---|---|
| Estado del servidor | [/salud](https://proyectofinaltei201grupo5-production.up.railway.app/salud) |
| Últimas lecturas | [/api/lecturas](https://proyectofinaltei201grupo5-production.up.railway.app/api/lecturas) |
| Resumen 24 h | [/api/resumen](https://proyectofinaltei201grupo5-production.up.railway.app/api/resumen) |
| Exportar CSV | [/api/lecturas.csv](https://proyectofinaltei201grupo5-production.up.railway.app/api/lecturas.csv) |

La escritura (POST) requiere API key, que no se publica en el repositorio.
## Archivos

| Archivo | Descripción |
|---|---|
| `server.js` | API (Express) |
| `schema.sql` | Tabla `lecturas` (se crea sola al iniciar el servidor) |
| `package.json` | Dependencias |
| `.env.example` | Variables de entorno necesarias |

## Modelo de datos

| Columna | Tipo | Descripción |
|---|---|---|
| `id` | BIGSERIAL | Identificador |
| `dispositivo` | VARCHAR(50) | Ej. `costop-1` |
| `sensor` | VARCHAR(20) | `co`, `temperatura` o `humedad` |
| `valor` | DOUBLE PRECISION | Lectura (CO en valor ADC 0–4095, T en °C, H en %) |
| `creado_en` | TIMESTAMPTZ | Hora en que llegó al servidor |

## Endpoints

| Método | Ruta | Descripción |
|---|---|---|
| POST | `/api/lecturas` | Guarda una lectura. Header `x-api-key`. Body: `{"dispositivo":"costop-1","sensor":"co","valor":812}` |
| GET | `/api/lecturas` | Últimas lecturas. Filtros: `?dispositivo=&sensor=&limite=` (máx. 5000) |
| GET | `/api/lecturas.csv` | Igual que el anterior, en CSV |
| GET | `/api/resumen` | Por sensor: último valor, promedio y máximo de 24 h |
| GET | `/salud` | `{"ok":true}` si la base responde |

Respuestas: `201` guardado, `400` datos inválidos, `401` API key incorrecta, `500` error de base de datos.

## Puesta en marcha

### 1. Base de datos en Aiven
1. Crear un servicio **PostgreSQL** (plan gratuito).
2. Copiar la **Service URI** (`postgres://avnadmin:...@...aivencloud.com:PUERTO/defaultdb?sslmode=require`).

### 2. API en Railway
1. Crear un proyecto desde este repositorio y en *Settings > Root Directory* poner `software/servidor`.
2. En *Variables* agregar:
   - `DATABASE_URL` = Service URI de Aiven
   - `API_KEY` = una clave larga inventada por ustedes
3. Railway ejecuta `npm install` y `npm start`. En *Settings > Networking* generar el dominio público.
4. Probar `https://TU-APP.up.railway.app/salud`.

### 3. ESP32
En `software/src/costop/secrets.h`:
```cpp
const char* SERVER_URL = "https://TU-APP.up.railway.app/api/lecturas";
const char* API_KEY    = "la misma API_KEY de Railway";
```

### Prueba local (opcional)
```bash
cd software/servidor
npm install
DATABASE_URL="postgres://..." API_KEY="prueba" npm start
curl -X POST localhost:3000/api/lecturas -H "Content-Type: application/json" \
     -H "x-api-key: prueba" -d '{"dispositivo":"costop-1","sensor":"co","valor":812}'
```

## Seguridad

- Nunca subir `.env` ni la Service URI (contiene la clave de la base de datos).
- Solo la escritura exige API key; la lectura (GET) es pública para poder mostrar los datos. Si no quieren que sea pública, avisar.
- La conexión a Aiven usa SSL sin verificar el certificado CA (simplifica el despliegue).

## Verificación

El servidor se probó localmente contra PostgreSQL: inserción (201), API key incorrecta (401), sensor inválido (400), consulta, resumen 24 h y exportación CSV respondieron correctamente.
