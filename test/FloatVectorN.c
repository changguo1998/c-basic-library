
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
#include "Type_FloatVectorN.h"

#define VectorLen 5

FloatVectorN(VectorLen)

void print_ivec(const struct IntVector_5* v) {
    printf("[");
    for(Int i = 0; i < VectorLen; i++) printf("%d,", v->methods->get(v, i));
    printf("]\n");
}

void print_fvec(const struct FloatVector_5* v) {
    printf("[");
    for(Int i = 0; i < VectorLen; i++) printf("%.3f,", v->methods->get(v, i));
    printf("]\n");
}

int main() {
    Int i, j;
    Float x, y;

    CBL_DECLARE_VARS(IntVector_5, 1, iv);
    CBL_DECLARE_VARS(FloatVector_5, 1, fv);

    printf("methods address: %p\n", &_CBL_FLOAT_VECTOR_5_METHODS);
    printf("after new:\n");
    printf("iv.data=%p\n", fv.data);
    printf("iv.methods=%p\n", fv.methods);

    printf("before initial: ");
    print_fvec(&fv);

    CBL_CALL(fv, rand_, 0, 10);
    printf("rand: ");
    print_fvec(&fv);
    x = CBL_CALL(fv, min);
    i = CBL_CALL(fv, argmin);
    printf("min: %.3f at %d\n", x, i);

    y = CBL_CALL(fv, max);
    j = CBL_CALL(fv, argmax);
    printf("max: %.3f at %d\n", y, j);

    CBL_CALL(fv, range_, 3, 1);
    printf("range: ");
    print_fvec(&fv);

    CBL_CALL(fv, set_all_, 8.0, 7.0, 6.0, 5.0, 4.0);
    printf("set all: ");
    print_fvec(&fv);

    printf("sum: %.3f\n", CBL_CALL(fv, sum));
    printf("prod: %.3f\n", CBL_CALL(fv, prod));

    CBL_CALL(fv, rand_, 0, 10);
    print_fvec(&fv);
    iv = CBL_CALL(fv, sortperm_);
    printf("sort: ");
    print_fvec(&fv);
    printf("perm:");
    print_ivec(&iv);

    return 0;
}
