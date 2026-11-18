# Hardware – Documentación

Documentación técnica del hardware de **COStop**, alarma doméstica de monóxido de carbono (CO).

| Carpeta | Contenido |
|---|---|
| `esquemas/` | Esquema del circuito y tabla de conexiones |
| `bom/` | Lista de materiales con costos |
| `fotos/` | Fotografías del prototipo ensamblado |

---

## Selección de componentes

| Componente | Función | Por qué se eligió |
|---|---|---|
| ESP32-S3 Super Mini | Microcontrolador | Pequeño (24,8 × 18,2 mm), ADC de 12 bits para el MQ-7 y WiFi integrado para Telegram y la base de datos |
| Sensor MQ-7 (módulo) | Detecta CO | Sensor específico para monóxido de carbono, bajo costo y disponible en la universidad |
| DHT11 | Temperatura y humedad | Permite registrar las condiciones del ambiente y detectar falla del sensor; económico |
| LED RGB KY-016 | Indicador visual | Un solo LED muestra los 5 estados del sistema con colores distintos |
| Buzzer pasivo | Alarma sonora | Aviso audible aunque la persona no esté mirando el equipo |
| Pulsador | Silenciar buzzer | Control accesible desde fuera de la caja |
| Interruptor (kill switch) | Encendido/apagado | Apagar sin desconectar la batería |
| Batería LiPo 3,7 V 1200 mAh | Alimentación | Funcionamiento autónomo, conectada directo a la placa (el TP4056 de v2 se eliminó por recomendación del profesor) |

---

## Conexiones

Pines según `software/src/costop/costop.ino` (v3):

| Componente | Pin del componente | Pin ESP32-S3 |
|---|---|---|
| DHT11 | DATA | GPIO 4 |
| MQ-7 | AO (salida analógica) | GPIO 1 (ADC1, compatible con WiFi) |
| Buzzer | + | GPIO 5 |
| KY-016 | R / G / B | GPIO 8 / GPIO 9 / GPIO 10 |
| Pulsador silencio | un terminal | GPIO 7 (el otro a GND) |
| Todos | GND | GND (bus de tierra en placa perforada) |
| DHT11, KY-016 | VCC | 3V3 |
| MQ-7 | VCC | 5V |
| Batería LiPo | + | Interruptor |
| Batería LiPo | − | GND |

> ⚠️ El calefactor del MQ-7 está especificado para 5 V. Si se alimenta directo desde la LiPo (3,7 V) la lectura puede variar.

---

## Instrucciones de ensamble

1. Soldar en la placa perforada el bus de tierra común.
2. Soldar los cables de DHT11, MQ-7, KY-016, buzzer y pulsador a los pines indicados en la tabla.
3. Conectar el + de la batería al interruptor y del interruptor a la alimentación del ESP32; el − de la batería a GND. Respetar polaridad.
4. Montar cada componente en su abertura de la caja: MQ-7 en el agujero frontal Ø17, DHT11 en la ventana lateral, LED y buzzer en la tapa.
5. Cerrar la tapa con los 4 tornillos autorroscantes 3 × 16 mm.

### Precauciones
- No invertir la polaridad de la LiPo.
- Sin módulo de protección, no dejar que la LiPo se descargue por completo (la daña) y cargarla solo con un cargador adecuado para LiPo. 
- El MQ-7 se calienta durante el funcionamiento: no dejarlo en contacto con cables o la batería.
- Esperar el calentamiento (LED azul) antes de confiar en las lecturas.
- Es un prototipo académico: **no reemplaza un detector de CO certificado**.

---

## Diseño para la reparación

- Tapa atornillada (4 tornillos), sin pegamento: se abre con un destornillador.
- Batería accesible al abrir la tapa para cambiarla o cargarla.
- Componentes en módulos estándar y baratos (ver BOM), reemplazables individualmente.
- [COMPLETAR: si usaron conectores/headers en vez de soldar directo, mencionarlo]

---

## Especificaciones técnicas

**Alimentación:** Batería LiPo 3,7 V, 1200 mAh, conectada directo a la placa
**Consumo:** [COMPLETAR: medir con multímetro, en mA]
**Autonomía:** [COMPLETAR: medir o calcular = 1200 mAh / consumo]
**Dimensiones:** 182 × 82 × 62 mm (encapsulado MDF)
**Peso:** [COMPLETAR: pesar el prototipo]

---

## Troubleshooting

| Problema | Posible causa | Solución |
|---|---|---|
| `T=nan` en el Monitor Serie | DHT11 desconectado | Revisar cables y alimentación del DHT11 |
| No llega el Telegram | Sin WiFi o credenciales malas | Ver troubleshooting en `software/docs/README.md` |
| Siempre en alerta/peligro | MQ-7 sin calentar o umbrales no calibrados | Esperar el calentamiento; ajustar `UMBRAL_ALERTA`/`UMBRAL_PELIGRO` |
| No enciende | Batería descargada o interruptor apagado | Cargar la batería; revisar interruptor y polaridad |
| Botón no silencia | Pin del botón distinto al del código | Verificar `PIN_BTN` en el código |
| LED con colores invertidos | LED de ánodo común | Invertir los valores en `setColor()` |
| Buzzer no suena | Buzzer activo en vez de pasivo | El código usa `tone()` (buzzer pasivo); revisar el componente |
