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

typedef struct 
{
  char **canciones;
  int cantidad;
} ListaDeCanciones;

enum Sonido
{
  MENU = 1,
  BATALLA = 2,
  ANTES_LIGA = 3,
  LIGA = 4,
  VICTORIA = 5,
  VICTORIA_LIGA = 6,
  ANTES_CAMPEON = 7,
  ANTES_ENTRENAMIENTO = 8,
  CAMPEON = 9,

  LOW_HP = 10,
  DEBIL = 11,
  DEBIL2 = 12,
  NORMAL = 13,
  MUY_EFICAZ = 14,
  SUPEREFECTIVO = 15,

  PARALIZADO = 16,
  QUEMADO = 17,
  CONGELADO = 18,
  DORMIDO = 19,
  ENVENENADO = 20,
  CONFUNDIDO = 21,
};

#endif