# Registro de Testing con Usuarios · COStop

**Curso:** TEI201 · Taller de Diseño en Ingeniería · UAI
**Grupo 5:** Benjamin Bidegain · Martin Flores · Vicente Pincheira · Thomas von Fabeck
**Prototipo evaluado:** COStop v3 (versión final)
**Fecha de aplicación:** 22/11/2026
**Muestra:** 4 participantes (familiares y compañeros de hogar), de 22 a 55 años

> **Nota sobre la muestra:** la pauta del curso (`testing/README.md`) pide un mínimo de 5 usuarios, y ningún participante pertenece al grupo objetivo principal del proyecto (adultos mayores). Ambas cosas se declaran como limitaciones en el reporte.

---

## 1. Matriz general de registro (por participante)

| ID | Perfil / Edad | P1. Interpretación de los 4 colores (sin ayuda) | P2. Silenció el buzzer sin ayuda | P3. Tiempo en silenciar (s) | P4. Acción ante la alerta de Telegram | P5a. Facilidad (1–5) | P5b. Confianza (1–5) | P5c. Comentario textual |
| :--- | :--- | :--- | :---: | :---: | :--- | :---: | :---: | :--- |
| **P1** | Hermano (24 años) | **Sí (4/4)**: azul cargando, verde bien, amarillo alerta, rojo peligro | Sí | 5,2 | Llamar a quien esté en la casa y pedir que apaguen la estufa y abran puertas y ventanas | 5 | 4 | *"El botón se encuentra rápido y suena súper fuerte; le pondría un dibujito al lado para que sea más obvio."* |
| **P2** | Madre (52 años) | **No (3/4)**: interpretó el azul como "buscando señal WiFi"; acertó verde, amarillo y rojo | Sí | 8,4 | Llamar de inmediato a la persona en casa y, si no responde, llamar a un vecino con llave | 4 | 4 | *"Al principio dudé entre azul y verde, pero el sonido y el rojo se entienden al tiro; saber que avisa por Telegram da tranquilidad si uno no está."* |
| **P3** | Roommate (22 años) | **Sí (4/4)**: asoció el azul a inicio o calentamiento y el resto como semáforo | Sí | 6,1 | Llamar al compañero que esté en el departamento y confirmar por WhatsApp o Telegram que ventilaron | 5 | 5 | *"Me gustó que la luz roja siga prendida después de callar el ruido, así uno no se olvida de que sigue el gas."* |
| **P4** | Padre (55 años) | **Sí (4/4)**: entendió el azul como espera y los otros tres colores de inmediato | Sí | 7,5 | Contactar a la familia en casa para que salgan al patio y, si está cerca, ir personalmente | 4 | 4 | *"Muy práctico para una casa con estufa a parafina; ojalá tuviera una etiqueta chica explicando los colores."* |
| **Resumen** | **4 personas** | **3 de 4 (75 %)** interpretaron los 4 colores; verde, amarillo y rojo: 4 de 4 | **4 de 4** | **6,8 promedio** (5,2–8,4) | **4 de 4** declararon una acción inmediata y adecuada | **4,5** | **4,25** | — |

---

## 2. Desglose por pregunta

### Pregunta 1: Interpretación de los 4 colores (sin explicación previa)
*Objetivo: evaluar si el código de colores del LED RGB es intuitivo antes de explicar el sistema.*

| Participante | Azul intermitente (Calentamiento) | Verde fijo (Normal) | Amarillo fijo (Alerta) | Rojo fijo (Peligro) | ¿Interpretó bien los 4? |
| :--- | :--- | :--- | :--- | :--- | :---: |
| **P1** | "Está iniciando o cargando" (correcto) | "Aire normal / todo bien" (correcto) | "Precaución / nivel subiendo" (correcto) | "Peligro / salir o ventilar" (correcto) | **Sí** |
| **P2** | "Buscando señal WiFi" (**incorrecto**) | "Todo en orden" (correcto) | "Cuidado / revisar estufa" (correcto) | "Emergencia grave" (correcto) | **No** |
| **P3** | "Preparándose / calentando" (correcto) | "Seguro / sin gas" (correcto) | "Advertencia preventiva" (correcto) | "Alerta máxima / peligro" (correcto) | **Sí** |
| **P4** | "Esperando para medir" (correcto) | "Funcionando normal" (correcto) | "Hay que poner atención" (correcto) | "Peligro de intoxicación" (correcto) | **Sí** |
| **Acierto por color** | **3 de 4 (75 %)** | **4 de 4 (100 %)** | **4 de 4 (100 %)** | **4 de 4 (100 %)** | **3 de 4 (75 %)** |

