#include <stdio.h>
#include <stdlib.h>

#include "dlist.h"
#include "sort.h"

typedef enum {
  INSERTION_SORT=0, 
  SELECTION_SORT=1, 
  BUBBLE_SORT, 
  QUICK_SORT=3, 
  HEAP_SORT, 
  MERGE_SORT=5, 
  RADIX_SORT_LSD,
  RADIX_SORT_MSD=7
} algorithm_type;

int main(int argc, char* argv[]) {
  
  dlist_t* list = create_dlist(student_cmp, student_print);

  if(argc<3) {
    printf("Insufficient arguments!\n");
    return 0;
  }
  
  FILE* fp = fopen(argv[1], "r");
  type_t student;
  
  while(fscanf(fp, "%d %s\n", &student.aem, student.name) != EOF) {
    insert(list, size(list), student);
  }
  print(stdout, list);
  
  switch(atoi(argv[2])) {
    case INSERTION_SORT:
      insertion_sort(list);
      break;
    case SELECTION_SORT:
      selection_sort(list);
      break;
    case BUBBLE_SORT:
      bubble_sort(list);
      break;
    case QUICK_SORT:
      quick_sort(list);
      break;
    case HEAP_SORT:
      heap_sort(list);
      break;
    case MERGE_SORT:
      merge_sort(list);
      break;
    case RADIX_SORT_LSD:
      if(argc<4) {
        printf("Insufficient arguments!\n");
        return 0;
      }
      radixSortLSD(list, atoi(argv[3]));
    case RADIX_SORT_MSD:
      if(argc<4) {
        printf("Insufficient arguments!\n");
        return 0;
      }
      radixSortMSD(list, atoi(argv[3]));
      break;
  }
  
  printf("-------------------\n");
  print(stdout, list);
}
