#ifndef structs_h
#define structs_h

#define MAX 25
#include "hashmap.h"
#include "list.h"

typedef struct
{
  char nombre[MAX];
  int revive;
  int todos;
  int curacion;
  int pp;
  int cantidad;

} Objeto;

typedef struct
{
  char nombre[MAX];
  float multiplicador;

} TipoElem;

typedef struct
{
  char nombre[MAX];
  char tipo[MAX];

  int potencia;
  int precision;

  int numUsosMAX;
  int numUsosActual;

  float efectoAtaque;
  float efectoDefensa;
  float efectoSalud;

  int direccion;

} Ataque;
  
typedef struct
{
  TipoElem tipoElem[MAX];
  
  char nombre[MAX];
  char tipo1[MAX];
  char tipo2[MAX];

  List *habilidades;

  int ataque;
  int ataqueBase;
  int defensa;
  int defensaBase;
  int salud;
  int saludActual;
  
  bool muerto;
  
} Pokemon;

typedef struct
{
  char nombre[50];
  Pokemon equipo[6];
  Objeto *mochila;
  int sizeTeam;
  int cantidadVivos;
  int cantidadObj;
  
} Entrenador;

typedef struct
{
  Ataque atk;
  float efc;
  int pos;

} AtkEfc;


#endif