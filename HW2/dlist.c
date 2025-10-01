#include <stdlib.h>
#include <stdio.h>

#include "type_t.h"
#include "dlist.h"

dlist_t* create_dlist(comparator_t cmp, printer_t printer) {
  dlist_t *temp, *list;

  temp = (dlist_t *) malloc(sizeof(dlist_t));

  if (temp == NULL) {
    printf("Problem in first memory allocation for the list\n");

    exit (-1);
  }

  list = temp;

  list->head = NULL;

  list->tail = NULL;

  list->size = 0;

  list->cmp = cmp;

  list->printer = printer;

  return list;
}

void clear_dlist(dlist_t* list) {
  dnode_t *current, *temp;

  for(current = list->head; current != NULL;){
    temp = current;
    current = current->next;
    free (temp);
  }

  list->head = NULL;
  list->tail = NULL;
  list->size = 0;
}

void destroy_dlist(dlist_t* list) {
  clear_dlist(list);
  free(list);
}

int size(dlist_t* list) {
  return list->size;
}

bool insert(dlist_t* list, int index, type_t data) {

  dnode_t *new_node, *current;
  int counter = 0;

  if (index > size(list) || index < 0) {
    return false;
  }

  new_node = (dnode_t*) malloc(sizeof(dnode_t));

  if (new_node == NULL) {
    printf("Problem in second memory allocation\n");
    exit(-1);
  }

  new_node->next = NULL;
  new_node->prev = NULL;
  new_node->data = data; 
  
  for(current = list->head; counter < index; current = current->next, counter++);
  
  if (size(list) == 0) {
    list->head = new_node;
    list->tail = new_node;

    list->size = 1;
    return true;
  }

  if(current == list->head) {
    new_node->next = list->head;
    new_node->prev = NULL;
    list->head->prev = new_node;
    list->head = new_node;
  }

  else if(current == NULL) {
    list->tail->next = new_node;
    new_node->prev = list->tail;
    list->tail = new_node;
  }

  else {
    new_node->next = current;
    if(current->prev != NULL){
      current->prev->next = new_node;
    }
    new_node->prev = current->prev;
    current->prev = new_node;
  }

  list->size++;

  return true;  

}

int index_of(dlist_t* list, type_t data) {

  int counter = 0;
  dnode_t *current;

  // current begins from head and goes to the next node until it finds the data or reaches NULL //
  for (current = list->head; (list->cmp(current->data, data) != 0) && (current != NULL); current = current->next) {
    counter++; // increase the counter each time the current does not find the data //
  }

  if (current == NULL) {
    return (-1);
  }

  return (counter);


}

int instances_of(dlist_t* list, type_t data) {

  int counter = 0;
  dnode_t *current;

  // current begins from head and goes to the next node until it reaches NULL //
  // every time current contains the data given by the user the counter increases by one //
  for (current = list->head; current != NULL; current = current->next) {
    if (list->cmp(current->data, data) == 0) {
      counter++;
    }
  }

  return (counter);

}

type_t get_index(dlist_t* list, int index) {
  dnode_t *current;
  int counter = 0;
  type_t zeroed_stud = { 0 };

  if (index >= list->size || index < 0){
    return zeroed_stud;
  }

  for (current = list->head; counter < index; counter++, current = current->next);

  return current->data;
}

bool rmv(dlist_t* list, type_t data) {
  dnode_t *current;

  for (current = list->head; current != NULL; current = current->next){
    if (list->cmp(current->data, data) == 0){
      if(current->prev != NULL){
        current->prev->next = current->next;
      }
      else{
        list->head = current->next; 
      }
      if(current->next != NULL){
        current->next->prev = current->prev;
      }
      else{
        list->tail = current->prev;
      }
      free(current);
      list->size--;

      return true;
    }
  }
  return false;
}

type_t rmv_index(dlist_t* list, int index) {
  type_t zeroed_stud = { 0 }, temp_stud;
  dnode_t *current;
  int counter = 0;


  if (index >= list->size || index < 0){
    return zeroed_stud;
  }

  for(current = list->head; counter < index; counter++, current = current->next);

  if(current->prev != NULL){
    current->prev->next = current->next;
  }
  else{
    list->head = current->next; 
  }
  if(current->next != NULL){
    current->next->prev = current->prev;
  }
  else{
    list->tail = current->prev;
  }
  temp_stud = current->data;
  free(current);
  list->size--;

  return temp_stud;

}

void swap(dnode_t* n1, dnode_t* n2) {
  type_t temp;

  temp = n1->data;
  n1->data = n2->data;
  n2->data = temp;
}

void catenate(dlist_t* list1, dlist_t* list2) {
  int sum;

  sum = list2->size + list1->size;

  if (list2->head == NULL){
    return;
  }
  
  if (list1->head == NULL){
    list1->head = list2->head;
    list1->tail = list2->tail;
  }
  else{
    list1->tail->next = list2->head;
    list2->head->prev = list1->tail;
    list1->tail = list2->tail;
  }
  
  list2->size = 0;
  list1->size = sum;
  list2->head = NULL;
  list2->tail = NULL;
}

type_t* dlist2table(dlist_t* list) {
  type_t* table = (type_t*)malloc((list->size) * sizeof(type_t));
  if(!table) {
    fprintf(stderr, "Malloc failure [%s:%d]\n", __FILE__, __LINE__);
    exit(-1);
  }
  int i=0;
  while(size(list)>0) {
    table[i++] = get_index(list, 0);
    rmv_index(list,0);
  }
  return table;
}

void table2dlist(type_t table[], int table_size, dlist_t* list) {
    for(int i=0; i<table_size; i++) {
        insert(list, size(list), table[i]);
    }
    free(table);
}

void print(FILE* fp, dlist_t* list) {
    
    for(dnode_t* curr=list->head; curr!=NULL; curr=curr->next) {
        list->printer(fp, curr->data, false);
        putchar('\n');
    }
}
