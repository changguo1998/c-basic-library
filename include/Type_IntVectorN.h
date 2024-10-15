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

#define _IntVectorN_inner(n) struct IntVector_##n{\
    Int data[n];\
    struct IntVector_##n##_methods* methods;\
};\
struct IntVector_##n##_methods{\
     Int (*get)(const struct IntVector_##n *this, Int i);\
    void (*set_)(struct IntVector_##n *this, Int i, Int value);\
    void (*set_all_)(struct IntVector_##n *this, ...);\
    void (*rand_)(struct IntVector_##n *this, Int min, Int max);\
    void (*fill_)(struct IntVector_##n *this, Int value);\
    void (*range_)(struct IntVector_##n *this, Int start, Int step);\
     Int (*count)(const struct IntVector_##n *this);\
     Int (*sum)(const struct IntVector_##n *this);\
     Int (*prod)(const struct IntVector_##n *this);\
     Int (*min)(const struct IntVector_##n *this);\
     Int (*max)(const struct IntVector_##n *this);\
     Int (*argmin)(const struct IntVector_##n *this);\
     Int (*argmax)(const struct IntVector_##n *this);\
    void (*cumsum_)(struct IntVector_##n *this, Int initial);\
    void (*cumprod_)(struct IntVector_##n *this, Int initial);\
    void (*sort_)(struct IntVector_##n *this);\
    struct IntVector_##n (*sortperm_)(struct IntVector_##n *this);\
};\
static inline void IntVector_##n##_new_(struct IntVector_##n *this);\
static inline Int IntVector_##n##_get(const struct IntVector_##n *this, Int i){\
    if(i<0||i>=n) error_index_out_of_bounds("(IntVectorN) index out of bounds");\
    return this->data[i];\
}\
static inline void IntVector_##n##_set_(struct IntVector_##n *this, Int i, Int value){\
    if(i<0||i>=n) error_index_out_of_bounds("(IntVectorN) index out of bounds");\
    this->data[i] = value;\
}\
static inline void IntVector_##n##_set_all_(struct IntVector_##n *this, ...){\
    va_list ap;\
    Int i;\
    va_start(ap, this);\
    for(i=0; i<n; i++) this->data[i] = va_arg(ap, Int);\
    va_end(ap);\
}\
static void IntVector_##n##_rand_(struct IntVector_##n *this, Int min, Int max){\
    struct IntVector buf;\
    IntVector_new_(&buf);\
    IntVector_alloc_(&buf, n);\
    IntVector_rand_(&buf, min, max);\
    memcpy(this->data, buf.data, n * sizeof(Int));\
    IntVector_free_(&buf);\
}\
static inline void IntVector_##n##_fill_(struct IntVector_##n *this, Int value){\
    Int i;\
    for(i=0; i<n; i++) this->data[i] = value;\
}\
static inline void IntVector_##n##_range_(struct IntVector_##n *this, Int start, Int step){\
    Int i;\
    for(i=0; i<n; i++) this->data[i] = start + i * step;\
}\
static inline Int IntVector_##n##_count(const struct IntVector_##n *this){\
    Int i, c;\
    c = 0;\
    for(i=0; i<n; i++) if(this->data[i]) c += 1;\
    return c;\
}\
static inline Int IntVector_##n##_sum(const struct IntVector_##n *this){\
    Int i, c;\
    c = 0;\
    for(i=0; i<n; i++) c += this->data[i];\
    return c;\
}\
static inline Int IntVector_##n##_prod(const struct IntVector_##n *this){\
    Int i, c;\
    c = 1;\
    for(i=0; i<n; i++) c *= this->data[i];\
    return c;\
}\
static inline Int IntVector_##n##_min(const struct IntVector_##n *this){\
    Int i, min;\
    min = CBL_INT_MAX;\
    for(i=0; i<n; i++) if(this->data[i] < min) min = this->data[i];\
    return min;\
}\
static inline Int IntVector_##n##_max(const struct IntVector_##n *this){\
    Int i, max;\
    max = CBL_INT_MIN;\
    for(i=0; i<n; i++) if(this->data[i] > max) max = this->data[i];\
    return max;\
}\
static inline Int IntVector_##n##_argmin(const struct IntVector_##n *this){\
    Int i, minv, mini;\
    minv = CBL_INT_MAX;\
    mini = -1;\
    for(i=0; i<n; i++) if(this->data[i] < minv) {\
        minv = this->data[i];\
        mini = i;\
    }\
    return mini;\
}\
static inline Int IntVector_##n##_argmax(const struct IntVector_##n *this){\
    Int i, maxv, maxi;\
    maxv = CBL_INT_MIN;\
    maxi = -1;\
    for(i=0; i<n; i++) if(this->data[i] > maxv) {\
        maxv = this->data[i];\
        maxi = i;\
    }\
    return maxi;\
}\
static inline void IntVector_##n##_cumsum_(struct IntVector_##n *this, Int initial){\
    Int i, sum;\
    sum = initial;\
    for(i=0; i<n; i++){\
        sum += this->data[i];\
        this->data[i] = sum;\
    }\
}\
static inline void IntVector_##n##_cumprod_(struct IntVector_##n *this, Int initial){\
    Int i, prod;\
    prod = initial;\
    for(i=0; i<n; i++){\
        prod *= this->data[i];\
        this->data[i] = prod;\
    }\
}\
static void IntVector_##n##_sort_(struct IntVector_##n *this){\
    struct IntVector buf;\
    IntVector_new_(&buf);\
    IntVector_alloc_(&buf, n);\
    memcpy(buf.data, this->data, n * sizeof(Int));\
    IntVector_sort_(&buf);\
    memcpy(this->data, buf.data, n * sizeof(Int));\
    IntVector_free_(&buf);\
}\
static struct IntVector_##n IntVector_##n##_sortperm_(struct IntVector_##n *this){\
    struct IntVector buf, perm;\
    struct IntVector_##n permN;\
    IntVector_new_(&buf);\
    IntVector_new_(&perm);\
    IntVector_##n##_new_(&permN);\
    IntVector_alloc_(&buf, n);\
    IntVector_alloc_(&perm, n);\
    memcpy(buf.data, this->data, n*sizeof(Int));\
    IntVector_sortperm_(&buf, &perm);\
    memcpy(this->data, buf.data, n*sizeof(Int));\
    memcpy(permN.data, perm.data, n*sizeof(Int));\
    IntVector_free_(&buf);\
    IntVector_free_(&perm);\
    return permN;\
}\
static struct IntVector_##n##_methods _CBL_INT_VECTOR_##n##_METHODS={\
    &IntVector_##n##_get,\
    &IntVector_##n##_set_,\
    &IntVector_##n##_set_all_,\
    &IntVector_##n##_rand_,\
    &IntVector_##n##_fill_,\
    &IntVector_##n##_range_,\
    &IntVector_##n##_count,\
    &IntVector_##n##_sum,\
    &IntVector_##n##_prod,\
    &IntVector_##n##_min,\
    &IntVector_##n##_max,\
    &IntVector_##n##_argmin,\
    &IntVector_##n##_argmax,\
    &IntVector_##n##_cumsum_,\
    &IntVector_##n##_cumprod_,\
    &IntVector_##n##_sort_,\
    &IntVector_##n##_sortperm_\
};\
static inline void IntVector_##n##_new_(struct IntVector_##n *this){\
    this->methods = &_CBL_INT_VECTOR_##n##_METHODS;\
}

#define IntVectorN(N) _IntVectorN_inner(N)

// IntVectorN(3)

#endif // _TYPE_INTVECTORN_H_
