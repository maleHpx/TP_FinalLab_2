#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "string.h"
#include"arregloDlistas.h"
#include "arbolLaberinto.h"
#include "archivos.h"

nodoSimple*inicLista()
{
    return NULL;
}

nodoSimple*crearNodoSimple(juego player)
{
    nodoSimple*nuevoNodo=(nodoSimple*)malloc(sizeof(nodoSimple));
    nuevoNodo->dato= player;
    nuevoNodo->sig=NULL;
    return nuevoNodo;
}

juego cargarJugador(int numPartida, int recorrido, int puntaje)
{
    juego player;
    player.numPartida = numPartida;
    player.habRecorridas = recorrido;
    player.puntaje= puntaje;

    return player;
}

nodoSimple* agregarAlFinal(nodoSimple* lista, nodoSimple* nuevo)
{
    if(lista==NULL)
    {
        lista = nuevo;
    }
    else
    {
        nodoSimple* ultimo = buscarUltimo(lista);
        ultimo->sig = nuevo;
    }
    return lista;
}

nodoSimple* buscarUltimo(nodoSimple* lista)
{
    nodoSimple* seg = lista;
    while(seg->sig!=NULL)
    {
        seg = seg->sig;
    }

    return seg;
}
int ingresarJugador(celda adl[], int dimension, int puntaje, int validos, int recorrido)
{
    char nickname[20];
    printf("\n\tIngrese su nombre: ");
    fflush(stdin);
    gets(nickname);
    validos=alta(adl, validos, puntaje, recorrido, nickname);

    return validos;
}

int alta(celda adl[], int validos, int puntaje, int recorrido, char nickname[])
{
    int numPartida = 1;
    int pos=buscarPosJugador(adl, nickname, validos);
    if (pos==-1)
    {
        validos=agregarJugador(adl, nickname, validos);
        pos=validos-1;
    }
    else
    {
        nodoSimple *ultimo = buscarUltimo(adl[pos].listaJugador);
        numPartida = ultimo->dato.numPartida +1;
    }
    juego jugador=cargarJugador(numPartida, recorrido, puntaje);
    nodoSimple*aux=crearNodoSimple(jugador);
    adl[pos].listaJugador=agregarAlFinal(adl[pos].listaJugador, aux);
    return validos;
}

int buscarPosJugador(celda adl[], char nickname[], int validos)
{
    int rta=-1;
    int i=0;
    while((i<validos)&&(rta==-1))
    {
        if(strcmp(adl[i].nickname, nickname)==0)
        {
            rta=i;
        }
        i++;
    }
    return rta;
}

int agregarJugador(celda adl[], char nickname[], int validos)
{
    strcpy(adl[validos].nickname, nickname);
    adl[validos].id = validos;
    ///copio el nombre del jugador
    adl[validos].listaJugador=inicLista();
    ///inicializo la lista
    validos++;
    return validos;
}
void mostrarArreglo(celda adl[], int validos)
{
    for(int i=0; i<validos; i++)
    {
        printf("\n\t______________________\n");
        printf("\n\t NickName: %s", adl[i].nickname);
        printf("\n\t ID: %i", adl[i].id);
        printf("\n\t______________________\n");
        mostrarLista(adl[i].listaJugador);
    }
}

void mostrarLista(nodoSimple*lista)
{
    nodoSimple*seg=lista;
    while(seg!=NULL)
    {
        printf("\n\t---------------------------");
        printf("\n\t| Partida: %i", seg->dato.numPartida);
        printf("\n\t| Habitaciones recorridas: %i", seg->dato.habRecorridas);
        printf("\n\t| Puntaje: %i\n", seg->dato.puntaje);
        printf("\t---------------------------\n");
        seg=seg->sig;
    }
}
void inicFila(Fila*fila)
{
    fila->primero=inicLista();
    fila->ultimo=inicLista();
}

