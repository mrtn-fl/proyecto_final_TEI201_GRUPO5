# Iteración 3 – Versión final (v3.0)

## Información general

**Fecha:** 22/11/2026
**Versión:** v3.0
**Estado:** Prototipo final funcional con alertas por Telegram y registro de datos en la nube
**Avance asociado:** Avance #3

---

## Descripción

La v3 convierte el aviso local de la v2 en un sistema conectado: además de la luz y el sonido, el equipo avisa por **Telegram a un tercero** cuando el CO llega a nivel de peligro y **registra las lecturas** en una base de datos PostgreSQL en la nube, con respaldo local si no hay WiFi. Esto responde al problema que quedó pendiente en la v2: el aviso solo servía si alguien estaba en la casa.

**Objetivos logrados:**
- Alerta remota por Telegram en nivel de peligro.
- Registro de CO, temperatura y humedad en la nube (API en Railway + PostgreSQL en Aiven).
- Respaldo local en la memoria del ESP32 (`/datos.csv`) cuando no hay WiFi.
- Botón de silencio funcionando (en la v2 el pin estaba definido pero no se usaba en el código).
- Credenciales fuera del código (`secrets.h`, excluido de GitHub).

---

## Cambios respecto a v2

### Hardware

| Cambio | Razón | Impacto |
|---|---|---|
| Se elimina el módulo TP4056; la batería LiPo va directo a la placa | Recomendación del profesor | Circuito más simple. Se pierde la protección de carga: la LiPo debe cargarse con un cargador adecuado (ver precauciones en `hardware/README.md`) |
| LED RGB pasa a los pines 8 / 9 / 10 | Reorganización de pines | MQ-7 en un pin de ADC1, compatible con WiFi |
| Pulsador de silencio en GPIO 7 | En v2 el pin estaba definido pero el código no lo leía | El botón ahora silencia el buzzer |

### Software

**Nuevas funcionalidades:**
- Conexión WiFi con reconexión cada 15 s sin bloquear el `loop()`.
- Mensaje por Telegram al llegar a peligro y otro cuando los niveles vuelven a la normalidad.
- Envío de cada lectura (CO, temperatura, humedad) a la API por HTTPS con API key.
- Respaldo en flash (LittleFS) y comandos por Serial para ver o descargar el CSV.
- 4 estados: calentamiento, normal, alerta y peligro.

**Correcciones:**
- Si el CO bajaba de golpe desde peligro hasta justo bajo el umbral de alerta, el equipo se quedaba en peligro. Ahora baja a alerta.
- El botón de silencio quedó implementado: silencia el buzzer 5 minutos en peligro y el LED sigue rojo.
- Token del bot y clave del WiFi sacados del código.

**Servidor** (`software/servidor/`): API en Node.js que valida la API key y el sensor, guarda en PostgreSQL y ofrece consultas (`/api/lecturas`, `/api/resumen`, `/api/lecturas.csv`, `/salud`).

### Diseño mecánico

- Se mantiene la caja de MDF de 5,5 mm (182 × 82 × 62 mm) de la v2.
- [COMPLETAR: confirmar si ya se agregaron al modelo las aberturas del pulsador y del interruptor, pendientes desde la v2.]
- La ventana posterior del micro-USB del TP4056 quedó como herencia de la v2, porque el TP4056 ya no está.

---

## Fotos del prototipo final

Las fotos van en [`hardware/fotos/`](../../hardware/fotos) con el prefijo `v3_`.

---

## Resultados

### Funcionalidad lograda

✅ Lectura de CO con MQ-7 y de temperatura/humedad con DHT11
✅ Estados con LED RGB y buzzer, con histéresis
✅ Silencio del buzzer con pulsador dedicado
✅ Alerta por Telegram en peligro
✅ Registro en la nube y respaldo local
✅ Funcionamiento con batería, sin cable USB

### Pruebas técnicas realizadas

| Prueba | Resultado |
|---|---|
| Servidor responde (`/salud`) | `{"ok":true}`: servidor y base de datos conectados |
| Guardar una lectura (POST con API key) | Se guarda y devuelve `id` y `creado_en` |
| Consultar datos (`/api/lecturas`, `/api/resumen`, CSV) | Devuelven los datos guardados |
| Integración ESP32 → nube (22/11/2026) | Llegaron 32 lecturas de CO, 30 de temperatura y 30 de humedad. Último CO = 53, T = 27,3 °C, H = 37 % |
| Tiempo hasta recibir el Telegram | 2 s [COMPLETAR: fecha y evidencia] |

> El máximo de CO de 812 que aparece en el resumen de 24 h corresponde a una lectura de prueba enviada a mano al servidor, no a una medición real.

El detalle y la evidencia están en [`testing/reportes/protocolo_pruebas.md`](../../testing/reportes/protocolo_pruebas.md).

### Testing con usuarios



### Contexto de impacto (ODS 3)

