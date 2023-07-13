#include "main.h"

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

void administrarOrden(Entrenador entrenadores[])
{
  char cadenaCompleta[1000];
  int size = entrenadores[0].sizeTeam;
  
  if (entrenadores[0].sizeTeam == 1)
  {
    escribirLentamente("Solo hay un Pokemon en el equipo, debes anadir al menos uno mas para acceder a esta funcion.",2);
    return;
  }
  
  int pos1, pos2;
  Pokemon aux;

  verEquipoActual(entrenadores);
  
  escribirLentamente("Ingresa posicion del Pokemon de origen:",1);
  scanf("%i", &pos1);
  pos1--;

  while(pos1 > size - 1 || pos1 < 0)
  {
    if (pos1 > size - 1) printf("\nIngresa posicion del Pokemon de origen valida, el equipo solo tiene %i Pokemon:\n", entrenadores[0].sizeTeam);
    if(pos1 < 0) printf("\nEl numero ingresado es invalido, ingresa un numero positivo:\n");
    scanf("%i", &pos1);
    pos1--;
  }
  
  puts("");
  escribirLentamente("Ingresa posicion del Pokemon de destino:",1);
  scanf("%i", &pos2);
  pos2--;

  while(pos2 > size - 1 || pos2 < 0)
  {
    if (pos2 > size - 1) printf("\nIngresa posicion del Pokemon de destino valida, el equipo solo tiene %i Pokemon:\n", entrenadores[0].sizeTeam);
    if(pos2 < 0) printf("\nEl numero ingresado es invalido, ingresa un numero positivo:\n");
    scanf("%i", &pos2);
    pos2--;
  }
  
  if (pos1 == pos2)
  {
    escribirLentamente("No se ha hecho ningun cambio, las posiciones son iguales.",1);
    return;
  }
  
  aux = entrenadores[0].equipo[pos1];
  entrenadores[0].equipo[pos1] = entrenadores[0].equipo[pos2];
  entrenadores[0].equipo[pos2] = aux;

  sprintf(cadenaCompleta, "\nPokemon '%s' ha sido intercambiado de posicion con '%s'!\n\n", entrenadores[0].equipo[pos1].nombre, entrenadores[0].equipo[pos2].nombre);
  escribirLentamente(cadenaCompleta, 0);
}

void verEquipoActual(Entrenador entrenadores[])
{
  int size = entrenadores[0].sizeTeam;

  char encabezado[50];
  sprintf(encabezado, "Equipo Pokemon de '%s'", entrenadores[0].nombre);
  int espaciosExtra = calcularEspaciosExtra(strlen(encabezado), 50);

  puts("+--------------------------------------------------+");
  printf("|%*s%*s|\n", espaciosExtra + (int) strlen(encabezado), encabezado, espaciosExtra, "");
  puts("+----+----------------------+---------+------------+");
  printf("| No | %-20s |   %-5s |    LVL     |\n", "Nombre", "PS");
  puts("+----+----------------------+---------+------------+");
  
  for (int i = 0 ; i < size ; i++)
  {
    char pokemon_info[31];
    sprintf(pokemon_info, "%-20s | %-3d/%-3d", entrenadores[0].equipo[i].nombre, entrenadores[0].equipo[i].saludActual, entrenadores[0].equipo[i].salud);
    espaciosExtra = calcularEspaciosExtra(strlen(pokemon_info), 30);  // 30 = longitud total del campo - 1

    printf("| %-2d | %*s%*s |  LVL. 100  |\n", i + 1, espaciosExtra + (int) strlen(pokemon_info), pokemon_info, espaciosExtra, "");
  }
  
  puts("+----+----------------------+---------+------------+");
  puts("");
}

