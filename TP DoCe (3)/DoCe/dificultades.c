#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "Funciones.h"
#include "pilaDinamica.h"

void facil(int pJugador, int pIA, int ultimaCarta, int *manoIA, int *elec)
{
    *elec = rand() % 3; /// la IA elige al azar[0][1][2]
}

void medio(int pJugador, int pIA, int ultimaCarta, int *manoIA, int *elec) /// pJugador = puntaje jugador, pIA = puntaje IA, ultimacarta = descarte, manoIA = la mano de la IA, elec = eleccion de IA
{
    int bandSumarPuntos = 0, bandPuntajeJugadorEs0 = 0, indiceEspejo, cantEspejos = 0;

    if (pIA >= 8) // si tiene mas de 8 puntos prioriza cartas que sumen
    {
        for (int i = 0; i < 3; i++)
        {
            if (*(manoIA + i) == MAS_DOS_PUNTOS || *(manoIA + i) == MAS_UN_PUNTO)
            {
                bandSumarPuntos = 1;
                *elec = i;
                break;
            }
        }
    }
    else
    {
        if (pJugador == 0) // pregunta si el usuario tiene 0 puntos para no tirar carta negativa
        {
            bandPuntajeJugadorEs0 = 1;
            int cantNoRestadoras = 0;

            for (int i = 0; i < 3; i++) // recorre toda la mano
            {
                if (*(manoIA + i) != RESTAR_DOS_PUNTOS && *(manoIA + i) != RESTAR_UN_PUNTO)
                {
                    if (*(manoIA + i) == ESPEJO) // cuenta la cantidad de espejos
                    {
                        cantEspejos++;
                        indiceEspejo = i; // guardo el indice del espejo
                    }
                    cantNoRestadoras++; // cuenta la cartas no restadoras
                }
            }
            if (cantNoRestadoras == 3) // no hay restadores
            {
                if (ultimaCarta == RESTAR_DOS_PUNTOS || ultimaCarta == RESTAR_UN_PUNTO)
                {
                    *elec = rand() % 3; // si le tirar un restar que tire cualquiera, no si o si debe tirar espejo
                }
                else // sino le tiraron restar debe tirar cualquiera menos espejo, ya que seria una jugada inefectiva
                {
                    for (int i = 0; i < 3; i++)
                    {
                        if (*(manoIA + i) != ESPEJO)
                        {
                            *elec = i;
                            break;
                        }
                    }
                }
            }
            else if (cantNoRestadoras == 0) // toda la mano son restadores, elige cualquiera
                *elec = rand() % 3;
            else // hay 1 o 2 restadores, debe elegir la sobrante
            {
                if (cantEspejos == 2 || (cantNoRestadoras == 1 && cantEspejos == 1)) // valida si hay dos restadoras y un espejo o si hay 2 espejos y una restadora, si cumple debe tirar espejo si o si ya que no debe tirar carta restadora cuando el oponente tiene 0 puntos
                {
                    *elec = indiceEspejo;
                }
                else // dentro de este else ya se valido que no haya 2 espejos, ni 2 restadoras con un espejo
                {
                    for (int i = 0; i < 3; i++)
                    {
                        if (cantNoRestadoras == 1) // si hay 2 restadoras tirar la primera no restadora que encuentre
                        {
                            if (*(manoIA + i) != RESTAR_DOS_PUNTOS && *(manoIA + i) != RESTAR_UN_PUNTO)
                            {
                                *elec = i;
                                break; // cortamos el ciclo
                            }
                        }
                        else if (cantEspejos == 1) //si hay un espejo 
                        {
                            if (ultimaCarta == RESTAR_DOS_PUNTOS || ultimaCarta == RESTAR_UN_PUNTO) //tiraron una carta restadora
                            {
                                if (*(manoIA + i) != RESTAR_DOS_PUNTOS && *(manoIA + i) != RESTAR_UN_PUNTO) //si no es restadora la tira
                                {
                                    *elec = i;
                                    break; // cortamos el ciclo
                                }
                            }
                            else //si no tiraron carta restadora no debe tirar el espejo ni restadora
                            {
                                if (*(manoIA + i) != ESPEJO && (*(manoIA + i) != RESTAR_DOS_PUNTOS && *(manoIA + i) != RESTAR_UN_PUNTO))
                                {
                                    *elec = i;
                                    break;
                                }
                            }
                        }
                        else if (*(manoIA + i) != RESTAR_DOS_PUNTOS && *(manoIA + i) != RESTAR_UN_PUNTO) //tiene dos cartas cualquiera y una restadora 
                        {
                            *elec = i;
                            break;
                        }
                    }
                }
            }
        }
    }

    if (!bandPuntajeJugadorEs0 && !bandSumarPuntos) // estamos en una situacion de que no tiene que priorizar nada, puede elegir random
    {
        if (ultimaCarta == RESTAR_DOS_PUNTOS || ultimaCarta == RESTAR_UN_PUNTO)
        {
            *elec = rand() % 3; // si le tirar un restar que tire cualquiera, no si o si debe tirar espejo
        }
        else // sino le tiraron restar debe tirar cualquiera menos espejo, ya que seria una jugada inefectiva
        {
            for (int i = 0; i < 3; i++)
            {
                if (*(manoIA + i) != ESPEJO)
                {
                    *elec = i;
                    break;
                }
            }
        }
    }

    // int band = 0, j = 0, random;
    // int *aux = (int *)malloc(3 * sizeof(int)); /// aux = manoAux
    // if (!aux)
    // {
    //     printf("Error al reservar memoria!");
    //     exit(ERR_MEM);
    // }
    // if (!pJugador) /// si el USUARIO tiene 0 puntos
    // {
    //     for (int i = 0; i < 3; i++)
    //     {
    //         if (*(manoIA + i) == MAS_DOS_PUNTOS || *(manoIA + i) == MAS_UN_PUNTO || *(manoIA + i) == REPETIR_TURNO || *(manoIA + i) == ESPEJO) /// la IA evita las cartas de sacar puntos.
    //         {
    //             *(aux + j) = *(manoIA + i); /// copio en un auxiliar las cartas que no son 2 y 3
    //             j++;
    //         }
    //     }
    // }
    // else
    // {
    //     memcpy(aux, manoIA, sizeof(*manoIA));
    //     j = 3;
    // }
    // if (!j) /// si todas las cartas son de sacar puntos copio toda la mano
    // {
    //     memcpy(aux, manoIA, sizeof(*manoIA));
    //     j = 3;
    // }

    // if (pIA >= 8) /// si el puntaje de la IA es mayor o igual a 8
    // {
    //     for (int i = 0; i < j; i++)
    //     {
    //         if (*(aux + i) == MAS_DOS_PUNTOS || *(aux + i) == MAS_UN_PUNTO) /// la IA prioriza las cartas de aumentase puntos.
    //         {
    //             *elec = i;
    //             band = 1;
    //             break;
    //         } /// recorro toda la mano hasta encontrar
    //     }
    // }
    // else /// si el puntaje de IA es menor a 8 elige al azar
    // {
    //     random = rand() % j;
    //     *elec = random;
    // }
    // if (!band) /// sino tiene cartas de aumentarse puntos. elige al azar
    // {
    //     random = rand() % j;
    //     *elec = random;
    // }
    // free(aux);
}

