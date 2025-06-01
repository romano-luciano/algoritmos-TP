#ifndef PILADINAMICA_H_INCLUDED
#define PILADINAMICA_H_INCLUDED
#define TODO_OK 0
#define PILA_LLENA 1
#define PILA_VACIA 1
#define ERR_ARCH 2
#define ERR_MEM 3
#define MIN(A,B) ((A)<=(B)?(A):(B))

typedef struct sNodo
{
    void*info;   ///aca va el contenido
    unsigned tamInfo;  ///aca va el tamaño del contenido
    struct sNodo *sig;
}tNodo;   ///esto es un tipo de dato estructura

typedef tNodo *tPila;


void crearPila(tPila *pila);
int apilar(tPila *pila,const void*dato,unsigned tamDato);
int desapilar(tPila *pila,void*dato,unsigned tamDato);
void vaciarPila(tPila *pila);
int pilaVacia(const tPila*pila);
int pilaLlena(const tPila*pila,unsigned tamDato);
int verTope(const tPila*pila,void*dato,unsigned tamDato);
#endif // PILADINAMICA_H_INCLUDED
