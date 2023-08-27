#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "list.h"

typedef struct Node Node;

struct Node {
    void * data;
    Node * next;
    Node * prev;
};

struct List {
    Node * head;
    Node * tail;
    Node * current;
};

typedef List List;

Node * createNode(void * data) {
    Node * new = (Node *)malloc(sizeof(Node));
    assert(new != NULL);
    new->data = data;
    new->prev = NULL;
    new->next = NULL;
    return new;
}
//funcion para crear lista
List * createList() {
  List * lista=(struct List*)malloc(sizeof(struct List));//se reserva el espacio de la lista con la funcion malloc
  lista->head=NULL;//se einicialisan los valores de las listas en nullo
  lista->tail=NULL;
  return lista;  
}
// funcion para obtener el primer numero de la lista
void * firstList(List * list) {
  if(list->head !=NULL){ // si la lista no esta vacia
    list->current=list->head; // se pone el nodo actual como el primer nodo de la lista 
    return list->current->data; // se retorna el valor de la primera posicion de la lista
  }
  return NULL;// y si la lista esta vacia se retorna NULL
}
// funcion para obtener el siguiente del actual
void * nextList(List * list) {
  if (list->current==NULL){ //si la posicion actual es NULL se retorna NULL
    return NULL;
  }
  if(list->head !=NULL && list->current->next!=NULL){ // si el inicio de la lista y el siguiente al actual es no NULLO
    list->current=list->current->next; // el actual se mueve al siguiente nodo y se retorna el valor
    return list->current->data;
  }
  return NULL;
}
//funcion para el ultimo elemento de la lista;
void * lastList(List * list) { 
  Node *actual = list->head;
  if (list->head == NULL){ // si la lista esta vacia se retorna NULL
    return NULL;
  }
  
  while (actual->next != NULL){//entra en el bucle hasta el final de la lista
    actual = actual->next; // se va actualizando la poscion actual hasta el final 
  }
  list->current = actual; // se establece el current como ultimo nodo
  return list->current->data; // se devuelve el ultimo valor  de la lista
}
// funcion para obtener el elemento previo al actual 
void * prevList(List * list) {
  if (list->current==NULL){ // si la lista esta vacia se retorna un valor NULL
    return NULL;
  }
  if(list ->current==list->head){  // se retorna NULL ya que no exixtiria elemento previo si el actual es el primero de la lista
    return NULL;
  }
  if(list->head !=NULL && list->current->prev!=NULL){
    list->current=list->current->prev;//se mueve al nodo previo
    return list->current->data;// se retorna el valor del nodo previo
  }
  return NULL;
}


void pushFront(List * list, void * data) {
  Node *temp=createNode(data);
  if (list->head==NULL){ // al estar vacia el nodo toma el valor de head y cola
    list->head=temp;
    list->tail=temp;
  }else{
    list->head->prev=temp; // se conectan los nodos   
    temp->next=list->head;
    list->head=temp;
    
  }
  
}

void pushBack(List * list, void * data) {
    list->current = list->tail;
    pushCurrent(list,data);
}

void pushCurrent(List * list, void * data){
  if (!list) {
    return;  // si esta vacia se retorna NULL
  }
  
  Node *temp = createNode(data);
  
  if (!list->head) { // la lista esta vacia el nodo se convierte en head y cola
    list->head = temp;
    list->tail = temp;
    list->current = temp;
  } else if (!list->current->next) {  //si el nodo actual es el ultimo de la lista 
    list->current->next = temp; //agregamos el nodo despues del nodo actual
    temp->prev = list->current;
    list->tail = temp;   // El nuevo nodo se convierte en la cola de la lista
  } else { // si el nodo no es el ultimo de la lista
    // agregamos el nodo nuevo despues del actual y actualizamos los enlaces
    temp->next = list->current->next;
    temp->prev = list->current;
    list->current->next->prev = temp;
    list->current->next = temp;
  }
}

void * popFront(List * list) {
    list->current = list->head;
    return popCurrent(list);
}

void * popBack(List * list) {
    list->current = list->tail;
    return popCurrent(list);
}

void * popCurrent(List * list) {
    if (list && list->current && list->head){ // se verifica que la lista no este vacia
      Node *eliminar = list->current; //creamos un puntero alnodo que queremos eliminar
      void* data = eliminar->data; //guardamos el dato que queremos eliminar
      if (eliminar->prev !=NULL){   
          eliminar->prev->next= eliminar->next;
      }else{
        list->head = eliminar->next; // Si es el primer nodo, actualizamos la cabeza
      }
      if (eliminar->next!=NULL){
        eliminar->next->prev=eliminar->prev;
      }else{
        list->tail =eliminar->prev; // Si es el último nodo, actualizamos la cola
      }
      list->current=eliminar->next;
      free(eliminar);// se livera el nodo
      return data;//se retorna el dato
    }
  
    return NULL;
}

void cleanList(List * list) {
    while (list->head != NULL) {
        popFront(list);
    }
}