void eliminarPokemon(Entrenador entrenadores[])
{
  char cadenaCompleta[1000];
  bool encontrado = false;
  int pokemonElim;
  char *auxPokeElim = malloc(MAX * sizeof(char));
  verEquipoActual(entrenadores);
  
  escribirLentamente("Ingrese Pokemon a eliminar del equipo:",1);
  
  scanf("%i", &pokemonElim);
  pokemonElim--;
  
  strcpy(auxPokeElim, entrenadores[0].equipo[pokemonElim].nombre);
  
  int i = 0;

  entrenadores[0].equipo[pokemonElim].nombre[0] = '\0';
  entrenadores[0].sizeTeam--;

  for (int i = pokemonElim; i < entrenadores[0].sizeTeam - 1; i++)
  {
    entrenadores[0].equipo[i] = entrenadores[0].equipo[i + 1];
  }
  
  sprintf(cadenaCompleta, "\nPokemon '%s' ha sido eliminado del equipo!\n\n", auxPokeElim);
  escribirLentamente(cadenaCompleta, 0);
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
      
      case 2 : eliminarPokemon(entrenadores); break;
      
      case 3 : administrarOrden(entrenadores); break;
      
      case 4 :
      if (!*equipoRegistrado) break;  
      verEquipoActual(entrenadores); break;
      
      case 5 : return;
    }
  }
}

void mostrarObjetos(HashMap *Objetos)
{
  Pair *auxMapa = firstMap(Objetos);
  int contador = 1;
  char *id = malloc(5 * sizeof(char));
  puts("+-----------------------------------+");
  puts("|        Listado de Objetos         |");
  puts("+-----------------------------------+");
  printf("| %-3s | %-27s |\n", "ID.", "Nombre");
  puts("+-----+-----------------------------+");
  
  while (contador != 14)
  {
    sprintf(id, "%i", contador);
    Pair *auxObjetos = searchMap(Objetos, id);
    Objeto *aux = auxObjetos -> value;
    
    printf("| %-3s | %-27s |\n", id, aux->nombre);
    contador++;
    auxMapa = nextMap(Objetos);
  }

  puts("+-----+-----------------------------+");
  sleep(1);
  puts("");
}

void mostrarMochila(Entrenador entrenadores[]) 
{
  escribirLentamente("Objetos en la mochila:",2);
  sleep(1);

  if(entrenadores[0].cantidadObj == 0)
  {
    escribirLentamente("No hay objetos en la mochila",2);
    sleep(1);
    return;
  }

  for (int i = 0 ; i < entrenadores[0].cantidadObj ; i++)
  {
    printf("%i. %s (Cantidad : %i)\n", i+1, entrenadores[0].mochila[i].nombre, entrenadores[0].mochila[i].cantidad);
  }
}

void eliminarObjeto(Entrenador entrenadores[])
{
  mostrarMochila(entrenadores);
  int numObj;
  int eliminar;
  char cadenaCompleta[1000];
  char item[MAX];
  
  puts("");
  escribirLentamente("Ingrese el objeto que desea eliminar de su mochila:",1);
  scanf("%i", &numObj);
  puts("");
  escribirLentamente("Ingrese la cantidad que desea eliminar",1);
  scanf("%d",&eliminar);
  numObj--;
  
  if(eliminar == 0 || numObj > entrenadores[0].cantidadObj)
  {
    puts("");
    escribirLentamente("Ingrese un Objeto o Cantidad Valida",1);
    sleep(1);
    return eliminarObjeto(entrenadores);
  }
  
  if(eliminar == entrenadores[0].mochila[numObj].cantidad)
  {
    char *aux = malloc(MAX * sizeof(char));
    strcpy(aux, entrenadores[0].mochila[numObj].nombre);
    
    for (int i = numObj; i < entrenadores[0].cantidadObj - 1; i++) 
    {
      entrenadores[0].mochila[i] = entrenadores[0].mochila[i + 1];
    }
    
    sprintf(cadenaCompleta, "\nEl objeto: %s ha sido eliminado de la mochila.\n",aux);

    escribirLentamente(cadenaCompleta, 0);
    
    free(aux);

    entrenadores[0].mochila = realloc(entrenadores[0].mochila, (entrenadores[0].cantidadObj - 1) * sizeof(Objeto));
    
    entrenadores[0].cantidadObj--;
    return;
  }
  else entrenadores[0].mochila[numObj].cantidad -= eliminar;
  
  printf("Se le ha restado %i a %s", eliminar, entrenadores[0].mochila[numObj].nombre);

}

