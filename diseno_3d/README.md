# Diseño 3D - Documentación

## ⚠️ REQUISITO CRÍTICO

El modelo 3D debe incluir **TODOS** los componentes del prototipo:
- ✅ Encapsulado exterior completo
- ✅ Placa ESP32/Arduino (con dimensiones exactas)
- ✅ Todos los sensores en posición de instalación
- ✅ Todos los actuadores
- ✅ Batería / fuente de alimentación
- ✅ Cableado (routing aproximado)
- ✅ Sistema de montaje (brackets, tornillos)
- ✅ Orificios de ventilación (si aplica)

**NO ES ACEPTABLE:** Solo el encapsulado vacío sin componentes internos

---

## Carpetas

#### `fusion360/`
Archivos nativos de Fusion 360 (.f3d)

#### `renders/`
Imágenes renderizadas de alta calidad

#### `planos/`
Planos técnicos con cotas

---

## Especificaciones

**Software:** Autodesk Fusion 360  
**Unidades:** Milímetros (mm)  
**Escala:** 1:1 (dimensiones reales)

**Dimensiones externas:** 182 mm × 82 mm × 62 mm  
**Peso estimado:** [XXX gramos]  
**Material:** MDF de 5,5 mm (corte láser)

---

## Consideraciones de Diseño

### Funcionales
- [x] Acceso a puertos USB/alimentación
- [x] Ventilación adecuada
- [ ] Protección de componentes
- [ ] Fácil acceso para mantenimiento
- [ ] Resistencia a condiciones ambientales

### Fabricación
- [ ] Imprimible sin soportes excesivos
- [ ] Tolerancias de ensamble (+0.2mm)
- [x] Grosor de pared mínimo 2mm
- [ ] Sin ángulos imposibles (overhangs <45°)

---

## Configuración de Impresión 3D (si fue utilizada)

No se utilizó impresión 3D: el encapsulado se fabricó en MDF de 5,5 mm con corte láser.
