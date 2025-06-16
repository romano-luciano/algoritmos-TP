#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pilaDinamica.h"

void crearPila(tPila *pila)
{
    *pila = NULL;    ///reservamos memoria con capacidad 0
}

int apilar(tPila *pila,const void *dato, unsigned tamDato) ///esto es poner en pila. se recibe la puntero a pila, el puntero del dato aponer, y el tamaño
{
    tNodo *nuevo = (tNodo *)malloc(sizeof(tNodo));  ///se reserva memoria para la estructura nuevo (tNodo)
    if (!nuevo) return ERR_MEM;

    nuevo->info = malloc(tamDato);  ///se reserva memoria para nuevo->info de tipo tamDato
    if (!nuevo->info)
    {
        free(nuevo);
        return ERR_MEM; ///si no se puede reservar, se libera la anterior y se sale
    }
    memcpy(nuevo->info, dato, tamDato);  /// copio dato en nuevo->info , ambos con tipo tamDato
    nuevo->tamInfo = tamDato; ///copio el tamDato en nuevo->tamInfo

    nuevo->sig = *pila;  ///el contenido de la pila ( dato anterior o NULL) es el siguiente, se va a desplazar lo guardado anteriormente
    *pila = nuevo;  /// lo nuevo es la pila
    return TODO_OK;
}

int desapilar(tPila *pila, void *dato, unsigned tamDato)
{
    tNodo *aux = *pila;  /// creo un auxiliar puntero al contenido de la pila  ///DESARROLLO LAS VARIABLES AL INICIO DEL BLOQUE
    if (pilaVacia(pila))
        return PILA_VACIA;    ///si la pila esta vacia me voy

    memcpy(dato, aux->info, tamDato > aux->tamInfo ? aux->tamInfo : tamDato);  ///copio el dato de la pila(auxiliar),comparo tamDato con tamInfo y uso el menor
    *pila = aux->sig; ///actualizo la pila

    free(aux->info);
    free(aux);
    return TODO_OK;
}

void vaciarPila(tPila *pila)
{
    tNodo *aux;
    while (*pila)  ///hasta que el contenido de pila no sea null sigo
    {
        aux = *pila;   /// guardo en aux la pila actual
        *pila = aux->sig;  ///guardo el siguiente en pila
        free(aux->info);   ///borro lo reservado  del contenido
        free(aux);    ///borro la estructura completa
    }
}

int pilaVacia(const tPila*pila)
{
    return *pila == NULL;  //si el contenido de la pila es NULL entonces esta vacio
}

int pilaLlena(const tPila*pila,unsigned tamDato)
{
    tNodo*aux = (tNodo*)malloc(sizeof(tNodo)); ///para la estructura entera
    if (aux == NULL) return ERR_MEM;
    void *test = malloc(tamDato); // Intentar reservar memoria  para el dato con cierto tamaño
    if (test == NULL)
    {
        free(aux);
        return ERR_MEM;
    }
    free(test); // Liberar la memoria de prueba
    free(aux);
    return TODO_OK; // Indicar que la pila no está llena
}

int verTope(const tPila*pila,void*dato,unsigned tamDato)
{
    if (!*pila)  // Si la pila está vacía
    {
        return PILA_VACIA; // Indicar que no hay elemento en el tope
    }
    // Copiar el dato del nodo superior al espacio proporcionado
    memcpy(dato, (*pila)->info, tamDato > (*pila)->tamInfo ? (*pila)->tamInfo : tamDato);
    return TODO_OK; // Indicar éxito
}
