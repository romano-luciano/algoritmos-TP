#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "Funciones.h"
#include "pilaDinamica.h"

void cargarCodigoGrupo(char *codigoGrupo, size_t tam)
{
    FILE* archivo = fopen("config.txt", "r"); ///abro el archivo "config.txt" en modo lectura
    if (!archivo) {
        printf("No se pudo abrir config.txt\n");
        exit(1);
    }

    fscanf(archivo, "%*s | %s", codigoGrupo); ///guardo en la variable codigoGrupo el codigo del grupo que esta en el txt
    fclose(archivo);
}
