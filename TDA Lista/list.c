/*  "list.c" */

#include "list.h"

/*
    Funcion que crea una nueva lista, asignandole memoria dinamica.
    Asigna sus campos con valores nulos

*/

List* createList()
{
    List* nueva_lista = (List*)malloc(sizeof(List));
    if(nueva_lista==NULL)
    {
        printf("Error en la creacion de una lista.\n");
        return NULL;
    }
    nueva_lista->current=NULL;
    nueva_lista->first=NULL;
    nueva_lista->last=NULL;

    return nueva_lista;
}

/*
    Funcion que crea un nuevo nodo, asignandole memoria dinamica.
    Asigna sus campos con valores nulos

*/

Node* createNode()
{
    Node* nuevo_nodo = (Node*)malloc(sizeof(Node));
    if(nuevo_nodo==NULL)
    {
        printf("Error al crear un nuevo nodo.\n");
        return NULL;
    }
    nuevo_nodo->data=NULL;
    nuevo_nodo->next=NULL;
    nuevo_nodo->prev=NULL;

    return nuevo_nodo;
}


/*
    Funcion que agrega un dato generico a una lista por el final.
*/

void push_back(List* lista,void* dato)
{
    Node* nuevo_nodo = createNode();
    nuevo_nodo->data=dato;

    if(lista->first==NULL)
    {
        lista->first=nuevo_nodo;

    }
    else
    {
        nuevo_nodo->prev=lista->last;
        lista->last->next=nuevo_nodo;

    }

    lista->last = nuevo_nodo;

}

/*
    Funcion que agrega un dato generico a una lista por el inicio.
*/

void push_front(List* lista,void* dato)
{
    Node* nuevo_nodo = createNode();
    nuevo_nodo->data=dato;

    if(lista->first==NULL)
    {
        lista->last=nuevo_nodo;
    }
    else
    {
        lista->first->prev=nuevo_nodo;
        nuevo_nodo->next=lista->first;
    }

    lista->first=nuevo_nodo;

}

/*
    Funcion que modifica el puntero a la posicion actual de una lista.
    Le asigna la primera posicion. En caso de no existir le asigna NULL

    Retorna la direccion del dato generico en la primera posicion.
*/

void* first(List* lista)
{
    lista->current=lista->first;

    if(lista->current!=NULL)
    {
        return lista->current->data;
    }
    return NULL;
}

/*
    Funcion que modifica el puntero a la posicion actual de una lista.
    Le asigna la ultima posicion. En caso de no existir le asigna NULL

    Retorna la direccion del dato generico en la ultima posicion.
*/

void* last(List* lista)
{
    lista->current=lista->last;
    if(lista->current!=NULL)
    {
        return lista->current->data;
    }
    return NULL;
}

/*
    Funcion que elimina un nodo de la posicion actual de la lista
*/

void popCurrent(List* list)
{
    if(list->current!=NULL) //Si el nodo existe.
    {
        if (list->current->prev!=NULL) //Si el nodo anterior existe.
        {
            list->current->prev->next=list->current->next;
        }
        if(list->current->next) //Si el nodo siguiente existe.
        {
            list->current->next->prev=list->current->prev;
        }
        if(list->first==list->current) //Actualizar el puntero al primero.
        {
            list->first=list->current->next;
        }
        if(list->last==list->current) //Actualizar el puntero al ultimo.
        {
            list->last=list->current->prev;
        }

        free(list->current);
    }
    else
    {
        return;
    }


}

/*
    Funcion que modifica el puntero a la posicion actual de una lista.
    Le asigna la siguiente posicion con respecto a la actual.
    En caso de no existir, mantiene la direccion

    Retorna la direccion del dato generico en la siguiente posicion.
*/

void* next(List* list)
{
    if(list->current==NULL)
    {
        return NULL;
    }
    if(list->current->next==NULL)
    {
        return NULL;
    }
    list->current=list->current->next;
    return list->current->data;
}


/*
    Funcion que modifica el puntero a la posicion actual de una lista.
    Le asigna la posicion anterior con respecto a la actual.
    En caso de no existir, mantiene la direccion

    Retorna la direccion del dato generico en la posicion anterior.
*/

void* prev(List* list)
{
   if(list->current==NULL)
    {
        return NULL;
    }
    if(list->current->prev==NULL)
    {
        return NULL;
    }
    list->current=list->current->prev;
    return list->current->data;

}
