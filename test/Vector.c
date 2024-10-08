#include <stdio.h>
#include "CBL_Vector.h"

int main() {
    Vector v1, v2;
    Int i, *p;

    v1 = VEC_allocate(TYPECODE_INT, sizeof(Int), 5);
    p = (Int*)v1.data;
    for(i = 0; i < 5; i++) p[i] = i;
    printf("v1:\n");
    for(i = 0; i < 5; i++) printf(" %d\n", p[i]);

    v2 = VEC_copy(v1);
    for(i = 0; i < 5; i++) ((Int*)v2.data)[i] += 1;
    printf("v2:");
    for(i = 0; i < 5; i++) printf(" %d", ((Int*)v2.data)[i]);

    VEC_free(&v1);
    VEC_free(&v2);
}
