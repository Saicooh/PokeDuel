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

void cargarObjetos(HashMap *Objetos)
{
  FILE *fp = fopen("pokemon_objetos.csv", "r");

  char linea[1024];
  int i;
  char *cont;
  
  fgets(linea, 1023, fp);
  
  int contador = 1;
  
  while(fgets(linea, 1023, fp) != NULL)
  {
    Objeto *objetoAux = malloc(sizeof(Objeto));
    for(i = 0; i < 6; i++)
    {
      char *aux = gets_csv_field(linea, i);
      
      switch(i)
      {
        case 0 : strcpy(objetoAux -> nombre, aux); break;
        case 1 : objetoAux->curacion = atoi(aux); break;
        case 2 : objetoAux->pp = atoi(aux); break;
        case 3 : objetoAux -> revive =  atoi(aux); break;
        case 4 : objetoAux->todos =  atoi(aux); break;
        case 5 : cont = strdup(aux); break;
      }
    }
    insertMap(Objetos,cont,objetoAux);
  }
  fclose(fp);
}

void cargarMovimientos(HashMap *Movimientos)
{
  FILE *fp = fopen("pokemon_movimientos.csv", "r");

  char linea[1024];
  int i;

  fgets(linea, 1023, fp);
  
  while(fgets(linea, 1023, fp) != NULL)
  {
    Ataque *ataqueAux = malloc(sizeof(Ataque));

    for(int i = 0; i < 9; i++)
    {
      char *aux = gets_csv_field(linea, i);
      switch(i)
      {
        case 0 : strcpy(ataqueAux -> nombre, aux); break;
        case 1 : ataqueAux -> potencia = atoi(aux); break;
        case 2 : strcpy(ataqueAux -> tipo, aux); break;
        case 3 : ataqueAux -> precision = atoi(aux); break;
        case 4 : ataqueAux -> numUsosMAX = atoi(aux); ataqueAux -> numUsosActual = atoi(aux); break;
        case 5 : ataqueAux -> efectoAtaque = atof(aux); break;
        case 6 : ataqueAux -> efectoDefensa = atof(aux); break;
        case 7 : ataqueAux -> efectoSalud = atof(aux); break;
        case 8 : ataqueAux -> direccion = atoi(aux); break;
      }
    }
    insertMap(Movimientos, ataqueAux -> nombre, ataqueAux);
  }
  fclose(fp);
}

void cargarMultiplicadores(HashMap *multiplicadores)
{
  FILE *fp = fopen("pokemon_multiplicadores.csv", "r");

  char linea[1024];
  int i;

  fgets(linea, 1023, fp);
  
  while(fgets(linea, 1023, fp) != NULL)
  {
    TipoElem *multi = malloc(sizeof(TipoElem));

    for(i = 0; i < 2; i++)
    {
      char *aux = gets_csv_field(linea, i);
      
      switch(i)
      {
        case 0 : strcpy(multi -> nombre, aux); break;
        case 1 : multi -> multiplicador = atof(aux); break;
      }
    }
    
    float multiplicador = multi -> multiplicador;
    float *ptr_multiplicador = malloc(sizeof(float));
    
    *ptr_multiplicador = multiplicador;

    insertMap(multiplicadores, multi -> nombre, ptr_multiplicador);
  }
  fclose(fp);
}

void cargarEntrenadoresLiga(Entrenador entrenadores[], HashMap *Pokedex)
{
  FILE *fp = fopen("pokemon_entrenadores_liga.csv", "r");

  char linea[1024];
  fgets(linea, 1023, fp);
  int j;

  Pair *auxPok;
  Pokemon *auxPok2;

  for (j = 2; j < 7; j++)
  {
    entrenadores[j].sizeTeam = 6;
    entrenadores[j].cantidadVivos = 6;
    
    if (fgets(linea, 1023, fp) == NULL) break;

    auxPok2 = malloc(sizeof(Pokemon));
    
    for(int i = 0; i < 7; i++)
    {
      char *aux = gets_csv_field(linea, i);
      if(i == 0) strcpy(entrenadores[j].nombre, aux); 
      else
      {
        auxPok = searchMap(Pokedex, aux);
        auxPok2 = auxPok -> value;
        entrenadores[j].equipo[i-1] = *auxPok2;
      }
    }
  }
  free(auxPok2);
  fclose(fp);
}
