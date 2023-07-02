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


