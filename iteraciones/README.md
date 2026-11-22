# Historial de Iteraciones

## Propósito

Esta carpeta documenta la evolución del prototipo a través de las diferentes versiones desarrolladas durante el curso.

**CRÍTICO:** Demostrar el proceso iterativo es un requisito para obtener puntaje completo en "Integración y Refinamiento" (2.5 puntos).

---

## Estructura de Carpetas

Cada iteración tiene su propia carpeta con documentación de esa versión:

```
iteraciones/
├── iteracion_1/    # Concepto inicial - Prototipo alpha
├── iteracion_2/    # Primera iteración - Avance #2
└── iteracion_3/    # Versión final - Avance #3
```

---

## Contenido de Cada Iteración

Cada carpeta debe incluir:

1. **README.md** - Descripción de la versión
2. **Fotos** - Imágenes del prototipo en ese estado
3. **Esquema** - Circuito de esa versión (si cambió)
4. **Código** - Versión del software (si cambió)
5. **Notas** - Problemas identificados y mejoras planificadas

---

## Tabla Comparativa de Iteraciones

| Aspecto | v1 | v2 | v3 |
|---------|----|----|----| 
| **Fecha** | 16/10/2026 | 26/10/2026 | 22/11/2026 |
| **Sensores** | MQ-7, DHT11 | MQ-7, DHT11 | MQ-7, DHT11 |
| **Actuadores** | LED RGB, buzzer pasivo | LED RGB, buzzer pasivo | LED RGB, buzzer pasivo |
| **Conectividad** | Ninguna (autónomo) | Ninguna (autónomo) | WiFi, Telegram y nube |
| **Alimentación** | USB (sin batería) | Batería LiPo + TP4056 | Batería LiPo directo a la placa |
| **Montaje** | Protoboard | Placa soldada | Placa soldada |
| **Botón de silencio** | BOOT del ESP32 (provisorio) | Pulsador dedicado (sin uso en el código) | Pulsador dedicado funcionando (GPIO 7) |
| **Encapsulado** | ❌ | Prototipo (diseño en Fusion 360) | Caja MDF ensamblada |
| **Testing** | Solo equipo | Solo equipo | Pruebas técnicas; usuarios pendiente |

---

## Evolución del Diseño

### Versión 1 (Iteración 1) - Concepto Inicial
**Fecha:** 16/10/2026  
**Estado:** Prototipo alpha - Prueba de concepto

**Características:**
- Montaje en protoboard, sin soldaduras
- Sin botón dedicado: se usaba el botón BOOT del ESP32 para silenciar
- Sin batería ni módulo TP4056: funcionaba conectado por USB
- Sin encapsulado
- Problemas principales identificados: no era portátil, el botón BOOT no es accesible desde una caja, y el montaje no era apto para encapsular
- Aprendizajes clave: el concepto funciona (detecta, avisa con LED y buzzer y permite silenciar), pero necesita alimentación autónoma y un montaje más robusto

### Versión 2 (Iteración 2) - Primera Mejora
**Fecha:** 26/10/2026  
**Estado:** Prototipo funcional mejorado (en integración final)

**Mejoras implementadas:**
- Placa perforada soldada, en reemplazo del protoboard
- Batería LiPo (3,7 V, 1200 mAh) con módulo de carga TP4056 con protección
- Pulsador dedicado para silenciar el buzzer
- Interruptor general (kill switch) para apagar el equipo
- Diseño del encapsulado en MDF con ventilación y tapa atornillada

**Problemas pendientes:**
- Terminar la integración completa en placa soldada y caja
- Agregar al diseño de la caja las aberturas del pulsador y del interruptor
- Calibrar los umbrales de alerta y alarma con datos reales

### Versión 3 (Iteración 3) - Versión Final
**Fecha:** 22/11/2026
**Estado:** Prototipo final funcional con alertas por Telegram y registro en la nube

**Mejoras finales:**
- Alerta por Telegram a un tercero cuando el CO llega a nivel de peligro
- Registro de CO, temperatura y humedad en una base de datos PostgreSQL en la nube (API en Railway + Aiven), con respaldo local en la memoria del ESP32
- Botón de silencio implementado en el código (5 minutos, el LED sigue rojo)
- Se elimina el módulo TP4056: la batería va directo a la placa (recomendación del profesor)
- Corrección de un error: el equipo podía quedarse en peligro si el CO bajaba de golpe
- Credenciales (WiFi, token, API key) fuera del código

**Resultado:**
- Los datos del ESP32 llegan a la nube (22/11/2026: 32 lecturas de CO, 30 de temperatura y 30 de humedad)
- Pendientes: calibrar el MQ-7 en ppm, medir consumo y autonomía, y hacer testing con usuarios
- Detalle en [`iteracion_3/README.md`](iteracion_3/README.md)

