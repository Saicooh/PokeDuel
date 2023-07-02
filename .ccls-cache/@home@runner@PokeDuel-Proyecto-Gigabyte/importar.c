#include "main.h"

void cargarPokedex(HashMap *Pokedex, HashMap *Movimientos)
{
  FILE *fp = fopen("pokemon_pokedex.csv", "r");

  char linea[1024];
  char *cont;
  char *ataque;
  fgets(linea, 1023, fp);
  
  while(fgets(linea, 1023, fp) != NULL)
  {
    Pokemon *pokemonAux = malloc(sizeof(Pokemon));
    pokemonAux -> muerto = false;
  
    for(int i = 0; i < 8; i++)
    {
      char *aux = gets_csv_field(linea, i);
      
      switch(i)
      {
        case 0 : cont = strdup(aux); break;
        case 1 : strcpy(pokemonAux -> nombre, aux); break;
        case 2 : strcpy(pokemonAux -> tipo1, aux); break;
        case 3 : strcpy(pokemonAux -> tipo2, aux); break;
        case 4 : pokemonAux -> ataqueBase = atoi(aux); pokemonAux -> ataque = atoi(aux); break;
        case 5 : pokemonAux -> defensaBase = atoi(aux); pokemonAux -> defensa = atoi(aux); break;
        case 6 : pokemonAux -> salud = atoi(aux); pokemonAux -> saludActual = atoi(aux); break;
        case 7 :
          
          pokemonAux -> habilidades = createList();
          
          for (int j = 0 ; j < 4 ; j++)
          {
            ataque = gets_csv_field(linea, j+7);
            
            Pair *pairAux = searchMap(Movimientos, ataque);
            
            Ataque *ataqueOriginal = pairAux -> value;

            Ataque *ataqueAux = malloc(sizeof(Ataque));

            *ataqueAux = *ataqueOriginal;
            
            pushBack(pokemonAux -> habilidades, ataqueAux);
          }  
        break;
      }
    }
    insertMap(Pokedex, cont, pokemonAux);
  }
  fclose(fp);
}