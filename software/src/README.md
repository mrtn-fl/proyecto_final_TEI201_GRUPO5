# Código Fuente

## `costop/costop.ino`

Firmware v3 del ESP32-S3 Super Mini. Arduino IDE exige que el `.ino` esté en una carpeta con el mismo nombre, por eso la ruta es `costop/costop.ino`.

## `costop/secrets_example.h`

Plantilla de credenciales. Copiarla como `secrets.h` en la misma carpeta y completar. `secrets.h` **no se sube a GitHub** (está en `.gitignore`).

---

## Funciones

| Función | Qué hace |
|---|---|
| `setColor(r, g, b)` | Enciende los canales del LED RGB |
| `hayWiFi()` | `true` si el WiFi está habilitado y conectado |
| `revisarWiFi()` | Reconecta cada `REINTENTO_WIFI` sin bloquear el `loop()` |
| `enviarTelegram(msg)` | Envía un mensaje al `TG_CHAT` por la Bot API (HTTPS) |
| `enviarNube(sensor, valor)` | POST JSON a la API (`x-api-key`); no envía valores `NaN` |
| `guardarFlash()` | Agrega una línea a `/datos.csv` en LittleFS |
| `descargar()` / `info()` | Imprimen el CSV o el número de registros por Serial |
| `evaluarAlarma()` | Calcula el nivel con histéresis y actualiza LED, buzzer y Telegram |
| `revisarBoton()` | Antirrebote de 50 ms; silencia el buzzer en peligro |
| `actualizarCalentamiento()` | LED azul intermitente hasta `TIEMPO_CALENTAMIENTO` |

Detalle en [`../docs/README.md`](../docs/README.md).

## Estándares de código

- Constantes en `#define` y `UPPER_SNAKE_CASE`; variables y funciones en `camelCase`.
- Comentarios en español.
- Mensajes de Serial con prefijo: `[ok]`, `[ERROR]`, `[aviso]`, `[wifi]`, `[telegram]`, `[nube]`, `[lectura]`, `[guardado]`, `[boton]`.
- Sin `delay()` en el `loop()`: todo se temporiza con `millis()` para que la alarma nunca se bloquee.

## Debugging

Monitor Serie a 115200. Cada 2 s:

```
[lectura] CO=<0-4095>  T=<°C>  H=<%>  nivel=<0|1|2>
```

Al iniciar imprime las redes WiFi visibles (`[scan]`) para diagnosticar la conexión.
