#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>

#include "dlist.h"
#include "sort.h"

// Global variables used for the metrics //
long int insertion_cmp = 0;
long int insertion_cpy = 0;
long int insertion_usec = 0;

long int selection_cmp = 0;
long int selection_cpy = 0;
long int selection_usec = 0;

long int bubble_cmp = 0;
long int bubble_cpy = 0;
long int bubble_usec = 0;

long int quick_cmp = 0;
long int quick_cpy = 0;
long int quick_usec = 0;

long int heap_cmp = 0;
long int heap_cpy = 0;
long int heap_usec = 0;

long int merge_cmp = 0;
long int merge_cpy = 0;
long int merge_usec = 0;

long int radixLSD_extra = 0; 
long int radixLSD_move = 0;
long int radixLSD_catenate = 0; 
long int radixLSD_usec = 0;

long int radixMSD_extra = 0; 
long int radixMSD_move = 0;
long int radixMSD_catenate = 0; 
long int radixMSD_usec = 0;
// use the following directive only for printing measurements
//#define _PERF_

type_t *create_max_heap(dlist_t *list, type_t *heap_array, int array_size, int parent_index)
{
  int minimum_index = parent_index;
  int left_child_index = 2 * parent_index + 1;
  int right_child_index = 2 * parent_index + 2;
  type_t temp_data;


  if ((++heap_cmp) && (left_child_index < array_size) && (list->cmp(heap_array[left_child_index], heap_array[minimum_index]) > 0))
  {
    minimum_index = left_child_index;
  }

  if ((++heap_cmp) && (right_child_index < array_size) && (list->cmp(heap_array[right_child_index], heap_array[minimum_index]) > 0))
  {
    minimum_index = right_child_index;
  }

  if (minimum_index != parent_index)
  {
    heap_cpy++;

    temp_data = heap_array[minimum_index];
    heap_array[minimum_index] = heap_array[parent_index];
    heap_array[parent_index] = temp_data;

    create_max_heap(list, heap_array, array_size, minimum_index);
  }

  return heap_array;
} 

//returns the node with the minimum value in the list starting from head //
dnode_t *min(dlist_t *list, dnode_t *head)
{
  dnode_t *current, *minimum = head; // set the list's head as the minimum node //

  for (current = head; current != NULL; current = current->next)
  {
    if ((list->cmp(minimum->data, current->data) > 0) && (++selection_cmp))
    {
      minimum = current;
      selection_cpy++;
    }
  }

  return minimum;
}

void recursive_quicksort(dlist_t *list, dnode_t *head, dnode_t *tail)
{
  dnode_t *pivot;
  dnode_t *current_right, *current_left;

  if ((head != NULL) && (tail != NULL))
  {
    if ((++quick_cmp) && (head != tail) && (++quick_cmp) && (head != tail->next) && (++quick_cmp) && (tail != head->prev))
    {
      pivot = tail;
      current_left = head;

      for (current_right = head; current_right != tail; current_right = current_right->next)
      {
        if (list->cmp(current_right->data, pivot->data) < 0)
        {
          swap(current_left, current_right);
          current_left = current_left->next;
          quick_cpy++;
        }
      }

      swap(current_left, pivot);
      quick_cpy++;
      recursive_quicksort(list, head, current_left->prev);
      recursive_quicksort(list, current_left->next, tail);
    }

  }

}

/*
void my_selection(dlist_t *list, dnode_t *head)
{
  if (head == list->tail)
  {
    return;
  }

  swap(head, min(list));
  my_selection(list, head->next);
}
*/

void insertion_sort(dlist_t* list) {
  dnode_t *temp_data = (dnode_t *) malloc(sizeof(dnode_t)), *curr, *curr2;
  
  insertion_usec = clock();
  // for every node in the list (starting from the 2nd one) //
  for (curr = list->head->next; curr != NULL; curr = curr->next)
  {
    // if the previous node has a greater value than the current one //
    if (++insertion_cmp && list->cmp(curr->prev->data, curr->data) > 0)
    {
      // store the data in a temporary node //
      temp_data->data = curr->data;
      insertion_cpy++;
      // then, for every node before the current one, as long as one of the previous nodes is greater than the temporary one //
      for (curr2 = curr->prev; (curr2 != NULL) && (list->cmp(curr2->data, temp_data->data) > 0); curr2 = curr2->prev)
      {
        // move the data to the next node //
        curr2->next->data = curr2->data;
        insertion_cpy++;
      }

      // in case the previous iteration reaches all the way until the list's head //
      // we replace head's data with temp node's data                             //
      if (curr2 == NULL)
      {
        list->head->data = temp_data->data;
        insertion_cpy++;
      }
      // else, we change the data of one of the list's inner nodes. // 
      else
      {
        curr2->next->data = temp_data->data;
        insertion_cpy++;
      }
    }
  }

  insertion_usec = clock() - insertion_usec;

  #ifdef _PERF_
    fprintf(stderr, "insertion sort:\nSize: %d\ncmp: %ld, cpy: %ld, usec: %ld\n", list->size, insertion_cmp, insertion_cpy, insertion_usec);
  #endif

  free(temp_data);

}

