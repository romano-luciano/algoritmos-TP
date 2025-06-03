
# Casos de prueba

| **#** | **Descripción** | **Salida esperada** | **Salida obtenida** |
|:--:|------------------|----------------------|----------------------|
| 1 | Se quiere probar qué es lo que pasaría si se vacía el mazo y se debe barajar el descarte. | Se espera que las cartas descartadas se mezclen y se forme un nuevo mazo. | La salida obtenida fue que el mazo se regeneró y el juego continuó normalmente. |
| 2 | Se quiere probar qué es lo que pasaría si un jugador intenta bajar de 0 puntos. | Se espera que el puntaje mínimo permanezca en 0. | La salida obtenida fue que el jugador se mantuvo en 0 puntos. |
| 3 | Se quiere probar qué el jugador reciba 3 cartas al iniciar. | Se espera que el jugador tenga 3 cartas al comenzar la partida. | La salida obtenida fue que el jugador recibió correctamente sus 3 cartas. |
| 4 | Se quiere probar qué es lo que pasaría si se juega una carta. | Se espera que el efecto se aplique (si corresponde) y se robe una nueva carta. | La salida obtenida fue que se aplicó el efecto y se robó otra carta. |
| 5 | Se quiere probar qué es lo que pasaría al finalizar una partida. | Se espera que se genere un archivo de informe con nombre `informe-juego_YYYY-MM-DD-HH-mm.txt`. | La salida obtenida fue que el archivo fue generado correctamente. |
| 6 | Se quiere probar qué es lo que pasaría si el jugador utiliza una carta “Repetir turno”. | Se espera que el jugador juegue inmediatamente otro turno. | La salida obtenida fue que el jugador pudo realizar dos jugadas consecutivas. |
| 7 | Se quiere probar qué es lo que pasaría si se envía un resultado de la partiada a la API. | Se espera que el resultado se registre correctamente. | La partida fue registrada correctamente |
| 8 | Se quiere probar qué es lo que pasaría si se usa la opción “Ver ranking”. | Se espera que se muestren los jugadores y sus victorias desde la API. | La salida obtenida fue que se consultó correctamente el endpoint