#ifndef _TYPE_T_H_
#define _TYPE_T_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

struct student {
    int aem;
    char name[32];
};

typedef struct student type_t;

int student_cmp(type_t s1, type_t s2);

void student_print(FILE* fp, type_t s, bool only_key);

#endif
