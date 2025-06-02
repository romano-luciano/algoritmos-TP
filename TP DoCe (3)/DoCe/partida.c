#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "Funciones.h"
#include "pilaDinamica.h"

void partida(int dific, FILE *informe)
{
    int tInic; /// si tInic = 1 es el usuario , 0 = es la IA
    int elec, puntajeUs = 0, puntajeIA = 0, vSacar, numElecIA, numElecUs, ronda = 1, descarte = -1;
    int *manoUs = (int *)malloc(3 * sizeof(int));
    int *manoIA = (int *)malloc(3 * sizeof(int));
    if (!manoUs || !manoIA)
    {
        free(manoUs);
        free(manoIA);
        printf("Error al reservar memoria");
        exit(ERR_MEM);
    }
    char frase[FRASE];
    tPila pilaA, pilaB;
    crearPila(&pilaA);
    crearPila(&pilaB);
    printf("Preparados...\nSe eligira al azar quien comienza!...\n");
    system("pause");
    srand(time(NULL));
    tInic = rand() % 2;
    if (tInic)
    {
        printf("Empiezas tu!!\n");
    }
    else
        printf("Empieza tu oponente!!\n");
    system("pause");
    system("cls");
    /// implemetar el maso=40 un vector que contenga los elementos en forma cartas, seran 40 elementos, y se deben mezclar aleatoriamente
    /// 0 = +2 puntos  1 = +1 punto  2 = -1 punto op  3 = -2 puntos op  4 = repetir turno 5 = espejo
    int vec[MAZO] = {0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 2, 2, 2, 3, 3, 3, 3, 3, 3, 4, 4, 4, 4, 4, 4, 5, 5, 5, 5};
    /// se mezcla el vector
    // ordenarPorBurbujeo(vec,MAZO,sizeof(int),intRandom);
    mezclar(vec, MAZO, sizeof(int));
    imprimirEnteros(vec, MAZO); /// PRUEBA
    system("pause");
    /// se mete todo el mazo a la pila
    for (int i = 0; i < MAZO; i++)
    {
        apilar(&pilaA, vec + i, sizeof(int));
    }
    /// repartir las primeras 3 cartas
    for (int i = 0; i < 3; i++)
    {
        desapilar(&pilaA, manoUs + i, sizeof(int));
        desapilar(&pilaA, manoIA + i, sizeof(int));
    }
    /// RONDA
    while (ronda)
    {
        ronda = 0;
        while (!pilaVacia(&pilaA) && puntajeUs < 12 && puntajeIA < 12)
        {
            /// COMIENZA EL QUE FUE ELEGIDO
            vSacar = 1;
            if (tInic)
            {

                /// JUGADA DE USUARIO
                while (vSacar)
                {
                    vSacar = 0;
                    do
                    {
                        system("cls");
                        printf("//////////////////////////////\n");
                        printf("PUNTAJES. USUARIO: %d  IA: %d\n", puntajeUs, puntajeIA);
                        if (descarte >= 0 && descarte <= 5) //Es necesaria?? Descarte va a estar siempre entre 0 y 5
                            printf("Ultima carta descartada: %s\n", numAfrase(descarte, frase));
                        printf("TU TURNO. Tienes las siguientes cartas:\n");
                        printf("[1] %s\n", numAfrase(*(manoUs + 0), frase));
                        printf("[2] %s\n", numAfrase(*(manoUs + 1), frase));
                        printf("[3] %s\n", numAfrase(*(manoUs + 2), frase));
                        printf("Cual quiere jugar?:\n");
                        scanf("%d", &elec);
                    } while (elec < 1 || elec > 3);

                    numElecUs = *(manoUs + elec - 1); /// numElecUs es el numero tipo de carta. elec es el subindice []
                    fprintf(informe, "---------------\nPUNTAJES. USUARIO: %d  IA: %d\nUSUARIO juega = %s\n", puntajeUs, puntajeIA, numAfrase(numElecUs, frase));
                    jugada(&puntajeUs, &puntajeIA, numElecUs, numElecIA, &vSacar);
                    apilar(&pilaB, &numElecUs, sizeof(int));
                    descarte = numElecUs;
                    desapilar(&pilaA, manoUs + elec - 1, sizeof(int));
                    printf("Has recibido la carta: %s\n", numAfrase(*(manoUs + elec - 1), frase));
                    system("pause");
                    system("cls");
                }
                tInic = 0; /// 0 es para juegue la IA
            }
            else
            {
                /// JUGADA DE IA
                while (vSacar)
                {
                    vSacar = 0;
                    printf("//////////////////////////////\n");
                    printf("PUNTAJES. USUARIO: %d  IA: %d\n", puntajeUs, puntajeIA);
                    if (descarte >= 0 && descarte <= 5)
                        printf("Ultima carta descartada: %s\n", numAfrase(descarte, frase));
                    /// TESTEO
                    printf("TURNO DE IA. Las cartas de la IA\n");
                    printf("* %s\n", numAfrase(*(manoIA + 0), frase));
                    printf("* %s\n", numAfrase(*(manoIA + 1), frase));
                    printf("* %s\n", numAfrase(*(manoIA + 2), frase));
                    /// se selecciona al azar por ser FACIL
                    switch (dific)
                    {
                    case 1:
                        facil(puntajeUs, puntajeIA, descarte, manoIA, &elec); //[1][2][3]
                        break;
                    case 2:
                        medio(puntajeUs, puntajeIA, descarte, manoIA, &elec);
                        break;
                    case 3:
                        dificil(puntajeUs, puntajeIA, descarte, manoIA, &elec);
                        break;
                    }
                    numElecIA = *(manoIA + elec);
                    fprintf(informe, "---------------\nPUNTAJES. USUARIO: %d  IA: %d\nIA juega = %s\n", puntajeUs, puntajeIA, numAfrase(numElecIA, frase));
                    jugada(&puntajeIA, &puntajeUs, numElecIA, numElecUs, &vSacar);
                    apilar(&pilaB, &numElecIA, sizeof(int));
                    descarte = numElecIA;
                    desapilar(&pilaA, manoIA + elec, sizeof(int));
                    printf("IA a recibido la carta: %s\n", numAfrase(*(manoIA + elec), frase));
                    system("pause");
                    system("cls");
                }
                tInic = 1; /// 1 es el usuario
            }
        }
        if (pilaVacia(&pilaA))
        {
            /// se junta toda la pila B, manda al vector se mezcla y se manda a la pila A
            printf("Nadie ha ganado. Se juntara todo el descarte y se mezclara para una nueva ronda. \n");
            system("cls");
            for (int i = 0; i < MAZO - 6; i++)
            {
                desapilar(&pilaB, &vec[i], sizeof(int));
            }
            mezclar(vec, MAZO - 6, sizeof(int));
            for (int i = 0; i < MAZO; i++)
            {
                apilar(&pilaA, &vec[i], sizeof(int));
            }
            ronda = 1;
        }
        else if ((pilaVacia(&pilaA) && puntajeUs >= 12) || puntajeUs >= 12)
        {
            /// GANADOR USUARIO
            printf("Has ganado!\n");
            fprintf(informe, "***********\nEl USUARIO ha ganado!");
        }
        else if ((pilaVacia(&pilaA) && puntajeIA >= 12) || puntajeIA >= 12)
        {
            /// GANADOR IA
            printf("La IA ha ganado!\n");
            fprintf(informe, "***********\nLa IA ha ganado!");
        }
    }
    vaciarPila(&pilaA);
    vaciarPila(&pilaB);
    free(manoUs);
    free(manoIA);
}
