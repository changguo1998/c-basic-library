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

#ifndef _TEMPLATE_VECTORN_H_
#define _TEMPLATE_VECTORN_H_

#include <stdarg.h>
#include <string.h>
#include "Module_Basic.h"
#include "Type_Part_math_basic.h"
// #include "Type_IntVector.h"


#define _VectorN_type_struct(T, N) struct T##Vector##N{\
    T data[N];\
    struct T##Vector##N##Methods* methods;\
};

#define _VectorN_internal_methods_declaration(T, N)\
    T    (*get)(   const struct T##Vector##N *this, Int i);\
    void (*set_)(        struct T##Vector##N *this, Int i, T value);\
    void (*set_all_)(    struct T##Vector##N *this, ...);\
    void (*rand_)(       struct T##Vector##N *this, T min, T max);\
    void (*fill_)(       struct T##Vector##N *this, T value);\
    void (*range_)(      struct T##Vector##N *this, T start, T step);\
    Int  (*count)( const struct T##Vector##N *this);\
    T    (*sum)(   const struct T##Vector##N *this);\
    T    (*prod)(  const struct T##Vector##N *this);\
    T    (*min)(   const struct T##Vector##N *this);\
    T    (*max)(   const struct T##Vector##N *this);\
    Int  (*argmin)(const struct T##Vector##N *this);\
    Int  (*argmax)(const struct T##Vector##N *this);\
    void (*cumsum_)(     struct T##Vector##N *this, T initial);\
    void (*cumprod_)(    struct T##Vector##N *this, T initial);\
    void (*sort_)(       struct T##Vector##N *this);\
    struct IntVector##N\
         (*sortperm_)(   struct T##Vector##N *this);\
    T    (*dot)(   const struct T##Vector##N *this, struct T##Vector##N b);

#define _VectorN_internal_methods_defination(T, N)\
static inline void T##Vector##N##_new_(struct T##Vector##N *this);\
static inline T T##Vector##N##_get(const struct T##Vector##N *this, Int i){\
    if(i<0||i>=N) error_index_out_of_bounds("(VectorN) index out of bounds");\
    return this->data[i];\
}\
static inline void T##Vector##N##_set_(struct T##Vector##N *this, Int i, T value){\
    if(i<0||i>=N) error_index_out_of_bounds("(VectorN) index out of bounds");\
    this->data[i] = value;\
}\
static inline void T##Vector##N##_set_all_(struct T##Vector##N *this, ...){\
    va_list ap;\
    Int i;\
    va_start(ap, this);\
    for(i=0; i<N; i++) this->data[i] = va_arg(ap, _VECTOR_N_VA_ARG_TYPE_##T);\
    va_end(ap);\
}\
static void T##Vector##N##_rand_(struct T##Vector##N *this, T min, T max){\
    Int i;\
    if(max <= min) return;\
    unsigned long long* pf = NULL;\
    pf = (unsigned long long*)malloc(N * sizeof(unsigned long long));\
    _bm_rand_ull_(pf, N);\
    for(i = 0; i < N; i++) this->data[i] = _bm_convert_ull_to_##T(pf[i], min, max);\
    free(pf);\
}\
static inline void T##Vector##N##_fill_(struct T##Vector##N *this, T value){\
    Int i;\
    for(i=0; i<N; i++) this->data[i] = value;\
}\
static inline void T##Vector##N##_range_(struct T##Vector##N *this, T start, T step){\
    Int i;\
    for(i=0; i<N; i++) this->data[i] = start + i * step;\
}\
static inline Int T##Vector##N##_count(const struct T##Vector##N *this){\
    Int i, c;\
    c = 0;\
    for(i=0; i<N; i++) if(this->data[i]) c += 1;\
    return c;\
}\
static inline T T##Vector##N##_sum(const struct T##Vector##N *this){\
    Int i;\
    T c = 0;\
    for(i=0; i<N; i++) c += this->data[i];\
    return c;\
}\
static inline T T##Vector##N##_prod(const struct T##Vector##N *this){\
    Int i;\
    T c = 1;\
    for(i=0; i<N; i++) c *= this->data[i];\
    return c;\
}\
static inline T T##Vector##N##_min(const struct T##Vector##N *this){\
    Int i;\
    T min = _VECTOR_N_VA_ARG_MAX_##T;\
    for(i=0; i<N; i++) if(this->data[i] < min) min = this->data[i];\
    return min;\
}\
static inline T T##Vector##N##_max(const struct T##Vector##N *this){\
    Int i;\
    T max = _VECTOR_N_VA_ARG_MIN_##T;\
    for(i=0; i<N; i++) if(this->data[i] > max) max = this->data[i];\
    return max;\
}\
static inline Int T##Vector##N##_argmin(const struct T##Vector##N *this){\
    Int i, mini;\
    T minv = _VECTOR_N_VA_ARG_MAX_##T;\
    mini = -1;\
    for(i=0; i<N; i++) if(this->data[i] < minv) {\
        minv = this->data[i];\
        mini = i;\
    }\
    return mini;\
}\
static inline Int T##Vector##N##_argmax(const struct T##Vector##N *this){\
    Int i, maxi;\
    T maxv = _VECTOR_N_VA_ARG_MIN_##T;\
    maxi = -1;\
    for(i=0; i<N; i++) if(this->data[i] > maxv) {\
        maxv = this->data[i];\
        maxi = i;\
    }\
    return maxi;\
}\
static inline void T##Vector##N##_cumsum_(struct T##Vector##N *this, T initial){\
    Int i;\
    T sum = initial;\
    for(i=0; i<N; i++){\
        sum += this->data[i];\
        this->data[i] = sum;\
    }\
}\
static inline void T##Vector##N##_cumprod_(struct T##Vector##N *this, T initial){\
    Int i;\
    T prod = initial;\
    for(i=0; i<N; i++){\
        prod *= this->data[i];\
        this->data[i] = prod;\
    }\
}\
static void T##Vector##N##_sort_(struct T##Vector##N *this){\
    Int i, j;\
    T   tv;\
    for(i = 0; i < N; i++)\
        for(j = i + 1; j < N; j++)\
            if(this->data[i]>this->data[j]){\
                tv = this->data[i];\
                this->data[i] = this->data[j];\
                this->data[j] = tv;\
            }\
}\
static struct IntVector##N T##Vector##N##_sortperm_(struct T##Vector##N *this){\
    Int i, j, ti;\
    T   tv;\
    CBL_DECLARE_VARS(IntVector##N, 1, perm);\
    CBL_CALL(perm, range_, 0, 1);\
    for(i = 0; i < N; i++)\
        for(j = i + 1; j < N; j++)\
            if(this->data[i]>this->data[j]){\
                tv = this->data[i];\
                this->data[i] = this->data[j];\
                this->data[j] = tv;\
                ti = perm.data[i];\
                perm.data[i] = perm.data[j];\
                perm.data[j] = ti;\
            }\
    return perm;\
}\
static inline T T##Vector##N##_dot(const struct T##Vector##N *this, struct T##Vector##N b){\
    Int i;\
    T sum = 0;\
    for(i=0; i < N; i++) sum += this->data[i] * b.data[i];\
    return sum;\
}

#define _VectorN_internal_methods_address(T, N)\
    &T##Vector##N##_get,\
    &T##Vector##N##_set_,\
    &T##Vector##N##_set_all_,\
    &T##Vector##N##_rand_,\
    &T##Vector##N##_fill_,\
    &T##Vector##N##_range_,\
    &T##Vector##N##_count,\
    &T##Vector##N##_sum,\
    &T##Vector##N##_prod,\
    &T##Vector##N##_min,\
    &T##Vector##N##_max,\
    &T##Vector##N##_argmin,\
    &T##Vector##N##_argmax,\
    &T##Vector##N##_cumsum_,\
    &T##Vector##N##_cumprod_,\
    &T##Vector##N##_sort_,\
    &T##Vector##N##_sortperm_,\
    &T##Vector##N##_dot


#define _VectorN_inner(T, N) \
    _VectorN_type_struct(T, N)\
struct T##Vector##N##Methods{\
    _VectorN_internal_methods_declaration(T, N)\
    _CBL_MACRO_SECOND_TO_END _CBL_MACRO_EMPTY() (T##Vector##N##_external_methods_declaration)\
};\
_VectorN_internal_methods_defination(T, N)\
_CBL_MACRO_SECOND_TO_END _CBL_MACRO_EMPTY() (T##Vector##N##_external_methods_defination)\
struct T##Vector##N##Methods static _CBL_##T##_VECTOR_##N##_METHODS={\
    _VectorN_internal_methods_address(T, N)\
    _CBL_MACRO_SECOND_TO_END _CBL_MACRO_EMPTY() (T##Vector##N##_external_methods_address)\
};\
static inline void T##Vector##N##_new_(struct T##Vector##N *this){\
    this->methods = &_CBL_##T##_VECTOR_##N##_METHODS;\
}

#define VectorN(T, N) _CBL_MACRO_EXPAND(_VectorN_inner(T, N))

// VectorN(Int, 3)
// VectorN(Float, 3)

#endif // _TEMPLATE_VECTORN_H_
