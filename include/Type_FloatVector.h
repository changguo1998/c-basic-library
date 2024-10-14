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

#ifndef _CBL_FLOATVECTOR_H_
#define _CBL_FLOATVECTOR_H_

#include "Module_Basic.h"
#include "Type_IntVector.h"

/**
 * @brief FloatVector
 * @param len Int
 * @param data Int*
 */
struct FloatVector {
    Int    len;
    Float* data;

    struct FloatVectorMethods* methods;
};

struct FloatVectorMethods {
    // # memory management
    /* may change the length of the vector */

    /**
     * @brief free allocated memory
     * @param this struct FloatVector*
     */
    void (*free_)(struct FloatVector* this);

    /**
     * @brief allocate memory with specified length.\n
     * If the memory is not allocated, it will allocate memory with given length;\n
     * If the memory is allocated and the current length is equal to the given length,
     * nothing will be changed;\n
     * If the memory is allocated but the current length is not equal to the given length,
     * it will free the current length, and allocate a new memory with given length.\n
     * @param this struct FloatVector*
     * @param len Int
     */
    void (*alloc_)(struct FloatVector* this, Int len);

    // # index
    /**
     * @brief get value at index, throw error when index is over bound
     * @param this
     * @param index Int
     */
    Float (*get)(const struct FloatVector* this, Int index);

    // # value setting
    // # by index
    void (*index_)(struct FloatVector* this, struct FloatVector src, struct IntVector indexs);

    void (*slice_)(struct FloatVector* this, struct FloatVector src, Int start, Int step, Int stop);

    void (*index_flag_)(struct FloatVector* this, struct FloatVector src, struct IntVector flags);

    void (*set_)(struct FloatVector* this, Int index, Float value);

    // # all
    void (*rand_)(struct FloatVector* this, Float min, Float max);

    void (*rand_from_)(struct FloatVector* this, struct FloatVector value_set);

    void (*fill_)(struct FloatVector* this, Float value);

    void (*range_)(struct FloatVector* this, Float start, Float stop);

    void (*copy_from_)(struct FloatVector* this, struct FloatVector src);

    // # methods without changing values in vector
    Float (*sum)(struct FloatVector* this);

    Float (*prod)(struct FloatVector* this);

    Float (*min)(struct FloatVector* this);

    Float (*max)(struct FloatVector* this);

    Int (*argmin)(struct FloatVector* this);

    Int (*argmax)(struct FloatVector* this);

    // # methods changing values in vector
    void (*cumsum_)(struct FloatVector* this, Float initial);

    void (*cumprod_)(struct FloatVector* this, Float initial);

    void (*sort_)(struct FloatVector* this);

    void (*sortperm_)(struct FloatVector* this, struct IntVector* perm);
};

extern struct FloatVectorMethods _CBL_FLOAT_VECTOR_METHODS;

inline static void FloatVector_new_(struct FloatVector* this) {
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
void  FloatVector_rand_(struct FloatVector* this, Float min, Float max);
void  FloatVector_rand_from_(struct FloatVector* this, struct FloatVector value_set);
void  FloatVector_fill_(struct FloatVector* this, Float value);
void  FloatVector_range_(struct FloatVector* this, Float start, Float stop);
void  FloatVector_copy_from_(struct FloatVector* this, struct FloatVector src);
Float FloatVector_sum(struct FloatVector* this);
Float FloatVector_prod(struct FloatVector* this);
Float FloatVector_min(struct FloatVector* this);
Float FloatVector_max(struct FloatVector* this);
Int   FloatVector_argmin(struct FloatVector* this);
Int   FloatVector_argmax(struct FloatVector* this);
void  FloatVector_cumsum_(struct FloatVector* this, Float initial);
void  FloatVector_cumprod_(struct FloatVector* this, Float initial);
void  FloatVector_sort_(struct FloatVector* this);
void  FloatVector_sortperm_(struct FloatVector* this, struct IntVector* perm);

#endif // _CBL_FLOATVECTOR_H_
