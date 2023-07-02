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

void atacar(Entrenador entrenadores[], HashMap *Pokedex, HashMap *Movimientos, HashMap *Multiplicadores, int *danio, int posicion, int *vivo, int *ganador)
{
  char cadenaCompleta[1000];
  char auxNombre[MAX];
  char ataque[MAX];
  int opcionAtaque;
  
  Ataque *ataq = firstList(entrenadores[0].equipo[0].habilidades);

  printf("Elija el ataque:\n\n");
  
  for(int i = 0 ; i < 4 ; i++)
  {
    printf("%d. %s ", i + 1, ataq -> nombre);
    printf("[%d/%d] pp\n", ataq -> numUsosActual, ataq -> numUsosMAX);
    ataq = nextList(entrenadores[0].equipo[0].habilidades);
  }

  while(true)
  {
    while(true)
    {
      puts("");
      scanf("%d", &opcionAtaque);
      puts("");  
      
      if(opcionAtaque > 0 && opcionAtaque < 5) break;
      else printf("Elija una opcion entre 1 y 4.");
    }
    
    ataq = firstList(entrenadores[0].equipo[0].habilidades);    
  
    for(int j = 1 ; j != opcionAtaque ; j++) ataq = nextList(entrenadores[0].equipo[0].habilidades);
    
    if(ataq -> numUsosActual < 1) printf("No puedes seguir usando este movimiento, elija otro\n.");
    else break;
  }

  
  strcpy(ataque, ataq -> nombre);
  ataq -> numUsosActual--;

  sprintf(cadenaCompleta, "%s uso %s", entrenadores[0].equipo[0].nombre, ataque);
  escribirLentamente(cadenaCompleta, 2);
  sleep(1);

  *danio = calculoDano(Pokedex, Movimientos, Multiplicadores, &entrenadores[0].equipo[0], &entrenadores[posicion].equipo[0], *ataq);

  entrenadores[posicion].equipo[0].saludActual -= *danio; 

  if(entrenadores[0].equipo[0].saludActual <= 0)
  {
    entrenadores[0].cantidadVivos--;
    
    sprintf(cadenaCompleta, "%s se desmayo!", entrenadores[0].equipo[0].nombre);
    escribirLentamente(cadenaCompleta, 2);
    sleep(2);
    
    entrenadores[0].equipo[0].saludActual = 0;

    entrenadores[0].equipo[0].muerto = true;
    
    if(entrenadores[0].cantidadVivos < 1)
    {
      *ganador = 0;
    }

    cambiarPBatalla(entrenadores);
  }

  if(entrenadores[posicion].equipo[0].saludActual <= 0)
  {
    sprintf(cadenaCompleta, "%s enemigo se desmayo!", entrenadores[posicion].equipo[0].nombre);
    escribirLentamente(cadenaCompleta, 2);
    sleep(2);
    
    entrenadores[posicion].equipo[0].saludActual = 0;
    *vivo = 0;

    entrenadores[posicion].equipo[0].muerto = true;

    for(int i = 1 ; i < 6 ; i++)
    {
      if(entrenadores[posicion].equipo[5].muerto == true) break;
      else
      {
        if(entrenadores[posicion].equipo[i].muerto == false)
        {
          Pokemon aux = entrenadores[posicion].equipo[0];
          entrenadores[posicion].equipo[0] = entrenadores[posicion].equipo[i];
          entrenadores[posicion].equipo[i] = aux;

          char cambiarPokemon[MAX];
    
          sprintf(cadenaCompleta, "%s va a utilizar a %s ...",entrenadores[posicion].nombre, entrenadores[posicion].equipo[0].nombre);
          escribirLentamente(cadenaCompleta, 2);
          sleep(1);

          sprintf(cadenaCompleta, "%s, quieres cambiar de Pokemon? (s/n)", entrenadores[0].nombre);
          escribirLentamente(cadenaCompleta, 1);
          usleep(500000);

          scanf("%s", cambiarPokemon);
          getchar();
          
          if(strcmp(cambiarPokemon, "s") == 0)
          {
            strcpy(auxNombre, entrenadores[0].equipo[0].nombre);
            cambiarPBatalla(entrenadores);

            sprintf(cadenaCompleta, "%s vuelve", auxNombre);
            escribirLentamente(cadenaCompleta, 2);
            usleep(500000);

            sprintf(cadenaCompleta, "Ve %s!", entrenadores[0].equipo[0].nombre);
            escribirLentamente(cadenaCompleta, 1);
            usleep(500000);
          }
          puts("");
          sprintf(cadenaCompleta, "%s envio a %s!",entrenadores[posicion].nombre, entrenadores[posicion].equipo[0].nombre);
          escribirLentamente(cadenaCompleta, 2);
          sleep(1);

          break;
        }
      }
    }
  }
}

int dificultadNormal(Entrenador entrenadores[], HashMap *Pokedex, HashMap *Movimientos, HashMap *Multiplicadores)
{
  char cadenaCompleta[50];

  srand(time(NULL));
  
  int danio;

  Ataque *ataq = firstList(entrenadores[1].equipo[0].habilidades);

  int randAttack = rand() % 4 + 1;

  for(int i = 1 ; i != randAttack ; i++) ataq = nextList(entrenadores[1].equipo[0].habilidades);
  
  printf("%s enemigo uso %s\n\n", entrenadores[1].equipo[0].nombre, ataq->nombre);
  sprintf(cadenaCompleta, "%s enemigo uso %s", entrenadores[1].equipo[0].nombre, ataq->nombre);
  escribirLentamente(cadenaCompleta, 2);
  sleep(2);

  danio = calculoDano(Pokedex, Movimientos, Multiplicadores, &entrenadores[1].equipo[0], &entrenadores[0].equipo[0], *ataq);

  return danio;
}

