#include "main.h"

void menu() // Opciones del menú.
{
  printf("Elige una opcion a continuacion:\n");

  printf("\n1. Mostrar la Pokedex.");
  printf("\n2. Administrar Pokemon."); // administrar movimientos tambien
  printf("\n3. Administrar objetos.");
  printf("\n4. Entrenamiento Pokemon.");
  printf("\n5. Entrar a la liga Pokemon.");
  printf("\n6. Salir del programa.\n");
  
  printf("\n");
}

void validarOpcion(int *opcion) // Valida las opciones del menú.
{
  char opcionAux[MAX];
  
  while (true) 
  {
    scanf("%15s", opcionAux);
    printf("\n");
      
    if (isdigit(*opcionAux)) 
    {
      *opcion = atoi(opcionAux);
        
      if (*opcion >= 1 && *opcion <= 6) break;
      else printf("Debe ingresar un numero valido entre 1 y 6.\n");
    }
    else printf("Debe ingresar un numero valido entre 1 y 6.\n");
    
    getchar();
  }
}

void validarOpcionPokemon(int *opcion, int equipoRegistrado) // Valida las opciones del menú.
{
  char opcionAux[MAX];
  
  while (true) 
  {
    scanf("%15s", opcionAux);
    printf("\n");
      
    if (isdigit(*opcionAux)) 
    {
      *opcion = atoi(opcionAux);
        
      if (*opcion >= 1 && *opcion <= 5)
      {
        if(*opcion != 1  && *opcion != 5 && !equipoRegistrado) 
        {
          puts("Debes registrar al menos un Pokemon en tu equipo para acceder a esta opcion!\n");
          *opcion = 0;
        }
      }
      else printf("Debe ingresar un numero valido entre 1 y 5.\n");
    }
    else printf("Debe ingresar un numero valido entre 1 y 5.\n");
    break;
    getchar();
  }
}

void validar(int *user_continue) // Validamos que el usuario desee seguir con la ejecución del programa.
{
  char salida[2];
  
  printf("Desea realizar otra operacion? (s/n)\n");
  scanf("%1s", salida);
  
  if(strcmp(salida, "n") == 0)
  {
    *user_continue = 0;
    printf("\nGracias por usar PokeDuel, esperamos que hayas disfrutado del juego!");
    exit(EXIT_SUCCESS);
  }
  else while (strcmp(salida, "s") != 0)
  {
    printf("Ingrese una opcion valida\n\n");
    printf("Desea realizar otra operacion? (s/n)\n");
    scanf("%1s", salida);
  }
}

char *gets_csv_field(char *tmp, int k) //
{
  int open_mark = 0;
  char *ret = (char*) malloc(100 * sizeof(char));
  int ini_i = 0, i = 0;
  int j = 0;
  int last_field = 0;
  
  while (tmp[i + 1] != '\0')
  {  
    if(tmp[i] == '\"')
    {
      open_mark = 1 - open_mark;
      if(open_mark) ini_i = i + 1;
      i++;
      continue;
    }
    
    if(open_mark || tmp[i] != ',')
    {
      if(k == j) ret[i - ini_i] = tmp[i];
      i++;
      continue;
    }

    if(tmp[i] == ',')
    {
      if(k == j) 
      {
        ret[i - ini_i] = 0;
        return ret;
      }
      j++; 
      ini_i = i + 1;
    }
    i++;
  }

  if(k == j) 
  {
    last_field = 1;
    ret[i - ini_i] = 0;
    return ret;
  }
  
  return NULL;
}

void escribirLentamente(char* cadena, int saltosLinea) 
{
  for (int i = 0; cadena[i] != '\0'; i++) 
  {
    putchar(cadena[i]); 
    fflush(stdout); 
    SDL_Delay(18);
  }
  
  switch (saltosLinea)
  {
    case 1 : puts(""); break;
    case 2 : puts("\n"); break;
    case 3 : puts("\n\n"); break;
    case 4 : puts("\n\n\n"); break;
    case 5 : puts("\n\n\n\n"); break;
  }
}

