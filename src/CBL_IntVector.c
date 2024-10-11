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

#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <errno.h>

#include "CBL_IntVector.h"

void INT_VECTOR_level0_get_by_vec(Int* b, const Int* a, Int len_a, const Int* index, Int len_index) {
    Int i_index;
    for(i_index = 0; i_index < len_index; i_index++) b[i_index] = a[index[i_index]];
}

void INT_VECTOR_level0_set_by_vec(Int* a, Int len_a, const Int* index, const Int* values, Int len_index) {
    Int i_index;
    for(i_index = 0; i_index < len_index; i_index++) a[index[i_index]] = values[i_index];
}

void INT_VECTOR_level0_set_by_flags(Int* a, Int len_a, const Bool* flags, Int value) {
    Int i;
    for(i = 0; i < len_a; i++) if(flags[i]) a[i] = value;
}

void INT_VECTOR_level0_find_trues(Int* a, Int len_a, const Int* flags, Int len_flags) {
    Int N_true = 0;
    Int i      = 0;
    for(i = 0; i < len_flags; i++)
        if(flags[i]) {
            if(N_true < len_a) {
                a[N_true] = i;
                N_true += 1;
            }
            else return;
        }
}

void INT_VECTOR_level0_fill(Int* a, Int n, Int val) { for(Int i = 0; i < n; i++) a[i] = val; }

void INT_VECTOR_level0_rand(Int* a, Int n, Int max) {
    srand(time(NULL));
    for(Int i = 0; i < n; i++) a[i] = (Int)rand() % (max + 1);
}

Int INT_VECTOR_level0_sum(const Int* a, Int n) {
    Int sum = 0;
    for(Int i = 0; i < n; i++) sum += a[i];
    return sum;
}

Int INT_VECTOR_level0_prod(const Int* a, Int n) {
    Int prod = 1;
    for(Int i = 0; i < n; i++) prod *= a[i];
    return prod;
}

void INT_VECTOR_level0_cumsum(Int* a, Int n) {
    Int sum = 0;
    for(Int i = 0; i < n; i++) {
        sum += a[i];
        a[i] = sum;
    }
}

void INT_VECTOR_level0_cumprod(Int* a, Int n) {
    Int prod = 1;
    for(Int i = 0; i < n; i++) {
        prod *= a[i];
        a[i] = prod;
    }
}

void INT_VECTOR_level0_min(const Int* a, Int n, Int* min_value, Int* min_index) {
    Int i;
    *min_value = INT_MAX;
    *min_index = -1;
    for(i = 0; i < n; i++)
        if(a[i] < *min_value) {
            *min_value = a[i];
            *min_index = i;
        }
}

void INT_VECTOR_level0_max(const Int* a, Int n, Int* max_value, Int* max_index) {
    Int i;
    *max_value = INT_MIN;
    *max_index = 0;
    for(i = 0; i < n; i++)
        if(a[i] > *max_value) {
            *max_value = a[i];
            *max_index = i;
        }
}

void INT_VECTOR_level0_sort(Int* a, Int* perm, Int n) {
    Int i, j, t;
    for(i = 0; i < n; i++) perm[i] = i;
    for(i = 0; i < n; i++)
        for(j = i + 1; j < n; j++)
            if(a[i] > a[j]) {
                t       = a[i];
                a[i]    = a[j];
                a[j]    = t;
                t       = perm[i];
                perm[i] = perm[j];
                perm[j] = t;
            }
}

void IntVector_fill(struct IntVector* this, Int value) {
    if(this == NULL) return;
    if(this->len <= 0) return;
    INT_VECTOR_level0_fill(this->data, this->len, value);
}

void IntVector_rand(struct IntVector* this, Int max) {
    if(this == NULL) return;
    if(this->len <= 0) return;
    INT_VECTOR_level0_rand(this->data, this->len, max);
}

void IntVector_range(struct IntVector* this, Int start, Int step, Int stop) {
    Int i, v, n;
    if(this == NULL) return;
    n = labs(stop - start) / labs(step) + 1;
    if(this->len < n) this->alloc_(this, n);
    for(i = 0, v = start; i < this->len; i++) {
        this->data[i] = v;
        v += step;
        if((v - start) * (stop - v) < 0) break;
    }
}

inline struct IntVector IntVector_deepcopy(const struct IntVector* this) {
    struct IntVector tmp;
    IntVector_init(&tmp);
    tmp.len  = this->len;
    tmp.data = (Int*)malloc(this->len * sizeof(Int));
    memcpy(tmp.data, this->data, this->len * sizeof(Int));
    return tmp;
}