void agregarObjeto(HashMap *Objetos, Entrenador entrenadores[])
{
  char item[3];
  int indice;
  int cantidad; 

  mostrarObjetos(Objetos);

  //Se pide el usuario Ingresar el Objeto añadir y su cantidad correspondiente
  puts("\nIngrese el objeto a anadir:\n");
  scanf("%d", &indice);

  //Se realiza una verificacion de que el item sea valido.

  if(indice <= 0 || indice > 13)
  {
    printf("\nIngrese un Item valido\n");
    return agregarObjeto(Objetos, entrenadores);
  }
  
  puts("\nIngrese la cantidad que quiere agregar (Max 99):");
  scanf("%d", &cantidad);

  sprintf(item, "%i", indice);
  
  // Aca realizamos Una verificacion sobre que la cantidad sea una cantidad valida
  while (cantidad < 0 || cantidad > 99)
  {
    puts("\nIngrese una cantidad valida (entre 0 y 99):");
    scanf("%d", &cantidad);
  }

  //Aca pasamos todos los datos del Item del mapa de Objetos a la mochila del usuario.
  entrenadores[0].mochila = realloc(entrenadores[0].mochila, (entrenadores[0].cantidadObj + 1) * sizeof(Objeto));

  Pair *objetoPair = searchMap(Objetos,item);
  Objeto *auxObjeto = malloc(sizeof(Objeto));
  Objeto *auxObjetoOriginal = objetoPair->value;

  *auxObjeto = *auxObjetoOriginal;
  auxObjeto -> cantidad = cantidad;
    
  entrenadores[0].mochila[entrenadores[0].cantidadObj] = *auxObjeto;
  entrenadores[0].cantidadObj++;
}

void menuObjeto(int *opcion)
{
  puts("\nQue deseas realizar?\n");
  puts("1. Ver todos los objetos disponibles.");
  usleep(250000);
  puts("2. Agregar un objeto a tu mochila.");
  usleep(250000);
  puts("3. Ver tus objetos.");
  usleep(250000);
  puts("4. Eliminar un objeto de la mochila.");
  usleep(250000);
  puts("5. Volver al menu.\n");

  scanf("%d", &opcion);
  getchar();
}

void administrarObjetos(HashMap *Objetos, Entrenador entrenadores[])
{
  printf("\033[2J\033[H");

  int opcion;
  
  while (1)
  {
    menuObjeto(&opcion);
    switch (opcion)
    {
      case 1 : mostrarObjetos(Objetos); break;
      case 2 : agregarObjeto(Objetos, entrenadores); break;
      case 3 : mostrarMochila(entrenadores); break;
      case 4 : eliminarObjeto(entrenadores); break;
      case 5 : return;
      default : puts("Ingrese una opcion valida.");
    }
  }
}