int calcularEspaciosExtra(int largoCadena, int ancho)
{
  return (ancho - largoCadena) / 2;
}

void iniciarSDL()
{
  if (SDL_Init(SDL_INIT_AUDIO) < 0) 
  {
    printf("Failed to init SDL\n");
    exit(1);
  }

  int flags = MIX_INIT_MP3;
  if (flags != Mix_Init(flags))
  {
    printf("Could not initialize mixer (result: %d).\n", Mix_Init(flags));
    printf("Mix_Init: %s\n", Mix_GetError());
    exit(1);
  }

  Mix_OpenAudio(22050, AUDIO_S16SYS, 2, 640);
}

void limpiarConsola()
{
  system("cls||clear");
  printf("\033[2J\033[H");
}

void reproducirMusica(const char *cancion, int loop) 
{
  Mix_Music *music = Mix_LoadMUS(cancion);
  Mix_VolumeMusic(25);
  if (loop) Mix_PlayMusic(music, -1);
  else Mix_PlayMusic(music, 0);
}

void playSoundEffect(const char *path, int loop, int volume)
{
  Mix_Chunk *soundEffect = Mix_LoadWAV(path);

  if (loop == 1) loop = -1;
  else loop = 0;

  int channel = Mix_PlayChannel(-1, soundEffect, loop);

  Mix_Volume(channel, volume);
}

