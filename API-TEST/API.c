//En nuestro caso no deberia de ser una lista -> analizar
//Definir la macro el filename


int create_json_file(const char *filename,tLista* pl,accion act){
    FILE *file = fopen(filename, "wt");
    if (!file) {
        perror("Error al crear el archivo");
        return 0;
    }

    if(!*pl) {
      fclose(file);
      return 0;
    }

    fprintf(file, "{\n \"codigoGrupo\": \"logica\",\n");
    fprintf(file, "    \"jugador\": \n{\n");

    
    // act((*pl)->dato,file);
    // pl = &(*pl)->sig;
    // while(*pl) {
    //   fprintf(file,",\n");
    //   act((*pl)->dato,file);
    //   pl = &(*pl)->sig;
    // }

    //Aca tenemos que pensar la logica para cargar el nombre y si gano o no
    fprintf(file, "\n}\n}");
    fclose(file);
    return 1;
}

void grabarArchivoJSON(void* a,void* b){
  tPersona* pa = (tPersona*)a;
  FILE* pb = (FILE*)b;
  fprintf(pb, "    {\"nombre\": \"%s\",\n",pa->nombre);
  fprintf(pb, "    \"puntos\": %d}",pa->puntuacion);
}
char *read_file(const char *filename){
    char linea[100] = {0};

    char* content;

    FILE *file = fopen(filename,"rt");
    if (!file) {
        perror("Error al abrir el archivo");
        return NULL;
    }

    fseek(file,0,SEEK_END);
    long file_size = ftell(file);
    rewind(file);

    content = malloc(file_size);
    if(!content) return NULL;

    *content = '\0';

    while(fgets(linea,100,file)) {
      strcat(content,linea);
    }


    fclose(file);
    return content;
}
int cargarConfiguracion(const char *filename,void* dato){
  char linea[TAM_LINEA];
  char* aux;
  tConfig config;
  FILE* pf;
  pf = fopen(filename,"rt");
  if(!pf)
    return 0;
  fgets(linea,TAM_LINEA,pf);
  aux = strchr(linea,'\n');
  *aux='\0';
  aux = strchr(linea,'|');
  strcpy(config.codGrup,aux+2);
  *(aux-1) = '\0';
  strcpy(config.url,linea);
  fgets(linea,TAM_LINEA,pf);
  sscanf(linea,"%d",&config.cantPartidas);
  memcpy(dato,&config,sizeof(tConfig));
  fclose(pf);
  return 1;
}
void generarUrl(char* cadena,void* dato){
    strcat(cadena,((tConfig*)dato)->url);
    strcat(cadena,"/");
    strcat(cadena,((tConfig*)dato)->codGrup);
}
size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp){
  size_t realsize = size * nmemb;
  char* linea = (char *)contents;
  char* aux;
  char nombre[51];
  int puntaje;
  int dia,mes,anio,hs,min,seg;
  if(strstr(linea,"[]")){
    printf("Aun no ha jugado nadie\n");
    return 0;
  }
  system("cls");
  puts("=================== RANKING ===================");
  puts("-----------------------------------------------");
  while(aux){

    aux = strchr(linea,',');

    *(aux-1) = '\0';
    linea = strchr(linea,':');
    strcpy(nombre,linea + 2);
    printf("NOMBRE JUGADOR: %s | ",nombre);
    aux = strchr(aux,':');

    sscanf(aux+1,"%d",&puntaje);
    printf("PUNTAJE: %d\n",puntaje);
    aux++;
    aux = strchr(aux,':');

    sscanf(aux+2,"%2d/%2d/%4d %2d:%2d:%2d",&dia,&mes,&anio,&hs,&min,&seg);
    printf("ULTIMA PARTIDA JUGADA: %02d/%02d/%d %02d:%02d:%02d\n",dia,mes,anio,hs,min,seg);

    printf("-----------------------------------------------");

    aux = strchr(aux,',');
    if(aux) {
      aux++;
      linea = aux;
    }
    puts("");
  }
  return realsize;
}
void iniciarGET(const char* urlGET){
  system("cls");
  puts("Cargando...");
  CURL *curl;
  CURLcode res;
  // Inicializar el manejo de curl
  curl_global_init(CURL_GLOBAL_DEFAULT);
  curl = curl_easy_init();

  if (curl){
    // Establecer la URL de la solicitud GET
    curl_easy_setopt(curl, CURLOPT_URL, urlGET);
    struct curl_slist *headers = NULL;
    headers = curl_slist_append(headers, "X-Secret: FADSFAS");
    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
    // Establecer la funci�n de retorno de llamada para manejar la respuesta
    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
    // Realizar la solicitud HTTP GET
    res = curl_easy_perform(curl);
    // Verificar si la solicitud fue exitosa
    if (res != CURLE_OK)
      fprintf(stderr, "Error en la solicitud: %s\n",

    curl_easy_strerror(res));
    // Limpiar y cerrar el manejo de curl
    curl_easy_cleanup(curl);
    // Finalizar el manejo global de curl
    curl_global_cleanup();
  }

}
int iniciarPOST(const char *filename,tLista* pl,accion act,const char* urlPOST){
    CURL *curl;
    CURLcode res;
    create_json_file(filename,pl,act);

    // Leer el JSON desde el archivo

    char *json_data = read_file(filename);

    if (!json_data) {
        fprintf(stderr, "Error al leer el archivo JSON\n");
        return 1;
    }
    system("cls");
    printf("JSON enviado:\n%s\n", json_data);  // Verificar JSON antes de enviarlo
    puts("");
    curl_global_init(CURL_GLOBAL_ALL);
    curl = curl_easy_init();

    if (curl) {
        struct curl_slist *headers = NULL;
        headers = curl_slist_append(headers, "Content-Type: application/json");
        headers = curl_slist_append(headers, "Expect:");  // Evitar problemas con "100-continue"

        curl_easy_setopt(curl, CURLOPT_URL, urlPOST);
        curl_easy_setopt(curl, CURLOPT_POST, 1L);
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, json_data);
        curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, (long)strlen(json_data));  // Asegurar tama�o correcto
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);  // Desactivar verificaci�n SSL
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L);

        res = curl_easy_perform(curl);
        if (res != CURLE_OK) {
            fprintf(stderr, "Error en POST: %s\n", curl_easy_strerror(res));
        }

        curl_slist_free_all(headers);
        curl_easy_cleanup(curl);
    }

    free(json_data);
    curl_global_cleanup();

    return 0;
}
void ocuparEspacio(void* a,void *b){
  tPersona* pa = (tPersona*)a;
  pa->ocupado = 1;
}
int compararFlag(const void* a,const void* b){
  tPersona* pa = (tPersona*)a;
  return pa->ocupado == 1;
}
void acumularPuntaje(void*a,void*b){
  tPersona* pa = (tPersona*)a;
  int* pb = (int*)b;
  pa->puntuacion += *pb;
}
int compararNombre(const void*a,const void*b){
  tPersona* pa = (tPersona*)a;
  tPersona* pb = (tPersona*)b;
  return strcmp(pa->nombre,pb->nombre);
}
int compararPuntaje(const void*a,const void*b){
  tPersona* pa = (tPersona*)a;
  tPersona* pb = (tPersona*)b;
  return pa->puntuacion - pb->puntuacion;
}
void grabarPuntaje(void*a,void*b){
  tPersona* pa = (tPersona*)a;
  FILE* pb = (FILE*)b;
  fprintf(pb,"Nombre %s Puntuacion %d\n",pa->nombre,pa->puntuacion);
}