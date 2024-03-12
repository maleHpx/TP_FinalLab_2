#ifndef ARCHIVOS_H_INCLUDED
#define ARCHIVOS_H_INCLUDED
#include"arregloDlistas.h"

void mostrarCamino(int camino);
int calcularPos(int camino);
void mostrarMatriz(char matriz[27][71]);

typedef struct
{
	int id;
	char nickname[20];
	int numPartida;
	int habRecorridas;
	int puntaje;
}registroJuego;

void cargarArchivoJugadores(celda adl[], int validos, char archivo[]);
int pasarDeArchivoToADL(celda adl[], char archivo[20]);
registroJuego pasarDatosArreg(celda adl, juego dato);
void mostrarArchivo(char archivo[]);
void mostrarRegistroJuego(registroJuego registro);



#endif // ARCHIVOS_H_INCLUDED
