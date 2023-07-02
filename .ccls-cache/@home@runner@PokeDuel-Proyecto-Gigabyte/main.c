#include "main.h"
//#include <windows.h>
void mostrarPokedex(HashMap *Pokedex)
{
  Pair *aux = firstMap(Pokedex);
  char numPokedex[4];
  int n = 1;

  printf("\x1b[32m%-4s | %-20s | %-15s | %-15s\x1b[0m\n", "#", "Nombre", "Tipo 1", "Tipo 2");
  printf("----------------------------------------------------\n");

  while(n != 152)
  {
    sprintf(numPokedex, "%i", n);
    Pair *aux2 = searchMap(Pokedex, numPokedex);
    Pokemon *pokemonAux = aux2 -> value;
    
    printf("%-4s | %-20s | %-15s | ", numPokedex, pokemonAux -> nombre, pokemonAux -> tipo1);
    
    if (strcmp(pokemonAux -> tipo2, "0") != 0) printf("%-15s\n", pokemonAux -> tipo2);
    else printf("N/A\n");
    
    n++;
  }
  puts("");
}

void agregarPokemon(Entrenador entrenadores[], int *equipoRegistrado, HashMap *Pokedex)
{
  char pokemonPKDX[MAX];
  int buscar;
  int size = entrenadores[0].sizeTeam;
  char cadenaCompleta[1000];
  
  if(size == 6)
  {
    escribirLentamente("El equipo esta lleno! No puedes agregar mas Pokemon.",2);
    return;
  }
  
  escribirLentamente("Ingrese numero de la Pokedex del Pokemon a agregar:",2);
  
  while(1)
  {
    scanf("%15s", pokemonPKDX);
    getchar();
    
    buscar = atoi(pokemonPKDX);
    
    if (buscar < 1 || buscar > 151)
    {
      puts("");
      escribirLentamente("Ingrese un numero valido entre 1 y 151.",1);
    }
    else break;
  }

  Pair *pokeBusc = searchMap(Pokedex, pokemonPKDX);

  Pokemon *pokemonOriginal = pokeBusc -> value;

  Pokemon *pokeAux = malloc(sizeof(Pokemon));

  *pokeAux = *pokemonOriginal;

  sprintf(cadenaCompleta, "\nPokemon: '%s', deseas agregarlo a tu equipo? (s/n)\n", pokeAux -> nombre);

  escribirLentamente(cadenaCompleta, 0);

  char salida[2];
  scanf("%1s", salida);
  
  if(strcmp(salida, "n") == 0) 
  {
    puts("");
    escribirLentamente("No se agrego ningun Pokemon.",2);
    return;
  }
  
  puts("");

  size++;
  escribirLentamente("Pokemon agregado!",2);
  sleep(1);
  entrenadores[0].equipo[entrenadores[0].sizeTeam] = *pokeAux;
  entrenadores[0].sizeTeam = size;
  entrenadores[0].cantidadVivos = size;
  
  *equipoRegistrado = 1;
}


void administrarPokemon(Entrenador entrenadores[], int *equipoRegistrado, int *volverMenu, HashMap *Pokedex)
{
  escribirLentamente("Que deseas realizar?",2);

  int opcion = 0;
  
  while (opcion != 5)
  {
    puts("1. Agregar Pokemon a tu equipo.");
    usleep(250000);
    puts("2. Eliminar Pokemon de tu equipo.");
    usleep(250000);
    puts("3. Administrar orden de equipo.");
    usleep(250000);
    puts("4. Ver tu equipo actual.");
    usleep(250000);
    puts("5. Volver al menu.\n");
    usleep(250000);
    
    validarOpcionPokemon(&opcion, *equipoRegistrado);
    
    switch (opcion)
    {
      case 1 : agregarPokemon(entrenadores, equipoRegistrado, Pokedex); break;
      case 2 : //eliminarPokemon(entrenadores); break;
      
      case 3 : //administrarOrden(entrenadores); break;
      
      case 4 :
      if (!*equipoRegistrado) break;  
      //verEquipoActual(entrenadores); break;
      
      case 5 : return;
    }
  }
}

int main()
{
/*
                      ____ _             _           _             
                     / ___(_) __ _  __ _| |__  _   _| |_ ___     
                    | |  _| |/ _` |/ _` | '_ \| | | | __/ _ \     
                    | |_| | | (_| | (_| | |_) | |_| | ||  __/     
                     \____|_|\__, |\__,_|_.__/ \__, |\__\___| 
                             |___/             |___/
                     ______                                      
                    (_____ \                           _         
                     _____) )___ ___  _   _  ____ ____| |_  ___  
                    |  ____/ ___) _ \| | | |/ _  ) ___)  _)/ _ \ 
                    | |   | |  | |_| | |_| ( (/ ( (___| |_| |_| |
                    |_|   |_|   \___/ \__  |\____)____)\___)___/ 
                                      (____/                      
*/

  srand(time(NULL));
  //playSongType(1,1,0);
  
  char trainer_username[MAX];
  
  escribirLentamente("Bienvenido al simulador de combates de Pokemon Pokeduel!", 2);
  
  escribirLentamente("Ingresa tu nombre de entrenador!", 1);
  
  scanf("%s", trainer_username);
  getchar();

  int user_continue = 1, equipoRegistrado = 0;
  
  Entrenador entrenadores[7];
  
  strcpy(entrenadores[0].nombre, trainer_username);

  HashMap *Pokedex = createMap(151);
  HashMap *Movimientos = createMap(105);
  HashMap *Objetos = createMap(15);
  HashMap *Multiplicadores = createMap(225);

  while(user_continue)
  {
    printf("\033[2J\033[H");
    int volverMenu = 0;
    menu();
    
    int opcion = 0;
    int entrenadorPos = 1;
    
    validarOpcion(&opcion);
    
    if(equipoRegistrado == 0 && opcion != 1 && opcion != 2 && opcion != 3 && opcion != 6) printf("Debes registrar al menos un Pokemon en tu equipo para acceder!\n");
      
    else switch(opcion)
    {
      case 1 :
        mostrarPokedex(Pokedex);
        validar(&user_continue);
        break;

      case 2 :
        administrarPokemon(entrenadores, &equipoRegistrado, &volverMenu, Pokedex);
        break;

      case 3 :
        //administrarObjetos(Objetos,entrenadores);
        break;

      case 4 :
        //entrenamientoPokemon(entrenadores, Pokedex, Movimientos, Multiplicadores, entrenadorPos, &ganador);
        break;

      case 5 :
        //ligaPokemon(entrenadores, Pokedex, Movimientos, Multiplicadores, Objetos, &ganador);
        validar(&user_continue);
        //playSongType(1,1,0,0);
        break;

      case 6 : 
        escribirLentamente("Gracias por usar PokeDuel, esperamos que hayas disfrutado del juego!", 0);
        exit(EXIT_SUCCESS);
    }
  }
  
  return 0;
  
}