void entrenamientoPokemon(Entrenador entrenadores[], HashMap *Pokedex, HashMap *Movimientos, HashMap *Multiplicadores,int entrenadorPos, int *ganador)
{
  char cadenaCompleta[1000];
  srand(time(NULL));
  
  int danio = 0;

  if(entrenadorPos == 1) printf("\033[2J\033[H");
  
  char auxNombre[MAX];
  int dificultad;

  *ganador = 1;

  if(entrenadorPos == 1)
  {
    playSongType(8,0,0,1);
    puts("");
    escribirLentamente("BIENVENIDO AL MODO ENTRENAMIENTO!!", 2);
    sleep(2);
    escribirLentamente("La entrenadora Jesicca sera tu enemigo!", 2);
    sleep(2);
    escribirLentamente("Escoge la dificultad del entrenamiento (1 = normal y 2 = dificil)", 2);
    
    while(1)
    {
      scanf("%d", &dificultad);
      if(dificultad == 1 || dificultad == 2) break;
      else printf("Escoja una dificultad correspondiente (1 o 2)");
    }
    
    escribirLentamente("Este sera el equipo de Jessica contra el que te enfrentaras:", 2);
    mostrarEquipoEnemigo(entrenadores, Pokedex);
  }
  else dificultad = 2;
  
  char pokeNum[MAX];
  int numPokedex;
  int size;
  int vivo = 1;

 if(entrenadorPos == 1) 
  {
    playSongType(2,1,0,1);
    printf("\033[2J\033[H");
  }
  
  puts("");
  escribirLentamente("La batalla comienza ahora!!",3);
  sleep(2);

  printf("\033[2J\033[H");

  sprintf(cadenaCompleta, "%s envio a %s",entrenadores[entrenadorPos].nombre, entrenadores[entrenadorPos].equipo[0].nombre);
  escribirLentamente(cadenaCompleta, 2);
  sleep(1);

  sprintf(cadenaCompleta, "Ve %s!", entrenadores[0].equipo[0].nombre);
  escribirLentamente(cadenaCompleta, 2);
  sleep(1);
  
  bool first = true;
  
  while(true)
  {
    if(entrenadores[0].equipo[0].muerto == true || entrenadores[entrenadorPos].equipo[0].muerto == true) break;

    infoEntrenador(entrenadores, 0);
    infoEntrenador(entrenadores, entrenadorPos);

    menuPelea();

    int opcionMenuBatalla;
    
    scanf("%d", &opcionMenuBatalla);
    puts("");

    if(entrenadorPos == 1)
    {
      switch(opcionMenuBatalla)
      {
        case 1 : atacar(entrenadores, Pokedex, Movimientos, Multiplicadores, &danio, entrenadorPos, &vivo, ganador); break;
  
        case 2 :
          entrenadores[0].equipo[0].ataque = entrenadores[0].equipo[0].ataqueBase;
          entrenadores[0].equipo[0].defensa = entrenadores[0].equipo[0].defensaBase;
          cambiarPBatalla(entrenadores); break;
        
        case 3 : usarObjeto(entrenadores); break;
        
        case 4 :
          entrenadores[0].equipo[0].ataque = entrenadores[0].equipo[0].ataqueBase;
          entrenadores[0].equipo[0].defensa = entrenadores[0].equipo[0].defensaBase;
          escribirLentamente("Has huido de la batalla ...", 2); 
          sleep(2);
          reiniciar(entrenadores);
          playSongType(1,1,0,1);
          return;
      }
    }
    else
    {
      while(opcionMenuBatalla == 4)
      {
        escribirLentamente("No puedes huir.",2);
        infoEntrenador(entrenadores, entrenadorPos);
        scanf("%d", &opcionMenuBatalla);
        puts("");
      }
      
      switch(opcionMenuBatalla)
      {
        case 1 : atacar(entrenadores, Pokedex, Movimientos, Multiplicadores, &danio, entrenadorPos, &vivo, ganador); break;
  
        case 2 : 
          entrenadores[0].equipo[0].ataque = entrenadores[0].equipo[0].ataqueBase;
          entrenadores[0].equipo[0].defensa = entrenadores[0].equipo[0].ataqueBase;
          cambiarPBatalla(entrenadores); break;
        
        case 3 : usarObjeto(entrenadores); break;
      }
    }
    
    first = false;

    danio = 0;
    
    if(vivo == 1)
    {
      switch(dificultad)
      {
        case 1 : danio = dificultadNormal(entrenadores, Pokedex, Movimientos, Multiplicadores); break;
        
        case 2 : danio = dificultadDificil(entrenadores, Pokedex, Movimientos, Multiplicadores, entrenadorPos); break;
      }
    }

    if(entrenadores[entrenadorPos].equipo[0].saludActual <= 0)
    { 
      if(entrenadores[entrenadorPos].equipo[5].muerto == false) 
      {
        sprintf(cadenaCompleta,"%s se desmayo!", entrenadores[entrenadorPos].equipo[0].nombre);
        escribirLentamente(cadenaCompleta, 2);
      }
      
      entrenadores[entrenadorPos].equipo[0].saludActual = 0;
      vivo = 0;
  
      entrenadores[entrenadorPos].equipo[0].muerto = true;
  
      for(int i = 1 ; i < 6 ; i++)
      {
        if(entrenadores[entrenadorPos].equipo[5].muerto == true) break;
        else
        {
          if(entrenadores[entrenadorPos].equipo[i].muerto == false)
          {
            Pokemon aux = entrenadores[entrenadorPos].equipo[0];
            entrenadores[entrenadorPos].equipo[0] = entrenadores[entrenadorPos].equipo[i];
            entrenadores[entrenadorPos].equipo[i] = aux;
  
            char cambiarPokemon[MAX];

            sprintf(cadenaCompleta, "%s va a utilizar a %s ...\n\n",entrenadores[entrenadorPos].nombre, entrenadores[entrenadorPos].equipo[0].nombre);
            escribirLentamente(cadenaCompleta, 2);
            sleep(1);

            sprintf(cadenaCompleta, "%s, quieres cambiar de Pokemon? (s/n)", entrenadores[0].nombre);
            escribirLentamente(cadenaCompleta, 1);

            scanf("%s", cambiarPokemon);
            getchar();
            
            if(strcmp(cambiarPokemon, "s") == 0)
            {
              strcpy(auxNombre, entrenadores[0].equipo[0].nombre);
              entrenadores[0].equipo[0].ataque = entrenadores[0].equipo[0].ataqueBase;
              entrenadores[0].equipo[0].defensa = entrenadores[0].equipo[0].defensaBase;
              cambiarPBatalla(entrenadores);

              sprintf(cadenaCompleta, "%s vuelve", auxNombre);
              escribirLentamente(cadenaCompleta, 2);
              usleep(500000);

              sprintf(cadenaCompleta, "Ve %s!", entrenadores[0].equipo[0].nombre);
              escribirLentamente(cadenaCompleta, 2);
              usleep(500000);
            }
            
            puts("");
            sprintf(cadenaCompleta, "%s envio a %s", entrenadores[entrenadorPos].nombre, entrenadores[entrenadorPos].equipo[0].nombre);
            escribirLentamente(cadenaCompleta, 2);
            break;
          }
        }
      }
    }
    
    entrenadores[0].equipo[0].saludActual -= danio;

    contadorBajando2(entrenadores, entrenadores[0].equipo[0].saludActual, danio, 0);
    
    float health_percent = ((float) entrenadores[0].equipo[0].saludActual / entrenadores[0].equipo[0].salud) * 100;

    printf("Porcentaje de vida restante : %.2f%%\n\n", health_percent);
  
    if (health_percent <= 25 && health_percent > 0 && Mix_Playing(0) == 0) playSongType(10,0,0,0);

    if(vivo == 0) vivo = 1;
    
    if(entrenadores[0].equipo[0].saludActual <= 0)
    {
      entrenadores[0].cantidadVivos--;
      
      sprintf(cadenaCompleta,"%s se desmayo!", entrenadores[0].equipo[0].nombre);
      escribirLentamente(cadenaCompleta, 2);
      sleep(3);
      
      entrenadores[0].equipo[0].saludActual = 0;
  
      entrenadores[0].equipo[0].muerto = true;
      
      if(entrenadores[0].cantidadVivos < 1)
      {
        *ganador = 0;
        break;
      }
      entrenadores[0].equipo[0].ataque = entrenadores[0].equipo[0].ataqueBase;
      entrenadores[0].equipo[0].defensa = entrenadores[0].equipo[0].defensaBase;
      cambiarPBatalla(entrenadores);
    }
  }

  if(entrenadorPos == 1)
  {
    reiniciar(entrenadores);
    
    if(*ganador == 1)
    {
      playSongType(5,0,0,1);
      escribirLentamente("Felicidades has derrotado a la Entrenadora Jessica!!", 2);
      sleep(4);
      system("clear");
      playSongType(1,1,0,1);
      return;
    }
    else
    {
      sleep(1);
      
      sprintf(cadenaCompleta, "%s se ha quedado sin Pokemon disponibles!", entrenadores[0].nombre);
      escribirLentamente(cadenaCompleta, 2);

      sleep(2);
      escribirLentamente("Has perdido ...", 1);

      sleep(2);
      playSongType(1,1,0,1);
      return;
    }
  }
}

