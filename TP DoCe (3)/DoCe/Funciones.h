#ifndef FUNCIONES_H_INCLUDED
#define FUNCIONES_H_INCLUDED
#define MAZO 40
#define FRASE 25
#define MAX_LINES 50

#define MAS_DOS_PUNTOS 0
#define MAS_UN_PUNTO 1
#define RESTAR_UN_PUNTO 2
#define RESTAR_DOS_PUNTOS 3
#define REPETIR_TURNO 4
#define ESPEJO 5

void menuDif(FILE*informe);
void partida(int dific,FILE*informe);
void mezclar(void*vec,size_t nMemb,size_t tamElem);
void imprimirEnteros(int*vec, size_t tam);
char*numAfrase(int num,char*frase);
void jugada(int*activo,int*pasivo,int elecActivo,int elecPasivo,int*vSacar,int*descarteAnterior);
void facil(int pJugador,int pIA,int ultimaCarta,int*manoIA,int*elec);
void medio(int pJugador,int pIA,int ultimaCarta,int*manoIA,int*elec);
void dificil(int pJugador,int pIA,int ultimaCarta,int*manoIA,int*elec);
int buscarEnMano(int*vec,size_t nMemb,int elem,int*subInd);
void ranking(void);
void pruebaIA(void);
void pruebaIAMedio(void);
void ordenarPorBurbujeo(void *vec, size_t nmemb, size_t tamanyo, int (*cmp)(void *, void*));
void interchange (void* a, void* b, size_t tamanyo);
#endif // FUNCIONES_H_INCLUDED
