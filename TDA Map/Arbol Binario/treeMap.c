/*  "treeMap.c"

    TAREA 3

    Nombre: Bruno Esteban Diaz Ureta
    Rut: 19850701-6
    Curso: ICI2240-1
    Fecha de entrega: 16/05/2017

*/

#include "treeMap.h"

/*
    Funcion constructora del TreeMap. Retorna un puntero a TreeMap
*/
TreeMap* createTreeMap(int (*lt)(void* key1,void* key2))
{
    TreeMap* tree = (TreeMap*) malloc(sizeof(TreeMap));
	tree -> root = NULL;
    tree -> current = NULL;
    tree ->lower_than = lt;
    return tree;
}

/*
    Funcion constructora de un nodo.
*/
tree_node* _crearNodo(void* key, void* dato)
{
	tree_node* t;
	t=(tree_node*) malloc (sizeof(tree_node));
	t -> data = dato;
    t -> key = key;
	t -> left = NULL;
    t -> right = NULL;
    t -> parent = NULL;
	return t;
}

/*
    Funcion que inserta un elemento al mapa por medio de su clave
*/
void insert(TreeMap* tree, void* key, void* dato)
{
	tree_node *z=_crearNodo(key, dato);
	tree_node* y=NULL;
	tree_node* x=tree->root;

	while(x){
        y=x;
        if(tree->lower_than(z->key,x->key)) //z->key < x->key
            x = x->left;
        else if(tree->lower_than(x->key,z->key))
            x = x->right;
        else return;
	}
    z->parent=y;
	if(y==NULL)
       tree->root=z;
	else if(tree->lower_than(z->key,y->key)) //z->key < y->key
        y->left=z;
    else if(tree->lower_than(y->key,z->key))
        y->right=z;
}

/*
    Funcion de busqueda en el mapa.
*/
tree_node* __searchR(TreeMap* tree, tree_node* x, int key)
{
    if( x==NULL || key == x->key)
        return x;

    tree_node* aux;
    if (key < x->key) //
        aux = __searchR(tree, x->left,key);
    else
        aux = __searchR(tree, x->right,key);

    if(aux && aux->key >= key && (x->key < key || aux->key < x->key) ) return aux;
    // if(aux && !tree->compare(aux->data,data) && (tree->compare(x->data,data) || tree->compare(aux->data,x->data) )) return aux;
    else if(x->key == key) return x;
    else return NULL;
}

/*
    Funcion de busqueda en el mapa.
*/
void* search(TreeMap* tree, void* key)
{
    tree->current=__searchR(tree, tree->root, key);
    if(!tree->current || lower_than(key,tree->current->key) || lower_than(tree->current,key)) return NULL;
    else return tree->current->data;
}

/*
    Funcion de transplante de subarboles.
*/
void _transplant(TreeMap* tree, tree_node* u, tree_node* v)
{
    if(!u->parent)
        tree->root=v;
    else if(u==u->parent->left)
        u->parent->left=v;
    else
        u->parent->right=v;
    if(v)
        v->parent=u->parent;
}

/*
    Funcion que elimina un elemento del mapa por medio de su clave
*/
void erase(TreeMap* tree, int key)
{
    search(tree, key);
    if(!tree->current) return;

    tree_node* z = tree->current;
    if(!z->left)
        _transplant(tree,z,z->right);
    else if(!z->right)
        _transplant(tree,z,z->left);
    else {
        tree_node *y=z->right;
        while(y->left)
           y=y->left;

        if(y->parent!=z){
            _transplant(tree,y,y->right);
            y->right=z->right;
            y->right->parent=y;
        }
        _transplant(tree,z,y);
        y->left=z->left;
        y->left->parent=y;
    }
    free(z);
    tree->current=NULL;
}

/*
    Funcion de busqueda en el mapa.
*/
tree_node* _upper_boundR(TreeMap* tree, tree_node* x, int key)
{
    if( x==NULL || key == x->key)
        return x;

    tree_node* aux;
    if (key < x->key)
        aux = _upper_boundR(tree, x->left,key);
    else
        aux = _upper_boundR(tree, x->right,key);

    if(aux && aux->key >= key &&  (x->key < key || aux->key < x->key) ) return aux;
    else if(x->key >= key) return x;
    else return NULL;
}

/*
    Funcion de busqueda en el mapa.
*/
void* upper_bound(TreeMap* tree, int key)
{
    tree->current=_upper_boundR(tree, tree->root, key);
    return (tree->current)? tree->current->data:NULL;
}


/*
    Funcion que modifica el puntero de la posicion actual de un mapa.
    Le asigna la primera posicion. En caso de no existir le asigna NULL

    Retorna la direccion del dato generico en la primera posicion.
*/
void* first(TreeMap* tree)
{
    tree_node* x=tree->root;
    while(x->left)
      x=x->left;

    tree->current=x;
    return (x)? x->data:NULL;
}

/*
    Funcion que modifica el puntero de la posicion actual de una mapa.
    Le asigna la siguiente posicion con respecto a la actual.
    En caso de no existir, mantiene la direccion

    Retorna la direccion del dato generico en la siguiente posicion.
*/
tree_node* _next(tree_node* x)
{
    if(!x) return NULL;
    if(x->right){
        tree_node* y=x->right;
        while(y->left)
            y=y->left;
        return y;
    }

    tree_node* y=x->parent;
    while(y && x==y->right){
        x=y;
        y=y->parent;
    }
    return y;
}

/*
    Funcion que modifica el puntero de la posicion actual de una mapa.
    Le asigna la siguiente posicion con respecto a la actual.
    En caso de no existir, mantiene la direccion

    Retorna la direccion del dato generico en la siguiente posicion.
*/
void* next(TreeMap* tree)
{
    tree_node* x=tree->current;
    tree->current=_next(x);
    return (tree->current)? tree->current->data:NULL;
}

/*
    Funcion que retorna la key del elemento actual del mapa
*/
void* get_key(TreeMap* tree)
{
    return tree->current->key;
}
