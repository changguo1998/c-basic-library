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

#include "Module_Basic.h"
#include "Type_IntVector.h"

void print_ivec(const struct IntVector* v) {
    printf("[");
    for(Int i = 0; i < v->len; i++) printf("%d,", v->methods->get(v, i));
    printf("]\n");
}

int main() {
    Int i, j;

    CBL_DECLARE_VARS(IntVector, 2, iv, iw);

    printf("after new:\n");
    printf("iv.len=%d\n", iv.len);
    printf("iv.data=%p\n", iv.data);
    printf("iv.methods=%p\n", iv.methods);

    printf("alloc: ");
    CBL_CALL(iv, alloc_, 10);
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

    CBL_CALL(iv, range_, 3, 1, iv.len + 2);
    printf("range: ");
    print_ivec(&iv);

    printf("sum: %d\n", CBL_CALL(iv, sum));
    printf("prod: %d\n", CBL_CALL(iv, prod));

    CBL_CALL(iv, rand_, 0, 20);
    print_ivec(&iv);
    CBL_CALL(iv, sortperm_, &iw);
    printf("sort: ");
    print_ivec(&iv);
    printf("perm:");
    print_ivec(&iw);

    CBL_FREE_VARS(IntVector, 2, iv, iw);
    return 0;
}