void selection_sort(dlist_t* list) {
 // my_selection(list, list->head);

  dnode_t *current;

  selection_usec = clock();

  for (current = list->head; current != list->tail; current = current->next)
  {
    swap(current, min(list, current));
    selection_cpy++;
  }

  selection_usec = clock() - selection_usec;
  #ifdef _PERF_
    fprintf(stderr, "selection sort:\nSize: %d\ncmp: %ld, cpy: %ld, usec: %ld\n", list->size, selection_cmp, selection_cpy, selection_usec);
  #endif
}

void bubble_sort(dlist_t* list) {
  int number_of_swaps;
  dnode_t *current;
  
  bubble_usec = clock();

  do
  {
    number_of_swaps = 0;

    for (current = list->head; current->next != NULL; current = current->next)
    {
      if ((list->cmp(current->data, current->next->data) > 0) && ++bubble_cmp)
      {
        swap(current, current->next);
        number_of_swaps ++;
      }
    }

    bubble_cpy += number_of_swaps;

  } while(number_of_swaps != 0);

  bubble_usec = clock() - bubble_usec;

  #ifdef _PERF_
    fprintf(stderr, "bubble sort:\nSize: %d\ncmp: %ld, cpy: %ld, usec: %ld\n", list->size, bubble_cmp, bubble_cpy, bubble_usec);
  #endif
}

void quick_sort(dlist_t* list) {

  quick_usec = clock();

  recursive_quicksort(list, list->head, list->tail);

  quick_usec = clock() - quick_usec;
  
  #ifdef _PERF_
    fprintf(stderr, "quick sort:\nSize: %d\ncmp: %ld, cpy: %ld, usec: %ld\n", list->size, quick_cmp, quick_cpy, quick_usec);
  #endif

}


void heap_sort(dlist_t* list) {
  int i;
  int array_size = list->size;
  type_t *heap_array;
  type_t temp_data;

  heap_usec = clock();

  heap_array = dlist2table(list);

  for (i = array_size / 2 - 1; i >= 0; i--)
  {
    heap_array = create_max_heap(list, heap_array, array_size, i);
  }

  for (i = array_size - 1; i >= 0; i--)
  {
    heap_cpy++;
    temp_data = heap_array[0];
    heap_array[0] = heap_array[i];
    heap_array[i] = temp_data;

    heap_array = create_max_heap(list, heap_array, i, 0);

  }

  table2dlist(heap_array, array_size, list);

  heap_usec = clock() - heap_usec;

  #ifdef _PERF_
    fprintf(stderr, "heap sort:\nSize: %d\ncmp: %ld, cpy: %ld, usec: %ld\n", list->size, heap_cmp, heap_cpy, heap_usec);
  #endif
}

type_t *merge(dlist_t *list, type_t merge_array[], int left, int medium, int right){
  int i, j, k;
  int s1 = medium - left + 1;
  int s2 = right - medium;
  type_t left_sub[s1];
  type_t right_sub[s2];

  //Copying the array's elements into the left and right sub arrays 
  for (i = 0; i < s1; i++)
  {
    left_sub[i] = merge_array[left + i];
  }

  for (j = 0; j < s2; j++)
  {
    right_sub[j] = merge_array[medium + 1 + j];
  }

  i = 0;
  j = 0;
  k = left;

  while (i < s1 && j < s2)
  {
    
    if(list->cmp(left_sub[i], right_sub[j]) <= 0)
    {
      merge_array[k] = left_sub[i];
      i++;
      merge_cpy++;
    }
    else
    {
      merge_array[k] = right_sub[j];
      j++;
      merge_cpy++;
    }

    k++;
  }

  while (i < s1)
  {
    merge_array[k] = left_sub[i];
    i++;
    k++;
    merge_cpy++;
  }

  while (j < s2)
  {
    merge_array[k] = right_sub[j];
    j++;
    k++;
    merge_cpy++;
  }

  return merge_array;
}

type_t *my_merge_sort(dlist_t *list, type_t merge_array[], int left, int right){
  int medium;

  if (left < right && ++merge_cmp)
  {
    medium = left + (right - left)/2;

    my_merge_sort(list, merge_array, left, medium);
    my_merge_sort(list, merge_array, medium + 1, right);

    merge_array = merge(list, merge_array, left, medium, right);
  }

  return merge_array;
}

void merge_sort(dlist_t* list) {
  int left = 0;
  int right = list->size - 1;

  type_t *merge_array;

  merge_usec = clock();

  merge_array = dlist2table(list);

  merge_array = my_merge_sort(list, merge_array, left, right);

  table2dlist(merge_array, right + 1, list);

  merge_usec = clock() - merge_usec;

  #ifdef _PERF_
    fprintf(stderr, "merge sort:\nSize: %d\ncmp: %ld, cpy: %ld, usec: %ld\n", list->size, merge_cmp, merge_cpy, merge_usec);
  #endif
}

