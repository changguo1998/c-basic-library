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

#include "Module_Basic.h"

#define DEFINE_STRUCT_TYPE_VECTOR(T) struct T##Vector{\
    Int len;\
    T *data;\
    struct T##VectorMethods *methods;\
};

#define DEFINE_STRUCT_TYPE_VECTOR_METHODS(T) struct T##VectorMethods{\
    void (*free_)(     struct T##Vector* this);\
    void (*alloc_)(    struct T##Vector* this, Int len);\
       T (*get)( const struct T##Vector* this, Int index);\
    void (*fill_)(     struct T##Vector* this, T value);\
    void (*rand_)(     struct T##Vector* this, T min, T max);\
    void (*rand_from_)(struct T##Vector* this, const struct T##Vector seed);\
    void (*set_)(      struct T##Vector* this, Int index, T value);\
    void (*range_)(    struct T##Vector* this, T start, T step, T stop);\
    void (*index_)(    struct T##Vector* this, const struct T##Vector src, struct IntVector indexs);\
    void (*index_f_)(  struct T##Vector* this, const struct T##Vector src, struct IntVector flags);\
    void (*slice_)(    struct T##Vector* this, const struct T##Vector src, Int start, Int step, Int stop);\
       T (*sum)( const struct T##Vector* this);\
       T (*prod)(const struct T##Vector* this);\
       T (*min)( const struct T##Vector* this);\
       T (*max)( const struct T##Vector* this);\
    Int (*argmin)(const struct T##Vector* this);\
    Int (*argmax)(const struct T##Vector* this);\
    void (*cumsum_)(   struct T##Vector* this, T initial_value);\
    void (*cumprod_)(  struct T##Vector* this, T initial_value);\
    void (*sort_)(     struct T##Vector* this);\
};


#define DECLARE_TYPE_VECTOR_METHODS(T)\
void T##Vector_free_(     struct T##Vector* this);\
void T##Vector_alloc_(    struct T##Vector* this, Int len);\
   T T##Vector_get( const struct T##Vector* this, Int index);\
void T##Vector_fill_(     struct T##Vector* this, T value);\
void T##Vector_rand_(     struct T##Vector* this, T min, T max);\
void T##Vector_rand_from_(struct T##Vector* this, const struct T##Vector seed);\
void T##Vector_set_(      struct T##Vector* this, Int index, T value);\
void T##Vector_range_(    struct T##Vector* this, T start, T step, T stop);\
void T##Vector_index_(    struct T##Vector* this, const struct T##Vector src, struct IntVector indexs);\
void T##Vector_index_f_(  struct T##Vector* this, const struct T##Vector src, struct IntVector flags);\
void T##Vector_slice_(    struct T##Vector* this, const struct T##Vector src, Int start, Int step, Int stop);\
   T T##Vector_sum( const struct T##Vector* this);\
   T T##Vector_prod(const struct T##Vector* this);\
   T T##Vector_min( const struct T##Vector* this);\
   T T##Vector_max( const struct T##Vector* this);\
 Int T##Vector_argmin(const struct T##Vector* this);\
 Int T##Vector_argmax(const struct T##Vector* this);\
void T##Vector_cumsum_(   struct T##Vector* this, T initial_value);\
void T##Vector_cumprod_(  struct T##Vector* this, T initial_value);\
void T##Vector_sort_(     struct T##Vector* this);

#define GLOBAL_METHODS_STRUCT_VAR_NAME(T) _TYPE_##T##_VECTOR_METHODS

#define DEFINE_TYPE_ARRAY_NEW_FUNCTION(T) void T##Vector_new_(struct T##Vector* this){\
    this->len = 0;\
    this->data = NULL;\
    this->methods = &GLOBAL_METHODS_STRUCT_VAR_NAME(T);\
}

#define DEFINE_TYPE_VECTOR_CLASS_HEADER_PART(T) \
    DEFINE_STRUCT_TYPE_VECTOR(T)\
    DEFINE_STRUCT_TYPE_VECTOR_METHODS(T)\
    DECLARE_TYPE_VECTOR_METHODS(T)\
    extern struct T##VectorMethods GLOBAL_METHODS_STRUCT_VAR_NAME(T);\
    DEFINE_TYPE_ARRAY_NEW_FUNCTION(T)

#define INITIALIZE_GLOBAL_METHODS_STRUCT(T) struct T##VectorMethods GLOBAL_METHODS_STRUCT_VAR_NAME(T) = {\
    &T##Vector_free_,\
    &T##Vector_alloc_,\
    &T##Vector_get,\
    &T##Vector_fill_,\
    &T##Vector_rand_,\
    &T##Vector_rand_from_,\
    &T##Vector_set_,\
    &T##Vector_range_,\
    &T##Vector_index_,\
    &T##Vector_index_f_,\
    &T##Vector_slice_,\
    &T##Vector_sum,\
    &T##Vector_prod,\
    &T##Vector_min,\
    &T##Vector_max,\
    &T##Vector_argmin,\
    &T##Vector_argmax,\
    &T##Vector_cumsum_,\
    &T##Vector_cumprod_,\
    &T##Vector_sort_\
};

#define DEFINE_TYPE_VECTOR_METHODS(T)\
void T##Vector_free_(struct T##Vector* this){\
    if(this->data) free(this->data);\
    this->data = NULL;\
    this->len = 0;\
}\
void T##Vector_alloc_(struct T##Vector* this, Int len){\
    T *p = NULL;\
    Int n;\
    if(this->data)\
        if(this->len == len) return;\
        else {\
            p = (T*)calloc(len, sizeof(T));\
            n = len > this->len ? this->len : len;\
            memcpy(p, this->data, n * sizeof(T));\
            free(this->data);\
            this->data = p;\
        }\
    else{\
        this->data = (T*)calloc(len, sizeof(T));\
        this->len = len;\
    }\
}\
T T##Vector_get(const struct T##Vector* this, Int index){\
    if(index<0 || index>=this->len) error_index_out_of_bounds("");\
    return this->data[index];\
}\
void T##Vector_fill_(struct T##Vector* this, T value){\
    Int i;\
    for(i=0; i<this->len; i++) this->data[i] = value;\
}\
void T##Vector_rand_(struct T##Vector* this, T min, T max){\
    Int i;\
    srand(time(NULL));\
    for(i=0; i<this->len; i++) this->data[i] = (T)(min + (Float)rand()/(Float)(max-min));\
}\
void T##Vector_rand_from_(struct T##Vector* this, const struct T##Vector seed){\
    Int i, idx;\
    srand(time(NULL));\
    for(i=0; i<this->len; i++){\
        idx = (Int)rand() % seed.len;\
        this->data[i] = seed.data[idx];\
    }\
}\
void T##Vector_set_(struct T##Vector* this, Int index, T value){\
    if(index < 0 || index >= this->len) error_index_out_of_bounds("");\
    this->data[index] = value;\
}\
void T##Vector_range_(struct T##Vector* this, T start, T step, T stop){\
    Int i;\
    if(this->len<=0) return;\
    if(step == 0) step = (Int)((stop - start)/((Float)(this->len - 1)));\
    for(i=0; i<this->len; i++) this->data[i] = start + i * step;\
}\
void T##Vector_index_(    struct T##Vector* this, const struct T##Vector src, struct IntVector indexs){\
    Int i, j;\
    T##Vector_alloc_(this, indexs.len);\
    for(i=0; i<indexs.len; i++){\
        j = indexs.data[i];\
        if(j<0||j>=src.len) error_index_out_of_bounds("");\
        this->data[i] = src.data[j];\
    }\
}\
void T##Vector_index_f_(  struct T##Vector* this, const struct T##Vector src, struct IntVector flags){\
    Int i, n;\
    n = 0;\
    for(i=0; i<flags.len; i++) if(flags.data[i]) n += 1;\
    T##Vector_alloc_(this, n);\
    n = 0; \
    for(i=0; i<flags.len; i++) if(flags.data[i]){\
        this->data[n] = src.data[i];\
        n += 1;\
    }\
}\
void T##Vector_slice_(struct T##Vector* this, const struct T##Vector src, Int start, Int step, Int stop){\
    Int i, j, n;\
    if((stop-start)*step <= 0) error_invalid_argument("");\
    if(start < 0 || start >= src.len) error_invalid_argument("");\
    if(stop < 0 || stop >= src.len) error_invalid_argument("");\
    if(step == 0) step = 1;\
    n = (stop - start) / step + 1;\
    T##Vector_alloc_(this, n);\
    j = start;\
    for(i=0; i<n; i++){\
        this->data[i] = src.data[j];\
        j += step;\
    }\
}\
T T##Vector_sum( const struct T##Vector* this){\
    T sum = 0;\
    Int i;\
    for(i=0; i<this->len; i++) sum += this->data[i];\
    return sum;\
}\
T T##Vector_prod(const struct T##Vector* this){\
    T prod = 1;\
    Int i;\
    for(i=0; i<this->len; i++) prod *= this->data[i];\
    return prod;\
}\
T T##Vector_min( const struct T##Vector* this){\
    T min_val = 0.0;\
    Int i;\
    if(this->len<=0) error_invalid_argument("");\
    min_val = this->data[0];\
    for(i=0; i<this->len; i++)\
        if(min_val > this->data[i])\
            min_val = this->data[i];\
}\
T T##Vector_max( const struct T##Vector* this){\
    T max_val = 0.0;\
    Int i;\
    if(this->len<=0) error_invalid_argument("");\
    max_val = this->data[0];\
    for(i=0; i<this->len; i++)\
        if(max_val < this->data[i])\
            max_val = this->data[i];\
}\
Int T##Vector_argmin(const struct T##Vector* this){\
    T min_val = 0.0;\
    Int i, min_idx;\
    if(this->len<=0) error_invalid_argument("");\
    min_val = this->data[0];\
    min_idx = 0;\
    for(i=0; i<this->len; i++)\
        if(min_val > this->data[i]){\
            min_val = this->data[i];\
            min_idx = i;\
        }\
}\
Int T##Vector_argmax(const struct T##Vector* this){\
    T max_val = 0.0;\
    Int i, max_idx;\
    if(this->len<=0) error_invalid_argument("");\
    max_val = this->data[0];\
    max_idx = 0;\
    for(i=0; i<this->len; i++)\
        if(max_val < this->data[i]){\
            max_val = this->data[i];\
            max_idx = i;\
        }\
}\
void T##Vector_cumsum_(   struct T##Vector* this, T initial_value){\
    Int i;\
    for(i=0; i<this->len; i++){\
        initial_value += this->data[i];\
        this->data[i] = initial_value;\
    }\
}\
void T##Vector_cumprod_(  struct T##Vector* this, T initial_value){\
    Int i;\
    for(i=0; i<this->len; i++){\
        initial_value *= this->data[i];\
        this->data[i] = initial_value;\
    }\
}\
void T##Vector_sort_(struct T##Vector* this){\
    Int i, j, t;\
    for(i = 0; i < this->len; i++)\
        for(j = i + 1; j < this->len; j++)\
            if(this->data[i] > this->data[j]) {\
                t             = this->data[i];\
                this->data[i] = this->data[j];\
                this->data[j] = t;\
            }\
}

#define DEFINE_TYPE_VECTOR_CLASS_SOURCE_PART(T)\
    INITIALIZE_GLOBAL_METHODS_STRUCT(T)\
    DEFINE_TYPE_VECTOR_METHODS(T)

// DEFINE_TYPE_VECTOR_CLASS_HEADER_PART(Int)
// DEFINE_TYPE_VECTOR_CLASS_HEADER_PART(Float)
// DEFINE_TYPE_VECTOR_CLASS_SOURCE_PART(Int)
// DEFINE_TYPE_VECTOR_METHODS(Float)

#endif // _TEMPLATE_VECTOR_H_
