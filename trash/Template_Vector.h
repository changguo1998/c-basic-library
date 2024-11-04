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

#ifndef _TEMPLATE_VECTOR_H_
#define _TEMPLATE_VECTOR_H_

#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <stdarg.h>

#include "Module_Basic.h"
#include "Type_Part_math_basic.h"

#define _Vector_type_struct(T) struct T##Vector{\
    Int len;\
    T *data;\
    struct T##VectorMethods* methods;\
};


#define _Vector_internal_methods_declaration(T) \
    void (*free_)(       struct T##Vector* this);\
    void (*alloc_)(      struct T##Vector* this, Int len);\
    T    (*get)(   const struct T##Vector* this, Int index);\
    void (*index_)(      struct T##Vector* this, struct T##Vector src, struct IntVector indexs);\
    void (*slice_)(      struct T##Vector* this, struct T##Vector src, Int start, Int step, Int stop);\
    Int  (*count)( const struct T##Vector* this);\
    void (*index_flag_)( struct T##Vector* this, struct T##Vector src, struct IntVector flags);\
    void (*set_)(        struct T##Vector* this, Int index, T value);\
    void (*setas_)(      struct T##Vector* this, Int n, ...);\
    void (*vcat_)(       struct T##Vector* this, Int n, ...);\
    void (*rand_)(       struct T##Vector* this, T min, T max);\
    void (*rand_from_)(  struct T##Vector* this, struct T##Vector value_set);\
    void (*fill_)(       struct T##Vector* this, T value);\
    void (*range_)(      struct T##Vector* this, T start, T step, T stop);\
    void (*copy_from_)(  struct T##Vector* this, struct T##Vector src);\
    void (*find_trues_)( struct T##Vector* this, struct T##Vector flags);\
    T    (*sum)(   const struct T##Vector* this);\
    T    (*prod)(  const struct T##Vector* this);\
    T    (*min)(   const struct T##Vector* this);\
    T    (*max)(   const struct T##Vector* this);\
    Int  (*argmin)(const struct T##Vector* this);\
    Int  (*argmax)(const struct T##Vector* this);\
    void (*cumsum_)(     struct T##Vector* this, T initial);\
    void (*cumprod_)(    struct T##Vector* this, T initial);\
    void (*sort_)(       struct T##Vector* this);\
    void (*sortperm_)(   struct T##Vector* this, struct IntVector* perm);\
    T    (*dot)(   const struct T##Vector* this, struct T##Vector b);

#define _Vector_internal_methods_defination(T)\
static inline void T##Vector_new_(struct T##Vector *this);\
static inline void T##Vector_free_(struct T##Vector* this){\
    if(this == NULL) return;\
    if(this->data) {\
        free(this->data);\
        this->data = NULL;\
    }\
    this->len = 0;\
}\
static inline void T##Vector_alloc_(struct T##Vector* this, Int len){\
    T *p = NULL;\
    Int n;\
    if(this == NULL) return;\
    if(this->len == len) return;\
    if(len <= 0){\
        T##Vector_free_(this);\
        return;\
    }\
    if(this->len <= 0) {\
        this->data = (T*)calloc(len, sizeof(T));\
        this->len = len;\
        return;\
    }\
    p = (T*)calloc(len, sizeof(T));\
    n = this->len < len ? this->len : len;\
    memcpy(p, this->data, n * sizeof(T));\
    free(this->data);\
    this->data = p;\
    this->len = len;\
}\
static inline T T##Vector_get(const struct T##Vector* this, Int index){\
    if((index >= this->len) || (index < 0))\
        error_index_out_of_bounds("(Vector_get) index out of bounds");\
    return this->data[index];\
}\
static inline void T##Vector_index_(struct T##Vector* this, struct T##Vector src, struct IntVector indexs){\
    Int i;\
    if(indexs.len <= 0) return;\
    T##Vector_alloc_(this, indexs.len);\
    if(src.len <= 0) return;\
    for(i = 0; i < indexs.len; i++) {\
        if(indexs.data[i] < 0 || indexs.data[i] >= src.len)\
            error_index_out_of_bounds("(Vector_index_) index out of bounds");\
        this->data[i] = src.data[indexs.data[i]];\
    }\
}\
static inline void T##Vector_slice_(struct T##Vector* this, struct T##Vector src, Int start, Int step, Int stop){\
    Int i, n;\
    if(stop == VECTOR_INDEX_END) stop = src.len - 1;\
    if(step == 0) error_invalid_argument("(Vector_slice_) step is 0");\
    if(start < 0) error_invalid_argument("(Vector_slice_) start < 0");\
    if(start >= src.len) error_invalid_argument("(Vector_slice_) start >= this->len");\
    if(stop < 0) error_invalid_argument("(Vector_slice_) stop < 0");\
    if(stop >= src.len) error_invalid_argument("(IntVector_slice_) stop >= src.len");\
    n = _bm_abs_int(stop - start) / _bm_abs_int(step) + 1;\
    T##Vector_alloc_(this, n);\
    for(i = 0; i < n; i++) this->data[i] = src.data[start + i * step];\
}\
static inline Int T##Vector_count(const struct T##Vector* this){\
    Int i = 0, n = 0;\
    if(this->len <= 0) return 0;\
    for(; i < this->len; i++) if(this->data[i]) n += 1;\
    return n;\
}\
static inline void T##Vector_index_flag_(struct T##Vector* this, struct T##Vector src, struct IntVector flags){\
    Int i, n;\
    if(src.len != flags.len) error_invalid_argument("(Vector_index_flag_) src.len != flags.len");\
    if(src.len <= 0) {\
        T##Vector_free_(this);\
        return;\
    }\
    n = IntVector_count(&flags);\
    T##Vector_alloc_(this, n);\
    n = 0;\
    for(i = 0; i < src.len; i++)\
        if(flags.data[i]) {\
            this->data[n] = src.data[i];\
            n += 1;\
        }\
}\
static inline void T##Vector_set_(struct T##Vector* this, Int index, T value){\
    if(this->len <= 0) return;\
    if(index < 0 || index >= this->len) error_index_out_of_bounds("(Vector_set_) index out of bounds");\
    this->data[index] = value;\
}\
static inline void T##Vector_setas_(struct T##Vector* this, Int n, ...){\
    va_list ap;\
    Int i;\
    va_start(ap, n);\
    T##Vector_alloc_(this, n);\
    for(i=0; i < n; i++) this->data[i] = va_arg(ap, _VECTOR_N_VA_ARG_TYPE_##T);\
    va_end(ap);\
}\
static inline void T##Vector_vcat_(struct T##Vector* this, Int n, ...){\
    Int i, j, row;\
    va_list ap;\
    struct T##Vector *pvec = NULL;\
    va_start(ap, n);\
    pvec = (struct T##Vector *)malloc(n*sizeof(struct T##Vector));\
    row = 0;\
    for(i=0; i < n; i++){\
        pvec[i] = va_arg(ap, struct T##Vector);\
        row += pvec[i].len;\
    }\
    T##Vector_alloc_(this, row);\
    row = 0;\
    for(i=0; i < n; i++){\
        for(j=0; j < pvec[i].len; j++){\
            this->data[row] = pvec[i].data[j];\
            row += 1;\
        }\
    }\
    va_end(ap);\
}\
static inline void T##Vector_rand_(struct T##Vector* this, T min, T max){\
    Int i;\
    if(this->len <= 0) return;\
    if(max <= min) error_invalid_argument("(Vector_rand_) min >= max");\
    unsigned long long* pf = NULL;\
    pf = (unsigned long long*)malloc(this->len * sizeof(unsigned long long));\
    _bm_rand_ull_(pf, this->len);\
    for(i = 0; i < this->len; i++) this->data[i] = _bm_convert_ull_to_##T(pf[i], min, max);\
    free(pf);\
}\
static inline void T##Vector_rand_from_(struct T##Vector* this, struct T##Vector value_set){\
    Int i;\
    CBL_DECLARE_VARS(IntVector, 1, idxs);\
    if(value_set.len <= 0) return;\
    if(this->len <= 0) return;\
    IntVector_alloc_(&idxs, this->len);\
    IntVector_rand_(&idxs, 0, value_set.len - 1);\
    for(i = 0; i < this->len; i++) this->data[i] = value_set.data[idxs.data[i]];\
    IntVector_free_(&idxs);\
}\
static inline void T##Vector_fill_(struct T##Vector* this, T value){\
    Int i;\
    if(this->len <= 0) return;\
    for(i = 0; i < this->len; i++) this->data[i] = value;\
}\
static inline void T##Vector_range_(struct T##Vector* this, T start, T step, T stop){\
    Int i;\
    if(this->len <= 0) return;\
    if(this->len == 1) {\
        this->data[0] = start;\
        return;\
    }\
    if(step == 0)\
        if(start != stop) step = (stop - start) / (this->len-1);\
    for(i = 0; i < this->len; i++) this->data[i] = start + i * step;\
}\
static inline void T##Vector_copy_from_(struct T##Vector* this, struct T##Vector src){\
    if(src.len <= 0) {\
        T##Vector_free_(this);\
        return;\
    }\
    if(src.len != this->len) T##Vector_alloc_(this, src.len);\
    memcpy(this->data, src.data, src.len * sizeof(T));\
}\
static inline void T##Vector_find_trues_(struct T##Vector* this, struct T##Vector flags){\
    Int i, n;\
    if(flags.len <= 0) {\
        T##Vector_free_(this);\
        return;\
    }\
    n = T##Vector_count(&flags);\
    if(n != this->len) T##Vector_alloc_(this, n);\
    n = 0;\
    for(i = 0; i < flags.len; i++)\
        if(flags.data[i]) {\
            this->data[n] = i;\
            n += 1;\
        }\
}\
static inline T T##Vector_sum(const struct T##Vector* this){\
    Int i;\
    T sum = 0;\
    if(this->len <= 0) return sum;\
    for(i = 0; i < this->len; i++) sum += this->data[i];\
    return sum;\
}\
static inline T T##Vector_prod(const struct T##Vector* this){\
    Int i = 0;\
    T prod = 1;\
    if(this->len <= 0) return 0;\
    for(i = 0; i < this->len; i++) prod *= this->data[i];\
    return prod;\
}\
static inline T T##Vector_min(const struct T##Vector* this){\
    Int i;\
    T min = _VECTOR_N_VA_ARG_MAX_##T;\
    if(this->len <= 0) return min;\
    for(i=0; i<this->len; i++) min = (this->data[i] < min) ? this->data[i] : min;\
    return min;\
}\
static inline T T##Vector_max(const struct T##Vector* this){\
    Int i;\
    T max = _VECTOR_N_VA_ARG_MIN_##T;\
    if(this->len <= 0) return max;\
    for(i=0; i<this->len; i++) max = (max < this->data[i]) ? this->data[i] : max;\
    return max;\
}\
static inline Int  T##Vector_argmin(const struct T##Vector* this){\
    Int i, mini = -1;\
    T minv = _VECTOR_N_VA_ARG_MAX_##T;\
    if(this->len <= 0) return -1;\
    for(i = 0; i < this->len; i++)\
        if(this->data[i] < minv) {\
            minv = this->data[i];\
            mini = i;\
        }\
    return mini;\
}\
static inline Int  T##Vector_argmax(const struct T##Vector* this){\
    Int i, maxi;\
    T maxv = _VECTOR_N_VA_ARG_MIN_##T;\
    maxi = -1;\
    if(this->len <= 0) return -1;\
    for(i=0; i < this->len; i++)\
        if(this->data[i] > maxv) {\
            maxv = this->data[i];\
            maxi = i;\
        }\
    return maxi;\
}\
static inline void T##Vector_cumsum_(struct T##Vector* this, T initial){\
    Int i;\
    T sum = initial;\
    for(i=0; i < this->len; i++){\
        sum += this->data[i];\
        this->data[i] = sum;\
    }\
}\
static inline void T##Vector_cumprod_(struct T##Vector* this, T initial){\
    Int i;\
    T prod = initial;\
    for(i=0; i < this->len; i++){\
        prod *= this->data[i];\
        this->data[i] = prod;\
    }\
}\
static inline void T##Vector_sort_(struct T##Vector* this){\
    Int i, j;\
    T   tv;\
    for(i = 0; i < this->len; i++)\
        for(j = i + 1; j < this->len; j++)\
            if(this->data[i] > this->data[j]){\
                tv = this->data[i];\
                this->data[i] = this->data[j];\
                this->data[j] = tv;\
            }\
}\
static inline void T##Vector_sortperm_(struct T##Vector* this, struct IntVector* perm){\
    Int i, j, ti;\
    T   tv;\
    if(this->len <= 0) return;\
    IntVector_alloc_(perm, this->len);\
    IntVector_range_(perm, 0, 1, this->len-1);\
    for(i = 0; i < this->len; i++)\
        for(j = i + 1; j < this->len; j++)\
            if(this->data[i] > this->data[j]){\
                tv = this->data[i];\
                this->data[i] = this->data[j];\
                this->data[j] = tv;\
                ti = perm->data[i];\
                perm->data[i] = perm->data[j];\
                perm->data[j] = ti;\
            }\
}\
static inline T T##Vector_dot(const struct T##Vector* this, struct T##Vector b){\
    Int i;\
    T sum = 0;\
    if(this->len != b.len) error_invalid_argument("(Vector_dot) length mismatch");\
    for(i=0; i < this->len; i++) sum += this->data[i]*b.data[i];\
    return sum;\
}

#define _Vector_internal_methods_address(T)\
    &T##Vector_free_,\
    &T##Vector_alloc_,\
    &T##Vector_get,\
    &T##Vector_index_,\
    &T##Vector_slice_,\
    &T##Vector_count,\
    &T##Vector_index_flag_,\
    &T##Vector_set_,\
    &T##Vector_setas_,\
    &T##Vector_vcat_,\
    &T##Vector_rand_,\
    &T##Vector_rand_from_,\
    &T##Vector_fill_,\
    &T##Vector_range_,\
    &T##Vector_copy_from_,\
    &T##Vector_find_trues_,\
    &T##Vector_sum,\
    &T##Vector_prod,\
    &T##Vector_min,\
    &T##Vector_max,\
    &T##Vector_argmin,\
    &T##Vector_argmax,\
    &T##Vector_cumsum_,\
    &T##Vector_cumprod_,\
    &T##Vector_sort_,\
    &T##Vector_sortperm_,\
    &T##Vector_dot


#define _Vector_inner(T) \
_Vector_type_struct(T)\
struct T##VectorMethods{\
    _Vector_internal_methods_declaration(T)\
    _CBL_MACRO_SECOND_TO_END _CBL_MACRO_EMPTY() (T##Vector_external_methods_declaration)\
};\
_Vector_internal_methods_defination(T)\
_CBL_MACRO_SECOND_TO_END _CBL_MACRO_EMPTY() (T##Vector_external_methods_defination)\
struct T##VectorMethods static _CBL_##T##_VECTOR_METHODS={\
    _Vector_internal_methods_address(T)\
    _CBL_MACRO_SECOND_TO_END _CBL_MACRO_EMPTY() (T##Vector_external_methods_address)\
};\
static inline void T##Vector_new_(struct T##Vector *this){\
    this->len = 0;\
    this->data = NULL;\
    this->methods = &_CBL_##T##_VECTOR_METHODS;\
}

#define Vector(T) _CBL_MACRO_EXPAND(_Vector_inner(T))

// Vector(Int)
// Vector(Float)

#endif // _TEMPLATE_VECTOR_H_