void radixSortLSD(dlist_t* list, int bits_per_digit) {

  dlist_t **list_array;
  int array_size = (int) pow(2.0, bits_per_digit);
  int i, k = 0, counter = 0;
  int loop = 32/bits_per_digit;
  unsigned int mask, temp;
  // dnode_t *current;
  type_t data;
  int startclock, endclock;

  startclock = clock();

  list_array = (dlist_t**) malloc(array_size * sizeof(dlist_t*));

  /*creating lists for every element of the array*/
  for(i = 0; i < array_size; i++)
  {
   list_array[i] = create_dlist(student_cmp, student_print);
  }

  /* Creation of mask where mask = (2^b_p_d) - 1 */
  mask = array_size - 1;

  do
  {
    /* After every loop we need to check the next digits */
    if (k != 0)
    {
      mask = mask << bits_per_digit;
    }

    /* For loop where we sort the list elements */
    while(list->head != NULL)
    {
      data = rmv_index(list, 0);
      temp = mask & data.aem;
      radixLSD_extra++;
      //Shifting the temp as many bits as the mask was shifted left before so that we have the real value of the part//
      temp = temp >> k;

      //insert the node into the bucket where the digit belongs to
      insert(list_array[temp], list_array[temp]->size, data);
      radixLSD_move++;
    }

    for (i = 1; i < array_size; ++i)
    {
      if(list_array[i] != NULL)
      {
        //merge all the sublist from the array into one bucket to create the new more sorted list
        catenate(list_array[0], list_array[i]);
        radixLSD_catenate++;
      }
    }

    //how many digits the mask will be shifted//
    k += bits_per_digit; 
    counter++;

    list->head = list_array[0]->head;
    list->tail = list_array[0]->tail;
    list->size = list_array[0]->size;
    
    list_array[0]->head = NULL;
    list_array[0]->tail = NULL;
    list_array[0]->size = 0;

  }while(counter < loop);

  endclock = clock();

  radixLSD_usec = endclock - startclock;

  #ifdef _PERF_
    fprintf(stderr, "radixLSD\nextract_digit: %ld, move_word: %ld, catenate_lists: %ld, usec: %ld\n", radixLSD_extra, radixLSD_move, radixLSD_catenate, radixLSD_usec);
  #endif

}

void recursive_radix_sort(dlist_t *list, int bits_per_digit, int digit)
{
  dlist_t **list_array;
  int array_size = (int) pow(2.0, bits_per_digit);
  int i;
  unsigned int mask, temp;
  type_t data;

  // create the list array //
  list_array = (dlist_t**) malloc(array_size * sizeof(dlist_t*));

  /*creating lists for every element of the array*/
  for(i = 0; i < array_size; i++)
  {
    list_array[i] = create_dlist(student_cmp, student_print);
  }

  // set the mask to the appropriate digit //
  mask = array_size - 1;
  mask = mask << (32 - ((digit + 1) * bits_per_digit));

  // insert every node in the list array //
  while (list->head != NULL)
  {
    data = rmv_index(list, 0);

    temp = mask & data.aem;
    radixMSD_extra++;
    temp = temp >> (32 - ((digit + 1) * bits_per_digit));

    insert(list_array[temp], list_array[temp]->size, data);
    radixMSD_move++;
  }

  // if we can operate based on the digits //
  if (digit < (32 / bits_per_digit))
  {
    for (i = 0; i < array_size; i++)
    {
      // find a list with two or more nodes and repeat the process for that specific list //
      if (list_array[i]->size > 1)
      {
        recursive_radix_sort(list_array[i], bits_per_digit, digit + 1);
      }
    }    
  }

  // when all lists of the array have 0 or 1 nodes, catenate them to the list_array[0] //
  for (i = 1; i < array_size; ++i)
  {
    if(list_array[i] != NULL)
    {
      catenate(list_array[0], list_array[i]);
      radixMSD_catenate++;
    }
  }

  // then connect the list with the result of the catenation //
  list->head = list_array[0]->head;
  list->tail = list_array[0]->tail;
  list->size = list_array[0]->size;
  
  // and disconnect the list_array[0] from the catenated list //
  list_array[0]->head = NULL;
  list_array[0]->tail = NULL;
  list_array[0]->size = 0;

  for (i = 0; i < array_size; i++)
  {
    destroy_dlist(list_array[i]);
  }

  free(list_array);

  // finally, return the list to the caller //
  // return list;
}

void radixSortMSD(dlist_t* list, int bits_per_digit) {

  radixMSD_usec = clock();

  recursive_radix_sort(list, bits_per_digit, 0);
  
  radixMSD_usec = clock() - radixMSD_usec;

  #ifdef _PERF_
    fprintf(stderr, "radixMSD:\nextract_digit: %ld, move_word: %ld, catenate_lists: %ld, usec: %ld\n", radixMSD_extra, radixMSD_move, radixMSD_catenate, radixMSD_usec);
  #endif

}
