#include <stdlib.h>
#include <time.h>
#include <string.h>

#include "CBL_IntVector.h"

void _INT_VECTOR_level0_get_by_vec(Int* b, const Int* a, Int len_a, const Int* index, Int len_index) {
    Int i_index;
    for(i_index = 0; i_index < len_index; i_index++) b[i_index] = a[index[i_index]];
}

void _INT_VECTOR_level0_set_by_vec(Int* a, Int len_a, const Int* index, Int len_index, const Int* values) {
    Int i_index;
    for(i_index = 0; i_index < len_index; i_index++) a[index[i_index]] = values[i_index];
}

void _INT_VECTOR_level0_set_by_flags(Int* a, Int len_a, const Int* flags, Int value) {
    Int i;
    for(i = 0; i < len_a; i++) if(flags[i]) a[i] = value;
}

void _INT_VECTOR_level0_find_trues(Int* a, Int len_a, const Int* flags, Int len_flags) {
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

void _INT_VECTOR_level0_fill(Int* a, Int n, Int val) { for(Int i = 0; i < n; i++) a[i] = val; }

void _INT_VECTOR_level0_rand(Int* a, Int n, Int max) {
    srand(time(NULL));
    for(Int i = 0; i < n; i++) a[i] = (Int)rand() % (max + 1);
}

Int _INT_VECTOR_level0_sum(Int* a, Int n) {
    Int sum = 0;
    for(Int i = 0; i < n; i++) sum += a[i];
    return sum;
}

Int _INT_VECTOR_level0_prod(Int* a, Int n) {
    Int prod = 1;
    for(Int i = 0; i < n; i++) prod *= a[i];
    return prod;
}

void _INT_VECTOR_level0_cumsum(Int* a, Int n) {
    Int sum = 0;
    for(Int i = 0; i < n; i++) {
        sum += a[i];
        a[i] = sum;
    }
}

void _INT_VECTOR_level0_cumprod(Int* a, Int n) {
    Int prod = 1;
    for(Int i = 0; i < n; i++) {
        prod *= a[i];
        a[i] = prod;
    }
}

Int _INT_VECTOR_level0_min(Int* a, Int n, Int* mi) {
    Int minv = INT_MAX, i;
    *mi      = 0;
    for(i = 0; i < n; i++)
        if(a[i] < minv) {
            minv = a[i];
            *mi  = i;
        }
    return minv;
}

Int _INT_VECTOR_level0_max(Int* a, Int n, Int* mi) {
    Int maxv = INT_MIN;
    *mi      = 0;
    for(Int i = 0; i < n; i++)
        if(a[i] > maxv) {
            maxv = a[i];
            *mi  = i;
        }
    return maxv;
}

void _INT_VECTOR_level0_sort(Int* a, Int* perm, Int n) {
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

inline void IntVector_init(struct IntVector* this) {
    if(this == NULL) return;
    this->len      = 0;
    this->data     = NULL;
    this->free     = &IntVector_free;
    this->alloc    = &IntVector_alloc;
    this->fill     = &IntVector_fill;
    this->rand     = &IntVector_rand;
    this->range    = &IntVector_range;
    this->get      = &IntVector_get;
    this->set      = &IntVector_set;
    this->deepcopy = &IntVector_deepcopy;
    this->index    = &IntVector_index;
    this->slice    = &IntVector_slice;
    this->findall  = &IntVector_findall;
    this->sum      = &IntVector_sum;
    this->prod     = &IntVector_prod;
    this->cumsum   = &IntVector_cumsum;
    this->cumprod  = &IntVector_cumprod;
    this->min      = &IntVector_min;
    this->max      = &IntVector_max;
    this->sort     = &IntVector_sort;
}

void IntVector_free(struct IntVector* this) {
    if(this == NULL) return;
    if(this->data) {
        free(this->data);
        this->data = NULL;
        this->len  = 0;
    }
}

void IntVector_alloc(struct IntVector* this, Int len) {
    if(this == NULL) return;
    if(this->data) free(this->data);
    this->len  = len;
    this->data = (Int*)malloc(len * sizeof(Int));
}

void IntVector_fill(struct IntVector* this, Int value) {
    if(this == NULL) return;
    if(this->len <= 0) return;
    _INT_VECTOR_level0_fill(this->data, this->len, value);
}

void IntVector_rand(struct IntVector* this, Int max) {
    if(this == NULL) return;
    if(this->len <= 0) return;
    _INT_VECTOR_level0_rand(this->data, this->len, max);
}

void IntVector_range(struct IntVector* this, Int start, Int step, Int stop) {
    Int i, v, n;
    if(this == NULL) return;
    n = labs(stop - start) / labs(step) + 1;
    if(this->len < n) this->alloc(this, n);
    for(i = 0, v = start; i < this->len; i++) {
        this->data[i] = v;
        v += step;
        if((v - start) * (stop - v) < 0) break;
    }
}

inline Int IntVector_get(const struct IntVector* this, Int i) {
    if(this == NULL) return INT_MAX;
    if(i >= this->len) return INT_MAX;
    return this->data[i];
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
    idxmax = _INT_VECTOR_level0_max(indexs.data, indexs.len, &itmp);
    if(idxmax >= this->len) return tmp;
    tmp.alloc(&tmp, indexs.len);
    _INT_VECTOR_level0_get_by_vec(tmp.data, this->data, this->len, indexs.data, indexs.len);
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
    tmp.alloc(&tmp, n_slice);
    for(i = 0, t = start; i < n_slice; i++) {
        tmp.data[i] = this->data[t];
        t += step;
    }
    return tmp;
}

void IntVector_set(struct IntVector* this, Int i, Int value) {
    if(this == NULL) return;
    if(i >= this->len) this->alloc(this, i + 1);
    this->data[i] = value;
}

struct IntVector IntVector_findall(struct IntVector* this) {
    Int              n, i;
    struct IntVector tmp;
    IntVector_init(&tmp);
    if(this == NULL) return tmp;
    if(this->len <= 0) return tmp;
    for(i = 0, n = 0; i < this->len; i++) if(this->data[i]) n += 1;
    tmp.alloc(&tmp, n);
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
    return _INT_VECTOR_level0_sum(this->data, this->len);
}

Int IntVector_prod(struct IntVector* this) {
    if(this == NULL) return 0;
    if(this->len <= 0) return 0;
    return _INT_VECTOR_level0_prod(this->data, this->len);
}

void IntVector_cumsum(struct IntVector* this) {
    if(this == NULL) return;
    if(this->len <= 0) return;
    _INT_VECTOR_level0_cumsum(this->data, this->len);
}

void IntVector_cumprod(struct IntVector* this) {
    if(this == NULL) return;
    if(this->len <= 0) return;
    _INT_VECTOR_level0_cumprod(this->data, this->len);
}

Int IntVector_min(struct IntVector* this, Int* imin) {
    if(this == NULL) return 0;
    if(this->len <= 0) return 0;
    return _INT_VECTOR_level0_min(this->data, this->len, imin);
}

Int IntVector_max(struct IntVector* this, Int* imax) {
    if(this == NULL) return 0;
    if(this->len <= 0) return 0;
    return _INT_VECTOR_level0_max(this->data, this->len, imax);
}

void IntVector_sort(struct IntVector* this, struct IntVector* perm) {
    IntVector_init(perm);
    if(this == NULL) return;
    if(this->len <= 0) return;
    perm->alloc(perm, this->len);
    _INT_VECTOR_level0_sort(this->data, perm->data, this->len);
}
