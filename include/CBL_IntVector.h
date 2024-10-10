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

#include "CBL_Basic.h"

void INT_VECTOR_level0_get_by_vec(Int* b, const Int* a, Int len_a, const Int* index, Int len_index);

void INT_VECTOR_level0_set_by_vec(Int* a, Int len_a, const Int* index, const Int* values, Int len_index);

void INT_VECTOR_level0_set_by_flags(Int* a, Int len_a, const Bool* flags, Int value);

void INT_VECTOR_level0_find_trues(Int* a, Int len_a, const Int* flags, Int len_flags);

void INT_VECTOR_level0_fill(Int* a, Int n, Int val);

void INT_VECTOR_level0_rand(Int* a, Int n, Int max);

Int INT_VECTOR_level0_sum(const Int* a, Int n);

Int INT_VECTOR_level0_prod(const Int* a, Int n);

void INT_VECTOR_level0_cumsum(Int* a, Int n, Int init);

void INT_VECTOR_level0_cumprod(Int* a, Int n, Int init);

void INT_VECTOR_level0_min_max(const Int* a, Int n, Int* min_value, Int* min_index, Int* max_value, Int* max_index);

void INT_VECTOR_level0_sort(Int* a, Int* perm, Int n);

/**
 * @brief IntVector
 * @param len Int
 * @param data Int*
 */
struct IntVector {
    Int  len;
    Int* data;

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

    void (*copy_from_)(struct IntVector* this, const struct IntVector* src);

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
    void (*cumsum_)(struct IntVector* this, Int initial_value);

    void (*cumprod_)(struct IntVector* this, Int initial_value);

    void (*sort_)(struct IntVector* this);

    void (*sortperm_)(struct IntVector* this, struct IntVector reference);
};

/**
 * @brief free allocated memory
 * @param this struct IntVector*
 */
void IntVector_free_(struct IntVector* this);

/**
* @brief allocate memory with specified length.\n
     * If the memory is not allocated, it will allocate memory with given length;\n
     * If the memory is allocated and the current length is equal to the given length,
     * nothing will be changed;\n
     * If the memory is allocated but the current length is not equal to the given length,
     * it will allocate a new memory with given length, and try to keep the values same to previous memory.\n
 * @param this
 * @param len
 */
void IntVector_alloc_(struct IntVector* this, Int len);

/**
 * @brief get value at index, throw error when index is over bound
 * @param index Int
 */
Int IntVector_get(const struct IntVector* this, Int index);

void IntVector_index_(struct IntVector* this, struct IntVector src, struct IntVector indexs);

void IntVector_slice_(struct IntVector* this, struct IntVector src, Int start, Int step, Int stop);

void IntVector_index_flag_(struct IntVector* this, struct IntVector src, struct IntVector flags);

void IntVector_set_(struct IntVector* this, Int index, Int value);

void IntVector_rand_(struct IntVector* this, Int min, Int max);

void IntVector_rand_from_(struct IntVector* this, struct IntVector value_set);

void IntVector_fill_(struct IntVector* this, Int value);

void IntVector_range_(struct IntVector* this, Int start, Int step, Int stop);

void IntVector_copy_from_(struct IntVector* this, const struct IntVector* src);

void IntVector_find_trues_(struct IntVector* this, struct IntVector flags);

Int IntVector_count(struct IntVector* this);

Int IntVector_sum(struct IntVector* this);

Int IntVector_prod(struct IntVector* this);

Int IntVector_min(struct IntVector* this);

Int IntVector_max(struct IntVector* this);

Int IntVector_argmin(struct IntVector* this);

Int IntVector_argmax(struct IntVector* this);

void IntVector_cumsum_(struct IntVector* this, Int initial_value);

void IntVector_cumprod_(struct IntVector* this, Int initial_value);

void IntVector_sort_(struct IntVector* this);

void IntVector_sortperm_(struct IntVector* this, struct IntVector reference);

inline static void IntVector_new_(struct IntVector* this) {
    if(this == NULL) return;
    this->len  = 0;
    this->data = NULL;

    this->free_  = &IntVector_free_;
    this->alloc_ = &IntVector_alloc_;

    this->get = &IntVector_get;


    this->index_      = &IntVector_index_;
    this->slice_      = &IntVector_slice_;
    this->index_flag_ = &IntVector_index_flag_;
    this->set_        = &IntVector_set_;

    this->rand_       = &IntVector_rand_;
    this->rand_from_  = &IntVector_rand_from_;
    this->fill_       = &IntVector_fill_;
    this->range_      = &IntVector_range_;
    this->copy_from_  = &IntVector_copy_from_;
    this->find_trues_ = &IntVector_find_trues_;

    this->count  = &IntVector_count;
    this->sum    = &IntVector_sum;
    this->prod   = &IntVector_prod;
    this->min    = &IntVector_min;
    this->max    = &IntVector_max;
    this->argmin = &IntVector_argmin;
    this->argmax = &IntVector_argmax;

    this->cumsum_   = &IntVector_cumsum_;
    this->cumprod_  = &IntVector_cumprod_;
    this->sort_     = &IntVector_sort_;
    this->sortperm_ = &IntVector_sortperm_;
}

#endif // _CBL_INTVECTOR_H_
