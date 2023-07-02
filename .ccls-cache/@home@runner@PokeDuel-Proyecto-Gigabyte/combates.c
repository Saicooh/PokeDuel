#include "main.h"



void mostrarEquipoEnemigo(Entrenador entrenadores[], HashMap *Pokedex)
{
  for(int i = 0; i < 6; i++)
  {
    char pokeNum[MAX];
    char cadenaCompleta[1000];

    int numPokedex = rand() % 152;
    
    sprintf(pokeNum, "%i", numPokedex);
  
    Pair *pokeKey = searchMap(Pokedex, pokeNum);
    Pokemon *pokeValue = pokeKey -> value;
  
    entrenadores[1].equipo[i] = *pokeValue;
    
    sprintf(cadenaCompleta, "Pokemon %d: %s\n", i+1, entrenadores[1].equipo[i].nombre);

    escribirLentamente(cadenaCompleta, 0);
  }
  entrenadores[1].sizeTeam = 6;
  entrenadores[1].cantidadVivos = 6;
}



void reiniciar(Entrenador entrenadores[])
{
  entrenadores[0].cantidadVivos = entrenadores[0].sizeTeam;

  for (int i = 0 ; i < entrenadores[0].sizeTeam ; i++)
  {
    entrenadores[0].equipo[i].muerto = false;
    entrenadores[0].equipo[i].saludActual = entrenadores[0].equipo[i].salud;
    entrenadores[0].equipo[i].ataque = entrenadores[0].equipo[i].ataqueBase;
    entrenadores[0].equipo[i].defensa = entrenadores[0].equipo[i].defensa;

    Ataque *ataque = firstList(entrenadores[0].equipo[i].habilidades);
    
    for (int j = 0 ; j < 4 ; j++)
    {
      ataque -> numUsosActual = ataque -> numUsosMAX;
      ataque = nextList(entrenadores[0].equipo[i].habilidades);
    }
  }
}