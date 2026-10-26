# 📦 BOM — Lista de Materiales · CoStop

Lista de materiales del detector de monóxido de carbono **CoStop**.

> ⚠️ **Sobre los precios:** la columna **Costo real** indica lo que el equipo efectivamente pagó.
> La columna **Precio referencial (ESTIMADO)** es solo una **aproximación** de lo que costaría cada
> componente en el mercado chileno (octubre 2026). **No son precios pagados**: se incluyen para
> estimar el costo de fabricar una unidad del producto. Los valores marcados con `*` no tienen una
> referencia directa en una tienda chilena y fueron aproximados a partir de precios internacionales.

---

## Electrónica

| # | Componente | Cant. | Especificación | Dimensiones (mm) | Origen | Costo real (CLP) | Precio referencial ESTIMADO (CLP) |
|---|------------|:-----:|----------------|------------------|--------|-----------------:|----------------------------------:|
| 1 | ESP32-S3 Super Mini | 1 | Microcontrolador con Wi-Fi y Bluetooth, USB-C | 24,8 × 18,2 × 12,6 | Préstamo universidad | $0 | ~$13.400 |
| 2 | Sensor MQ-7 (módulo) | 1 | Sensor de monóxido de carbono (CO) | 38 × 20,15 × 16,45 | Préstamo universidad | $0 | ~$3.400 |
| 3 | Sensor DHT11 (módulo 3 pines) | 1 | Sensor de temperatura y humedad | 28,1 × 12,8 × 7,3 | Préstamo universidad | $0 | ~$2.500 `*` |
| 4 | LED RGB KY-016 | 1 | Indicador visual de estado, LED de 5 mm | 23,6 × 15 × 15,25 | Préstamo universidad | $0 | ~$1.500 `*` |
| 5 | Buzzer pasivo | 1 | Alarma sonora | Ø 11,8 × 8,45 | Préstamo universidad | $0 | ~$500 `*` |
| 6 | Batería LiPo | 1 | 3,7 V, 1200 mAh | 50 × 30 × 9,5 | Préstamo universidad | $0 | ~$7.000 `*` |
| 7 | Módulo cargador TP4056 | 1 | Micro-USB, con protección de batería (B−/B+, OUT−/OUT+, IN−/IN+) | — | Préstamo universidad | $0 | ~$2.290 |
| 8 | Placa perforada | 1 | Conexiones soldadas (bus de tierra) | — | Préstamo universidad | $0 | ~$1.500 `*` |
| 9 | Protoboard mini 170 puntos | 1 | Distribución de conexiones | 47 × 35 × 9,5 | Préstamo universidad | $0 | ~$1.500 `*` |
| 10 | Cable | — | Reutilizado de cables Dupont, cortado y soldado | — | Préstamo universidad | $0 | ~$1.000 `*` |

## Encapsulado

| # | Componente | Cant. | Especificación | Dimensiones | Origen | Costo real (CLP) | Precio referencial ESTIMADO (CLP) |
|---|------------|:-----:|----------------|-------------|--------|-----------------:|----------------------------------:|
| 11 | Plancha MDF | 2 | Espesor 5,5 mm, corte láser | 350 × 400 mm | Comprado | $3.580 | $3.580 |
| 12 | Tornillos autorroscantes | 4 | Para madera, fijación de la tapa | 3 × 16 mm | Disponible (no incluido en costos) | — | — |
| 13 | Adhesivo para madera | — | Unión de paredes y base. **Por definir** (referencia: cola fría 250 g) | — | Por comprar | — | ~$3.990 |

---

## Resumen de costos

| Categoría | Costo real (CLP) | Precio referencial ESTIMADO (CLP) |
|-----------|-----------------:|----------------------------------:|
| Electrónica | $0 | ~$34.590 |
| Encapsulado | $3.580 | ~$7.570 |
| **Total** | **$3.580** | **~$42.160** |

> - **Costo real del prototipo: $3.580.** Los componentes electrónicos fueron facilitados por la universidad
>   y solo se compraron las planchas de MDF.
> - **Costo ESTIMADO de fabricar una unidad: ~$42.160.** Es una aproximación con precios de mercado
>   minoristas por unidad; al comprar por volumen el costo sería menor.
> - Los tornillos no se consideran porque el equipo ya los tenía.
> - El adhesivo del encapsulado aún no está definido; su valor es solo referencial.

## Referencias de precios (consultadas en octubre 2026)

| Componente | Fuente |
|------------|--------|
| ESP32-S3 Mini | [MercadoLibre Chile](https://listado.mercadolibre.cl/esp-32) |
| Sensor MQ-7 | [MechatronicStore](https://www.mechatronicstore.cl/sensor-gas-monoxido-mq7/) · [Altronics](https://altronics.cl/sensor-co-mq7) |
| TP4056 micro-USB con protección | [Makers Chile](https://makerschile.cl/producto/cargador-bateria-tp4056-micro-usb/) |
| Cola fría 250 g | [Easy](https://www.easy.cl/cola-fria-250-gr-multiuso-con-pincel-1080326/p) |
| Valores con `*` | Aproximados desde precios internacionales; sin referencia directa en Chile |
