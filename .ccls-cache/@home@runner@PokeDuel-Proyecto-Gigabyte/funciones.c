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
    printf("%c", cadena[i]); 
    fflush(stdout); 
    usleep(2);
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

/*void playSongType(int type, int loop, int numLiga) 
{
  PlaySound(NULL, 0, SND_ASYNC);

  char *cancionesMenu[] =
  {
    "musiquita\\menu1.wav",
    "musiquita\\menu2.wav",
    "musiquita\\menu3.wav",
    "musiquita\\menu4.wav",
  }; // 1

  char *cancionesBatalla[] =
  {
    "musiquita\\batalla1.wav",
    "musiquita\\batalla2.wav",
    "musiquita\\batalla3.wav",
    "musiquita\\batalla4.wav",
  }; // 2

  char *cancionesAntesLiga[] =
  {
    "musiquita\\road.wav",
  }; // 3

  char *cancionesLiga[] =
  {
    "musiquita\\liga1.wav",
    "musiquita\\liga2.wav",
    "musiquita\\liga3.wav",
    "musiquita\\liga4.wav",
  }; // 4
  
  char *cancionesVictoriaNormal[] =
  {
    "musiquita\\victoria.wav",
  }; // 5

  char *cancionesVictoriaLiga[] =
  {
    "musiquita\\victoriaLiga.wav",
  }; //6

  char *cancionAntesCampeon[] =
  {
    "musiquita\\antescampeon1.wav",
    "musiquita\\antescampeon2.wav",
  }; // 7

  char *cancionesAntesEntrenamiento[] =
  {
    "musiquita\\pre_entrenamiento.wav",
  }; // 8

  char *cancionesCampeon[] =
  {
    "musiquita\\araya.wav",
  }; // 9
  char **cancionesSeleccionadas;
  int cantidadDeCanciones;
  const char *cancionAleatoria;
  switch (type) 
  {
    case 1:
      cancionesSeleccionadas = cancionesMenu;
      cantidadDeCanciones = sizeof(cancionesMenu) / sizeof(cancionesMenu[0]);
      break;
    case 2:
      cancionesSeleccionadas = cancionesBatalla;
      cantidadDeCanciones = sizeof(cancionesBatalla) / sizeof(cancionesBatalla[0]);
      break;
    case 3:
      cancionesSeleccionadas = cancionesAntesLiga;
      cantidadDeCanciones = sizeof(cancionesAntesLiga) / sizeof(cancionesAntesLiga[0]);
      break;
    case 4:
      cancionesSeleccionadas = cancionesLiga;
      cancionAleatoria = cancionesSeleccionadas[numLiga];
      if (loop) PlaySound(TEXT(cancionAleatoria), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
      else PlaySound(TEXT(cancionAleatoria), NULL, SND_FILENAME | SND_ASYNC);
      return;

    case 5:
      cancionesSeleccionadas = cancionesVictoriaNormal;
      cantidadDeCanciones = sizeof(cancionesVictoriaNormal) / sizeof(cancionesVictoriaNormal[0]);
      break;
    case 6:
      cancionesSeleccionadas = cancionesVictoriaLiga;
      cantidadDeCanciones = sizeof(cancionesVictoriaLiga) / sizeof(cancionesVictoriaLiga[0]);
      break;
    case 7:
      cancionesSeleccionadas = cancionAntesCampeon;
      cantidadDeCanciones = sizeof(cancionAntesCampeon) / sizeof(cancionAntesCampeon[0]);
      break;
    case 8:
      cancionesSeleccionadas = cancionesAntesEntrenamiento;
      cantidadDeCanciones = sizeof(cancionesAntesEntrenamiento) / sizeof(cancionesAntesEntrenamiento[0]);
      break;
    case 9:
      cancionesSeleccionadas = cancionesCampeon;
      cantidadDeCanciones = sizeof(cancionesCampeon) / sizeof(cancionesCampeon[0]);
      break;
    }

    int indiceAleatorio = rand() % cantidadDeCanciones;
    cancionAleatoria = cancionesSeleccionadas[indiceAleatorio];
    if (loop) PlaySound(TEXT(cancionAleatoria), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
    else PlaySound(TEXT(cancionAleatoria), NULL, SND_FILENAME | SND_ASYNC);
}
*/
