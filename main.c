#include "main.h"
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
  
}