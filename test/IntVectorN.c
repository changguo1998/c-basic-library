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
#include "Module_Basic.h"
#include "Type_IntVectorN.h"

#define VectorLen 5

IntVectorN(VectorLen)

void print_ivec(const struct IntVector_5* v) {
    printf("[");
    for(Int i = 0; i < VectorLen; i++) printf("%d,", v->methods->get(v, i));
    printf("]\n");
}

int main() {
    Int i, j;

    CBL_DECLARE_VARS(IntVector_5, 2, iv, iw);

    printf("IntVector methods collection: %p\n", &_CBL_INT_VECTOR_5_METHODS);
    printf("before new:\n");
    printf("iv.data=%p\n", iv.data);
    printf("iv.methods=%p\n", iv.methods);
    IntVector_5_new_(&iv);
    IntVector_5_new_(&iw);
    printf("after new:\n");
    printf("iv.data=%p\n", iv.data);
    printf("iv.methods=%p\n", iv.methods);

    printf("before initial: ");
    print_ivec(&iv);

    CBL_CALL(iv, rand_, 0, 20);
    printf("rand: ");
    print_ivec(&iv);
    i = CBL_CALL(iv, min);
    j = CBL_CALL(iv, argmin);
    printf("min: %d at %d\n", i, j);

    i = CBL_CALL(iv, max);
    j = CBL_CALL(iv, argmax);
    printf("max: %d at %d\n", i, j);

    CBL_CALL(iv, range_, 3, 1);
    printf("range: ");
    print_ivec(&iv);

    CBL_CALL(iv, set_all_, 8, 7, 6, 5, 4);
    printf("set all: ");
    print_ivec(&iv);

    printf("sum: %d\n", CBL_CALL(iv, sum));
    printf("prod: %d\n", CBL_CALL(iv, prod));

    CBL_CALL(iv, rand_, 0, 20);
    print_ivec(&iv);
    iw = CBL_CALL(iv, sortperm_);
    printf("sort: ");
    print_ivec(&iv);
    printf("perm:");
    print_ivec(&iw);

    return 0;
}
