#include <stdio.h>
#include <stdlib.h>
#include "arbolLaberinto.h"
#include <time.h>
#include "string.h"
#include "archivos.h"

int main()
{
    char archivo1 [20]= {"singlePlayer.bin"};//en single
    char archivo2 [20]= {"multiPlayer.bin"}; //en multi
    int eleccion;
    char seguir;

    do
    {
        system("cls");
        mostrarCamino(10);
        scanf("%i", &eleccion);
        switch(eleccion)
        {
        case 1: //juego nuevo
            system("cls");
            printf("\n\tSeleccione el modo de juego: \n\t1.Un jugador. \n\t2.Multiples jugadores.");
            printf("\n\t");
            scanf("%i", &eleccion);
            switch(eleccion)
            {
            case 1: //singlePlayer
                system("cls");
                singlePlayer();
                break;
            case 2:
                system("cls");
                multiPlayer();
                break;
            }
            break;
        case 2: //instrucciones
            system("cls");
            mostrarCamino(11);
            break;
        case 3: //puntuaciones
            system("cls");
            printf("\n\tQue puntuaciones desea ver? \n\t1.Un jugador. \n\t2.Multiples jugadores.");
            printf("\n\t");
            scanf("%i", &eleccion);
            switch(eleccion)
            {
            case 1: //singlePlayer
                system("cls");
                mostrarArchivo(archivo1);

                break;
            case 2: //multiPlayer
                system("cls");
                mostrarArchivo(archivo2);
                break;
            }
            break;
        default:
            printf("\n\tOpcion invalida.");
        }
        printf ("\n\tDesea volver al menu? s/n  ");
        fflush(stdin);
        scanf("%c", &seguir);
    }while (seguir=='s');

    return 0;
}