void playSongType(int type, int loop, int numLiga, int stop)
{
  static char *cancionesMenu[] = 
  {
    "musiquita\\menu1.mp3",
    "musiquita\\menu2.mp3",
    "musiquita\\menu3.mp3",
    "musiquita\\menu4.mp3",
    "musiquita\\menu5.mp3",
    "musiquita\\menu6.mp3",
  };

  static ListaDeCanciones listaCancionesMenu = {.canciones = cancionesMenu, .cantidad = sizeof(cancionesMenu) / sizeof(cancionesMenu[0])};

  static char *cancionesBatalla[] =
  {
    "musiquita\\batalla1.mp3",
    "musiquita\\batalla2.mp3",
    "musiquita\\batalla3.mp3",
    "musiquita\\batalla4.mp3",
  }; // 2

  static ListaDeCanciones listaCancionesBatalla = {.canciones = cancionesBatalla, .cantidad = sizeof(cancionesBatalla) / sizeof(cancionesBatalla[0])};

  static char *cancionesAntesLiga[] =
  {
    "musiquita\\road.mp3",
    "musiquita\\road2.mp3",
    "musiquita\\road3.mp3",
  }; // 3

  static ListaDeCanciones listaCancionesAntesLiga = {.canciones = cancionesAntesLiga, .cantidad = sizeof(cancionesAntesLiga) / sizeof(cancionesAntesLiga[0])};

  static char *cancionesLiga[] =
  {
    "musiquita\\liga1.mp3",
    "musiquita\\liga2.mp3",
    "musiquita\\liga3.mp3",
    "musiquita\\liga4.mp3",
  }; // 4
  
  static ListaDeCanciones listaCancionesLiga = {.canciones = cancionesLiga, .cantidad = sizeof(cancionesLiga) / sizeof(cancionesLiga[0])};

  static char *cancionesVictoriaNormal[] =
  {
    "musiquita\\victoria.mp3",
  }; // 5

  static ListaDeCanciones listaCancionesVictoriaNormal = {.canciones = cancionesVictoriaNormal, .cantidad = sizeof(cancionesVictoriaNormal) / sizeof(cancionesVictoriaNormal[0])};
  
  static char *cancionesVictoriaLiga[] =
  {
    "musiquita\\victoriaLiga.mp3",
  }; //6

  static ListaDeCanciones listaCancionesVictoriaLiga = {.canciones = cancionesVictoriaLiga, .cantidad = sizeof(cancionesVictoriaLiga) / sizeof(cancionesVictoriaLiga[0])};

  static char *cancionAntesCampeon[] =
  {
    "musiquita\\antescampeon1.mp3",
    "musiquita\\antescampeon2.mp3",
  }; // 7

  static ListaDeCanciones listaCancionAntesCampeon = {.canciones = cancionAntesCampeon, .cantidad = sizeof(cancionAntesCampeon) / sizeof(cancionAntesCampeon[0])};

  static char *cancionesAntesEntrenamiento[] =
  {
    "musiquita\\pre_entrenamiento.wav",
  }; // 8

  static ListaDeCanciones listaCancionesAntesEntrenamiento = {.canciones = cancionesAntesEntrenamiento, .cantidad = sizeof(cancionesAntesEntrenamiento) / sizeof(cancionesAntesEntrenamiento[0])};

  static char *cancionesCampeon[] =
  {
    "musiquita\\araya.mp3",
    "musiquita\\campeon2.mp3"
  }; // 9

  static ListaDeCanciones listaCancionesCampeon = {.canciones = cancionesCampeon, .cantidad = sizeof(cancionesCampeon) / sizeof(cancionesCampeon[0])};

  static char *cancionLowHP[] =
  {
    "musiquita\\lowhp.mp3",
  }; // 10

  static ListaDeCanciones listaCancionLowHP = {.canciones = cancionLowHP, .cantidad = sizeof(cancionLowHP) / sizeof(cancionLowHP[0])};

  ListaDeCanciones *listaSeleccionada = NULL;

  char **cancionesSeleccionadas;
  int cantidadDeCanciones;
  const char *cancionAleatoria;
  Mix_OpenAudio(22050, AUDIO_S16SYS, 2, 640);

  switch (type) 
  {
    case 1: listaSeleccionada = &listaCancionesMenu; break;
    case 2: listaSeleccionada = &listaCancionesBatalla; break;
    case 3: listaSeleccionada = &listaCancionesAntesLiga; break;
    case 4:

      listaSeleccionada = &listaCancionesLiga;
      const char *cancionAleatoria = listaSeleccionada->canciones[numLiga];
      reproducirMusica(cancionAleatoria, loop);
      return;

    case 5: listaSeleccionada = &listaCancionesVictoriaNormal; break;
    case 6: listaSeleccionada = &listaCancionesVictoriaLiga; break;
    case 7: listaSeleccionada = &listaCancionAntesCampeon; break;
    case 8: listaSeleccionada = &listaCancionesAntesEntrenamiento; break;
    case 9: listaSeleccionada = &listaCancionesCampeon; break;

    case 10: playSoundEffect("musiquita\\lowhp.mp3", loop, 25); return;
    case 11: playSoundEffect("musiquita\\debil.mp3", loop, 25); return;
    case 12: playSoundEffect("musiquita\\debil2.mp3", loop, 25); return;
    case 13: playSoundEffect("musiquita\\normal.mp3", loop, 25); return;
    case 14: playSoundEffect("musiquita\\muy_eficaz.mp3", loop, 25); return;
    case 15: playSoundEffect("musiquita\\superefectivo.mp3", loop, 25); return;

    case 16: playSoundEffect("musiquita\\paralizado.mp3", loop, 25); return;
    case 17: playSoundEffect("musiquita\\quemado.mp3", loop, 25); return;
    case 18: playSoundEffect("musiquita\\congelado.mp3", loop, 25); return;
    case 19: playSoundEffect("musiquita\\dormido.mp3", loop, 25); return;
    case 20: playSoundEffect("musiquita\\envenenado.mp3", loop, 25); return;
    case 21: playSoundEffect("musiquita\\confundido.mp3", loop, 25); return;
  }

  int indiceAleatorio = rand() % listaSeleccionada -> cantidad;
  cancionAleatoria = listaSeleccionada -> canciones[indiceAleatorio];

  printf("Cancion aleatoria: %s\n", cancionAleatoria);

  reproducirMusica(cancionAleatoria, loop);
}