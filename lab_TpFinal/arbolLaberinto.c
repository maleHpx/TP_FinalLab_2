#include <stdio.h>
#include <stdlib.h>
#include "arbolLaberinto.h"
#include <time.h>
#include "arregloDlistas.h"
#include "archivos.h"

nodoArbol *inicArbol()
{
    return NULL;
}
nodoArbol *crearNodoArbol(int dato)
{
    nodoArbol *nodoNuevo = (nodoArbol*)malloc(sizeof(nodoArbol));

    nodoNuevo->dato = dato;
    nodoNuevo->izq = NULL;
    nodoNuevo->der=NULL;
    return nodoNuevo;
}
//crea el arbol automaticamente
nodoArbol *insertarAutom(nodoArbol *arbol)
{
    srand(time(NULL));
    int dato;
    int validos = rand() % 8+11;
    arbol = insertarEnArbol(arbol, 75);
    for(int i = 0; i < validos; i++)
    {
        dato = rand() % 150;
        arbol = insertarEnArbol(arbol, dato);
    }
    return arbol;

}
nodoArbol *insertarEnArbol(nodoArbol *arbol, int dato)
{
    if(arbol ==NULL)
    {
        arbol = crearNodoArbol(dato);
    }
    else
    {
        if(dato > arbol->dato)
        {
            arbol->der = insertarEnArbol(arbol->der, dato);
        }
        else
            arbol->izq = insertarEnArbol(arbol->izq, dato);

    }
    return arbol;
}
//inserta o elige la celda ganadora
nodoArbol *insertarUltCelda(nodoArbol *arbol, int *celdaGanadora)
{
    srand(time(NULL));
    int numCelda = rand()% 150;
    while((numCelda > 69) && (numCelda < 81))
    {
        numCelda = rand()% 150;
    }
    int rta;
    rta = buscarEnArbol(arbol, numCelda);
    if(rta == 1)
    {
        *celdaGanadora = numCelda;
    }
    else
    {
        *celdaGanadora = numCelda;
        arbol = insertarEnArbol(arbol, numCelda);
    }
    return arbol;
}
//busca si ya existe el nodo con la celda ganadora
int buscarEnArbol(nodoArbol *arbol, int dato)
{
    int rta = 0;
    if(arbol !=NULL)
    {
        if(arbol->dato == dato)
        {
            rta = 1;
        }
        else if(arbol->dato < dato)
        {
            rta = buscarEnArbol(arbol->der, dato);
        }
        else
            rta = buscarEnArbol(arbol->izq, dato);

    }
    return rta;
}
void mostrarPreorder(nodoArbol *arbol)
{
    if(arbol != NULL)
    {
        printf("%i ", arbol->dato);
        mostrarPreorder(arbol->izq);
        mostrarPreorder(arbol->der);
    }
}
//recorre el arbol con las desiciones del jugador, a(izq), d(der), s(atras), el recorrido comienza en mil para guardar la cantidad de ayudas restantes y las habitaciones recorridas, una vez ganado el juego, se resta el mil y si no se usaron las ayudas tambien se restan, quedando solamente el recorrido
int recorrerArbol(nodoArbol *arbol, int celdaGanadora, int recorrido)
{
    char camino = 'y';
    int rta = 0;
    int caminoUsado = 0;
    if(arbol != NULL)
    {
        if(arbol->dato != celdaGanadora)
        {
            camino = elegirCamino(arbol, &recorrido, celdaGanadora);

            if(camino == 'a')
            {
                rta = recorrerArbol(arbol->izq, celdaGanadora, recorrido+1);
                recorrido = rta;
                caminoUsado = 1;
                if((rta > 1000)&&(rta < 2000))
                {
                    camino = elegir2doCamino(arbol, caminoUsado, &recorrido, celdaGanadora);
                    if(camino == 'd')
                    {
                        rta = recorrerArbol(arbol->der, celdaGanadora, recorrido+1);
                        recorrido = rta;
                        caminoUsado = 3;
                        if((rta > 1000)&&(rta < 2000))
                            camino = elegir2doCamino(arbol, caminoUsado, &recorrido, celdaGanadora);
                    }
                }
                else if(rta > 2000)
                {
                    recorrido-=1000;
                    camino = elegir2doCamino(arbol, caminoUsado, &recorrido, celdaGanadora);
                    if(camino == 'd')
                    {
                        rta = recorrerArbol(arbol->der, celdaGanadora, recorrido+1);
                        recorrido = rta;
                        caminoUsado = 3;
                        if((rta > 1000)&&(rta < 2000))
                            camino = elegir2doCamino(arbol, caminoUsado, &recorrido, celdaGanadora);
                    }
                }

            }
            else if(camino == 'd')
            {
                rta = recorrerArbol(arbol->der, celdaGanadora, recorrido+1);
                recorrido = rta;
                caminoUsado = 2;
                if((rta > 1000)&&(rta < 2000))
                {
                    camino = elegir2doCamino(arbol, caminoUsado, &recorrido, celdaGanadora);
                    if(camino == 'a')
                    {
                        rta = recorrerArbol(arbol->izq, celdaGanadora, recorrido+1);
                        recorrido = rta;
                        caminoUsado = 3;
                        if((rta > 1000)&&(rta < 2000))
                            camino = elegir2doCamino(arbol, caminoUsado, &recorrido, celdaGanadora);
                    }
                }
                else if(rta > 2000)
                {
                    recorrido-=1000;
                    camino = elegir2doCamino(arbol, caminoUsado, &recorrido, celdaGanadora);
                    if(camino == 'a')
                    {
                        rta = recorrerArbol(arbol->izq, celdaGanadora, recorrido+1);
                        recorrido = rta;
                        caminoUsado = 3;
                        if((rta > 1000)&&(rta < 2000))
                            camino = elegir2doCamino(arbol, caminoUsado, &recorrido, celdaGanadora);
                    }
                }
            }

            if(camino == 'x')
            {
                rta = recorrido+1000;
            }
            else if(camino == 's')
            {
                if(rta == 0)
                {
                    rta = recorrido;
                }
            }

        }
        else
        {
            mostrarCamino(9);//win
            system("pause");
            rta = recorrido-1000;
        }
    }
    return rta;
}
char elegirCamino(nodoArbol *arbol, int *recorrido, int celdaGanadora)
{
    char camino = 's';
    int opcion;
    int **puntRecorrido = recorrido;
    if((arbol->der != NULL)&&(arbol->izq != NULL))
    {
        opcion = 1;
        printf("\n\tNum habitacion: %i \n", arbol->dato);
        mostrarCamino(0);//dos caminos
        printf("\tCamino: ");
        camino = verifResp(opcion, puntRecorrido, arbol->dato, celdaGanadora);
        system("cls");
    }
    else if(arbol->izq != NULL)
    {
        opcion = 2;
        printf("\n\tNum habitacion: %i \n", arbol->dato);
        mostrarCamino(1);//camino izq
        printf("\tCamino: ");
        camino = verifResp(opcion, puntRecorrido, arbol->dato, celdaGanadora);
        system("cls");
    }
    else if(arbol->der != NULL)
    {
        opcion = 3;
        printf("\n\tNum habitacion: %i \n", arbol->dato);
        mostrarCamino(2);//camino der
        printf("\tCamino: ");
        camino = verifResp(opcion, puntRecorrido, arbol->dato, celdaGanadora);
        system("cls");
    }
    else
    {
        printf("\n\tNum habitacion: %i \n", arbol->dato);
        mostrarCamino(3);//no hay camino
        system("pause");
        system("cls");
    }

    return camino;
}
char elegir2doCamino(nodoArbol *arbol, int caminoUsado, int *recorrido, int celdaGanadora)
{
    char camino = 's';
    int opcion;
    int **puntRecorrido = recorrido;
    if((arbol->der != NULL)&&(arbol->izq != NULL))
    {
        if (caminoUsado ==1)
        {
            opcion = 3;
            printf("\n\tNum habitacion: %i \n", arbol->dato);
            mostrarCamino(5);//dos caminos, izq usado
            printf("\tCamino: ");
            camino = verifResp(opcion, puntRecorrido, arbol->dato, celdaGanadora);
            system("cls");
        }
        else if(caminoUsado == 2)
        {
            opcion = 2;
            printf("\n\tNum habitacion: %i \n", arbol->dato);
            mostrarCamino(4);//dos caminos, der usado
            printf("\tCamino: ");
            camino = verifResp(opcion, puntRecorrido, arbol->dato, celdaGanadora);
            system("cls");
        }
        else if(caminoUsado ==3)
        {
            printf("\n\tNum habitacion: %i \n", arbol->dato);
            mostrarCamino(6);//dos caminos usados
            camino = 'x';
            system("pause");
            system("cls");
        }
    }
    else if(arbol->der != NULL)
    {
        printf("\n\tNum habitacion: %i \n", arbol->dato);
        mostrarCamino(7);//der usado
        system("pause");
        system("cls");
    }
    else if(arbol->izq != NULL)
    {
        printf("\n\tNum habitacion: %i \n", arbol->dato);
        mostrarCamino(8);
        system("pause");
        system("cls");
    }

    return camino;
}

