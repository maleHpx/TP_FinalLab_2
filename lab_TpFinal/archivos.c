#include <stdio.h>
#include <stdlib.h>
#include "string.h"
#include "archivos.h"
#include "arbolLaberinto.h"
#include"arregloDlistas.h"

void mostrarCamino(int caminoInterfaz)
{
    FILE *fp;
    fp = fopen("interfaz.bin", "rb");
    int camino = calcularPos(caminoInterfaz);
    char matriz[27][71];
    if(fp != NULL)
    {
        fseek(fp, camino, SEEK_SET);
        for(int i = 0; i < 27; i++)
        {
            fread(&matriz[i], sizeof(char), 70, fp);
        }

    }
    fclose(fp);
    mostrarMatriz(matriz);
}
int calcularPos(int caminoInterfaz)
{
    int camino;
    camino = (27*70)*caminoInterfaz;

    return camino;
}
void mostrarMatriz(char matriz[27][71])
{
    for(int i = 0; i < 27; i++)
    {
        printf("%s\n", matriz[i]);
    }
}

void cargarArchivoJugadores(celda adl[], int validos, char archivo[])
{
    registroJuego jugador;
    FILE *fp;
    fp = fopen(archivo, "wb");
    if(fp != NULL)
    {
        for(int i = 0; i < validos; i++)
        {
            while(adl[i].listaJugador!= NULL)
            {
                jugador = pasarDatosArreg(adl[i], adl[i].listaJugador->dato);
                adl[i].listaJugador =adl[i].listaJugador->sig;
                fwrite(&jugador, sizeof(registroJuego), 1, fp);
            }
        }

    }
    fclose(fp);
}
registroJuego pasarDatosArreg(celda adl, juego dato)
{
    registroJuego jugador;
    strcpy(jugador.nickname, adl.nickname);
    jugador.id = adl.id;
    jugador.numPartida = dato.numPartida;
    jugador.habRecorridas = dato.habRecorridas;
    jugador.puntaje = dato.puntaje;

    return jugador;
}
int pasarDeArchivoToADL(celda adl[], char archivo[])
{
    FILE *fp;
    int validos = 0;
    int pos;
    registroJuego jugador;
    nodoSimple *listaJugador;
    fp = fopen(archivo, "rb");
    if(fp != NULL)
    {
        while(fread(&jugador,sizeof(registroJuego),1,fp)>0)
        {
            pos = buscarPosJugador(adl, jugador.nickname, validos);
            if(pos == -1)
            {
                validos = agregarJugador(adl, jugador.nickname, validos);
                pos=validos-1;
            }

            juego player = cargarJugador(jugador.numPartida, jugador.habRecorridas, jugador.puntaje);
            nodoSimple *nuevoNodo = crearNodoSimple(player);
            adl[pos].listaJugador= agregarAlFinal(adl[pos].listaJugador, nuevoNodo);
//            mostrarArreglo(adl, validos);
        }

    }
    fclose(fp);

    return validos;;
}
void mostrarArchivo(char archivo[])
{
    registroJuego jugador;
    FILE * fp = fopen(archivo,"rb");
    if(fp != NULL)
    {
        while(fread(&jugador,sizeof(registroJuego),1,fp)>0)
        {
            mostrarRegistroJuego(jugador);
        }
    }
    fclose(fp);
}

void mostrarRegistroJuego(registroJuego jugador)
{
    printf("\n\t---------------------------");
    printf("\n\t| NickName: %s",jugador.nickname);
    printf("\n\t| ID: %i",jugador.id);
    printf("\n\t| Partida: %i",jugador.numPartida);
    printf("\n\t| Habitaciones recorridas: %i",jugador.habRecorridas);
    printf("\n\t| Puntaje: %i",jugador.puntaje);
    printf("\n\t---------------------------\n");
}
