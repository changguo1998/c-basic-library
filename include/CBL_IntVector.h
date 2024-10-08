#ifndef _CBL_INTVECTOR_H_
#define _CBL_INTVECTOR_H_

#include "CBL_Basic.h"

void _INT_VECTOR_level0_get_by_vec(Int* b, const Int* a, Int len_a, const Int* index, Int len_index);

void _INT_VECTOR_level0_set_by_vec(Int* a, Int len_a, const Int* index, Int len_index, const Int* values);

void _INT_VECTOR_level0_set_by_flags(Int* a, Int len_a, const Int* flags, Int value);

void _INT_VECTOR_level0_find_trues(Int* a, Int len_a, const Int* flags, Int len_flags);

void _INT_VECTOR_level0_fill(Int* a, Int n, Int val);

void _INT_VECTOR_level0_rand(Int* a, Int n, Int max);

Int _INT_VECTOR_level0_sum(Int* a, Int n);

Int _INT_VECTOR_level0_prod(Int* a, Int n);

void _INT_VECTOR_level0_cumsum(Int* a, Int n);

void _INT_VECTOR_level0_cumprod(Int* a, Int n);

Int _INT_VECTOR_level0_min(Int* a, Int n, Int* mi);

Int _INT_VECTOR_level0_max(Int* a, Int n, Int* mi);

void _INT_VECTOR_level0_sort(Int* a, Int* perm, Int n);

/**
 * @brief IntVector
 * @param len Int
 * @param data Int*
 */
struct IntVector {
    Int  len;
    Int* data;

    void (*free)(struct IntVector* this);

    void (*alloc)(struct IntVector* this, Int len);

    void (*fill)(struct IntVector* this, Int value);

    void (*rand)(struct IntVector* this, Int max);

    void (*range)(struct IntVector* this, Int start, Int step, Int stop);

    Int (*get)(const struct IntVector* this, Int i);

    struct IntVector (*deepcopy)(const struct IntVector* this);

    struct IntVector (*index)(struct IntVector* this, struct IntVector indexs);

    struct IntVector (*slice)(struct IntVector* this, Int start, Int step, Int stop);

    void (*set)(struct IntVector* this, Int i, Int value);

    struct IntVector (*findall)(struct IntVector* this);

    Int (*sum)(struct IntVector* this);

    Int (*prod)(struct IntVector* this);

    void (*cumsum)(struct IntVector* this);

    void (*cumprod)(struct IntVector* this);

    Int (*min)(struct IntVector* this, Int* imin);

    Int (*max)(struct IntVector* this, Int* imax);

    void (*sort)(struct IntVector* this, struct IntVector* perm);
};

void IntVector_init(struct IntVector* this);

void IntVector_free(struct IntVector* this);

void IntVector_alloc(struct IntVector* this, Int len);

void IntVector_fill(struct IntVector* this, Int value);

void IntVector_rand(struct IntVector* this, Int max);

void IntVector_range(struct IntVector* this, Int start, Int step, Int stop);

Int IntVector_get(const struct IntVector* this, Int i);

struct IntVector IntVector_deepcopy(const struct IntVector* this);

struct IntVector IntVector_index(struct IntVector* this, struct IntVector indexs);

struct IntVector IntVector_slice(struct IntVector* this, Int start, Int step, Int stop);

void IntVector_set(struct IntVector* this, Int i, Int value);

struct IntVector IntVector_findall(struct IntVector* this);

Int IntVector_sum(struct IntVector* this);

Int IntVector_prod(struct IntVector* this);

void IntVector_cumsum(struct IntVector* this);

void IntVector_cumprod(struct IntVector* this);

Int IntVector_min(struct IntVector* this, Int* imin);

Int IntVector_max(struct IntVector* this, Int* imax);

void IntVector_sort(struct IntVector* this, struct IntVector* perm);

#endif // _CBL_INTVECTOR_H_
