#ifndef combates_h
#define combates_h
#include "structs.h"

int calculoDano(HashMap *Pokedex, HashMap *Movimientos, HashMap *Multiplicadores, Pokemon *PokeAtaca, Pokemon *PokeRecibe, Ataque ataque);

void mostrarEquipoEnemigo(Entrenador entrenadores[], HashMap *Pokedex);

void atacar(Entrenador entrenadores[], HashMap *Pokedex, HashMap *Movimientos, HashMap *Multiplicadores, int *danio, int posicion, int *vivo, int *ganador);

void reiniciar(Entrenador entrenadores[]);

int dificultadNormal(Entrenador entrenadores[], HashMap *Pokedex, HashMap *Movimientos, HashMap *Multiplicadores);

int dificultadDificil(Entrenador entrenadores[], HashMap *Pokedex, HashMap *Movimientos, HashMap *Multiplicadores, int posicion);

void salonDeLaFama(Entrenador entrenadores[]);

void eliminarObjPelea(Entrenador entrenador[],int item);

void efectos(int posicion, Entrenador entrenadores[], int item);

void usarObjeto(Entrenador entrenadores[]);

#endif /* COMBATE_H */