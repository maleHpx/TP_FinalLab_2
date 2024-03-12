#ifndef ARREGLODLISTAS_H_INCLUDED
#define ARREGLODLISTAS_H_INCLUDED

typedef struct
{
    int numPartida;
    int habRecorridas;
    int puntaje;
}juego;

typedef struct
{
    juego dato;
    struct nodoSimple*sig;
}nodoSimple;

typedef struct
{
    int id;
    char nickname[20];
    nodoSimple*listaJugador;
}celda;


nodoSimple*inicLista();
nodoSimple*crearNodoSimple(juego player);
juego cargarJugador(int numPartida, int recorrido, int puntaje);
nodoSimple* agregarAlFinal(nodoSimple* lista, nodoSimple* nuevo);
nodoSimple* buscarUltimo(nodoSimple* lista);
int ingresarJugador(celda adl[], int dimension, int puntaje, int validos, int recorrido);
int alta(celda adl[20], int validos, int puntaje, int recorrido, char nickname[]);
int buscarPosJugador(celda adl[], char nickname[], int validos);
int agregarJugador(celda adl[], char nickname[], int validos);
void mostrarArreglo(celda adl[], int validos);
void mostrarLista(nodoSimple*lista);

typedef struct
{
    char nickname[20];
    struct nodoFila*sig;
}nodoFila;

typedef struct
{
    nodoFila* primero;
	nodoFila* ultimo;
} Fila;

void inicFila(Fila*fila);
void multiPlayer();
void singlePlayer();
nodoFila *crearNodoFila(char nombre[20]);
Fila agregar(Fila filita, char nickName[20]);
Fila cargarFila();
void extraer(Fila*filita);
nodoFila *borrarPrimero(nodoFila*lista);
void mostrarFila(Fila fila);
void mostrarNodoFila(nodoFila*lista);
celda buscarPuntajeMayor(celda adl[], int validos);


#endif // ARREGLODLISTAS_H_INCLUDED
