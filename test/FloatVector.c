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

#include "Type_FloatVector.h"

void print_ivec(const struct IntVector* v) {
    printf("[");
    for(Int i = 0; i < v->len; i++) printf("%d,", v->methods->get(v, i));
    printf("]\n");
}

void print_fvec(const struct FloatVector* v) {
    printf("[");
    for(Int i = 0; i < v->len; i++) printf("%.3f,", v->methods->get(v, i));
    printf("]\n");
}

int main() {
    CBL_DECLARE_VARS(IntVector, 1, iv);
    CBL_DECLARE_VARS(FloatVector, 1, fv);

    Int   i, j;
    Float x, y;

    printf("after new:\n");
    printf("iv.len=%d\n", fv.len);
    printf("iv.data=%p\n", fv.data);
    printf("iv.methods=%p\n", fv.methods);

    printf("alloc: ");
    CBL_CALL(fv, alloc_, 10);
    print_fvec(&fv);

    CBL_CALL(fv, rand_, 0.0, 20.0);
    printf("rand: ");
    print_fvec(&fv);
    x = CBL_CALL(fv, min);
    i = CBL_CALL(fv, argmin);
    printf("min: %.3f at %d\n", x, i);

    y = CBL_CALL(fv, max);
    j = CBL_CALL(fv, argmax);
    printf("max: %.3f at %d\n", y, j);

    CBL_CALL(fv, range_, 1.0, 2.0);
    printf("range: ");
    print_fvec(&fv);

    printf("sum: %.3f\n", CBL_CALL(fv, sum));
    printf("prod: %.3f\n", CBL_CALL(fv, prod));

    CBL_CALL(fv, rand_, 0.0, 10.0);
    print_fvec(&fv);
    CBL_CALL(fv, sortperm_, &iv);
    printf("sort: ");
    print_fvec(&fv);
    printf("perm:");
    print_ivec(&iv);

    CBL_FREE_VARS(FloatVector, 1, fv);
    return 0;
}
