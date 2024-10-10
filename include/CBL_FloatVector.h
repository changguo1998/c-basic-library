/******************************************************************************
 * MIT License                                                                *
 *                                                                            *
 * Copyright (c) 2024 Chang Guo                                               *
 *                                                                            *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell  *
 * copies of the Software, and to permit persons to whom the Software is      *
 * furnished to do so, subject to the following conditions:                   *
 *                                                                            *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.                            *
 *                                                                            *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR *
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,   *
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE*
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER     *
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.                                                                  *
 *                                                                            *
 ******************************************************************************/

#ifndef _CBL_FLOATVECTOR_H_
#define _CBL_FLOATVECTOR_H_

#include "CBL_Basic.h"

void _FLOAT_VECTOR_level0_get_by_vec(Float* b, const Float* a, Int len_a, const Int* index, Int len_index);

void _FLOAT_VECTOR_level0_set_by_vec(Float* a, Int len_a, const Int* index, const Float* values, Int len_index);

void _FLOAT_VECTOR_level0_fill(Float* a, Int n, Float value);

void _FLOAT_VECTOR_level0_rand(Float* a, Int n, Float min, Float max);

void _FLOAT_VECTOR_level0_rand_gauss(Float* a, Int n, Float mean, Float std);

Float _FLOAT_VECTOR_level0_sum(Float* a, Int n);

Float _FLOAT_VECTOR_level0_prod(Float* a, Int n);

void _FLOAT_VECTOR_level0_cumsum(Float* a, Int n);

void _FLOAT_VECTOR_level0_cumprod(Float* a, Int n);

Float _FLOAT_VECTOR_level0_min(Float* a, Int n, Int* mi);

Float _FLOAT_VECTOR_level0_max(Float* a, Int n, Int* mi);

Float _FLOAT_VECTOR_level0_mean(Float* a, Int n);

Float _FLOAT_VECTOR_level0_var(Float* a, Int n);

Float _FLOAT_VECTOR_level0_std(Float* a, Int n, Float correction);

void _FLOAT_VECTOR_level0_sort(Float* a, Int* perm, Int n);

struct FloatVector {
    Int    len;
    Float* data;

    void (*free)(struct FloatVector* this);

    void (*alloc)(struct FloatVector* this, Int len);

    void (*fill)(struct FloatVector* this, Float value);
    void (*rand)(struct FloatVector* this, Float min, Float max);
    void (*rand_gauss)(struct FloatVector* this, Float mean, Float std);
};

void FloatVector_init(struct FloatVector* this);

#endif // _CBL_FLOATVECTOR_H_
