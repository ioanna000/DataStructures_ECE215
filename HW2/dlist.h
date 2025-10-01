#include <stdbool.h>
#include <stdio.h>
#include "type_t.h"

#ifndef __DLIST_H__
#define __DLIST_H__

typedef int (*comparator_t)(type_t v1, type_t v2);
typedef void (*printer_t)(FILE* fp, type_t value, bool only_key);

typedef struct dlist_node {
  struct dlist_node* next;
  struct dlist_node* prev;
  type_t data;
} dnode_t;

typedef struct dlist {
  struct dlist_node *head, *tail;
  int size;
  
  comparator_t cmp;
  printer_t printer;
} dlist_t;

dlist_t* create_dlist(comparator_t cmp, printer_t printer);

void clear_dlist(dlist_t* list);

void destroy_dlist(dlist_t* list);

int size(dlist_t* list);

bool insert(dlist_t* list, int index, type_t data);

int index_of(dlist_t* list, type_t data);

int instances_of(dlist_t* list, type_t data);

type_t get_index(dlist_t* list, int index);

bool rmv(dlist_t* list, type_t data);

type_t rmv_index(dlist_t* list, int index);

void swap(dnode_t* n1, dnode_t* n2);

/* Catenates the two lists in list1. After calling
 * function list2 is empty.
 */
void catenate(dlist_t* list1, dlist_t* list2);

/* convert dlist to a table containing type_t* elements
 */
type_t* dlist2table(dlist_t* list);

/* convert type_t* table to dlist
 */
void table2dlist(type_t table[], int table_size, dlist_t* list);

void print(FILE* fp, dlist_t* list);

#endif
