# Iteración 2 – Placa soldada, batería y encapsulado

## Información general

**Fecha:** 26/10/2026
**Versión:** v2.0
**Estado:** Prototipo funcional mejorado
**Avance asociado:** Avance #2

---

## Cambios respecto a v1

### Hardware
**Agregado:**
- Batería LiPo 3,7 V 1200 mAh + módulo TP4056 con protección
- Pulsador dedicado para silenciar el buzzer
- Interruptor general (kill switch)

**Modificado:**
- Protoboard → placa perforada soldada. Razón: conexiones permanentes y compactas para meter el circuito en una caja.
- Botón BOOT → pulsador dedicado. Razón: el BOOT queda dentro de la caja y no se puede presionar.

**Removido:**
- Alimentación solo por cable USB. Razón: el equipo debe funcionar de forma autónoma.

### Software
Sin cambios significativos respecto a v1 (misma máquina de estados, umbrales e histéresis).

### Diseño mecánico
- Primer encapsulado diseñado en Fusion 360: caja de MDF 5,5 mm, 182 × 82 × 62 mm, corte láser.
- 3 ranuras de ventilación, ventanas para DHT11 y micro-USB, agujeros para LED, buzzer y MQ-7.
- Tapa fijada con 4 tornillos para mantenimiento.
- Detalle en [`diseno_3d/JUSTIFICACION_DISENO.md`](../../diseno_3d/JUSTIFICACION_DISENO.md).

---

## Fotos del prototipo v2

[COMPLETAR: subir fotos a esta carpeta, ej. `v2_placa_soldada.jpg`, `v2_encapsulado.jpg`]

---

## Funcionalidad lograda

✅ Detección de gas con MQ-7 y estados con LED/buzzer (heredado de v1)
✅ Funcionamiento con batería
✅ Silencio con pulsador dedicado
⚠️ Integración completa en la caja: en proceso

## Feedback del Avance #2

1. Eliminar el módulo TP4056 y conectar la batería directo a la placa [COMPLETAR: confirmar que este fue el comentario del Avance #2]
   - Acción para v3: se eliminó el TP4056 (ver [`../iteracion_3/README.md`](../iteracion_3/README.md))

---

## Problemas pendientes (para v3)

1. **Aberturas del pulsador e interruptor en la caja**
   - Prioridad: Alta
   - Plan: agregarlas al modelo en Fusion 360.
2. **Umbrales sin calibrar**
   - Descripción: `T_ALERTA` y `T_ALARMA` están en valores crudos de ADC, no en ppm.
   - Prioridad: Media
   - Plan: procedimiento de calibración documentado en el código v3 (base en aire limpio)
3. **El aviso solo sirve si alguien está en la casa**
   - Prioridad: Alta
   - Plan: alertas remotas por Telegram y registro de datos en la nube (v3)
4. **Nombre grabado "CoStop" vs "COStop"**
   - Prioridad: Baja

---

## Comparación v1 vs v2

| Aspecto | v1 | v2 |
|---|---|---|
| Montaje | Protoboard | Placa perforada soldada |
| Alimentación | USB | LiPo 1200 mAh + TP4056 |
| Botón de silencio | BOOT (inaccesible en caja) | Pulsador dedicado |
| Encendido/apagado | Desconectar USB | Interruptor |
| Encapsulado | ❌ | Caja MDF diseñada |

## Archivos

- Código: igual a v1 ([`../iteracion_1/v1_codigo.ino`](../iteracion_1/v1_codigo.ino))
- Modelo 3D: [`diseno_3d/fusion360/CoStop.f3d`](../../diseno_3d/fusion360/CoStop.f3d)
