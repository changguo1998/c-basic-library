/**********************************************************************************
 * MIT License                                                                    *
 *                                                                                *
 * Copyright (c) 2024 Chang Guo                                                   *
 *                                                                                *
 * Permission is hereby granted, free of charge, to any person obtaining a copy   *
 * of this software and associated documentation files (the "Software"), to deal  *
 * in the Software without restriction, including without limitation the rights   *
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell      *
 * copies of the Software, and to permit persons to whom the Software is          *
 * furnished to do so, subject to the following conditions:                       *
 *                                                                                *
 * The above copyright notice and this permission notice shall be included in all *
 * copies or substantial portions of the Software.                                *
 *                                                                                *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR     *
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,       *
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE    *
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER         *
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,  *
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE  *
 * SOFTWARE.                                                                      *
 *                                                                                *
 **********************************************************************************/

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
    iv.alloc_(&iv, 5);
    print_ivec(&iv);

    iv.rand_(&iv, 20);
    printf("rand: ");
    print_ivec(&iv);
    i = iv.min(&iv, &j);
    printf("min: %d at %d\n", i, j);
    i = iv.max(&iv, &j);
    printf("max: %d at %d\n", i, j);

    iv.range_(&iv, 3, 1, iv.len+2);
    printf("range: ");
    print_ivec(&iv);

    printf("sum: %d\n", iv.sum(&iv));
    printf("prod: %d\n", iv.prod(&iv));

    iv.rand_(&iv, 20);
    print_ivec(&iv);
    iv.sort(&iv, &iw);
    printf("sort: ");
    print_ivec(&iv);
    printf("perm:");
    print_ivec(&iw);

    iv.free_(&iv);
    return 0;
}