Los datos del problema vienen de las fuentes citadas en [`FUENTES.md`](../../FUENTES.md): los ingresos a centros asistenciales por intoxicación con CO pasaron de 13 en 2023 a 31 en 2024 (solo hasta mayo), y los más afectados son adultos mayores (60 %) y preescolares (14 %).

El prototipo **todavía no mide impacto**: no hubo piloto ni testing con usuarios, así que no hay indicadores medidos.

Costo estimado de fabricar una unidad: ~$39.870 CLP (precios de referencia del BOM).

---

## Comparación de las 3 iteraciones

| Aspecto | v1 | v2 | v3 |
|---|---|---|---|
| Fecha | 16/10/2026 | 26/10/2026 | 22/11/2026 |
| Sensores | MQ-7, DHT11 | MQ-7, DHT11 | MQ-7, DHT11 |
| Actuadores | LED RGB, buzzer | LED RGB, buzzer | LED RGB, buzzer |
| Conectividad | Ninguna | Ninguna | WiFi + Telegram + nube |
| Registro de datos | No | No | Nube y flash local |
| Alimentación | USB | LiPo + TP4056 | LiPo directo a la placa |
| Montaje | Protoboard | Placa soldada | Placa soldada |
| Botón de silencio | BOOT del ESP32 | Pulsador (sin uso en el código) | Pulsador funcionando (GPIO 7) |
| Encapsulado | No | Diseño en Fusion 360 | Caja MDF [COMPLETAR: ¿ya fabricada y ensamblada?] |
| Testing | Solo equipo | Solo equipo | Pruebas técnicas; usuarios pendiente |

---

## Fortalezas

1. **El aviso local funciona aunque falle internet.** LED y buzzer no dependen del WiFi; el Telegram y la nube son un complemento.
   - Evidencia: diseño del firmware (ver `software/README.md`).
2. **Los datos llegan a la nube y se pueden consultar y exportar.**
   - Evidencia: resumen del 22/11/2026 y CSV en `testing/datos/`.
3. **Bajo costo y reparable.** Módulos estándar, caja atornillada y costo estimado de ~$39.870 CLP.
   - Evidencia: BOM y `hardware/README.md`.

## Limitaciones

1. **MQ-7 sin calibrar en ppm.**
   - Descripción: los umbrales están en valores crudos del ADC (alerta 2000, peligro 3000). No reemplaza a un detector certificado.
   - Posible solución futura: calibrar contra un patrón de CO y definir los umbrales en ppm.
2. **Sin testing con usuarios.**
   - Descripción: no hay datos de usabilidad ni de comprensión de las alertas.
   - Posible solución futura: aplicar el protocolo de `testing/README.md`.
3. **Batería sin módulo de protección.**
   - Descripción: al quitar el TP4056, la carga y la descarga profunda dependen del usuario.
   - Posible solución futura: volver a incluir un módulo con protección.
4. **Dependencia del WiFi de 2,4 GHz** para Telegram y nube. Sin WiFi, funciona el aviso local y el respaldo en flash.
5. **API de lectura pública y conexión SSL sin verificar el certificado.** Aceptable para el prototipo; para producción hay que restringir el acceso.
6. **Consumo y autonomía sin medir.** El calefactor del MQ-7 está especificado para 5 V y la batería entrega 3,7 V.

---

## Aprendizajes del proceso

### Técnicos
1. Una LiPo necesita protección de carga y descarga: quitar el TP4056 simplificó el circuito pero trasladó ese riesgo al usuario.
2. En el ESP32-S3 el MQ-7 debe ir en un pin de ADC1 para poder leerlo con el WiFi activo.
3. Las claves no deben quedar en el código: se movieron a `secrets.h` y al `.gitignore`.
4. Declarar un pin no garantiza que se use: el botón de silencio estaba definido y nunca se leía hasta que se revisó el código.
5. Sin `delay()` en el `loop()`, la alarma no se bloquea mientras se conecta el WiFi o se envía un mensaje.

### De trabajo en equipo y gestión
[COMPLETAR: 1 o 2 aprendizajes del equipo, por ejemplo sobre reparto de tareas, tiempos y uso de GitHub.]

---

## Trabajo futuro

**Corto plazo**
- [ ] Medir consumo y autonomía.
- [ ] Testing con usuarios.

**Mediano plazo**
- [ ] Módulo de carga con protección para la LiPo.
- [ ] Intervalo de registro de 60 s (hoy 10 s para pruebas) y calentamiento más largo para uso real.
- [ ] Restringir el acceso de lectura a la API.

**Escalabilidad**
- [ ] Panel para ver los datos de varios equipos.
- [ ] Reducir el costo por unidad comprando por volumen.

---

## Archivos en esta carpeta

- [`v3_codigo.ino`](v3_codigo.ino): copia del firmware v3 (el original está en `software/src/costop/`).
- [`secrets_example.h`](secrets_example.h): plantilla de credenciales.