struct IntVector IntVector_index(struct IntVector* this, struct IntVector indexs) {
    struct IntVector tmp;
    Int              idxmax, itmp;
    IntVector_init(&tmp);
    if(this == NULL) return tmp;
    idxmax = INT_VECTOR_level0_max(indexs.data, indexs.len, &itmp, TODO);
    if(idxmax >= this->len) return tmp;
    tmp.alloc_(&tmp, indexs.len);
    INT_VECTOR_level0_get_by_vec(tmp.data, this->data, this->len, indexs.data, indexs.len);
    return tmp;
}

struct IntVector IntVector_slice(struct IntVector* this, Int start, Int step, Int stop) {
    struct IntVector tmp;
    Int              n_slice, t, i;
    IntVector_init(&tmp);
    if(this == NULL) return tmp;
    if(this->len <= 0) return tmp;
    if(start >= this->len || stop >= this->len) return tmp;
    n_slice = labs(stop - start) / labs(step) + 1;
    tmp.alloc_(&tmp, n_slice);
    for(i = 0, t = start; i < n_slice; i++) {
        tmp.data[i] = this->data[t];
        t += step;
    }
    return tmp;
}

void IntVector_set(struct IntVector* this, Int i, Int value) {
    if(this == NULL) return;
    if(i >= this->len) this->alloc_(this, i + 1);
    this->data[i] = value;
}

struct IntVector IntVector_findall(struct IntVector* this) {
    Int              n, i;
    struct IntVector tmp;
    IntVector_init(&tmp);
    if(this == NULL) return tmp;
    if(this->len <= 0) return tmp;
    for(i = 0, n = 0; i < this->len; i++) if(this->data[i]) n += 1;
    tmp.alloc_(&tmp, n);
    for(i = 0, n = 0; i < this->len; i++)
        if(this->data[i]) {
            tmp.data[n] = i;
            n += 1;
        }
    return tmp;
}

Int IntVector_sum(struct IntVector* this) {
    if(this == NULL) return 0;
    if(this->len <= 0) return 0;
    return INT_VECTOR_level0_sum(this->data, this->len);
}

Int IntVector_prod(struct IntVector* this) {
    if(this == NULL) return 0;
    if(this->len <= 0) return 0;
    return INT_VECTOR_level0_prod(this->data, this->len);
}

void IntVector_cumsum(struct IntVector* this) {
    if(this == NULL) return;
    if(this->len <= 0) return;
    INT_VECTOR_level0_cumsum(this->data, this->len);
}

void IntVector_cumprod(struct IntVector* this) {
    if(this == NULL) return;
    if(this->len <= 0) return;
    INT_VECTOR_level0_cumprod(this->data, this->len);
}

Int IntVector_min(struct IntVector* this, Int* imin) {
    if(this == NULL) return 0;
    if(this->len <= 0) return 0;
    return INT_VECTOR_level0_min(this->data, this->len, imin, TODO);
}

Int IntVector_max(struct IntVector* this, Int* imax) {
    if(this == NULL) return 0;
    if(this->len <= 0) return 0;
    return INT_VECTOR_level0_max(this->data, this->len, imax, TODO);
}

void IntVector_sort(struct IntVector* this, struct IntVector* perm) {
    IntVector_init(perm);
    if(this == NULL) return;
    if(this->len <= 0) return;
    perm->alloc_(perm, this->len);
    INT_VECTOR_level0_sort(this->data, perm->data, this->len);
}

// ============================================================================

void IntVector_free_(struct IntVector* this) {
    if(this == NULL) return;
    if(this->data) {
        free(this->data);
        this->data = NULL;
        this->len  = 0;
    }
}

void IntVector_alloc_(struct IntVector* this, Int len) {
    Int *p = NULL, n;
    // check parameter
    if(this == NULL) return;
    if(len <= 0) return;
    // this vector is not allocated before, allocate new memory
    if(this->len <= 0) {
        this->data = (Int*)malloc(len * sizeof(Int));
        this->len  = len;
        return;
    }
    // new length is equal to current length, keep it not changed
    if(this->len == len) return;
    // new length is not equal to current length
    p = (Int*)calloc(len, sizeof(Int));
    n = this->len < len ? this->len : len;
    memcpy(p, this->data, n * sizeof(Int));
    free(this->data);
    this->data = p;
    this->len  = len;
}

Int IntVector_get(const struct IntVector* this, Int index) {
    if(this == NULL) return INT_MAX;
    if((index >= this->len)||(index<0)) {
        errno = EOVERFLOW;
        return INT_MAX;
    }
    return this->data[i];
}
