# Iteración 1 - Concepto Inicial

## Información General

**Fecha:** [XX/XX/2026]  
**Versión:** v1.0  
**Estado:** Prototipo alpha - Prueba de concepto  
**Avance asociado:** Planificación inicial / Avance #1

---

## Descripción

Primera versión del prototipo, enfocada en validar la factibilidad técnica del concepto.

**Objetivo de esta iteración:**
- Probar conexión de sensores básicos
- Validar comunicación con microcontrolador
- Demostrar concepto de actuación
- Circuito básico en protoboard

---

## Componentes Utilizados

### Hardware
- Microcontrolador: ESP32-S3 Super Mini
- Sensores:
  - MQ-7 (monóxido de carbono)
  - DHT11 (temperatura y humedad)
- Actuadores:
  - LED RGB KY-016
  - Buzzer pasivo
- Otros: protoboard, botón BOOT del ESP32 usado para silenciar, alimentación por USB (sin batería ni TP4056)

### Software
- IDE: Arduino IDE
- Librerías: DHT sensor library (Adafruit), Adafruit Unified Sensor
- Versión código: v1.0

---

## Fotos del Prototipo

Incluir en esta carpeta:
- `v1_circuito_protoboard.jpg`
- `v1_vista_general.jpg`
- `v1_detalle_conexiones.jpg`

---

## Resultados de Testing Inicial

### Funcionalidad Lograda
✅ [COMPLETAR: lectura del sensor de gas MQ-7]  
✅ [COMPLETAR: indicación de estado con LED RGB y buzzer]  
✅ [COMPLETAR: silencio del buzzer con el botón BOOT]  
❌ Funcionamiento autónomo (sin batería, dependía del cable USB)

### Problemas Identificados

1. **Problema 1: sin alimentación autónoma**
   - Descripción: el prototipo no tenía batería y solo funcionaba conectado por USB
   - Causa probable: v1 se construyó solo para validar el concepto
   - Solución propuesta: agregar una batería LiPo con un módulo de carga TP4056 con protección (la batería se calienta y se daña si se carga sin control)

2. **Problema 2: botón no accesible**
   - Descripción: se usaba el botón BOOT del ESP32 para silenciar, que quedaría dentro de una caja
   - Causa probable: uso provisorio de un botón ya existente en la placa
   - Solución propuesta: agregar un pulsador dedicado

3. **Problema 3: montaje no apto para encapsular**
   - Descripción: el circuito estaba en protoboard
   - Causa probable: el protoboard sirve para pruebas, no para un montaje compacto y permanente
   - Solución propuesta: pasar a una placa perforada soldada

---

## Aprendizajes

### Técnicos
- El concepto es viable con los sensores y el microcontrolador elegidos [CONFIRMAR]
- Una batería LiPo necesita un módulo de carga con protección

### De Diseño
- Los controles del usuario (botón e interruptor) deben quedar accesibles desde el exterior
- Hay que diseñar el circuito pensando en el encapsulado

---

## Plan para Iteración 2

### Mejoras Planificadas

**Hardware:**
- [x] Pasar de protoboard a placa soldada
- [x] Agregar batería LiPo con módulo TP4056
- [x] Agregar pulsador dedicado
- [x] Agregar interruptor general (kill switch)

**Software:**
- [ ] [COMPLETAR: cambios de código, por ejemplo cambiar el pin del botón de 0 (BOOT) a 7]

**Diseño:**
- [x] Iniciar diseño de encapsulado
- [x] Mejorar ruteo de cables (soldadura sobre placa perforada)

---

## Archivos en esta Carpeta

- `v1_codigo.ino` - Código de esta versión
- `v1_esquema.png` - Esquema del circuito
- `v1_fotos/` - Fotografías del prototipo
- `v1_notas.txt` - Notas adicionales del equipo
