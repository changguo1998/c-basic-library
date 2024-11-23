// MIT License
//
// Copyright (c) 2024 Chang Guo
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.
//

#ifndef _CBL_INTVECTOR_H_
#define _CBL_INTVECTOR_H_

#include "Module_Basic.h"

struct IntVectorMethods {
    // memory management
    void (*free_)(struct IntVector* this);
    void (*alloc_)(struct IntVector* this, Int len);
    // basic
    Int (* get)(const struct IntVector* this, Int index);
    void (*index_)(struct IntVector* this, struct IntVector indexs);
    void (*slice_)(struct IntVector* this, Int start, Int step, Int stop);
    Int (* count)(const struct IntVector* this);
    void (*index_flag_)(struct IntVector* this, struct IntVector flags);
    void (*set_)(struct IntVector* this, Int index, Int value);
    void (*setas_)(struct IntVector* this, Int n, ...);
    void (*vcat_)(struct IntVector* this, Int n, ...);
    void (*rand_)(struct IntVector* this, Int a, Int b);
    void (*rand_from_)(struct IntVector* this, struct IntVector value_set);
    void (*fill_)(struct IntVector* this, Int value);
    void (*range_)(struct IntVector* this, Int start, Int step, Int stop);
    void (*copy_from_)(struct IntVector* this, struct IntVector src);
    void (*find_trues_)(struct IntVector* this, struct IntVector flags);
    void (*filter_)(struct IntVector* this, i_Func_i isOK);
    void (*push_)(struct IntVector* this, Int value);
    // math
    Bool (*isequal)(struct IntVector* this, struct IntVector other);
    Int (* sum)(const struct IntVector* this);
    Int (* prod)(const struct IntVector* this);
    Int (* min)(const struct IntVector* this);
    Int (* max)(const struct IntVector* this);
    Int (* argmin)(const struct IntVector* this);
    Int (* argmax)(const struct IntVector* this);
    void (*cumsum_)(struct IntVector* this, Int initial);
    void (*cumprod_)(struct IntVector* this, Int initial);
    void (*sort_)(struct IntVector* this);
    void (*sortperm_)(struct IntVector* this, struct IntVector* perm);
    Int (* dot)(const struct IntVector* this, struct IntVector b);
    // index converting
    Int (* coord_linear)(const struct IntVector* this, struct IntVector size);
    void (*coord_cartesian_)(struct IntVector* this, struct IntVector size, Int linear_index);
};

extern struct IntVectorMethods _CBL_INT_VECTOR_METHODS;

static inline void IntVector_new_(struct IntVector* this) {
    this->len = 0;
    this->data = NULL;
    this->methods = &_CBL_INT_VECTOR_METHODS;
}

void IntVector_free_(struct IntVector* this);
void IntVector_alloc_(struct IntVector* this, Int len);
Int  IntVector_get(const struct IntVector* this, Int index);
void IntVector_index_(struct IntVector* this, struct IntVector indexs);
void IntVector_slice_(struct IntVector* this, Int start, Int step, Int stop);
Int  IntVector_count(const struct IntVector* this);
void IntVector_index_flag_(struct IntVector* this, struct IntVector flags);
void IntVector_set_(struct IntVector* this, Int index, Int value);
void IntVector_setas_(struct IntVector* this, Int n, ...);
void IntVector_vcat_(struct IntVector* this, Int n, ...);
void IntVector_rand_(struct IntVector* this, Int a, Int b);
void IntVector_rand_from_(struct IntVector* this, struct IntVector value_set);
void IntVector_fill_(struct IntVector* this, Int value);
void IntVector_range_(struct IntVector* this, Int start, Int step, Int stop);
void IntVector_copy_from_(struct IntVector* this, struct IntVector src);
void IntVector_find_trues_(struct IntVector* this, struct IntVector flags);
void IntVector_filter_(struct IntVector* this, i_Func_i isOK);
void IntVector_push_(struct IntVector* this, Int value);
Bool IntVector_isequal(struct IntVector* this, struct IntVector other);
Int  IntVector_sum(const struct IntVector* this);
Int  IntVector_prod(const struct IntVector* this);
Int  IntVector_min(const struct IntVector* this);
Int  IntVector_max(const struct IntVector* this);
Int  IntVector_argmin(const struct IntVector* this);
Int  IntVector_argmax(const struct IntVector* this);
void IntVector_cumsum_(struct IntVector* this, Int initial);
void IntVector_cumprod_(struct IntVector* this, Int initial);
void IntVector_sort_(struct IntVector* this);
void IntVector_sortperm_(struct IntVector* this, struct IntVector* perm);
Int  IntVector_dot(const struct IntVector* this, struct IntVector b);
Int  IntVector_coord_linear(const struct IntVector* this, struct IntVector size);
void IntVector_coord_cartesian_(struct IntVector* this, struct IntVector size, Int linear_index);

#endif // _CBL_INTVECTOR_H_