void dificil(int pJugador, int pIA, int ultimaCarta, int *manoIA, int *elec) /// me retorna la posicion en la mano
{
    int bandPuntos = 0, bandEspejo = 0, cartaBuena = 0, bandRepetir = 0, cartaRestadora = 0, contRepetirTurno = 0;
    if (pJugador >= 8) /// si el jugador tiene 8 o mas puntos, IA prioriza cartas restar y repetir
    {
        for (int i = 0; i < 3; i++) /// recorre toda la mano hasta encontrar cartas de sumarse puntos o repetir turno
        {
            if (*(manoIA + i) == RESTAR_UN_PUNTO || *(manoIA + i) == RESTAR_DOS_PUNTOS || *(manoIA + i) == REPETIR_TURNO) /// la IA prioriza las cartas de sacar puntos o repetir turno.
            {
                bandPuntos = 1;                                                           // bandera para tirar si o si alguna de esas 3 cartas
                if (*(manoIA + i) == RESTAR_DOS_PUNTOS || *(manoIA + i) == REPETIR_TURNO) // priorizo la carta restadora mas alta o repetir el turno. Si es la elige y listo
                {
                    *elec = i;
                    break;
                }
                else
                {
                    *elec = i; // es -1 y la guarda
                }
            }
        }
    }
    else if (pIA >= 10) // prioriza ganar cuando llega a 10 puntos y busca la carta sumadora mas alta
    {
        for (int i = 0; i < 3; i++)
        {
            if (*(manoIA + i) == MAS_DOS_PUNTOS || *(manoIA + i) == MAS_UN_PUNTO) // encontro una carta sumadora
            {
                cartaBuena = 1;                      // bandera de que encontro carta buena
                if (*(manoIA + i) == MAS_DOS_PUNTOS) // si es +2 que la tire y listo
                {
                    *elec = i;
                    break;
                }
                else
                    *elec = i; // sino va a ser +1 y la almacena
            }
        }
    }
    else if (ultimaCarta == RESTAR_DOS_PUNTOS || ultimaCarta == RESTAR_UN_PUNTO) /// Si le llego carta negativa busca un espejo
    {
        for (int i = 0; i < 3; i++) /// recorre toda la mano hasta encontrar espejo
        {
            if (*(manoIA + i) == ESPEJO) /// usa espejo si existe
            {
                *elec = i;
                bandEspejo = 1;
                break;
            }
        }
    }
    else /// Si no sucedio nada de lo anterior va a contar las cartas buenas y buscar si tiene "repetir turno"
    {
        for (int i = 0; i < 3; i++)
        {
            if (*(manoIA + i) == MAS_DOS_PUNTOS || *(manoIA + i) == MAS_UN_PUNTO) /// cuenta las cartas buenas
            {
                cartaBuena++;
            }
        }
    }
    if (cartaBuena > 1) /// Si tiene mas de 1 carta buena, busca si tiene carta "repetir turno"
    {
        for (int i = 0; i < 3; i++) /// recorre toda la mano hasta encontrar cartas de "repetir turno"
        {
            if (*(manoIA + i) == REPETIR_TURNO)
            {
                *elec = i;
                bandRepetir = 1;
                break;
            }
        }
    }
    if (!bandRepetir && !bandEspejo && !bandPuntos) /// Si no entro en la condicion de que encontro repetir turno en mas de una carta buena
    {                                               // y tampoco encontro espejo en un restador recibido. Entonces tiene solo restadoras o sumadoras (debe tirar la mejor)
        for (int i = 0; i < 3; i++)
        {
            // primero va a evaluar si tiene 2 repetir turno, los demas es el else
            if (*(manoIA + i) == REPETIR_TURNO)
            {
                contRepetirTurno++;
                if (contRepetirTurno == 2) // si hay 2 repetir turno en la baraja que elija uno
                {
                    *elec = i;
                    break;
                }
            }
            if (pJugador > 0) // si tiene mas de 1 que busque restadoras sino no hace falta
            {
                if (*(manoIA + i) == RESTAR_UN_PUNTO || *(manoIA + i) == RESTAR_DOS_PUNTOS) // encontro una carta restadora
                {
                    cartaRestadora = 1;
                    if (*(manoIA + i) == RESTAR_DOS_PUNTOS && pJugador >= 2) // si es -2 (negativa mas alta) y tiene 2 o mas puntos que la tire y listo
                    {
                        *elec = i;
                        break;
                    }
                    else if (*(manoIA + i) == RESTAR_UN_PUNTO)
                        *elec = i; // que asigne solo si es restar un punto porque sino asignaria un -2 aunque no haya entrado en la condicion anterior
                }
            }
            if (*(manoIA + i) == MAS_DOS_PUNTOS || *(manoIA + i) == MAS_UN_PUNTO) // encontro una carta sumadora
            {
                cartaBuena = 1;
                if (*(manoIA + i) == MAS_DOS_PUNTOS) // si es +2 que la tire y listo
                {
                    *elec = i;
                    break;
                }
                else
                    *elec = i; // sino va a ser +1 y la almacena
            }
        }
    }

    //situacion de tener dos espejos y un repetir o dos repetir y un espejo
    if (!cartaBuena && !cartaRestadora && !bandEspejo && !bandPuntos) // si esto pasa entonces tiene que tirar un repetir
    {
        for (int i = 0; i < 3; i++)
        {
            if (*(manoIA + i) == REPETIR_TURNO)
            {
                *elec = i;
                break;
            }
        }
    }
}