---

## Justificación de Cambios

### Hardware
**De v1 a v2:**
- Cambio: de protoboard a placa perforada soldada
- Razón: conexiones permanentes y compactas, necesarias para instalar el circuito dentro de una caja
- Impacto: circuito más robusto y apto para encapsular

- Cambio: se agrega batería LiPo con módulo TP4056 con protección
- Razón: la batería se calienta y se daña si se carga sin control; el módulo entrega una carga segura y evita ese problema. Además permite funcionar sin cable USB
- Impacto: equipo autónomo y portátil, con la batería protegida (autonomía: por medir)

- Cambio: de botón BOOT a pulsador dedicado
- Razón: el botón BOOT queda dentro de la caja y no se puede usar
- Impacto: el usuario puede silenciar el buzzer sin abrir el equipo

- Cambio: se agrega un interruptor general (kill switch)
- Razón: apagar y encender el equipo sin desconectar la batería
- Impacto: control simple del encendido por parte del usuario

**De v2 a v3:**
- Cambio: se elimina el módulo TP4056 y la batería se conecta directo a la placa
- Razón: recomendación del profesor
- Impacto: circuito más simple; la carga y la descarga profunda de la LiPo quedan a cargo del usuario, así que se documenta el uso de un cargador adecuado

- Cambio: LED RGB a los pines 8 / 9 / 10 y pulsador en GPIO 7
- Razón: MQ-7 en un pin de ADC1 (compatible con WiFi) y botón de silencio funcional
- Impacto: el botón ahora silencia el buzzer

### Software
**De v1 a v2:**
No hubieron cambios significantes.

**De v2 a v3:**
- Se agregan WiFi, Telegram, envío a la nube (HTTPS con API key) y respaldo en flash (LittleFS)
- Se implementa el botón de silencio y se corrige el error de bajada de peligro a alerta
- Las credenciales pasan a `secrets.h`, fuera de GitHub
- Razón: el aviso de v2 solo servía si alguien estaba en la casa
- Impacto: el equipo avisa a un tercero y deja registro de los datos

### Diseño 3D
**De v1 a v2:**
- v1 no tenía encapsulado. En v2 se diseñó una caja de MDF de 5,5 mm (182 × 82 × 62 mm) con 3 ranuras de ventilación, ventanas para el DHT11 y el micro-USB, y una tapa fijada con 4 tornillos para acceder a los componentes

**De v2 a v3:**
- La caja se mantiene (182 × 82 × 62 mm).
- [COMPLETAR: si se agregaron las aberturas del pulsador y del interruptor]
- La ventana del micro-USB del TP4056 queda sin uso porque el TP4056 se eliminó.

---

## Incorporación de Feedback

### Feedback del Avance #1 → Cambios en v2
1. [COMPLETAR: comentario del profesor/ayudante en el Avance #1]
   - Acción tomada: [COMPLETAR]

### Feedback del Avance #2 → Cambios en v3
1. Eliminar el módulo TP4056 y conectar la batería directo a la placa [COMPLETAR: confirmar que fue en el Avance #2]
   - Acción tomada: se eliminó en la v3 y se documentaron las precauciones de carga de la LiPo.

### Feedback de Usuarios → Cambios en v3

---

## Métricas de Mejora

Las métricas de usuarios no existen porque no se hizo testing. Se documentan las diferencias medibles entre versiones:

| Métrica | v1 | v2 | v3 |
|---|---|---|---|
| Alimentación | Solo USB | LiPo 1200 mAh + TP4056 | LiPo directo a la placa |
| Autonomía con batería (h) | No aplica | [COMPLETAR: medir] | [COMPLETAR: medir] |
| Botón de silencio | BOOT (inaccesible en caja) | Pulsador | Pulsador funcionando |
| Aviso remoto | No | En proceso | Telegram |
| Registro de datos | No | En proceso | Nube y flash local |
| Encapsulado | Sin caja | Caja MDF diseñada | Caja MDF ensamblada |

---

## Lecciones Aprendidas

### Técnicas
- Las baterías LiPo necesitan protección de carga y descarga; sin el TP4056 ese cuidado pasa al usuario.
- El MQ-7 debe ir en un pin de ADC1 para leerse con el WiFi activo.
- Las claves no se deben dejar en el código: van en `secrets.h` y en el `.gitignore`.
- Un pin declarado no es un pin usado: el botón de silencio no hacía nada hasta que se implementó.

### De Proceso
- Documentar cada versión al terminarla evita reconstruir los cambios al final.

### De Trabajo en Equipo
- Anticipar proximos proyectos con tiempo para no estar apurados.
