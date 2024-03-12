#ifndef ARBOLLABERINTO_H_INCLUDED
#define ARBOLLABERINTO_H_INCLUDED
#include "arregloDlistas.h"

typedef struct
{
    struct nodoArbol *izq;
    struct nodoArbol *der;
    int dato;
}nodoArbol;

nodoArbol *insertarAutom(nodoArbol *arbol);
nodoArbol *inicArbol();
nodoArbol *crearNodoArbol(int dato);
nodoArbol *insertarEnArbol(nodoArbol *arbol, int dato);
nodoArbol *insertarUltCelda(nodoArbol *arbol, int *celdaGanadora);
int buscarEnArbol(nodoArbol *arbol, int dato);
void mostrarPreorder(nodoArbol *arbol);
int recorrerArbol(nodoArbol *arbol, int celdaGanadora, int recorrido);
char elegirCamino(nodoArbol *arbol, int *recorrido, int celdaGanadora);
char elegir2doCamino(nodoArbol *arbol, int caminoUsado, int *recorrido, int celdaGanadora);
int calcularPuntaje(int *recorrido);
int iniciarJuego(int *puntaje);
int hints(int recorrido, int numHabitacion, int celdaGanadora);
void mostrarHint(int numHabitacion, int celdaGanadora);
char verifResp(int opcion, int **recorrido, int numHabitacion, int celdaGanadora);



#endif // ARBOLLABERINTO_H_INCLUDED
