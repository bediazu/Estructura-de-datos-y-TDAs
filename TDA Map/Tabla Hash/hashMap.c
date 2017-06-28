/*  "hashMap.c"

    TAREA 2

    Nombre: Bruno Esteban Diaz Ureta
    Rut: 19850701-6
    Curso: ICI2240-1
    Fecha de entrega: 16/04/2017

*/

#include "hashMap.h"

/*
    Funcion constructora del HashMap. Retorna un puntero a HashMap

*/

HashMap* createHashMap(int capac){
    int i;
    HashMap* map=(HashMap*) malloc(sizeof(HashMap));
    map->capac=capac;
    map->size=0;
    map->hashArray = malloc(sizeof(hashElem*)*map->capac);
    for(i=0;i<map->capac;i++) map->hashArray[i]=NULL;
    return map;
}

/*
    Funcion de dispersion Hash

*/

long hash(long key,long capac)
{
    double constante = 0.1415;
    double t = key * constante - floor(key*constante);

    long index = (int) capac * t;

    return index;

}

/*
    Funcion de dispersion hash para un string

*/

long hash_string(char* key,long capac)
{
    /*ALGORITMO DJB2 - Daniel J. Bernstein*/
    unsigned long hash_number = 5381;
    int c;

    while (c = *key++)
        hash_number = ((hash_number << 5) + hash_number) + c;

    //Genera un id gigante para cada string.

    long hash_limitado = hash(hash_number,capac); //Limita el id al tamanio del mapa.
    return hash_limitado;
}

/*
    Funcion de busqueda en el mapa

*/

void* search(HashMap* map, long key){
    int i;
    int hvalue=hash(key,map->capac);
    for(i=0;i<map->capac;i++){
        int new_hvalue=(hvalue+i)%map->capac;
        if(!map->hashArray[new_hvalue]) return NULL;
        else if(map->hashArray[new_hvalue]->key == key){
           return map->hashArray[new_hvalue]->data;
        }
    }
    return NULL;
}

/*
    Funcion que elimina un elemento del mapa por medio de su clave

*/

void erase(HashMap* map, long key){
    int i;
    int hvalue=hash(key,map->capac);
    for(i=0;i<map->capac;i++){
        int new_hvalue=(hvalue+i)%map->capac;
        if(!map->hashArray[new_hvalue]) return;
        else if(map->hashArray[new_hvalue]->key == key){
           map->hashArray[new_hvalue]->data=NULL;
        }
    }
}

/*
    Funcion que inserta un elemento al mapa por medio de su clave

*/

void insert(HashMap* map, long key, void* data){
   int hvalue=hash(key,map->capac);
   if(map->hashArray[hvalue]){ //se busca una casilla disponible a partir de hvalue
       int new_hvalue=-1, i;
       for(i=1;i<map->capac;i++){
          new_hvalue=(hvalue+i)%map->capac;
          if(!map->hashArray[new_hvalue] || !map->hashArray[new_hvalue]->data){
             hvalue=new_hvalue;
             break;
          }
       }
   }

   if(!map->hashArray[hvalue]) map->hashArray[hvalue]=(hashElem*) malloc(sizeof(hashElem));
   map->hashArray[hvalue]->data=data;
   map->hashArray[hvalue]->key=key;
   map->size++;
   if((double)map->size/(double)map->capac > 0.7) enlarge(map); //agranda la tabla
}

/*
    Funcion que agranda el tamanio del hashMap en caso de necesitarse

*/

void enlarge(HashMap* map){
    hashElem **old_array=map->hashArray;
    int old_capac=map->capac;

    //se reinicializan las variables de la tabla con el nuevo tamaño
    int i;
    map->capac*=2;
    map->size=0;
    map->hashArray = malloc(sizeof(hashElem*)*map->capac);
    for(i=0;i<map->capac;i++) map->hashArray[i]=NULL;

    //se reasingnan los elementos de la tabla antigua a la nueva
    for(i=0;i<old_capac;i++){
       if(old_array[i]){
           if(old_array[i]->data)
              insert(map, old_array[i]->key, old_array[i]->data);
           free(old_array[i]);
       }

    }

    free(old_array);
}

/*
    Funcion que retorna ela capacidad del HashMap

*/

int get_capac(HashMap* map)
{
    return map->capac;
}
