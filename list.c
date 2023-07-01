#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include "list.h"

typedef struct Node Node;

struct Node 
{
  void * data;
  Node * next;
  Node * prev;
};

struct List 
{
  Node * head;
  Node * tail;
  Node * current;
};

typedef List List;

Node * createNode(void * data) 
{
  Node * new = (Node *)malloc(sizeof(Node));
  assert(new != NULL);
  new->data = data;
  new->prev = NULL;
  new->next = NULL;
  return new;
}
//1
List * createList() 
{
  List * list = (List *)malloc(sizeof(List));
  if(list == NULL) return NULL;
  list->head = NULL;
  list->tail = NULL;
  return list;
}
//2
void * firstList(List * list)
{
  if(list == NULL || list->head == NULL) return NULL;
  list->current = list->head;
  return (list->current->data);
}

void * nextList(List * list)
{
  if(list == NULL || list->current == NULL || list->current->next == NULL) return NULL;
  list->current = list->current->next;
  return (list->current->data);
}
//3
void * lastList(List * list) 
{
  if(list == NULL || list->current == NULL || list->current->next == NULL) return NULL;
  
  while(list->current->next != NULL) list->current = list->current->next;
  return list->current->data;
}

void * prevList(List * list) {
  if(list == NULL || list->current == NULL || list->current->prev == NULL) return NULL;
  list->current = list->current->prev;
  return list->current->data;
}
//4
void pushFront(List * list, void * data) {
  Node* nuevo_nodo = createNode(data);
  if(list->head == NULL){
    list->head = nuevo_nodo;
    list->tail = nuevo_nodo;
  }
  else{
    nuevo_nodo->next = list->head;
    list->head->prev = nuevo_nodo;
    list->head = nuevo_nodo;
  }
}

void pushBack(List * list, void * data) {
    list->current = list->tail;
    pushCurrent(list,data);
}
//5
void pushCurrent(List * list, void * data) {
  Node* nuevo_nodo = createNode(data);
  
  if(list->current == NULL)
  {
    list->head = nuevo_nodo;
    list->tail = nuevo_nodo;
  }
  else{
    if(list->current == list->tail)
    {
      list->tail = nuevo_nodo;
    }
    else
    {
      nuevo_nodo->next = list->current->next;
      list->current->next->prev = nuevo_nodo;
    }
    nuevo_nodo->prev = list->current;
    list->current->next = nuevo_nodo;
  }
}
//6
void *popFront(List *list) 
{
  list->current = list->head;
  return popCurrent(list);
}

void * popBack(List * list) {
    list->current = list->tail;
    return popCurrent(list);
}

void *popCurrent(List * list)
{
  assert(list != NULL || list->head != NULL);
  
  if (list->current == NULL) return NULL;
  
  Node * aux = list->current;
  
  if (aux->next != NULL) aux->next->prev = aux->prev;
  
  if (aux->prev != NULL) aux->prev->next = aux->next;
  
  void *data = (void *) aux->data;
  
  if(list->current == list->tail) list->tail = list->current->prev;

  if(list->current == list->head) list->head = list->current->next;
      
  list->current = aux->prev;

  free(aux);
  
  return data;
}


void cleanList(List * list)
{
  while (list->head != NULL) popFront(list);
}

bool List_isEmpty(List *list)
{
  return (list -> head == NULL);
}

List *List_clone(List *src)
{
  if (src == NULL) {
    return NULL;
  }

  List *dst = createList();

  List *tempStack = createList();
  while (!List_isEmpty(src)) 
  {
    void *element = popFront(src);
    pushFront(dst, element);
    pushFront(tempStack, element);
  }

  while (!List_isEmpty(tempStack)) 
  {
    pushFront(src, popFront(tempStack));
  }

  free(tempStack);

  return dst;
}