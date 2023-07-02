#ifndef importar_h
#define importar_h
#include "main.h"
#include "structs.h"

void cargarPokedex(HashMap *Pokedex, HashMap *Movimientos);

void cargarObjetos(HashMap *Objetos);

void cargarMovimientos(HashMap *Movimientos);

void cargarMultiplicadores(HashMap *multiplicadores);

void cargarEntrenadoresLiga(Entrenador entrenadores[], HashMap *Pokedex);

#endif /* importar_h */