/*  "treeMap.h"

    TAREA 3

    Nombre: Bruno Esteban Diaz Ureta
    Rut: 19850701-6
    Curso: ICI2240-1
    Fecha de entrega: 16/05/2017

*/

/*  FUNCIONES DEL TDA MAP */

#ifndef TREEMAP_H_INCLUDED
#define TREEMAP_H_INCLUDED

#include <stdlib.h>
#include <stdio.h>

typedef struct node{
   void* data;
   void* key;
   struct node* left;
   struct node* right;
   struct node* parent;
}tree_node;

typedef struct{
   tree_node* root;
   tree_node* current;
   int (*lower_than)(void* key1,void* key2);
}TreeMap;

/*<Funciones constructoras de tipos de datos ("treeMap.h")>*/
TreeMap* createTreeMap();
tree_node* _crearNodo(void* key, void* dato);

/*<Funciones secundarias del TDA MAP>*/
void insert(TreeMap* tree, void* key, void* dato);
tree_node* __searchR(TreeMap* tree, tree_node* x, int key);
void* search(TreeMap* tree, void* key);
void _transplant(TreeMap* tree, tree_node* u, tree_node* v);
void erase(TreeMap* tree, int key);
tree_node* _upper_boundR(TreeMap* tree, tree_node* x, int key);
void* upper_bound(TreeMap* tree, int key);
void* first(TreeMap* tree);
tree_node* _next(tree_node* x);
void* next(TreeMap* tree);
void* get_key(TreeMap* tree);

#endif // TREEMAP_H_INCLUDED
