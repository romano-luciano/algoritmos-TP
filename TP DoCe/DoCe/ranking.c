#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "Funciones.h"
#include "pilaDinamica.h"

void ranking(const char *codigoGrupo)
{
    setColor(11);
    printf("MENU RANKING\n");
    setColor(15);
    verRanking(codigoGrupo);
    putchar('\n');
    setColor(14);
    system("pause");
    system("cls");
}
