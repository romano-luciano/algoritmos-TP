#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "Funciones.h"
#include "pilaDinamica.h"

char *numAfrase(int num, char *frase)
{
    switch (num)
    {
    case 0:
        strcpy(frase, "+2 puntos");
        break;
    case 1:
        strcpy(frase, "+1 punto");
        break;
    case 2:
        strcpy(frase, "-1 punto al oponente");
        break;
    case 3:
        strcpy(frase, "-2 puntos al oponente");
        break;
    case 4:
        strcpy(frase, "Repetir turno");
        break;
    case 5:
        strcpy(frase, "Espejo");
        break;
    }
    return frase;
}

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

void mezclar(void *vec, size_t nMemb, size_t tamElem) /// GENERICA
{
    for (size_t i = nMemb - 1; i > 0; i--) /// I=39
    {
        size_t j = rand() % (i + 1);  /// 40    NUMERO ALEATORIO ENTRE 0 Y 39
        void *temp = malloc(tamElem); /// CREO UN AUXILIAR
        if (!temp)
        {
            printf("Error al reservar memoria");
            exit(ERR_MEM);
        }
        memcpy(temp, (char *)vec + i * tamElem, tamElem);                      /// COPIO EL ELEMENTO 39 A TEMP
        memcpy((char *)vec + i * tamElem, (char *)vec + j * tamElem, tamElem); /// COPIO EL ELEMENTO ALEATORIO DEL VECTOR AL ELEMENTO 39
        memcpy((char *)vec + j * tamElem, temp, tamElem);                      /// COPIO EL TEMP A ELEMENTO ALEATORIO
        free(temp);
    }
}

void imprimirEnteros(int *vec, size_t nMemb)
{
    for (size_t i = 0; i < nMemb; i++)
    {
        printf("%d ", vec[i]);
    }
    printf("\n");
}

