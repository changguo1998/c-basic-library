#include <stdio.h>
#include <stdlib.h>
#include "CBL_IntVector.h"

void print_ivec(const struct IntVector* v) {
    printf("[");
    for(Int i = 0; i < v->len; i++) printf("%d,", v->get(v, i));
    printf("]\n");
}

int main() {
    struct IntVector iv, iw;
    Int i, j;
    IntVector_init(&iv);
    IntVector_init(&iw);

    printf("alloc: ");
    iv.alloc(&iv, 5);
    print_ivec(&iv);

    iv.rand(&iv, 20);
    printf("rand: ");
    print_ivec(&iv);
    i = iv.min(&iv, &j);
    printf("min: %d at %d\n", i, j);
    i = iv.max(&iv, &j);
    printf("max: %d at %d\n", i, j);

    iv.range(&iv, 3, 1, iv.len+2);
    printf("range: ");
    print_ivec(&iv);

    printf("sum: %d\n", iv.sum(&iv));
    printf("prod: %d\n", iv.prod(&iv));

    iv.rand(&iv, 20);
    print_ivec(&iv);
    iv.sort(&iv, &iw);
    printf("sort: ");
    print_ivec(&iv);
    printf("perm:");
    print_ivec(&iw);

    iv.free(&iv);
    return 0;
}
