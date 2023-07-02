  #include "main.h"

int calculoDano(HashMap *Pokedex, HashMap *Movimientos, HashMap *Multiplicadores, Pokemon *PokeAtaca, Pokemon *PokeRecibe, Ataque ataque)
{
  if(ataque.direccion == 1)
  {
    if(ataque.efectoAtaque != 1)
    {
      PokeAtaca->ataque = PokeAtaca->ataque + (PokeAtaca->ataqueBase * ataque.efectoAtaque) / (1 + PokeAtaca->ataque / PokeAtaca->ataqueBase);
    }
    else if(ataque.efectoDefensa != 1)
    {
      PokeAtaca->defensa = PokeAtaca->defensa + (PokeAtaca->defensaBase * ataque.efectoDefensa) / (1 + PokeAtaca->ataque / PokeAtaca->defensaBase);
    }
    else if(ataque.efectoSalud > 1 && ataque.efectoSalud != 50)
    {
      PokeAtaca->saludActual *= ataque.efectoSalud;
      if(PokeAtaca->saludActual > PokeAtaca->salud) PokeAtaca->saludActual = PokeAtaca->salud;
    }
  }
  else if(ataque.direccion == 2)
  {
    if(ataque.efectoAtaque != 1)
    { 
      PokeRecibe->ataque = PokeRecibe->ataqueBase - (PokeRecibe->ataqueBase - (PokeRecibe->ataque * ataque.efectoAtaque));
    }
    else if(ataque.efectoDefensa != 1)
    {
      PokeRecibe->defensa = PokeRecibe->defensaBase - (PokeRecibe->defensaBase - (PokeRecibe->defensa * ataque.efectoAtaque));
    }
    else if(ataque.efectoSalud < 1)
    {
      PokeRecibe->saludActual *= ataque.efectoSalud;
    }
  }
  
  if(ataque.potencia > 0)
  {
    srand(time(NULL));
    
    char *concatAttack = malloc(MAX * sizeof(char));
  
    concatAttack[0] = '\0';
    
    float bono, *mult1, *mult2, eficiencia, atk, potencia, defensaRecibe, randomAcc, modifAcc;
    
    if (strcmp(PokeAtaca->tipo1, ataque.tipo) == 0) bono = 1.5;
    else bono = 1;
  
    int crit;
  
    float *num1 = malloc(sizeof(float));
    *num1 = 1;
  
    randomAcc = rand() % 256;
    
    modifAcc = (ataque.precision / 100.0) * 255;
    
    if (randomAcc >= modifAcc)
    {
      printf("El ataque ha fallado!\n\n");
      return 0;
    }
  
    int probabilidadCrit = rand() % 100 + 1;
    
    if (probabilidadCrit <= 6) crit = 2;
    else crit = 1;
  
    char *aux = malloc(MAX * sizeof(char));
  
    strcpy(aux, ataque.tipo);
    
    concatAttack = strcat(aux, PokeRecibe->tipo1);
    
    Pair *aux4 = searchMap(Multiplicadores, concatAttack);
    mult1 = aux4 -> value;
    
    concatAttack[0] = '\0';
  
    strcpy(aux, ataque.tipo);
    
    if (PokeRecibe->tipo2[0] == '0') mult2 = num1;
    else if (PokeRecibe->tipo2[0] != '0')
    {
      concatAttack = strcat(aux, PokeRecibe->tipo2);
      
      Pair *aux5 = searchMap(Multiplicadores, concatAttack);
      
      mult2 = aux5 -> value;
    }
    
    eficiencia = *mult1 * *mult2;
  
    atk = PokeAtaca->ataque;
    potencia = ataque.potencia;
  
    defensaRecibe = PokeRecibe->defensa;
    
    float parte1 = ((2 * 100 * crit * 0.2) + 2);
    float parte2 = potencia * (atk/defensaRecibe);
    float parte3 = bono * eficiencia;
  
    float parte4 = ( ( (parte1 * parte2) / 50) + 2) * parte3;
  
    float var = rand() % 39 + 217;
    var = var / 255;
    
    float potenciaFinal = parte4 * var;
    
    if (eficiencia == 0)
    {
      escribirLentamente("No le afecta ...", 2);
      return 0;
    }
    
    if (crit == 2) escribirLentamente("GOLPE CRITICO!", 2);
    
    if (eficiencia == 0.25) escribirLentamente("Muy poco eficaz ...", 2);
    else if (eficiencia == 0.5) escribirLentamente("Poco eficaz ...", 2);
    else if (eficiencia == 2.0) escribirLentamente("Es muy eficaz!", 2);
    else if (eficiencia == 4.0) escribirLentamente("Es super eficaz!", 2);

    sleep(1);
    
    free(concatAttack);
    free(num1);

    if(ataque.efectoSalud == 50)
    {
      PokeAtaca->saludActual += potenciaFinal/2;
      if(PokeAtaca->saludActual > PokeAtaca->salud) PokeAtaca->saludActual = PokeAtaca->salud;
    }
    else if(ataque.direccion == 1 && ataque.efectoSalud < 1)
    {
      if(ataque.efectoSalud == 0) PokeAtaca->saludActual = 0;
      else
      {
        PokeAtaca->saludActual -= potenciaFinal * ataque.efectoSalud;
        if(PokeAtaca->saludActual < 0) PokeAtaca->saludActual = 0;
      }
      
    }
    
    return potenciaFinal;
  }
  
  return 0;
}

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

