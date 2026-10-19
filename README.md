# COStop – El gas que no se ve

Proyecto final de Taller de Diseño en Ingeniería (TEI201) – Facultad de Ingeniería y Ciencias – Universidad Adolfo Ibáñez.

## Información del Equipo
**Grupo 5**
**Integrantes:**
  - Benjamin Bidegain
  - Martin Flores
  - Vicente Pincheira
  - Thomas von Fabeck

- **ODS Seleccionado:** ODS 3 – Salud y bienestar

- **Problema a resolver:** Las familias del sur de Chile que se calefaccionan con leña, parafina o kerosene no tienen dispositivos accesibles para medir el monóxido de carbono (CO), un gas incoloro e inodoro. Los ingresos a centros asistenciales por intoxicación con CO pasaron de 13 en 2023 a 31 en 2024 (solo hasta mayo), y los grupos más afectados son los adultos mayores (60%) y los preescolares (14%). En 2025 se certificaron 116.423 nuevas estufas a kerosene, así que el riesgo sigue creciendo.

## Descripción del Proyecto

**COStop** es una alarma doméstica de CO de bajo costo y fácil instalación, dirigida a adultos mayores y familias con niños pequeños en hogares del sur de Chile con calefacción a combustión. No requiere cambiar el sistema de calefacción: hace visible un riesgo que hoy es invisible, avisando con luz y sonido antes de que el CO alcance niveles peligrosos para dar tiempo a ventilar o evacuar.

El prototipo está basado en un **ESP32-S3 Super Mini**. Mide continuamente el gas con un sensor MQ y la temperatura/humedad con un DHT22, y comunica el estado mediante un LED RGB y un buzzer:

| Estado | LED RGB | Buzzer |
| Calentamiento (warm-up) | Azul intermitente | Apagado |
| Normal | Verde  | Apagado |
| Alerta | Amarillo intermitente | Pitidos cortos |
| Alarma | Rojo fijo | Continuo |
| Falla de sensor | Magenta | Doble pitido |

Un botón permite **silenciar** el buzzer (no desactiva la alarma). El sistema usa histéresis y confirmación de lecturas consecutivas para evitar falsas alarmas.

## Estructura del Repositorio
```
├── hardware/          # Circuitos, esquemas y BOM
├── software/          # Código Arduino y librerías
├── diseno_3d/         # Modelos Fusion 360 y renders
├── testing/           # Validación con usuarios
├── documentacion/     # Reportes y presentación
└── iteraciones/       # Historial de versiones
``` 

## Inicio Rápido

### Requisitos Previos

- Arduino IDE 2.x
- Soporte de placas ESP32 (Espressif) instalado en el gestor de placas
- Librería *DHT sensor library* (Adafruit) y *Adafruit Unified Sensor*
- Fusion 360 (para abrir los modelos 3D)

### Instalación

1. Clonar el repositorio.
2. Instalar las librerías (ver `software/README.md` y `software/librerias/`).
3. Abrir `software/codigo_esp32.ino` en Arduino IDE y seleccionar la placa ESP32-S3.
4. Conectar el hardware según `hardware/README.md`.
5. Cargar el código y abrir el Monitor Serie a 115200 baudios.

## Checklist de Entrega

### Hardware
- [ ] Esquema del circuito (Fritzing/Wokwi)
- [ ] BOM completo
- [ ] Fotos de alta resolución

### Software
- [x] Código comentado
- [x] Librerías documentadas
- [x] Manual de instalación

### Diseño 3D
- [ ] Archivos Fusion 360 (.f3d) con TODOS los componentes
- [ ] Renders de alta calidad (1+ ángulos)
- [ ] Planos técnicos

### Testing
- [ ] Reporte de testing con usuarios (mín. 5)
- [ ] Evidencias fotográficas/videos
- [ ] Datos cuantitativos

### Documentación
- [ ] Reporte final (máx. 15 páginas)
- [x] Presentación (10 min)
- [x] Avance 1 (`COStop_Avance1.pdf`): problemática, ODS 3, evidencia, usuarios y solución

## Fuentes

- Diario Usach (2024, 24 de junio). *Advierte aumento de intoxicaciones por monóxido de carbono al interior de las casas.* https://www.diariousach.cl
- Cuerpo de Bomberos de Punta Arenas (2019, 6 de mayo). *Intoxicación por monóxido de carbono.* https://www.bomberospuntaarenas.cl/2019/05/06/intoxicacion-por-monoxido-de-carbono/
- Ministerio de Energía (2026). Registro de certificación de estufas a kerosene.

---

## Licencia

Este proyecto es desarrollado como parte del curso TEI201 - Facultad de Ingeniería y Ciencias - Universidad Adolfo Ibáñez.
