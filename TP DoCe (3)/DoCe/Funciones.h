#ifndef FUNCIONES_H_INCLUDED
#define FUNCIONES_H_INCLUDED

#include <curl/curl.h> //incluyo la libreria de curl en este archivo para que este en todos los demas sin inconvenientes

#define MAZO 40
#define FRASE 25
#define MAX_LINES 50

#define MAS_DOS_PUNTOS 0
#define MAS_UN_PUNTO 1
#define RESTAR_UN_PUNTO 2
#define RESTAR_DOS_PUNTOS 3
#define REPETIR_TURNO 4
#define ESPEJO 5

void menuDif(FILE*informe, const char *codigoGrupo, const char *nombreJugador); ///el codigoGrupo y el nombre son necesarios para pasarlos a la funcion "partida"
void partida(int dific,FILE*informe, const char *codigoGrupo, const char *nombreJugador); ///el codigoGrupo y el nombre son necesarios a la hora de enviar el ganador a la API
void mezclar(void*vec,size_t nMemb,size_t tamElem);
char*numAfrase(int num,char*frase);
void jugada(int*activo,int*pasivo,int elecActivo,int elecPasivo,int*vSacar,int*descarteAnterior);
void facil(int pJugador,int pIA,int ultimaCarta,int*manoIA,int*elec);
void medio(int pJugador,int pIA,int ultimaCarta,int*manoIA,int*elec);
void dificil(int pJugador,int pIA,int ultimaCarta,int*manoIA,int*elec);
int buscarEnMano(int*vec,size_t nMemb,int elem,int*subInd); //NO SE IMPLEMENTO
void ranking(const char *codigoGrupo);
void setColor(int color); ///para los colores a la hora de imprimir texto en pantalla

///FUNCIONES DE LA API
void cargarCodigoGrupo(char *codigoGrupo, size_t tam);
void enviarResultadoAPI(const char* nombreJugador, int gano, const char* codigoGrupo);
void verRanking(const char* codigoGrupo);

#endif // FUNCIONES_H_INCLUDED
