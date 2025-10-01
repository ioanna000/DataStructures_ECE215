
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "type_t.h"

int student_cmp(type_t s1, type_t s2) {
    return s1.aem - s2.aem;
}

void student_print(FILE* fp, type_t s, bool only_key) {
    if(only_key)
        fprintf(fp, "%5d", s.aem);
    else
        fprintf(fp, "%5d. %s", s.aem, s.name);
}
