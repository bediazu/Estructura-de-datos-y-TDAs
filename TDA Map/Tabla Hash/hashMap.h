/*  "hashMap.h"

    TAREA 2

    Nombre: Bruno Esteban Diaz Ureta
    Rut: 19850701-6
    Curso: ICI2240-1
    Fecha de entrega: 16/04/2017

*/


/*  FUNCIONES DEL TDA MAP */

#ifndef HASHMAP_H_INCLUDED
#define HASHMAP_H_INCLUDED

#include <stdlib.h>
#include <math.h>

typedef struct nodo{
  long key;
  void* data;
}hashElem;

typedef struct{
  hashElem** hashArray;
  int size; //cant. elementos no nulos
  int capac; //Dimension tabla
}HashMap;

/*<Funciones constructoras de tipos de datos ("hashMap.h")>*/
HashMap* createHashMap(int capac);

/*<Funciones secundarias del TDA MAP>*/
long hash(long key,long capac);
long hash_string(char* key,long capac);
void insert(HashMap* map, long key, void* data);
void erase(HashMap* map, long key);
void* search(HashMap* map, long key);
int get_capac(HashMap* map);
void enlarge(HashMap* map);



#endif // HASHMAP_H_INCLUDED
