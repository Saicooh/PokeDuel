#ifndef main_h
#define main_h

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

#define SDL_MAIN_HANDLED

#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_audio.h>
#include <SDL2/SDL_timer.h>

#define MAX 25

void mostrarPokedex(HashMap *Pokedex);

//
void administrarPokemon(Entrenador entrenadores[], int *equipoRegistrado, int *volverMenu, HashMap *Pokedex);

void agregarPokemon(Entrenador entrenadores[], int *equipoRegistrado, HashMap *Pokedex);
void eliminarPokemon(Entrenador entrenadores[]);
void administrarOrden(Entrenador entrenadores[]);
void verEquipoActual(Entrenador entrenadores[]);
//

//
void administrarObjetos(HashMap *Objetos, Entrenador entrenadores[]);

void menuObjeto(int *opcion);
void mostrarObjetos(HashMap *Objetos);
void agregarObjeto(HashMap *Objetos ,Entrenador entrenadores[]);
void mostrarMochila(Entrenador entrenadores[]);
void eliminarObjeto(Entrenador entrenadores[]);
//

//
void entrenamientoPokemon(Entrenador entrenadores[], HashMap *Pokedex, HashMap *Movimientos, HashMap *Multiplicadores,int entrenadorPos, int *ganador);

void mostrarEquipoEnemigo(Entrenador entrenadores[], HashMap *Pokedex);
void atacar(Entrenador entrenadores[], HashMap *Pokedex, HashMap *Movimientos, HashMap *Multiplicadores, int *danio, int posicion, int *vivo, int *ganador);
void cambiarPokemon(char *auxNombre, Entrenador entrenadores[]);
//

//liga
void ligaPokemon(Entrenador entrenadores[], HashMap *Pokedex, HashMap *Movimientos, HashMap *Multiplicadores,HashMap *Objetos, int ganador);
//
#endif /* main_h */