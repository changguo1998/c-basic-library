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

#ifndef _CBL_FLOATVECTOR_H_
#define _CBL_FLOATVECTOR_H_

#include "Module_Basic.h"
#include "Type_IntVector.h"


struct FloatVectorMethods {
    // memory management
    void (*free_)(struct FloatVector* this);
    void (*alloc_)(struct FloatVector* this, Int len);
    // basic
    Float (*get)(const struct FloatVector* this, Int index);
    void (* index_)(struct FloatVector* this, struct FloatVector src, struct IntVector indexs);
    void (* slice_)(struct FloatVector* this, struct FloatVector src, Int start, Int step, Int stop);
    void (* index_flag_)(struct FloatVector* this, struct FloatVector src, struct IntVector flags);
    void (* set_)(struct FloatVector* this, Int index, Float value);
    void (* setas_)(struct FloatVector* this, Int n, ...);
    void (* vcat_)(struct FloatVector* this, Int n, ...);
    void (* rand_)(struct FloatVector* this, Float min, Float max);
    void (* rand_from_)(struct FloatVector* this, struct FloatVector value_set);
    void (* fill_)(struct FloatVector* this, Float value);
    void (* fill_range_)(struct FloatVector* this, Float start, Float stop);
    void (* range_)(struct FloatVector* this, Float start, Float step, Float stop);
    void (* copy_from_)(struct FloatVector* this, struct FloatVector src);
    // math
    Float (*sum)(const struct FloatVector* this);
    Float (*mean)(const struct FloatVector* this);
    Float (*var)(const struct FloatVector* this);
    Float (*std)(const struct FloatVector* this);
    Float (*norm)(const struct FloatVector* this, Int order);
    Float (*prod)(const struct FloatVector* this);
    Float (*min)(const struct FloatVector* this);
    Float (*max)(const struct FloatVector* this);
    Int (*  argmin)(const struct FloatVector* this);
    Int (*  argmax)(const struct FloatVector* this);
    void (* cumsum_)(struct FloatVector* this, Float initial);
    void (* cumprod_)(struct FloatVector* this, Float initial);
    void (* sort_)(struct FloatVector* this);
    void (* sortperm_)(struct FloatVector* this, struct IntVector* perm);
    Float (*dot)(const struct FloatVector* this, struct FloatVector b);
    void (* cross_)(struct FloatVector* this, struct FloatVector x, struct FloatVector y);
    void (* map_f_ff_)(struct FloatVector* this, f_Func_ff func, struct FloatVector x);
    void (* add_scalar_)(struct FloatVector* this, Float value);
    void (* sub_scalar_)(struct FloatVector* this, Float value);
    void (* mul_scalar_)(struct FloatVector* this, Float value);
    void (* div_scalar_)(struct FloatVector* this, Float value);
    void (* add_)(struct FloatVector* this, struct FloatVector b);
    void (* sub_)(struct FloatVector* this, struct FloatVector b);
    void (* mul_)(struct FloatVector* this, struct FloatVector b);
    void (* div_)(struct FloatVector* this, struct FloatVector b);
    void (* sqrt_)(struct FloatVector* this);
    void (* root_)(struct FloatVector* this, Int order);
    void (* pow_)(struct FloatVector* this, Int order);
    void (* normalize_)(struct FloatVector* this);
    // polynomial
    Float (*polyval)(const struct FloatVector* this, Float x);
    void (* polyint_)(struct FloatVector* this, Float y0);
    void (* polydiff_)(struct FloatVector* this);
    // matrix
    void (*get_row_)(struct FloatVector* this, struct FloatMatrix M, Int r);
    void (*get_column_)(struct FloatVector* this, struct FloatMatrix M, Int c);
    // complex
    void (*ifft_)(struct FloatVector* this, struct ComplexVector X);
};

extern struct FloatVectorMethods _CBL_FLOAT_VECTOR_METHODS;

