#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "Funciones.h"
#include "pilaDinamica.h"

void jugada(int *activo, int *pasivo, int elecActivo, int elecPasivo, int *vSacar, int *descarteAnterior) /// ACTIVO es el puntaje del que esta jugando
/// PASIVO es el puntaje del oponente
/// elecActivo es la carta elegida del q esta jugando
/// elecPasivo es la carta que descarto el oponente y estas viendo
/// vSacar viene de repetir de turno
{
    switch (elecActivo)
    {
    case MAS_DOS_PUNTOS:
        *activo += 2;
        setColor(10); //verde claro
        printf("Elegido: +2 puntos!\n");
        break;
    case MAS_UN_PUNTO:
        *activo += 1;
        setColor(10);
        printf("E1egido: +1 punto!\n");
        break;
    case RESTAR_UN_PUNTO:
        /// codicion de no tener puntaje negativo al que recibe el ataque
        if (*pasivo - 1 < 0)
            *pasivo = 0;
        else
            *pasivo -= 1;
        setColor(12);
        printf("Elegido: -1 punto al oponente!\n");
        break;
    case RESTAR_DOS_PUNTOS:
        /// codicion de no tener puntaje negativo al que recibe el ataque
        if (*pasivo - 2 < 0)
            *pasivo = 0;
        else
            *pasivo -= 2;
        setColor(12);
        printf("Elegido: -2 puntos al oponente!\n");
        break;
    case REPETIR_TURNO:
        setColor(13); //magenta claro
        printf("Elegido: Repetir el turno!\n");
        *descarteAnterior = elecPasivo; //guardo el descarte anterior
        *vSacar = 1;
        break;
    case ESPEJO:
        setColor(11); //cian claro
        printf("Elegido: Espejo!\n");
        setColor(15);
        ///
        if (*vSacar)
        {
            printf("Jugada no valida: no se puede tirar espejo despues de repetir turno!\n");
        }
        else
        {
            if (elecPasivo == 2) /// 2 -1 al oponente
            {
                printf("El espejo surtio efecto y se ha devuelto: 1 punto, y restado 1 punto al oponente!\n");
                *activo += 1;
                if (*pasivo - 1 < 0)
                    *pasivo = 0;
                else
                    *pasivo -= 1;
            }
            else if (elecPasivo == 3) /// 3 -2 al oponente
            {
                printf("El espejo surtio efecto y se ha devuelto: 2 puntos, y restado 2 puntos al oponente!\n");
                *activo += 2;
                if (*pasivo - 2 < 0)
                    *pasivo = 0;
                else
                    *pasivo -= 2;
            }
            else
                printf("El espejo no surtio efecto!\n");
        }
        break;
    }
    setColor(15);
}
