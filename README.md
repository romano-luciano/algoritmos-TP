
# Cómo jugar DoCe

## Objetivo del juego
El objetivo de DoCe es ser el primer jugador en alcanzar **12 puntos** mediante el uso estratégico de cartas con distintos efectos.

---

## Inicio del juego
1. **Menú principal**:  
   Al iniciar el programa, aparecerán 3 opciones:  
   - `[A] Jugar`: Inicia una nueva partida.  
   - `[B] Ver ranking`: Muestra el historial de partidas ganadas por jugador.  
   - `[C] Salir`: Cierra el juego.  

2. **Configuración inicial**:  
   - Si seleccionas `[A] Jugar`, se te pedirá:  
     - **Nombre del jugador**: Ingresa tu nombre.  
     - **Dificultad de la IA**: Elige entre:  
       - *Fácil*: La máquina juega cartas al azar.  
       - *Medio*: La máquina evita jugadas inefectivas (ej: no resta puntos si el rival tiene 0).  
       - *Difícil*: La máquina elige la mejor jugada posible (usa estrategias avanzadas).  

---

## Desarrollo del juego
- **Cartas iniciales**:  
  - Tú y la máquina recibirán **3 cartas cada uno** al inicio.  
  - El orden del primer turno se decide aleatoriamente.  

- **Mazo de cartas**:  
  - Total: 40 cartas distribuidas así:  
    - `+2 puntos` (6 cartas)  
    - `+1 punto` (10 cartas)  
    - `-1 punto al oponente` (8 cartas)  
    - `-2 puntos al oponente` (6 cartas)  
    - `Repetir turno` (6 cartas)  
    - `Espejo` (4 cartas): Anula un efecto negativo y lo devuelve.  

- **Turnos**:  
  1. **Juega una carta**: Selecciona una de tus cartas para activar su efecto.  
  2. **Roba una carta**: Al finalizar tu turno, tomas una nueva carta del mazo. 


- **Efectos especiales**:  
  - **Repetir turno**: Juega otro turno inmediatamente.  
  - **Espejo**: Úsala cuando recibas una carta negativa para anularla y devolver el efecto.  

---

## Fin del juego
- **Victoria**: El primer jugador en alcanzar **12 puntos** gana.  
- **Informe**: Al terminar, se genera un archivo con los detalles de la partida (jugadas, puntos, ganador) en formato:  
  `informe-juego_AAAA-MM-DD-HH-MM.txt`.  
- **Ranking**: El resultado se envía a una API para actualizar el historial de partidas ganadas.  

---

## Reglas clave
- **Puntos negativos**: Ningún jugador puede tener menos de 0 puntos.  
- **Estrategia de la IA**:  
  - *Fácil*: Aleatoria.  
  - *Medio*: Evita restar puntos si el rival tiene 0.  
  - *Difícil*: Prioriza cartas de "repetir turno" o "restar puntos" si estás cerca de ganar.  

