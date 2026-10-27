# Planos Técnicos

## Planos Requeridos

### 1. Plano de Conjunto
`plano_conjunto_v3.pdf`

Incluir:
- Vistas principales (frontal, lateral, superior)
- Escala apropiada
- Cotas principales externas
- Tabla de piezas

### 2. Planos de Detalle
Para cada componente crítico del encapsulado:
- Cotas completas
- Tolerancias importantes
- Notas de fabricación

---

## Planos Entregados

### Plano de conjunto del encapsulado: `plano_conjunto_v3.pdf`

**Título del plano:** CoStop_Completo  
**Autor:** Vicente Pincheira, 26-10-2026  
**Hoja:** 1/1  
**Unidades:** milímetros (mm)  
**Material:** MDF 5,5 mm, corte láser

**Contenido del plano:**
- Vista lateral larga, vista del extremo, vista superior e isométrica (referencia)
- Dimensiones externas: **182 × 82 × 62 mm**
- Uniones tipo "dedos" entre paredes
- 3 ranuras de ventilación en el lateral largo
- Agujero frontal Ø17 mm (MQ-7)
- Tapa: 4 agujeros de fijación Ø9 mm, agujero del LED Ø5 mm y agujero del buzzer Ø7 mm
- Ventana lateral derecha de 16 × 12,7 mm (DHT11)
- Ventana posterior de 8,5 × 3,8 mm (micro-USB del TP4056)

Las decisiones detrás de cada una de estas dimensiones están en [`../JUSTIFICACION_DISENO.md`](../JUSTIFICACION_DISENO.md).

### Cumplimiento de lo requerido

- [x] Vistas: frontal, lateral, superior e isométrica
- [x] Cotas principales externas
- [x] Unidades en mm
- [x] Cajetín con título, autor y fecha
- [ ] Cajetín con escala, material, versión e integrantes del equipo
- [ ] Tabla de piezas
- [ ] Corte A-A
- [ ] Planos de detalle de los componentes del encapsulado
- [ ] Tolerancias indicadas

### Pendiente para la versión final

- Completar el cajetín (escala, material, versión, integrantes)
- Agregar la tabla de piezas (paredes, base, tapa)
- Agregar el corte A-A con el interior de la caja
- Agregar las aberturas del pulsador de silencio y del interruptor general, que aún no aparecen en el plano
- Corregir el nombre grabado de "CoStop" a "COStop"

---

## Estándares de Planos

### Vistas Ortogonales Requeridas
- Vista Frontal
- Vista Superior
- Vista Lateral Derecha
- Vista Isométrica (referencia)

### Cortes
- Corte A-A: Sección transversal mostrando interior
- Corte B-B: (si es necesario para claridad)

---

## Formato de Planos

**Tamaño de hoja:** A4 o A3  
**Orientación:** Según convenga  
**Escala:** 1:1, 1:2, o según sea necesario  
**Unidades:** Milímetros (mm)

### Información en Cajetín
- Título del proyecto
- Nombre de la pieza/ensamble
- Escala
- Material
- Fecha
- Versión
- Integrantes del equipo

---

## Acotación

### Reglas Generales
- Cotas en milímetros sin unidad
- Líneas de cota finas
- Texto legible (mín. 2.5mm de altura)
- Cotas críticas resaltadas

### Tolerancias
Indicar tolerancias para:
- Orificios de tornillos: ±0.1mm
- Encajes: +0.2mm / +0.0mm
- Dimensiones generales: ±0.5mm

---

## Exportación desde Fusion 360

```
Opción 1: Drawing (Plano tradicional)
1. Create Drawing
2. Configurar vistas y cotas
3. Export como PDF

Opción 2: Export directo
File > Export > Formato PDF/DWG
```

---

## Archivos a Entregar

- `plano_conjunto_v3.pdf` - Plano principal
