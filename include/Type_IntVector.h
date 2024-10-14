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

#ifndef _CBL_INTVECTOR_H_
#define _CBL_INTVECTOR_H_

#include "Module_Basic.h"

/**
 * @brief IntVector
 * @param len Int
 * @param data Int*
 */
struct IntVector {
    Int                      len;
    Int*                     data;
    struct IntVectorMethods* methods;
};

struct IntVectorMethods {
    // # memory management
    /* may change the length of the vector */

    /**
     * @brief free allocated memory
     * @param this struct IntVector*
     */
    void (*free_)(struct IntVector* this);

    /**
     * @brief allocate memory with specified length.\n
     * If the memory is not allocated, it will allocate memory with given length;\n
     * If the memory is allocated and the current length is equal to the given length,
     * nothing will be changed;\n
     * If the memory is allocated but the current length is not equal to the given length,
     * it will free the current length, and allocate a new memory with given length.\n
     * @param this struct IntVector*
     * @param len Int
     */
    void (*alloc_)(struct IntVector* this, Int len);

    // # index
    /**
     * @brief get value at index, throw error when index is over bound
     * @param this
     * @param index Int
     */
    Int (*get)(const struct IntVector* this, Int index);

    // # value setting
    // # by index
    void (*index_)(struct IntVector* this, struct IntVector src, struct IntVector indexs);

    void (*slice_)(struct IntVector* this, struct IntVector src, Int start, Int step, Int stop);

    void (*index_flag_)(struct IntVector* this, struct IntVector src, struct IntVector flags);

    void (*set_)(struct IntVector* this, Int index, Int value);

    // # all
    void (*rand_)(struct IntVector* this, Int min, Int max);

    void (*rand_from_)(struct IntVector* this, struct IntVector value_set);

    void (*fill_)(struct IntVector* this, Int value);

    void (*range_)(struct IntVector* this, Int start, Int step, Int stop);

    void (*copy_from_)(struct IntVector* this, struct IntVector src);

    void (*find_trues_)(struct IntVector* this, struct IntVector flags);

    // # methods without changing values in vector
    Int (*count)(struct IntVector* this);

    Int (*sum)(struct IntVector* this);

    Int (*prod)(struct IntVector* this);

    Int (*min)(struct IntVector* this);

    Int (*max)(struct IntVector* this);

    Int (*argmin)(struct IntVector* this);

    Int (*argmax)(struct IntVector* this);

    // # methods changing values in vector
    void (*cumsum_)(struct IntVector* this, Int initial);

    void (*cumprod_)(struct IntVector* this, Int initial);

    void (*sort_)(struct IntVector* this);

    void (*sortperm_)(struct IntVector* this, struct IntVector* perm);
};


void IntVector_free_(struct IntVector* this);

void IntVector_alloc_(struct IntVector* this, Int len);

Int IntVector_get(const struct IntVector* this, Int index);

void IntVector_index_(struct IntVector* this, struct IntVector src, struct IntVector indexs);

void IntVector_slice_(struct IntVector* this, struct IntVector src, Int start, Int step, Int stop);

void IntVector_index_flag_(struct IntVector* this, struct IntVector src, struct IntVector flags);

void IntVector_set_(struct IntVector* this, Int index, Int value);

void IntVector_rand_(struct IntVector* this, Int min, Int max);

void IntVector_rand_from_(struct IntVector* this, struct IntVector value_set);

void IntVector_fill_(struct IntVector* this, Int value);

void IntVector_range_(struct IntVector* this, Int start, Int step, Int stop);

void IntVector_copy_from_(struct IntVector* this, struct IntVector src);

void IntVector_find_trues_(struct IntVector* this, struct IntVector flags);

Int IntVector_count(struct IntVector* this);

Int IntVector_sum(struct IntVector* this);

Int IntVector_prod(struct IntVector* this);

Int IntVector_min(struct IntVector* this);

Int IntVector_max(struct IntVector* this);

Int IntVector_argmin(struct IntVector* this);

Int IntVector_argmax(struct IntVector* this);

void IntVector_cumsum_(struct IntVector* this, Int initial);

void IntVector_cumprod_(struct IntVector* this, Int initial);

void IntVector_sort_(struct IntVector* this);

void IntVector_sortperm_(struct IntVector* this, struct IntVector* perm);

extern struct IntVectorMethods _CBL_INT_VECTOR_METHODS;

inline static void IntVector_new_(struct IntVector* this) {
    this->len = 0;
    this->data = NULL;
    this->methods = &_CBL_INT_VECTOR_METHODS;

}

#endif // _CBL_INTVECTOR_H_