int calcularPuntaje(int *recorrido)
{
    int puntajeMaximo= 20000;
    if((*recorrido == 0)||(*recorrido > 1000))
    {
        puntajeMaximo = 0;
        while(*recorrido >100)
            {
                *recorrido -=100;
            }
    }
    else
    {
        if(*recorrido > 100)
        {
            while(*recorrido >100)
            {
                *recorrido -=100;
                puntajeMaximo+=350;
            }
        }
        for(int i = 0; i < *recorrido; i++)
        {
            if(i < 4)
            {
                puntajeMaximo-=350;
            }
            else if((i>3) &&(i<7))
            {
                puntajeMaximo-=500;
            }
            else if((i>6) &&(i<10))
            {
                puntajeMaximo-=650;
            }
            else
                puntajeMaximo-=1000;

        }
    }

    return puntajeMaximo;
}

int iniciarJuego(int *puntaje)
{
    int celdaGanadora;
    nodoArbol *arbol = inicArbol();
    int recorrido = 1200; //comienza en 1000 para que cuando termine la recursion no entre a ningun if por debajo de las llamadas, y el 200 es para saber la cantidad de ayudas restantes

    arbol = insertarAutom(arbol);
    arbol = insertarUltCelda(arbol, &celdaGanadora);
    // printf("celda ganadora %i \n", celdaGanadora);
    recorrido = recorrerArbol(arbol, celdaGanadora, recorrido);
    *puntaje = calcularPuntaje(&recorrido);


    return recorrido;
}
int hints(int recorrido, int numHabitacion, int celdaGanadora)
{
    mostrarHint(numHabitacion, celdaGanadora);
    recorrido -=100; //si se utiliza una, se resta de la parte en donde guarda las ayudas
    if(recorrido >= 1100)
    {
        printf("\n\tUna ayuda restante.");
    }
    else
        printf("\n\tCero ayudas restantes.");


    return recorrido;
}
void mostrarHint(int numHabitacion, int celdaGanadora)
{
    if(celdaGanadora > numHabitacion)
    {
        printf("\n\tEl numero de habitacion que busca es mayor al actual.\n");
    }
    else
        printf("\n\tEl numero de habitacion que busca es menor al actual.\n");
}
char verifResp(int opcion, int **recorrido, int numHabitacion, int celdaGanadora)
{
    char respuesta;
    int verificar = 0;
    switch(opcion)
    {
    case 1:
        do
        {
            fflush(stdin);
            printf("\n\t");
            scanf("%c", &respuesta);
            if((respuesta == 'a')||(respuesta == 'd')||(respuesta == 's'))
            {
                verificar = 1;
            }
            else if((respuesta == 'h')&&(*recorrido >1100))
            {
                *recorrido = hints(*recorrido, numHabitacion, celdaGanadora);
            }
            else
                printf("\n\tOpcion no valida, ingrese de nuevo: ");

        }
        while(verificar == 0);
        break;
    case 2:
        do
        {
            fflush(stdin);
            printf("\n\t");
            scanf("%c", &respuesta);
            if((respuesta == 'a')||(respuesta == 's'))
            {
                verificar = 1;
            }
            else if((respuesta == 'h')&&(*recorrido >1100))
            {
                *recorrido = hints(*recorrido, numHabitacion, celdaGanadora);
            }
            else
                printf("\n\tOpcion no valida, ingrese de nuevo: ");

        }
        while(verificar == 0);
        break;
    case 3:
        do
        {
            fflush(stdin);
            printf("\n\t");
            scanf("%c", &respuesta);
            if((respuesta == 'd')||(respuesta == 's'))
            {
                verificar = 1;
            }
            else if((respuesta == 'h')&&(*recorrido >1100))
            {
                *recorrido = hints(*recorrido, numHabitacion, celdaGanadora);
            }
            else
                printf("\n\tOpcion no valida, ingrese de nuevo: ");

        }
        while(verificar == 0);
        break;

    }
    return respuesta;
}