void ligaPokemon(Entrenador entrenadores[], HashMap *Pokedex, HashMap *Movimientos, HashMap *Multiplicadores,HashMap *Objetos, int ganador)
{
  char cadenaCompleta[1000];
  
  printf("\033[2J\033[H");

  playSongType(3,0,0,1);

  escribirLentamente("BIENVENIDO A LA LIGA POKEMON!!", 2);
  sleep(2);
  escribirLentamente("Te enfrentaras contra entrenadores muy duros a continuacion !!", 2);
  sleep(2);
  escribirLentamente("Si pierdes contra alguno de ellos, perderas todo tu progreso y tendras que empezar de nuevo !", 2);
  sleep(2);
  escribirLentamente("Recuerda que no puedes huir.", 2);
  sleep(2);
  escribirLentamente("Buena suerte!!", 2);
  sleep(4);

  for(int entrenadorPos = 2 ; entrenadorPos < 7 ; entrenadorPos++)
  {
    entrenadores[0].equipo[0].ataque = entrenadores[0].equipo[0].ataqueBase;
    entrenadores[0].equipo[0].defensa = entrenadores[0].equipo[0].defensaBase;
    
    printf("\033[2J\033[H");
    
    if (entrenadorPos == 6)
    {
      playSongType(7,0,0,1);

      sleep(1);

      escribirLentamente("Hola .......", 2);
      sleep(2);

      escribirLentamente("Soy el campeon .............", 0);
      escribirLentamente("Ignacio Araya ...", 2);
      sleep(2);

      escribirLentamente("Te felicito por llegar hasta aqui ............", 2);
      sleep(2);

      escribirLentamente("Pero no te dejare ganar tan facilmente ............", 2);
      sleep(2);
      
      playSongType(9,1,0,1);
      printf("\033[2J\033[H");
      sleep(1);
    }
    else
    {
      playSongType(4,1,entrenadorPos-2,1);
      puts("");
      sprintf(cadenaCompleta, "Te enfrentaras contra %s!",entrenadores[entrenadorPos].nombre);
      escribirLentamente(cadenaCompleta, 1);
      sleep(3);
    }
    while(true)
    {
      entrenamientoPokemon(entrenadores, Pokedex, Movimientos, Multiplicadores, entrenadorPos, &ganador);
      
      if(ganador == 0)
      {
        sleep(2);
        sprintf(cadenaCompleta, "%s se ha quedado sin Pokemon disponibles!", entrenadores[0].nombre);

        escribirLentamente(cadenaCompleta, 2);
        sleep(2);

        escribirLentamente("Has perdido ...", 1);
        sleep(2);

        playSongType(1,1,0,1);
        system("cls");
        return;
      }
      else
      {
        if(entrenadorPos == 6) playSongType(6,0,0,1);
        else playSongType(5,0,0,1);
        sprintf(cadenaCompleta, "Has derrotado a %s!!", entrenadores[entrenadorPos].nombre);
        escribirLentamente(cadenaCompleta, 2);
        sleep(4);
        
        if(entrenadorPos != 6)
        {
          int opcionBatallaLiga = 0;
          
          while(opcionBatallaLiga != 3)
          {
            printf("Que desea hacer?\n\n");
            printf("1. Administar Pokemon.\n");
            printf("2. Usar Objeto.\n");
            printf("3. Continuar con las batallas.\n");
            
            scanf("%d", &opcionBatallaLiga);
              
            switch(opcionBatallaLiga)
            {
              case 1: administrarOrden(entrenadores); break;
    
              case 2: usarObjeto(entrenadores); break;
            }
          }
        }
        break;
      }
    }
  }
  
  salonDeLaFama(entrenadores);
  reiniciar(entrenadores);
  return;
}

