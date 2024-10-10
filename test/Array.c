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

#include "CBL_Array.h"

int main() {
    Vector index;
    Array  array;
    Int *  ivec, n,      i,      ivar1, ivar2, ivar3;
    Float *fv, * fvar1, *fvar2, *fvar3;

    index   = VEC_allocate(TYPECODE_INT, sizeof(Int), 2);
    ivec    = (Int*)index.data;
    ivec[0] = 4;
    ivec[1] = 3;
    array   = ARR_allocate(sizeof(Float), TYPECODE_FLOAT, index);
    n       = ARR_prod_Int_vector(array.size);
    fv      = (Float*)array.data;
    for(i = 0; i < n; i++) fv[i] = (Float)rand() / (Float)RAND_MAX;

    printf("float matrix in linear range:\n");
    for(i = 0; i < n; i++) printf("  %.3f", fv[i]);
    printf("\n\n");

    for(i = 0; i < 4; i++) {
        ivec[0] = i;
        ivec[1] = 0;
        ivar1   = ARR_linear_index(index, array.size);
        fvar1   = (Float*)ARR_address(array, index);
        ivec[1] = 1;
        ivar2   = ARR_linear_index(index, array.size);
        fvar2   = (Float*)ARR_address(array, index);
        ivec[1] = 2;
        ivar3   = ARR_linear_index(index, array.size);
        fvar3   = (Float*)ARR_address(array, index);
        printf("  %02d %02d %02d %.3f %.3f %.3f\n", ivar1, ivar2, ivar3, *fvar1, *fvar2, *fvar3);
    }
    return 0;
}
