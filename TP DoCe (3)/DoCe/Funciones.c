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


#ifdef _WIN32
#include <windows.h>
void setColor(int color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}
#else
void setColor(int color) {
    printf("\033[0;%dm", color);
}
#endif
