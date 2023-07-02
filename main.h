#ifndef main_h
#define main_h

#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <unistd.h>
#include "structs.h"
#include "combate.h"
#include "list.h"
#include "hashmap.h"
#include "funciones.h"
#include "importar.h"

#define MAX 25

void mostrarPokedex(HashMap *Pokedex);

//
void administrarPokemon(Entrenador entrenadores[], int *equipoRegistrado, int *volverMenu, HashMap *Pokedex);

void agregarPokemon(Entrenador entrenadores[], int *equipoRegistrado, HashMap *Pokedex);
void eliminarPokemon(Entrenador entrenadores[]);
void administrarOrden(Entrenador entrenadores[]);
void verEquipoActual(Entrenador entrenadores[]);
//
void administrarObjetos(HashMap *Objetos, Entrenador entrenadores[]);

void mostrarObjetos(HashMap *Objetos);
void agregarObjeto(HashMap *Objetos ,Entrenador entrenadores[]);
void mostrarMochila(Entrenador entrenadores[]);
void eliminarObjeto(Entrenador entrenadores[]);
//

//
void entrenamientoPokemon(Entrenador entrenadores[], HashMap *Pokedex, HashMap *Movimientos, HashMap *Multiplicadores,int entrenadorPos, int *ganador);

#define MAX 25
#endif /* main_h */