void jugada(int *activo, int *pasivo, int elecActivo, int elecPasivo, int *vSacar) /// ACTIVO es el puntaje del que esta jugando
/// PASIVO es el puntaje del oponente
/// elecActivo es la carta elegida del q esta jugando
/// elecPasivo es la carta que descarto el oponente y estas viendo
/// vSacar viene de repetir de turno
{
    switch (elecActivo)
    {
    case MAS_DOS_PUNTOS:
        *activo += 2;
        printf("Elegido: +2 puntos!\n");
        break;
    case MAS_UN_PUNTO:
        *activo += 1;
        printf("E1egido: +1 punto!\n");
        break;
    case RESTAR_UN_PUNTO:
        /// codicion de no tener puntaje negativo al que recibe el ataque
        if (*pasivo - 1 < 0)
            *pasivo = 0;
        else
            *pasivo -= 1;
        printf("Elegido: -1 punto al oponente!\n");
        break;
    case RESTAR_DOS_PUNTOS:
        /// codicion de no tener puntaje negativo al que recibe el ataque
        if (*pasivo - 2 < 0)
            *pasivo = 0;
        else
            *pasivo -= 2;
        printf("Elegido: -2 puntos al oponente!\n");
        break;
    case REPETIR_TURNO:
        printf("Elegido: Repetir el turno!\n");
        *vSacar = 1;
        break;
    case ESPEJO:
        printf("Elegido: Espejo!\n");
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
}

void facil(int pJugador, int pIA, int ultimaCarta, int *manoIA, int *elec)
{
    *elec = rand() % 3; /// la IA elige al azar[0][1][2]
}

void medio(int pJugador, int pIA, int ultimaCarta, int *manoIA, int *elec) /// pJugador = puntaje jugador, pIA = puntaje IA, ultimacarta = descarte, manoIA = la mano de la IA, elec = eleccion de IA
{
    int band = 0, j = 0, random;
    int *aux = (int *)malloc(3 * sizeof(int)); /// aux = manoAux
    if (!aux)
    {
        printf("Error al reservar memoria!");
        exit(ERR_MEM);
    }
    if (!pJugador) /// si el USUARIO tiene 0 puntos
    {
        for (int i = 0; i < 3; i++)
        {
            if (*(manoIA + i) == MAS_DOS_PUNTOS || *(manoIA + i) == MAS_UN_PUNTO || *(manoIA + i) == REPETIR_TURNO || *(manoIA + i) == ESPEJO) /// la IA evita las cartas de sacar puntos.
            {
                *(aux + j) = *(manoIA + i); /// copio en un auxiliar las cartas que no son 2 y 3
                j++;
            }
        }
    }
    else
    {
        memcpy(aux, manoIA, sizeof(*manoIA));
        j = 3;
    }
    if (!j) /// si todas las cartas son de sacar puntos copio toda la mano
    {
        memcpy(aux, manoIA, sizeof(*manoIA));
        j = 3;
    }

    if (pIA >= 8) /// si el puntaje de la IA es mayor o igual a 8
    {
        for (int i = 0; i < j; i++)
        {
            if (*(aux + i) == MAS_DOS_PUNTOS || *(aux + i) == MAS_UN_PUNTO) /// la IA prioriza las cartas de aumentase puntos.
            {
                *elec = i;
                band = 1;
                break;
            } /// recorro toda la mano hasta encontrar
        }
    }
    else /// si el puntaje de IA es menor a 8 elige al azar
    {
        random = rand() % j;
        *elec = random;
    }
    if (!band) /// sino tiene cartas de aumentarse puntos. elige al azar
    {
        random = rand() % j;
        *elec = random;
    }
    free(aux);
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
                bandPuntos = 1;                               // bandera para tirar si o si alguna de esas 3 cartas
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
    else if(pIA >= 10) //prioriza ganar cuando llega a 10 puntos y busca la carta sumadora mas alta
    {
        for(int i = 0; i < 3; i++)
        {
            if (*(manoIA + i) == MAS_DOS_PUNTOS || *(manoIA + i) == MAS_UN_PUNTO) // encontro una carta sumadora
            {
                cartaBuena = 1; //bandera de que encontro carta buena
                if (*(manoIA + i) == MAS_DOS_PUNTOS) // si es +2 que la tire y listo
                {
                    *elec = i;
                    break;
                }
                else *elec = i; // sino va a ser +1 y la almacena
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
    if (!bandRepetir && !bandEspejo && !bandPuntos) ///Si no entro en la condicion de que encontro repetir turno en mas de una carta buena
    {                                 //y tampoco encontro espejo en un restador recibido. Entonces tiene solo restadoras o sumadoras (debe tirar la mejor)
        for (int i = 0; i < 3; i++)
        {
            //primero va a evaluar si tiene 2 repetir turno, los demas es el else
            if(*(manoIA + i) == REPETIR_TURNO)
            {
                contRepetirTurno++;
                if(contRepetirTurno == 2) //si hay 2 repetir turno en la baraja que elija uno
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
                    else if(*(manoIA + i) == RESTAR_UN_PUNTO) *elec = i; // que asigne solo si es restar un punto porque sino asignaria un -2 aunque no haya entrado en la condicion anterior
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
                else *elec = i; // sino va a ser +1 y la almacena
            }
        }
    }

    if(!cartaBuena && !cartaRestadora && !bandEspejo) //si esto pasa entonces tiene que tirar un repetir o un espejo
    {
        for (int i = 0; i < 3; i++)
        {
            if(*(manoIA + i) == REPETIR_TURNO)
            {
                *elec = i;
                break;
            }
        }
    }


    // if (!bandPuntos) /// si no tiene -1, -2 o repetir turno. elige al azar
    // {
    //     random = rand() % 3;
    //     *elec = random;
    // }
    // if (!bandEspejo) /// sino tiene cartes de espejo. elige al azar
    // {
    //     random = rand() % 3;
    //     *elec = random;
    // }
}

void pruebaIA(void)
{
    int mano[3], ultimaCarta, pUsuario, pIA, resultado; /// resultado es la posicion en la mano
    char frase[FRASE];
    printf("/////////MODO PRUEBA DE IA/////////\n");
    printf("0 = +2 puntos, 1 = +1 punto, 2 = -1 punto al oponente, 3 = -2 puntos al oponente, 4 = volver a sacar, 5 = espejo\n");
    printf("Ingrese 1ra carta: ");
    scanf("%d", &mano[0]);
    printf("Ingrese 2da carta: ");
    scanf("%d", &mano[1]);
    printf("Ingrese 3ra carta: ");
    scanf("%d", &mano[2]);
    printf("Ingrese ultimaCarta: ");
    scanf("%d", &ultimaCarta);
    printf("Ingrese puntaje de usuario: ");
    scanf("%d", &pUsuario);
    printf("Ingrese puntaje de IA: ");
    scanf("%d", &pIA);
    system("cls");
    printf("* %s\n", numAfrase(*(mano + 0), frase));
    printf("* %s\n", numAfrase(*(mano + 1), frase));
    printf("* %s\n", numAfrase(*(mano + 2), frase));
    printf("Ultima carta: %s\n", numAfrase(ultimaCarta, frase));
    printf("Puntaje de usuario: %d\n", pUsuario);
    printf("Puntaje de IA: %d\n", pIA);
    dificil(pUsuario, pIA, ultimaCarta, mano, &resultado);
    printf("LA IA HA ELEGIDO: %d  %s\n", mano[resultado], numAfrase(mano[resultado], frase));
    system("pause");
    system("cls");
}

/////////   GENERICAS
void ordenarPorBurbujeo(void *vec, size_t nmemb, size_t tamanyo, int (*cmp)(void *, void *))
{
    for (int i = 0; i < nmemb; i++)
        for (int j = 0; j < nmemb - 1; j++)
            if (cmp(vec + j * tamanyo, vec + (j + 1) * tamanyo) > 0)
                interchange(vec + j * tamanyo, vec + (j + 1) * tamanyo, tamanyo);
}

void interchange(void *a, void *b, size_t tamanyo)
{
    char *aux = malloc(tamanyo); // t_alumno aux;

    memcpy(aux, a, tamanyo); // aux = *a;
    memcpy(a, b, tamanyo);   //*a = *b;
    memcpy(b, aux, tamanyo); //*b = aux;

    free(aux);
}
