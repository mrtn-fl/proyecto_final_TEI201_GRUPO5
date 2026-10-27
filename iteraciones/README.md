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
| **Fecha** | [16/10/2026] | [26/10/2026] | Pendiente (Avance #3) |
| **Sensores** | MQ-7, DHT11 | MQ-7, DHT11 | Pendiente |
| **Actuadores** | LED RGB, buzzer pasivo | LED RGB, buzzer pasivo | Pendiente |
| **Conectividad** | Ninguna (autónomo) | Ninguna (autónomo) | Pendiente |
| **Alimentación** | USB (sin batería) | Batería LiPo + TP4056 | Pendiente |
| **Montaje** | Protoboard | Placa soldada | Pendiente |
| **Botón de silencio** | BOOT del ESP32 (provisorio) | Pulsador dedicado | Pendiente |
| **Encapsulado** | ❌ | Prototipo (diseño en Fusion 360) | Pendiente |
| **Testing** | Solo equipo | [por realizar: 2 usuarios] | 5+ usuarios |

---

## Evolución del Diseño

### Versión 1 (Iteración 1) - Concepto Inicial
**Fecha:** [16/10/2026]  
**Estado:** Prototipo alpha - Prueba de concepto

**Características:**
- Montaje en protoboard, sin soldaduras
- Sin botón dedicado: se usaba el botón BOOT del ESP32 para silenciar
- Sin batería ni módulo TP4056: funcionaba conectado por USB
- Sin encapsulado
- Problemas principales identificados: no era portátil, el botón BOOT no es accesible desde una caja, y el montaje no era apto para encapsular
- Aprendizajes clave: el concepto funciona (detecta, avisa con LED y buzzer y permite silenciar), pero necesita alimentación autónoma y un montaje más robusto

### Versión 2 (Iteración 2) - Primera Mejora
**Fecha:** [26/10/2026]  
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
**Fecha:** Pendiente (Avance #3)  
**Estado:** Por desarrollar

**Mejoras finales:**
- Pendiente

**Resultado:**
- Pendiente

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
- Cambio: [Descripción]
- Razón: [Justificación técnica]
- Impacto: [Mejora cuantitativa]

### Software
**De v1 a v2:**
No hubieron cambios significantes.

**De v2 a v3:**
- Pendiente

### Diseño 3D
**De v1 a v2:**
- v1 no tenía encapsulado. En v2 se diseñó una caja de MDF de 5,5 mm (182 × 82 × 62 mm) con 3 ranuras de ventilación, ventanas para el DHT11 y el micro-USB, y una tapa fijada con 4 tornillos para acceder a los componentes

**De v2 a v3:**
- Pendiente

---

## Incorporación de Feedback

### Feedback del Avance #1 → Cambios en v2
1. [Comentario profesor/ayudante]
   - Acción tomada: 

### Feedback del Avance #2 → Cambios en v3
1. [Comentario profesor/ayudante]
   - Acción tomada: 

### Feedback de Usuarios → Cambios en v3
1. [Comentario común de usuarios]
   - Acción tomada: 

---

## Métricas de Mejora

Las métricas cuantitativas de usuarios se completarán con el testing. Por ahora se documentan las diferencias medibles entre versiones:

| Métrica | v1 | v2 | v3 | Mejora Total |
|---------|----|----|----| -------------|
| Alimentación | Solo USB | Batería LiPo 1200 mAh + TP4056 | Pendiente | Equipo autónomo |
| Autonomía con batería (h) | No aplica | [medir] | Pendiente | [medir] |
| Botón de silencio | BOOT (inaccesible en caja) | Pulsador dedicado | Pendiente | Accesible |
| Encapsulado | Sin caja | Caja MDF con ventilación | Pendiente | — |
| Satisfacción usuario (1-5) | — | [medir en testing] | Pendiente | [medir] |

---

## Lecciones Aprendidas

### Técnicas
- Las baterías LiPo necesitan un módulo de carga con protección para evitar sobrecalentamiento y daño
- [Lección 2]

### De Proceso
- [Lección 1]
- [Lección 2]

### De Trabajo en Equipo
- [Lección 1]
- [Lección 2]
