//
//  HashMap.h
//  TablaHashLab
//
//  Created by Matias Barrientos on 11-08-18.
//  Copyright © 2018 Matias Barrientos. All rights reserved.
//

#ifndef HashMap_h
#define HashMap_h


typedef struct HashMap HashMap;

typedef struct Pair 
{
  char * key;
  void * value;
} Pair;

HashMap * createMap(long capacity);

void insertMap(HashMap * table, void * key, void * value);

void eraseMap(HashMap * table, char * key);

Pair * searchMap(HashMap * table, char * key);

Pair * firstMap(HashMap * table);

Pair * nextMap(HashMap * table);

void enlarge(HashMap * map);

#endif /* HashMap_h */
