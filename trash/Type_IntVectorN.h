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

#ifndef _TYPE_INTVECTORN_H_
#define _TYPE_INTVECTORN_H_

#include <stdarg.h>
#include <string.h>
#include "Module_Basic.h"
#include "Type_IntVector.h"

#define _IntVectorN_type_struct(n) static struct IntVector##n{\
    Int data[n];\
    struct IntVector##n##Methods* methods;\
};

#define _IntVectorN_internal_methods_declaration(n)\
     Int (*get)(const struct IntVector##n *this, Int i);\
    void (*set_)(struct IntVector##n *this, Int i, Int value);\
    void (*set_all_)(struct IntVector##n *this, ...);\
    void (*rand_)(struct IntVector##n *this, Int min, Int max);\
    void (*fill_)(struct IntVector##n *this, Int value);\
    void (*range_)(struct IntVector##n *this, Int start, Int step);\
     Int (*count)(const struct IntVector##n *this);\
     Int (*sum)(const struct IntVector##n *this);\
     Int (*prod)(const struct IntVector##n *this);\
     Int (*min)(const struct IntVector##n *this);\
     Int (*max)(const struct IntVector##n *this);\
     Int (*argmin)(const struct IntVector##n *this);\
     Int (*argmax)(const struct IntVector##n *this);\
    void (*cumsum_)(struct IntVector##n *this, Int initial);\
    void (*cumprod_)(struct IntVector##n *this, Int initial);\
    void (*sort_)(struct IntVector##n *this);\
    struct IntVector##n (*sortperm_)(struct IntVector##n *this);\

#define _IntVectorN_internal_methods_defination(n)\
static inline void IntVector##n##_new_(struct IntVector##n *this);\
static inline Int IntVector##n##_get(const struct IntVector##n *this, Int i){\
    if(i<0||i>=n) error_index_out_of_bounds("(IntVectorN) index out of bounds");\
    return this->data[i];\
}\
static inline void IntVector##n##_set_(struct IntVector##n *this, Int i, Int value){\
    if(i<0||i>=n) error_index_out_of_bounds("(IntVectorN) index out of bounds");\
    this->data[i] = value;\
}\
static inline void IntVector##n##_set_all_(struct IntVector##n *this, ...){\
    va_list ap;\
    Int i;\
    va_start(ap, this);\
    for(i=0; i<n; i++) this->data[i] = va_arg(ap, Int);\
    va_end(ap);\
}\
static void IntVector##n##_rand_(struct IntVector##n *this, Int min, Int max){\
    struct IntVector buf;\
    IntVector_new_(&buf);\
    IntVector_alloc_(&buf, n);\
    IntVector_rand_(&buf, min, max);\
    memcpy(this->data, buf.data, n * sizeof(Int));\
    IntVector_free_(&buf);\
}\
static inline void IntVector##n##_fill_(struct IntVector##n *this, Int value){\
    Int i;\
    for(i=0; i<n; i++) this->data[i] = value;\
}\
static inline void IntVector##n##_range_(struct IntVector##n *this, Int start, Int step){\
    Int i;\
    for(i=0; i<n; i++) this->data[i] = start + i * step;\
}\
static inline Int IntVector##n##_count(const struct IntVector##n *this){\
    Int i, c;\
    c = 0;\
    for(i=0; i<n; i++) if(this->data[i]) c += 1;\
    return c;\
}\
static inline Int IntVector##n##_sum(const struct IntVector##n *this){\
    Int i, c;\
    c = 0;\
    for(i=0; i<n; i++) c += this->data[i];\
    return c;\
}\
static inline Int IntVector##n##_prod(const struct IntVector##n *this){\
    Int i, c;\
    c = 1;\
    for(i=0; i<n; i++) c *= this->data[i];\
    return c;\
}\
static inline Int IntVector##n##_min(const struct IntVector##n *this){\
    Int i, min;\
    min = CBL_INT_MAX;\
    for(i=0; i<n; i++) if(this->data[i] < min) min = this->data[i];\
    return min;\
}\
static inline Int IntVector##n##_max(const struct IntVector##n *this){\
    Int i, max;\
    max = CBL_INT_MIN;\
    for(i=0; i<n; i++) if(this->data[i] > max) max = this->data[i];\
    return max;\
}\
static inline Int IntVector##n##_argmin(const struct IntVector##n *this){\
    Int i, minv, mini;\
    minv = CBL_INT_MAX;\
    mini = -1;\
    for(i=0; i<n; i++) if(this->data[i] < minv) {\
        minv = this->data[i];\
        mini = i;\
    }\
    return mini;\
}\
static inline Int IntVector##n##_argmax(const struct IntVector##n *this){\
    Int i, maxv, maxi;\
    maxv = CBL_INT_MIN;\
    maxi = -1;\
    for(i=0; i<n; i++) if(this->data[i] > maxv) {\
        maxv = this->data[i];\
        maxi = i;\
    }\
    return maxi;\
}\
static inline void IntVector##n##_cumsum_(struct IntVector##n *this, Int initial){\
    Int i, sum;\
    sum = initial;\
    for(i=0; i<n; i++){\
        sum += this->data[i];\
        this->data[i] = sum;\
    }\
}\
static inline void IntVector##n##_cumprod_(struct IntVector##n *this, Int initial){\
    Int i, prod;\
    prod = initial;\
    for(i=0; i<n; i++){\
        prod *= this->data[i];\
        this->data[i] = prod;\
    }\
}\
static void IntVector##n##_sort_(struct IntVector##n *this){\
    Int i,j,t;\
    for(i = 0; i < n; i++)\
        for(j = i + 1; j < n; j++)\
            if(this->data[i]>this->data[j]){\
                t = this->data[i];\
                this->data[i] = this->data[j];\
                this->data[j] = t;\
            }\
}\
static struct IntVector##n IntVector##n##_sortperm_(struct IntVector##n *this){\
    struct IntVector buf, perm;\
    struct IntVector##n permN;\
    IntVector_new_(&buf);\
    IntVector_new_(&perm);\
    IntVector##n##_new_(&permN);\
    IntVector_alloc_(&buf, n);\
    IntVector_alloc_(&perm, n);\
    memcpy(buf.data, this->data, n*sizeof(Int));\
    IntVector_sortperm_(&buf, &perm);\
    memcpy(this->data, buf.data, n*sizeof(Int));\
    memcpy(permN.data, perm.data, n*sizeof(Int));\
    IntVector_free_(&buf);\
    IntVector_free_(&perm);\
    return permN;\
}

