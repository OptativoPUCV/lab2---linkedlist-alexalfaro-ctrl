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

List * createList() {
  List * lista=(struct List*)malloc(sizeof(struct List));
  lista->head=NULL;
  lista->tail=NULL;
  return lista;  
}

void * firstList(List * list) {
  if(list->head !=NULL){
    list->current=list->head;
    return list->current->data;
  }
  return NULL;
}

void * nextList(List * list) {
  if (list->current==NULL){
    return NULL;
  }
  if(list->head !=NULL && list->current->next!=NULL){
    list->current=list->current->next;
    return list->current->data;
  }
  return NULL;
}

void * lastList(List * list) {
  Node *actual = list->head;
  if (list->head == NULL){
    return NULL;
  }
  
  while (actual->next != NULL){
    actual = actual->next;
  }
  list->current = actual;
  return list->current->data;
}

void * prevList(List * list) {
  if (list->current==NULL){
    return NULL;
  }
  if(list ->current==list->head){
    return NULL;
  }
  if(list->head !=NULL && list->current->prev!=NULL){
    list->current=list->current->prev;
    return list->current->data;
  }
  return NULL;
}


void pushFront(List * list, void * data) {
  Node *temp=createNode(data);
  if (list->head==NULL){
    list->head=temp;
    list->tail=temp;
  }else{
    list->head->prev=temp;
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
    return;  // Retorna si la lista es nula
  }
  
  Node *temp = createNode(data);
  
  if (!list->head) {
    list->head = temp;
    list->tail = temp;
    list->current = temp;
  } else if (!list->current->next) {
    list->current->next = temp;
    temp->prev = list->current;
    list->tail = temp;  // Actualiza el tail si se agrega al final
  } else {
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
    if (list && list->current && list->head){
      Node *eliminar = list->current;
      void* data = eliminar->data;
      if (eliminar->next==NULL){
        list->head =eliminar -> next;
      }else{
        list->head=eliminar->next;
      }
      if (eliminar->prev==NULL){
        list->tail=eliminar->prev;
        
      }else{
        list->tail=eliminar->prev;
      }
      list->current =eliminar->next;
      free(eliminar);
      return data;
    }
  
    return NULL;
}

void cleanList(List * list) {
    while (list->head != NULL) {
        popFront(list);
    }
}