#ifndef main_h
#define main_h

#include <stdio.h>
#include "list.h"
#include "hashmap.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <unistd.h>
#include "structs.h"
#include "funciones.h"


void mostrarPokedex(HashMap *Pokedex);

//
void administrarPokemon(Entrenador entrenadores[], int *equipoRegistrado, int *volverMenu, HashMap *Pokedex);

void agregarPokemon(Entrenador entrenadores[], int *equipoRegistrado, HashMap *Pokedex);
void eliminarPokemon(Entrenador entrenadores[]);
void administrarOrden(Entrenador entrenadores[]);
void verEquipoActual(Entrenador entrenadores[]);
//

#define MAX 25
#endif /* main_h */