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

void pruebaIA(void)
{
    int mano[3], ultimaCarta, pUsuario, pIA, resultado; /// resultado es la posicion en la mano
    char frase[FRASE];
    printf("/////////MODO PRUEBA DE IA: DIFICIL/////////\n");
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

void pruebaIAMedio(void)
{
    int mano[3], ultimaCarta, pUsuario, pIA, resultado; /// resultado es la posicion en la mano
    char frase[FRASE];
    printf("/////////MODO PRUEBA DE IA: MEDIO/////////\n");
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
    medio(pUsuario, pIA, ultimaCarta, mano, &resultado);
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
