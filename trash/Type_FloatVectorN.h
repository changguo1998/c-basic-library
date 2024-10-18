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

#ifndef _TYPE_FLOATVECTORN_H_
#define _TYPE_FLOATVECTORN_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include "Module_Basic.h"
#include "Type_IntVectorN.h"
#include "Type_FloatVector.h"

#define _FloatVectorN_inner(n)\
IntVectorN(n)\
static struct FloatVector##n{\
    Float data[n];\
    struct FloatVector##n##_methods* methods;\
};\
static struct FloatVector##n##_methods{\
     Float (*get)(const struct FloatVector##n *this, Int i);\
    void (*set_)(struct FloatVector##n *this, Int i, Float value);\
    void (*set_all_)(struct FloatVector##n *this, ...);\
    void (*rand_)(struct FloatVector##n *this, Float min, Float max);\
    void (*fill_)(struct FloatVector##n *this, Float value);\
    void (*range_)(struct FloatVector##n *this, Float start, Float stop);\
    Float (*sum)(const struct FloatVector##n *this);\
    Float (*prod)(const struct FloatVector##n *this);\
    Float (*min)(const struct FloatVector##n *this);\
    Float (*max)(const struct FloatVector##n *this);\
     Int (*argmin)(const struct FloatVector##n *this);\
     Int (*argmax)(const struct FloatVector##n *this);\
    void (*cumsum_)(struct FloatVector##n *this, Float initial);\
    void (*cumprod_)(struct FloatVector##n *this, Float initial);\
    void (*sort_)(struct FloatVector##n *this);\
    struct IntVector_##n (*sortperm_)(struct FloatVector##n *this);\
};\
static inline void FloatVector##n##_new_(struct FloatVector##n *this);\
static inline Float FloatVector##n##_get(const struct FloatVector##n *this, Int i){\
    if(i<0||i>=n) error_index_out_of_bounds("(FloatVectorN) index out of bounds");\
    return this->data[i];\
}\
static inline void FloatVector##n##_set_(struct FloatVector##n *this, Int i, Float value){\
    if(i<0||i>=n) error_index_out_of_bounds("(FloatVectorN) index out of bounds");\
    this->data[i] = value;\
}\
static inline void FloatVector##n##_set_all_(struct FloatVector##n *this, ...){\
    va_list ap;\
    Int i;\
    va_start(ap, this);\
    for(i=0; i<n; i++) this->data[i] = (Float)va_arg(ap, double);\
    va_end(ap);\
}\
static void FloatVector##n##_rand_(struct FloatVector##n *this, Float min, Float max){\
    struct FloatVector buf;\
    FloatVector_new_(&buf);\
    FloatVector_alloc_(&buf, n);\
    FloatVector_rand_(&buf, min, max);\
    memcpy(this->data, buf.data, n * sizeof(Float));\
    FloatVector_free_(&buf);\
}\
static inline void FloatVector##n##_fill_(struct FloatVector##n *this, Float value){\
    Int i;\
    for(i=0; i<n; i++) this->data[i] = value;\
}\
static inline void FloatVector##n##_range_(struct FloatVector##n *this, Float start, Float stop){\
    Int i;\
    Float step;\
    if(n==1) this->data[0] = start;\
    step = (stop-start)/(n-1);\
    for(i=0; i<n; i++) this->data[i] = start + i * step;\
}\
static inline Float FloatVector##n##_sum(const struct FloatVector##n *this){\
    Int i;\
    Float c=0.0;\
    for(i=0; i<n; i++) c += this->data[i];\
    return c;\
}\
static inline Float FloatVector##n##_prod(const struct FloatVector##n *this){\
    Int i;\
    Float c = 1.0;\
    for(i=0; i<n; i++) c *= this->data[i];\
    return c;\
}\
static inline Float FloatVector##n##_min(const struct FloatVector##n *this){\
    Int i;\
    Float min=CBL_FLOAT_MAX;\
    for(i=0; i<n; i++) if(this->data[i] < min) min = this->data[i];\
    return min;\
}\
static inline Float FloatVector##n##_max(const struct FloatVector##n *this){\
    Int i;\
    Float max = CBL_FLOAT_MIN;\
    for(i=0; i<n; i++) if(this->data[i] > max) max = this->data[i];\
    return max;\
}\
static inline Int FloatVector##n##_argmin(const struct FloatVector##n *this){\
    Int i, mini;\
    Float minv = CBL_FLOAT_MAX;\
    mini = -1;\
    for(i=0; i<n; i++) if(this->data[i] < minv) {\
        minv = this->data[i];\
        mini = i;\
    }\
    return mini;\
}\
static inline Int FloatVector##n##_argmax(const struct FloatVector##n *this){\
    Int i, maxi;\
    Float maxv = CBL_FLOAT_MIN;\
    maxi = -1;\
    for(i=0; i<n; i++) if(this->data[i] > maxv) {\
        maxv = this->data[i];\
        maxi = i;\
    }\
    return maxi;\
}\
static inline void FloatVector##n##_cumsum_(struct FloatVector##n *this, Float initial){\
    Int i;\
    Float sum;\
    sum = initial;\
    for(i=0; i<n; i++){\
        sum += this->data[i];\
        this->data[i] = sum;\
    }\
}\
static inline void FloatVector##n##_cumprod_(struct FloatVector##n *this, Float initial){\
    Int i;\
    Float prod;\
    prod = initial;\
    for(i=0; i<n; i++){\
        prod *= this->data[i];\
        this->data[i] = prod;\
    }\
}\
static void FloatVector##n##_sort_(struct FloatVector##n *this){\
    Int i, j;\
    Float t;\
    for(i = 0; i < n; i++)\
        for(j = i + 1; j < n; j++)\
            if(this->data[i]>this->data[j]){\
                t = this->data[i];\
                this->data[i] = this->data[j];\
                this->data[j] = t;\
            }\
}\
static struct IntVector_##n FloatVector##n##_sortperm_(struct FloatVector##n *this){\
    struct FloatVector buf;\
    struct IntVector perm;\
    struct IntVector_##n permN;\
    FloatVector_new_(&buf);\
    IntVector_new_(&perm);\
    IntVector_##n##_new_(&permN);\
    FloatVector_alloc_(&buf, n);\
    IntVector_alloc_(&perm, n);\
    memcpy(buf.data, this->data, n*sizeof(Float));\
    FloatVector_sortperm_(&buf, &perm);\
    memcpy(this->data, buf.data, n*sizeof(Float));\
    memcpy(permN.data, perm.data, n*sizeof(Int));\
    FloatVector_free_(&buf);\
    IntVector_free_(&perm);\
    return permN;\
}\
static struct FloatVector##n##_methods _CBL_FLOAT_VECTOR_##n##_METHODS={\
    &FloatVector##n##_get,\
    &FloatVector##n##_set_,\
    &FloatVector##n##_set_all_,\
    &FloatVector##n##_rand_,\
    &FloatVector##n##_fill_,\
    &FloatVector##n##_range_,\
    &FloatVector##n##_sum,\
    &FloatVector##n##_prod,\
    &FloatVector##n##_min,\
    &FloatVector##n##_max,\
    &FloatVector##n##_argmin,\
    &FloatVector##n##_argmax,\
    &FloatVector##n##_cumsum_,\
    &FloatVector##n##_cumprod_,\
    &FloatVector##n##_sort_,\
    &FloatVector##n##_sortperm_\
};\
static inline void FloatVector##n##_new_(struct FloatVector##n *this){\
    this->methods = &_CBL_FLOAT_VECTOR_##n##_METHODS;\
}

#define FloatVectorN(N) _FloatVectorN_inner(N)

#endif // _TYPE_FLOATVECTORN_H_
