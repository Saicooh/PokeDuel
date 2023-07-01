#ifndef List_h
#define List_h
#include <stdbool.h>

typedef struct List List;

List * createList(void);

void * firstList(List * list);

void * nextList(List * list);

void * lastList(List * list);

void * prevList(List * list);

void pushFront(List * list, void * data);

void pushBack(List * list, void * data);

void pushCurrent(List * list, void * data);

void * popFront(List * list);

void * popBack(List * list);

void * popCurrent(List * list);

void cleanList(List * list);

bool List_isEmpty(List *list);

List *List_clone(List *src);

#endif /* List_h */