#define _IntVectorN_internal_methods_address(n) &IntVector##n##_get,\
    &IntVector##n##_set_,\
    &IntVector##n##_set_all_,\
    &IntVector##n##_rand_,\
    &IntVector##n##_fill_,\
    &IntVector##n##_range_,\
    &IntVector##n##_count,\
    &IntVector##n##_sum,\
    &IntVector##n##_prod,\
    &IntVector##n##_min,\
    &IntVector##n##_max,\
    &IntVector##n##_argmin,\
    &IntVector##n##_argmax,\
    &IntVector##n##_cumsum_,\
    &IntVector##n##_cumprod_,\
    &IntVector##n##_sort_,\
    &IntVector##n##_sortperm_


#define _IntVectorN_inner(n) \
    _IntVectorN_type_struct(n)\
static struct IntVector##n##Methods{\
    _IntVectorN_internal_methods_declaration(n)\
    _CBL_MACRO_SECOND_TO_END _CBL_MACRO_EMPTY() (IntVector##n##_external_methods_declaration)\
};\
_IntVectorN_internal_methods_defination(n)\
_CBL_MACRO_SECOND_TO_END _CBL_MACRO_EMPTY() (IntVector##n##_external_methods_defination)\
static struct IntVector##n##Methods _CBL_INT_VECTOR_##n##_METHODS={\
    _IntVectorN_internal_methods_address(n)\
_CBL_MACRO_SECOND_TO_END _CBL_MACRO_EMPTY() (IntVector##n##_external_methods_address)\
};\
static inline void IntVector##n##_new_(struct IntVector##n *this){\
    this->methods = &_CBL_INT_VECTOR_##n##_METHODS;\
}

#define IntVectorN(N) _CBL_MACRO_EXPAND(_IntVectorN_inner(N))


#endif // _TYPE_INTVECTORN_H_