static inline void FloatVector_new_(struct FloatVector* this) {
    this->len = 0;
    this->data = NULL;
    this->methods = &_CBL_FLOAT_VECTOR_METHODS;
}

void  FloatVector_free_(struct FloatVector* this);
void  FloatVector_alloc_(struct FloatVector* this, Int len);
Float FloatVector_get(const struct FloatVector* this, Int index);
void  FloatVector_index_(struct FloatVector* this, struct FloatVector src, struct IntVector indexs);
void  FloatVector_slice_(struct FloatVector* this, struct FloatVector src, Int start, Int step, Int stop);
void  FloatVector_index_flag_(struct FloatVector* this, struct FloatVector src, struct IntVector flags);
void  FloatVector_set_(struct FloatVector* this, Int index, Float value);
void  FloatVector_setas_(struct FloatVector* this, Int n, ...);
void  FloatVector_vcat_(struct FloatVector* this, Int n, ...);
void  FloatVector_rand_(struct FloatVector* this, Float min, Float max);
void  FloatVector_rand_from_(struct FloatVector* this, struct FloatVector value_set);
void  FloatVector_fill_(struct FloatVector* this, Float value);
void  FloatVector_fill_range_(struct FloatVector* this, Float start, Float stop);
void  FloatVector_range_(struct FloatVector* this, Float start, Float step, Float stop);
void  FloatVector_copy_from_(struct FloatVector* this, struct FloatVector src);
Float FloatVector_sum(const struct FloatVector* this);
Float FloatVector_mean(const struct FloatVector* this);
Float FloatVector_var(const struct FloatVector* this);
Float FloatVector_std(const struct FloatVector* this);
Float FloatVector_norm(const struct FloatVector* this, Int order);
Float FloatVector_prod(const struct FloatVector* this);
Float FloatVector_min(const struct FloatVector* this);
Float FloatVector_max(const struct FloatVector* this);
Int   FloatVector_argmin(const struct FloatVector* this);
Int   FloatVector_argmax(const struct FloatVector* this);
void  FloatVector_cumsum_(struct FloatVector* this, Float initial);
void  FloatVector_cumprod_(struct FloatVector* this, Float initial);
void  FloatVector_sort_(struct FloatVector* this);
void  FloatVector_sortperm_(struct FloatVector* this, struct IntVector* perm);
Float FloatVector_dot(const struct FloatVector* this, struct FloatVector b);
void  FloatVector_cross_(struct FloatVector* this, struct FloatVector x, struct FloatVector y);
void  FloatVector_map_f_ff_(struct FloatVector* this, f_Func_ff func, struct FloatVector x);
void  FloatVector_add_scalar_(struct FloatVector* this, Float value);
void  FloatVector_sub_scalar_(struct FloatVector* this, Float value);
void  FloatVector_mul_scalar_(struct FloatVector* this, Float value);
void  FloatVector_div_scalar_(struct FloatVector* this, Float value);
void  FloatVector_add_(struct FloatVector* this, struct FloatVector b);
void  FloatVector_sub_(struct FloatVector* this, struct FloatVector b);
void  FloatVector_mul_(struct FloatVector* this, struct FloatVector b);
void  FloatVector_div_(struct FloatVector* this, struct FloatVector b);
void  FloatVector_sqrt_(struct FloatVector* this);
void  FloatVector_root_(struct FloatVector* this, Int order);
void  FloatVector_pow_(struct FloatVector* this, Int order);
void  FloatVector_normalize_(struct FloatVector* this);
Float FloatVector_polyval(const struct FloatVector* this, Float x);
void  FloatVector_polyint_(struct FloatVector* this, Float y0);
void  FloatVector_polydiff_(struct FloatVector* this);
void  FloatVector_get_row_(struct FloatVector* this, struct FloatMatrix M, Int r);
void  FloatVector_get_column_(struct FloatVector* this, struct FloatMatrix M, Int c);
void  FloatVector_ifft_(struct FloatVector* this, struct ComplexVector X);

#endif // _CBL_FLOATVECTOR_H_