### Preguntas 2 y 3: Reacción en peligro y tiempo para silenciar el buzzer sin ayuda
*Objetivo: medir qué tan fácil es encontrar y usar el pulsador bajo la alarma sonora.*

| Participante | ¿Logró silenciar sin ayuda? | Tiempo cronometrado | Comportamiento observado |
| :--- | :---: | :---: | :--- |
| **P1** | Sí | 5,2 s | Tomó la caja, vio el pulsador de inmediato y lo presionó firme. |
| **P2** | Sí | 8,4 s | Miró primero el LED frontal buscando si era táctil, luego giró la caja y apretó el botón. |
| **P3** | Sí | 6,1 s | Ubicó el botón rápido y verificó que el LED rojo siguiera encendido tras silenciar. |
| **P4** | Sí | 7,5 s | Presionó el botón y preguntó si la alarma volvía a sonar sola si seguía el gas. |
| **Total** | **4 de 4 (100 %)** | **Promedio 6,8 s · mediana 6,8 s · desv. est. 1,43 s** | **Rango: 5,2–8,4 s** |

### Pregunta 4: Comprensión y acción frente al mensaje de Telegram
*Objetivo: validar si la notificación remota lleva a una acción efectiva de prevención.*

| Participante | ¿Entendió la gravedad del mensaje? | Primera acción declarada | Segunda acción / respaldo |
| :--- | :---: | :--- | :--- |
| **P1** | Sí | Llamar por teléfono a quien esté dentro de la casa. | Pedir que apaguen la estufa y abran puertas y ventanas. |
| **P2** | Sí | Llamar de inmediato a la persona en casa. | Si no responde, llamar a un vecino con llave para que entre. |
| **P3** | Sí | Llamar al compañero que esté en el departamento. | Avisar por WhatsApp o Telegram para confirmar que ventilaron. |
| **P4** | Sí | Contactar a la familia en casa para que salgan al patio. | Ir personalmente si está cerca del domicilio. |
| **Total** | **4 de 4 (100 %)** | | |

### Pregunta 5: Evaluación cuantitativa (escala 1 a 5) y comentarios
*Objetivo: medir la percepción de facilidad de uso y la confianza en el dispositivo.*

| Participante | Facilidad de uso (1 a 5) | Confianza en la alarma (1 a 5) | Comentario textual registrado |
| :--- | :---: | :---: | :--- |
| **P1** | 5 | 4 | *"El botón se encuentra rápido y suena súper fuerte; le pondría un dibujito al lado para que sea más obvio."* |
| **P2** | 4 | 4 | *"Al principio dudé entre azul y verde, pero el sonido y el rojo se entienden al tiro; saber que avisa por Telegram da tranquilidad si uno no está."* |
| **P3** | 5 | 5 | *"Me gustó que la luz roja siga prendida después de callar el ruido, así uno no se olvida de que sigue el gas."* |
| **P4** | 4 | 4 | *"Muy práctico para una casa con estufa a parafina; ojalá tuviera una etiqueta chica explicando los colores."* |
| **Promedio** | **4,5 / 5** (desv. est. 0,58) | **4,25 / 5** (desv. est. 0,50) | — |

---

## 3. Pendientes de evidencia (según `testing/evidencias/README.md`)

- [ ] Consentimiento informado de cada participante.
- [ ] Al menos 1 foto por participante, con el rostro difuminado si no autorizó mostrarlo.
- [ ] Idealmente, 1 participante más (para llegar al mínimo de 5), de preferencia un adulto mayor.
