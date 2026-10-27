# Justificación de las Decisiones de Diseño – Encapsulado COStop

Este documento explica por que se tomó cada decisión de diseño del encapsulado. Las dimensiones y detalles salen del plano técnico (`planos/`) y del BOM (`hardware/bom/README.md`).

## Requisitos de partida

- Alojar todos los componentes del prototipo: ESP32-S3 Super Mini, sensor MQ-7, DHT11, LED RGB KY-016, buzzer, batería LiPo, módulo TP4056 y placa de conexiones.
- Dejar que el aire (y el gas) llegue a los sensores.
- Permitir ver el LED, escuchar el buzzer y cargar la batería sin abrir la caja.
- Ser barata y fácil de fabricar en la universidad, y permitir abrirla para mantenimiento.

## Decisiones de diseño

- Decisión - Qué se hizo - Justificación 

-Material - MDF de 5,5 mm - Material económico (costo real del prototipo: $3.580), fácil de cortar con láser y suficientemente rígido para proteger la electrónica.  

- Método de fabricación - Corte láser - Da precisión en los cortes y permite uniones y ventanas pequeñas. 

- Dimensiones - 182 × 82 × 62 mm - Espacio interior aproximado de 171 × 71 × 51 mm (descontando la pared de 5,5 mm), suficiente para los componentes del BOM, el más largo de ellos es la batería de 50 mm. 

- Uniones - Ensamble tipo "dedos" entre paredes - Une las piezas planas cortadas a láser sin piezas adicionales y deja la caja rígida. 

- Ranuras de ventilación - 3 ranuras alargadas en el lateral largo - Evitar el sobrecalentamiento y dañar los componentes, y que el DHT no de lecturas erroneas por la temperatura dentro de la caja, Las ranuras seran cubiertas por una rejilla con material **POR DEFINIR**

- Ventana del DHT11 - Abertura de 16 × 12,7 mm en el lateral derecho - El DHT11 mide temperatura y humedad del ambiente, por lo que necesita estar expuesto al aire. 

- Ventana micro-USB - Abertura de 8,5 × 3,8 mm en la parte posterior - Deja accesible el conector del TP4056 para cargar la batería sin abrir la caja. 

- Agujero del LED - Ø5 mm en la tapa - Coincide con el LED de 5 mm del KY-016; en la tapa el estado se ve desde arriba. 

- Agujero del buzzer - Ø7 mm en la tapa - Permite que el sonido salga. Con la caja cerrada el sonido se apagaría. 

- Agujero frontal - Ø17 mm en el extremo - MQ-7, el sensor toma muestras del ambiente y **NO** del interior de la caja

- Tapa con 4 tornillos - 4 agujeros Ø9 en las esquinas de la tapa - La tapa se fija con 4 tornillos autorroscantes de 3 × 16 mm y se puede abrir para mantenimiento o cambio de batería. 

- Nombre grabado - "CoStop" en el frente - Identifica nuestro producto. 

## Puntos pendientes de diseño

- **Botón de silencio:** el firmware lo usa para silenciar el buzzer, pero el plano no muestra una abertura para un pulsador. Hay que agregarla o explicar cómo se accede.
- **Escritura del nombre:** el grabado dice "CoStop"; el nombre del proyecto es "COStop".
- **Tolerancias:** agujeros ±0,1 mm; encajes +0,2/0 mm no deberia ser un problema con el corte laser.
