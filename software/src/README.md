# Código Fuente – COStop

## Archivos principales

### `codigo_esp32/codigo_esp32.ino`
Sketch único del firmware para el ESP32-S3 Super Mini. Todo el código (pines, parámetros, lectura de sensores, máquina de estados y control de salidas) está en este archivo.

> Arduino IDE exige que el `.ino` esté dentro de una carpeta con el mismo nombre, por eso la ruta es `codigo_esp32/codigo_esp32.ino`.

**Estructura:**
- `setup()`: inicia el serial (115200), configura pines, apaga LED y buzzer, ajusta la atenuación del ADC del sensor MQ e inicia el DHT22.
- `loop()`: revisa el botón, lee el DHT22 cada 2 s, lee el sensor MQ cada 1 s, calcula el estado y actualiza LED y buzzer.

---

## Funciones del código

| Función | Qué hace |
|---------|----------|
| `setColor(r, g, b)` | Enciende el LED RGB (soporta ánodo o cátodo común) |
| `buzzerOn()` / `buzzerOff()` | Activa o apaga el buzzer (activo con HIGH, o pasivo con `tone`) |
| `leerMQ()` | Promedia 4 lecturas ADC del sensor MQ |
| `objetivo(raw, actual)` | Define el nivel (0 normal, 1 alerta, 2 alarma) aplicando histéresis |
| `revisarBoton()` | Antirrebote (50 ms) y silencio del buzzer |
| `actualizarSalidas()` | Patrones de LED y buzzer según el estado |

Detalle de cada función en [`../docs/README.md`](../docs/README.md).

---

## Comportamiento

| Estado | LED RGB | Buzzer |
|--------|---------|--------|
| Calentamiento (`WARMUP`) | Azul intermitente | Apagado |
| Normal (`NORMAL`) | Verde, destello breve cada 3 s ("latido") | Apagado |
| Alerta (`ALERTA`) | Amarillo intermitente | Pitidos cortos |
| Alarma (`ALARMA`) | Rojo fijo | Continuo |
| Falla de sensor (`FALLA`) | Magenta intermitente | Doble pitido |

- **Histéresis (200):** se sube de nivel al superar el umbral y solo se baja cuando la lectura cae 200 unidades por debajo.
- **Confirmación (3):** hacen falta 3 lecturas seguidas (1 por segundo) en el nuevo nivel para cambiar de estado.
- **Botón de silencio:** apaga el buzzer en ALERTA, ALARMA y FALLA durante `SILENCIO_MS`. No apaga el LED. El silencio se cancela cuando el nivel vuelve a normal.
- **Falla:** se declara con 5 lecturas seguidas del MQ en 0, o 3 lecturas fallidas seguidas del DHT22 (cada 2 s). Una alerta o alarma de gas tiene prioridad sobre la falla.

---

## Parámetros ajustables (inicio del archivo)

```cpp
const int PIN_DHT = 4, PIN_MQ = 1, PIN_BUZZER = 5;
const int PIN_R = 6, PIN_G = 8, PIN_B = 9;
const int PIN_BTN = 0;               // botón BOOT (provisorio); con pulsador real: 7

const int T_ALERTA = 1500;           // umbral alerta (ADC 0-4095)
const int T_ALARMA = 2500;           // umbral alarma
const int HIST = 200;                // histéresis
const int CONFIRMAR = 3;             // lecturas seguidas para cambiar de nivel
const unsigned long WARMUP_MS = 20000;    // prototipo; equipo real: minutos
const unsigned long SILENCIO_MS = 30000;  // prototipo; equipo real: 300000 (5 min)
```

Opciones de hardware: `BUZZER_ACTIVO` (true/false) y `LED_ANODO_COMUN` (false para el KY-016).

---

## Estándares de código

- Variables y funciones: `camelCase`. Constantes: `PIN_*`, `T_*`, `*_MS` en mayúsculas (`UPPER_SNAKE_CASE`).
- Comentarios en español, explicando el porqué.

---

## Debugging

Monitor Serie a **115200 baudios**. Cada 2 s imprime:

```
MQ=<valor> | T=<°C> | H=<%> | estado=<n> | DHT_fallas=<n>
```

Valores de `estado`: 0 = WARMUP, 1 = NORMAL, 2 = ALERTA, 3 = ALARMA, 4 = FALLA. También imprime `Calentando...` al iniciar y `>> Alarma silenciada` al presionar el botón. El código no usa `#define DEBUG` ni prefijos `[INFO]`/`[ERROR]`.

---

## Limitaciones

- Los umbrales están en valores crudos del ADC, **no en ppm**. El sensor MQ requiere calibración y el prototipo **no reemplaza a un detector de CO certificado**.
- El DHT22 solo se usa para mostrar temperatura/humedad y detectar su propia falla; no influye en la alarma de gas.
- `WARMUP_MS` y `SILENCIO_MS` están reducidos para pruebas; para uso real deben aumentarse.
