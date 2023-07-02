#ifndef combates_h
#define combates_h
#include "structs.h"



void mostrarEquipoEnemigo(Entrenador entrenadores[], HashMap *Pokedex);



void reiniciar(Entrenador entrenadores[]);

int dificultadNormal(Entrenador entrenadores[], HashMap *Pokedex, HashMap *Movimientos, HashMap *Multiplicadores);

#endif /* COMBATE_H */