void multiPlayer()
{
    Fila fila;

    celda adlGanadores[10];
    int dimension = 20;
    int puntaje;
    int validosGanadores = 0;
    int recorrido=0;
    char seguir;
    char archivo [20]= {"multiPlayer.bin"};
    validosGanadores = pasarDeArchivoToADL(adlGanadores, archivo);
    do
    {
        celda adl[20];
        int validos = 0;
        fila=cargarFila();
        mostrarFila(fila);
        while (fila.ultimo!=NULL)
        {
            recorrido = iniciarJuego(&puntaje);
            validos = alta(adl,validos, puntaje, recorrido, fila.primero->nickname);
            printf("\n\tTurno del siguiente jugador");
            extraer(&fila);
        }
        mostrarArreglo(adl, validos);
        celda ganador = buscarPuntajeMayor(adl, validos);
        validosGanadores = alta(adlGanadores, validosGanadores, ganador.listaJugador->dato.puntaje, ganador.listaJugador->dato.habRecorridas, ganador.nickname);
        printf("\n\tEl ganador es %s con un puntaje de %i", ganador.nickname, ganador.listaJugador->dato.puntaje);
        printf("\n\tDesea jugar de nuevo? s/n ");
        fflush(stdin);
        scanf("%c", &seguir);

    }
    while(seguir =='s');
    cargarArchivoJugadores(adlGanadores, validosGanadores, archivo);

}
void singlePlayer()
{
    char archivo [20]= {"singlePlayer.bin"};
    celda adl[20];
    int dimension = 20;
    int puntaje;
    int validos = 0;
    validos = pasarDeArchivoToADL(adl, archivo);

    char seguir;
    do
    {
        int recorrido= iniciarJuego(&puntaje);
        validos = ingresarJugador(adl, dimension, puntaje, validos, recorrido);
        mostrarArreglo(adl, validos);
        printf("Desea jugar de nuevo? s/n");
        fflush(stdin);
        scanf("%c", &seguir);
    }while (seguir=='s');
    cargarArchivoJugadores(adl, validos, archivo);
}
nodoFila*crearNodoFila(char nombre[20])
{
    nodoFila*nuevoNodo=(nodoFila*)malloc(sizeof(nodoFila));
    strcpy(nuevoNodo->nickname, nombre);
    nuevoNodo->sig = NULL;
    return nuevoNodo;
}

Fila agregar(Fila filita, char nickName[20])
{
    nodoFila*nuevo=crearNodoFila(nickName);
    if (filita.primero==NULL)
    {
        filita.primero=nuevo;
        filita.ultimo=nuevo;
    }
    else
    {
        filita.ultimo->sig=nuevo;
        filita.ultimo=nuevo;
    }
    return filita;
}

Fila cargarFila()
{
    Fila filita;
    inicFila(&filita);
    char nickName[20];
    char seguir;
    int i=1;
    do
    {
        printf("\n\tIngrese el nickname del jugador %i\n", i);
        printf("\n\t");
        fflush(stdin);
        gets(nickName);
        filita = agregar(filita, nickName);
        printf ("\n\tDesea agregar mas jugadores? s/n\n");
        printf("\n\t");
        fflush(stdin);
        scanf("%c", &seguir);
        i++;
    }
    while (seguir=='s');
    return filita;
}

void extraer(Fila*filita)
{
    if (filita->primero!=NULL)
    {
        filita->primero=borrarPrimero(filita->primero);
        if (filita->primero==NULL)
        {
            filita->ultimo=inicLista();
        }
    }
}

nodoFila*borrarPrimero(nodoFila*lista)
{
    nodoFila*aBorrar=lista;
    if (lista!=NULL)
    {
        lista=lista->sig;
        free(aBorrar);
    }
    return lista;
}

void mostrarFila(Fila fila)
{
    printf("\n\tLos jugadores en la lista de espera son:\n");
    while (fila.primero!=NULL)
    {
        printf("\n\t----------------");
        printf("\n\t|");
        puts(fila.primero->nickname);
        printf("\t----------------");
        fila.primero=fila.primero->sig;
    }
}

celda buscarPuntajeMayor(celda adl[], int validos)
{
    celda ganador;
    ganador = adl[0];
    for(int i = 0; i < validos; i++)
    {
        if(adl[i].listaJugador->dato.puntaje > ganador.listaJugador->dato.puntaje)
        {
            ganador = adl[i];
        }
    }

    return ganador;
}
