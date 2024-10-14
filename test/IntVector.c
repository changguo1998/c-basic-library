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
#include <time.h>

#include "Type_IntVector.h"

#define CALLV(obj, mth) ((obj).methods->mth(&(obj)))
#define CALL(obj, mth, ...) ((obj).methods->mth(&(obj), __VA_ARGS__))

void print_ivec(const struct IntVector* v) {
    printf("[");
    for(Int i = 0; i < v->len; i++) printf("%d,", v->methods->get(v, i));
    printf("]\n");
}

int main() {
    struct IntVector iv, iw;
    Int              i,  j;

    srand(time(NULL));
    printf("IntVector methods collection: %p\n", &_CBL_INT_VECTOR_METHODS);
    printf("before new:\n");
    printf("iv.len=%d\n", iv.len);
    printf("iv.data=%p\n", iv.data);
    printf("iv.methods=%p\n", iv.methods);
    IntVector_new_(&iv);
    IntVector_new_(&iw);
    printf("after new:\n");
    printf("iv.len=%d\n", iv.len);
    printf("iv.data=%p\n", iv.data);
    printf("iv.methods=%p\n", iv.methods);

    printf("alloc: ");
    CALL(iv, alloc_, 10);
    print_ivec(&iv);

    CALL(iv, rand_, 0, 20);
    printf("rand: ");
    print_ivec(&iv);
    i = CALLV(iv, min);
    j = CALLV(iv, argmin);
    printf("min: %d at %d\n", i, j);

    i = CALLV(iv, max);
    j = CALLV(iv, argmax);
    printf("max: %d at %d\n", i, j);

    CALL(iv, range_, 3, 1, iv.len + 2);
    printf("range: ");
    print_ivec(&iv);

    printf("sum: %d\n", CALLV(iv, sum));
    printf("prod: %d\n", CALLV(iv, prod));

    CALL(iv, rand_, 0, 20);
    print_ivec(&iv);
    CALL(iv, sortperm_, &iw);
    printf("sort: ");
    print_ivec(&iv);
    printf("perm:");
    print_ivec(&iw);

    CALLV(iv, free_);
    CALLV(iw, free_);
    return 0;
}
