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

void enviarResultadoAPI(const char* nombreJugador, int gano, const char* codigoGrupo)
{
    CURL *curl;
    CURLcode res; ///resultado de la operacion

    curl_global_init(CURL_GLOBAL_DEFAULT); ///se incializa libcurl globalmente
    curl = curl_easy_init(); ///crea una nueva instancia

    if (curl) ///verifica si curl se inicio correctamente
    {
        char jsonData[256];
        sprintf(jsonData,
                "{\"codigoGrupo\":\"%s\",\"jugador\":{\"nombre\":\"%s\",\"vencedor\":%d}}",
                codigoGrupo, nombreJugador, gano);

        struct curl_slist *headers = NULL; ///crea lista de cabecera HTTP y la agrega
        headers = curl_slist_append(headers, "Content-Type: application/json");

        curl_easy_setopt(curl, CURLOPT_URL, "https://algoritmos-api.azurewebsites.net/api/doce"); ///Le dice a libcurl cual es la URL a la que va a hacer el POST
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers); ///Se le pasa la cabecera HTTP
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, jsonData); ///Le pasamos el contenido del cuerpo del POST (jsonData)
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L); ///Desactiva la verificacion del certificado SSL

        res = curl_easy_perform(curl); ///Se ejecuta la peticion HTTP POST a la API
        if (res != CURLE_OK)
            fprintf(stderr, "Error en la solicitud: %s\n", curl_easy_strerror(res));
        else
            printf("Resultado enviado exitosamente!\n");

        ///Limpio y cierro el manejo de curl
        curl_slist_free_all(headers);
        curl_easy_cleanup(curl);
    }

    ///finaliza el manejo global de curl
    curl_global_cleanup();
}
