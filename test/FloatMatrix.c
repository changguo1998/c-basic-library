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
#include "Type_FloatMatrix.h"

#define call(...) CBL_CALL(__VA_ARGS__)

void print_fmat(struct FloatMatrix fmat) {
    Int i, j;
    for(i = 0; i < fmat.nrow; i++) {
        for(j = 0; j < fmat.ncol; j++)
            printf("%.2f ", CBL_CALL(fmat, get, i, j));
        printf("\n");
    }
}

int main() {
    Int   i, j;
    Float x, y, z;

    CBL_DECLARE_VARS(FloatMatrix, 3, X, Y, Z);

    call(Y, alloc_, 3, 3);
    call(Z, alloc_, 3, 2);
    call(Y, rand_, 0.0, 10.0);
    call(Z, rand_, 0.0, 10.0);

    printf("Y:\n");
    print_fmat(Y);
    printf("Z:\n");
    print_fmat(Z);

    call(X, hcat_, Y, Z);
    printf("X:\n");
    print_fmat(X);

    call(Z, alloc_, 2, 3);
    call(Z, fill_, 1.5);
    printf("Z:\n");
    print_fmat(Z);
    call(X, vcat_, Y, Z);
    printf("X:\n");
    print_fmat(X);


    CBL_FREE_VARS(FloatMatrix, 3, X, Y, Z);
    return 0;
}
