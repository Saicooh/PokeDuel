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
#include "funciones.h"
#include "importar.h"
#include "list.h"
#include "hashmap.h"


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

#define MAX 25
#endif /* main_h */