
# Estrategias

## Nivel fácil
El algoritmo se basa en tomar decisiones completamente al azar. Simplemente genera un número aleatorio entre 0 y 2 para seleccionar una carta.  
No considera:  
1. El puntaje del jugador  
2. Su propio puntaje  
3. La última carta jugada  
4. Las cartas específicas que tiene en su mano  

## Nivel medio
El nivel medio tiene una lógica más avanzada que considera:  
1. Si la IA tiene 8 o más puntos, prioriza cartas que sumen puntos.  
2. Si el jugador tiene 0 puntos, evita tirar cartas que resten puntos.

### Estrategia:
1. **Priorizar sumar puntos cuando IA tiene 8+ puntos:**  
    * Busca cartas `MAS_DOS_PUNTOS` o `MAS_UN_PUNTO` en su mano; si encuentra alguna, la juega inmediatamente.  
2. **Manejo cuando el jugador tiene 0 puntos:**  
    * Evita jugar cartas que resten puntos (`RESTAR_DOS_PUNTOS`, `RESTAR_UN_PUNTO`).  
    * Cuenta cuántas cartas no restadoras tiene.  
    * Maneja varios escenarios:  
      * Si todas son cartas negativas, elige al azar.  
      * Si hay espejos, los prioriza en ciertas situaciones.  
      * Selecciona cuidadosamente qué carta jugar para no beneficiar al jugador.  
3. **Situación normal:**  
    * Si la última carta fue restadora, elige al azar.  
    * Si no, evita jugar el espejo.  
    * Selecciona la primera carta no espejo que encuentre.  

## Nivel difícil
El nivel difícil implementa una estrategia que considera múltiples factores para tomar decisiones óptimas.

### Estrategia:
1. **Cuando el jugador tiene 8+ puntos:**  
    * Prioriza cartas que reduzcan los puntos del jugador.  
    * También considera `REPETIR_TURNO` como opción valiosa.  
2. **Cuando la IA está cerca de ganar (>= 10 puntos):**  
    * Busca cartas que sumen puntos.  
    * Prefiere `MAS_DOS_PUNTOS` si está disponible para ganar más rápido.  
3. **Defensa contra cartas negativas:**  
    * Si la última carta jugada fue negativa, busca y juega un `ESPEJO` si tiene uno para revertir el efecto.  
4. **Gestión de cartas positivas:**  
    * Cuenta cuántas cartas positivas tiene; si tiene más de una carta buena, busca `REPETIR_TURNO` para poder jugar dos veces.  
5. **Casos especiales:**  
    * Selección de la mejor carta para restar puntos cuando el jugador tiene puntos.  
    * Priorizar `MAS_DOS_PUNTOS` sobre `MAS_UN_PUNTO`.  