int main(int argc, char *argv[])
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

  iniciarSDL();
  
  char trainer_username[MAX];
  
  playSongType(1,1,0,1);

  escribirLentamente("Bienvenido al simulador de combates de Pokemon Pokeduel!", 2);
  sleep(1);

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
  
  cargarMultiplicadores(Multiplicadores);
  cargarMovimientos(Movimientos);
  cargarPokedex(Pokedex, Movimientos);
  cargarObjetos(Objetos);
  cargarEntrenadoresLiga(entrenadores, Pokedex);
  
  strcpy(entrenadores[1].nombre, "Jessica");
  
  int ganador;
  
  entrenadores[0].cantidadObj = 0;
  
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
        administrarObjetos(Objetos,entrenadores);
        break;

      case 4 :
        entrenamientoPokemon(entrenadores, Pokedex, Movimientos, Multiplicadores, entrenadorPos, &ganador);
        break;

      case 5 :
        ligaPokemon(entrenadores, Pokedex, Movimientos, Multiplicadores, Objetos, &ganador);
        validar(&user_continue);
        playSongType(1,1,0,1);
        break;

      case 6 : 
        escribirLentamente("Gracias por usar PokeDuel, esperamos que hayas disfrutado del juego!", 0);
        exit(EXIT_SUCCESS);
    }
  }

  SDL_Quit();

  return 0;
}
