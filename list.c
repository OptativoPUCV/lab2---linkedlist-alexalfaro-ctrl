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
    list->head=temp;
    
  }
  
  
}

void pushBack(List * list, void * data) {
    list->current = list->tail;
    pushCurrent(list,data);
}

void pushCurrent(List * list, void * data) {
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
    return NULL;
}

void cleanList(List * list) {
    while (list->head != NULL) {
        popFront(list);
    }
}