#include "dlist.h"
#include <math.h>

#ifndef _SORT_H_
#define _SORT_H_

void insertion_sort(dlist_t* list);
void selection_sort(dlist_t* list);
void bubble_sort(dlist_t* list);
void quick_sort(dlist_t* list);
void heap_sort(dlist_t* list);
void merge_sort(dlist_t* list);
void radixSortLSD(dlist_t* list, int bits_per_digit);
void radixSortMSD(dlist_t* list, int bits_per_digit);

#endif