int dificultadDificil(Entrenador entrenadores[], HashMap *Pokedex, HashMap *Movimientos, HashMap *Multiplicadores, int posicion)
{
  char cadenaCompleta[100];
  
  AtkEfc *arr = malloc(4 * sizeof(AtkEfc));

  int danio = 0;
  float eficiencia[3];
  float *mult1, *mult2;
  float *numeroUno = malloc(sizeof(float));
  *numeroUno = 1;
  
  char *concatAttack = malloc(MAX * sizeof(char));
  char *tipoAtaq = malloc(MAX * sizeof(char));
  
  Ataque *ataq = firstList(entrenadores[posicion].equipo[0].habilidades);

  
  for(int i = 0 ; i < 4 ; i++)
  {
    strcpy(tipoAtaq,ataq->tipo);

    concatAttack = strcat(tipoAtaq, entrenadores[0].equipo[0].tipo1);
    
    Pair *aux = searchMap(Multiplicadores, concatAttack);
    
    mult1 = aux -> value;

    concatAttack[0] = '\0';

    strcpy(tipoAtaq,ataq->tipo);
    
    if (entrenadores[0].equipo[0].tipo2[0] == '0')
    {
      mult2 = numeroUno;
    }
    else if (entrenadores[0].equipo[0].tipo2[0] != '0')
    {
      concatAttack = strcat(tipoAtaq, entrenadores[0].equipo[0].tipo2);
      Pair *aux2 = searchMap(Multiplicadores, concatAttack);
      if(aux2 == NULL) printf("a\n");
      mult2 = aux2 -> value;
    }
    
    arr[i].atk = *ataq;
    arr[i].efc = *mult1 * *mult2;
    arr[i].pos = i;
    
    ataq = nextList(entrenadores[posicion].equipo[0].habilidades);
  }
  
  free(numeroUno);
  
  qsort(arr, 4, sizeof(AtkEfc), compararEficiencia);

  ataq = firstList(entrenadores[posicion].equipo[0].habilidades);

  for (int i = 0 ; i != arr[0].pos ; i++)
  {
    ataq = nextList(entrenadores[posicion].equipo[0].habilidades);
  }
  
  sprintf(cadenaCompleta, "%s enemigo uso %s", entrenadores[posicion].equipo[0].nombre, ataq->nombre);
  escribirLentamente(cadenaCompleta, 2);
  sleep(1);
  
  danio = calculoDano(Pokedex, Movimientos, Multiplicadores, &entrenadores[posicion].equipo[0], &entrenadores[0].equipo[0], *ataq);
  
  return danio;
}

void mostrarCreditos()
{
  char *creditos[] =
  {
        "\033[0;36m-------------------------------------------------------\n",
        "\033[0;35m                       CREDITOS\n",
        "\033[0;36m-------------------------------------------------------\n\n",
        "\033[0;34m\n",
        "\033[1;37m                       Proyecto:\n\n",
        "\033[0;34m                      \"PokeDuel\"\n",
        "\033[1;37m\n",
        "\033[0;34m                      Creado por:\n\n",
        "\033[1;37m                     Team Gigabyte\n\n",
        "\n",
        "                  Miembros del equipo:\n\n",
        "      Jose Lara Arce   ->  Jugando Replit hace 13hrs...\n\n",
        "      Claudio Toledo   ->  \"BOOM\" \n\n",
        "       Fabian Solis    ->  \"Ya, esta listo... (core dumped)\"\n\n"
        "      Matias Villegas  ->  \"Pero ChatGPT me dijo que...\"\n\n",
        "\n",
        "\033[1;37m               Agradecimientos especiales:\n\n",
        "                        ChatGPT 4\n\n",
        "                         YOU.com\n\n",
        "\033[0;36m     Este juego no hubiera sido posible sin su ayuda.\n\n",
        "\n",
        "\033[0;36m-------------------------------------------------------\n",
        "\033[0;35m  Team Gigabyte © 2023. Todos los derechos reservados.\n",
        "\033[0;36m-------------------------------------------------------\n\n",
    };

    
    int num_lineas = sizeof(creditos) / sizeof(creditos[0]);
  
    for (int i = 0; i < num_lineas; i++) 
    {
      printf("%s", creditos[i]);
      sleep(1);
      fflush(stdout);
    }
  
    printf("\033[0m");
}

void salonDeLaFama(Entrenador entrenadores[])
{
  system("clear");
  system("cls");
  puts("+---------------------------------------+");
  printf("|       FELICIDADES   %-9s!!!      |\n", entrenadores[0].nombre);
  puts("+---------------------------------------+\n");

  puts("+---------------------------------------+");
  puts("|                                       |");
  puts("|    BIENVENIDO AL SALON DE LA FAMA     |");
  puts("|                                       |");
  puts("+---------------------------------------+\n");
  
  sleep(3);

  for(int i = 0; i < entrenadores[0].sizeTeam ; i++)
  {
    puts("+---------------------------------------+");
    puts("|                                       |");
    printf("|    %30s     |\n",entrenadores[0].equipo[i].nombre);
    puts("|       LVL. 100                        |");
    printf("|    TIPO 1 %-23s     |\n",entrenadores[0].equipo[i].tipo1);
    if(strcmp(entrenadores[0].equipo[i].tipo2, "0") == 0)
    {
      puts("|                                       |");
    }else
      printf("|    TIPO 2 %-23s     |\n",entrenadores[0].equipo[i].tipo2);
    puts("+---------------------------------------+\n");
    sleep(2);
  }

  escribirLentamente("MUCHAS GRACIAS POR JUGAR NUESTRO VIDEOJUEGO!!!",2);
  sleep(5);
  printf("\033[2J\033[H");
  
  mostrarCreditos();
}

