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

#ifndef _CBL_FLOAT_MATRIX_H_
#define _CBL_FLOAT_MATRIX_H_

#include "CBL_Basic.h"

void _FLOAT_MATRIX_level0_get_row(Float* v, Float* X, Int m, Int n);

void _FLOAT_MATRIX_level0_get_column(Float* v, Float* X, Int m, Int n);

void _FLOAT_MATRIX_level0_transpose(Float* X, Int m, Int n);

void _FLOAT_MATRIX_level0_diag(Float* v, Float* X, Int m, Int n);

void _FLOAT_MATRIX_level0_diagm(Float* X, Float* v, Int m, Int n);

void _FLOAT_MATRIX_level0_product(Float  Z,
                                  Float* X,
                                  Float* Y,
                                  Int    p,
                                  Int    q,
                                  Int    r);

void _FLOAT_MATRIX_level0_inverse(Float* Y, Float* X, Int m, Int n);

/**
 * @brief FloatMatrix
 * @param nrow Int
 * @param ncol Int
 * @param data Float*
 */
struct FloatMatrix {
    Int    nrow; /**< number of row */
    Int    ncol;
    Float* data;
};

#endif // _CBL_FLOAT_MATRIX_H_
