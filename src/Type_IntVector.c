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

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#include "Type_IntVector.h"

struct IntVectorMethods _CBL_INT_VECTOR_METHODS = {
    &IntVector_free_,
    &IntVector_alloc_,
    &IntVector_get,
    &IntVector_index_,
    &IntVector_slice_,
    &IntVector_index_flag_,
    &IntVector_set_,
    &IntVector_rand_,
    &IntVector_rand_from_,
    &IntVector_fill_,
    &IntVector_range_,
    &IntVector_copy_from_,
    &IntVector_find_trues_,
    &IntVector_count,
    &IntVector_sum,
    &IntVector_prod,
    &IntVector_min,
    &IntVector_max,
    &IntVector_argmin,
    &IntVector_argmax,
    &IntVector_cumsum_,
    &IntVector_cumprod_,
    &IntVector_sort_,
    &IntVector_sortperm_
};


void IntVector_free_(struct IntVector* this) {
    if(this == NULL) return;
    if(this->data) {
        free(this->data);
        this->data = NULL;
        this->len = 0;
    }
}

void IntVector_alloc_(struct IntVector* this, Int len) {
    Int *p = NULL, n;
    // check parameter
    if(this == NULL) return;
    // new length is equal to current length, keep it not changed
    if(this->len == len) return;
    if(len <= 0) error_invalid_argument("(IntVector_alloc) len <= 0");
    // this vector is not allocated before, allocate new memory
    if(this->len <= 0) {
        this->data = (Int*)malloc(len * sizeof(Int));
        this->len = len;
        return;
    }
    // new length is not equal to current length
    p = (Int*)calloc(len, sizeof(Int));
    n = this->len < len ? this->len : len;
    memcpy(p, this->data, n * sizeof(Int));
    free(this->data);
    this->data = p;
    this->len = len;
}

Int IntVector_get(const struct IntVector* this, Int index) {
    if((index >= this->len) || (index < 0)) error_index_out_of_bounds("(IntVector_get) index out of bounds");
    return this->data[index];
}

void IntVector_index_(struct IntVector* this, struct IntVector src, struct IntVector indexs) {
    Int i;
    if(src.len <= 0) return;
    if(indexs.len <= 0) return;
    if(this->len != indexs.len) IntVector_alloc_(this, indexs.len);
    for(i = 0; i < indexs.len; i++) {
        if(indexs.data[i] < 0 || indexs.data[i] >= src.len) error_index_out_of_bounds("(IntVector_index_)");
        this->data[i] = src.data[indexs.data[i]];
    }
}

void IntVector_slice_(struct IntVector* this, struct IntVector src, Int start, Int step, Int stop) {
    Int i, n;
    if(stop == VECTOR_INDEX_END) stop = src.len - 1;
    if(step == 0) error_invalid_argument("(IntVector_slice_) step is zero");
    if(start < 0) error_invalid_argument("(IntVector_slice_) start < 0");
    if(stop >= src.len) error_invalid_argument("(IntVector_slice_) stop >= src.len");
    n = labs(stop - start) / labs(step) + 1;
    if(n != this->len) IntVector_alloc_(this, n);
    for(i = 0; i < n; i++) this->data[i] = src.data[start + i * step];
}

void IntVector_index_flag_(struct IntVector* this, struct IntVector src, struct IntVector flags) {
    Int i, n;
    if(src.len <= 0) error_invalid_argument("(IntVector_index_)src is empty");
    if(src.len != flags.len) error_invalid_argument("(IntVector_index_flag_) src.len != flags.len");
    n = IntVector_count(&flags);
    if(n != this->len) IntVector_alloc_(this, n);
    n = 0;
    for(i = 0; i < src.len; i++)
        if(flags.data[i]) {
            this->data[n] = src.data[i];
            n += 1;
        }
}

void IntVector_set_(struct IntVector* this, Int index, Int value) {
    if(this->len <= 0) return;
    if(index < 0 || index >= this->len) error_index_out_of_bounds("(IntVector_set_) index out of bounds");
    this->data[index] = value;
}

void IntVector_rand_(struct IntVector* this, Int min, Int max) {
    Int i;
    if(this->len <= 0) return;
    if(max <= min) return;

#ifdef UNIX
    FILE* fp;
    fp = fopen("/dev/urandom", "r");
    if(fp == NULL) error_file_not_exists("/dev/urandom");

    fread(this->data, sizeof(Int), this->len, fp);
    fclose(fp);
#endif
#ifdef WINDOWS
    for(i = 0; i < this->len; i++) this->data[i] = rand();
#endif
    for(i = 0; i < this->len; i++) this->data[i] = this->data[i] % (max - min + 1) + min;

}

void IntVector_rand_from_(struct IntVector* this, struct IntVector value_set) {
    Int              i;
    struct IntVector idxs;

    if(value_set.len <= 0) return;
    if(this->len <= 0) return;
    IntVector_new_(&idxs);
    IntVector_alloc_(&idxs, this->len);
    IntVector_rand_(&idxs, 0, value_set.len - 1);
    for(i = 0; i < this->len; i++) this->data[i] = value_set.data[idxs.data[i]];
    IntVector_free_(&idxs);
}

void IntVector_fill_(struct IntVector* this, Int value) {
    Int i;
    if(this->len <= 0) return;
    for(i = 0; i < this->len; i++) this->data[i] = value;
}

void IntVector_range_(struct IntVector* this, Int start, Int step, Int stop) {
    Int i;
    if(step == 0)
        if(start > stop) step = -1;
        else if(start < stop) step = 1;

    for(i = 0; i < this->len; i++) this->data[i] = start + i * step;
}

void IntVector_copy_from_(struct IntVector* this, struct IntVector src) {
    if(src.len <= 0) {
        IntVector_free_(this);
        return;
    }
    if(src.len != this->len) IntVector_alloc_(this, src.len);
    memcpy(this->data, src.data, src.len * sizeof(Int));
}

void IntVector_find_trues_(struct IntVector* this, struct IntVector flags) {
    Int i, n;
    if(flags.len <= 0) {
        IntVector_free_(this);
        return;
    }
    n = IntVector_count(&flags);
    if(n != this->len) IntVector_alloc_(this, n);
    n = 0;
    for(i = 0; i < flags.len; i++)
        if(flags.data[i]) {
            this->data[n] = i;
            n += 1;
        }
}

Int IntVector_count(struct IntVector* this) {
    Int i = 0, n = 0;
    if(this->len <= 0) return 0;
    for(; i < this->len; i++) if(this->data[i]) n += 1;
    return n;
}

Int IntVector_sum(struct IntVector* this) {
    Int sum = 0, i;
    if(this->len <= 0) return 0;
    for(i = 0; i < this->len; i++) sum += this->data[i];
    return sum;
}

Int IntVector_prod(struct IntVector* this) {
    Int prod = 0, i = 0;
    if(this->len <= 0) return 0;
    for(i = 0; i < this->len; i++) prod *= this->data[i];
    return prod;
}

Int IntVector_min(struct IntVector* this) {
    Int min = INT_MAX, i;
    if(this->len <= 0) return min;
    for(i = 0; i < this->len; i++) if(this->data[i] < min) min = this->data[i];
    return min;
}

Int IntVector_max(struct IntVector* this) {
    Int max = INT_MIN, i;
    if(this->len <= 0) return max;
    for(i = 0; i < this->len; i++) if(this->data[i] > max) max = this->data[i];
    return max;
}

Int IntVector_argmin(struct IntVector* this) {
    Int minv = INT_MAX, i, mini = -1;
    if(this->len <= 0) return -1;
    for(i = 0; i < this->len; i++)
        if(this->data[i] < minv) {
            minv = this->data[i];
            mini = i;
        }
    return mini;
}

Int IntVector_argmax(struct IntVector* this) {
    Int maxv = INT_MIN, i, maxi = -1;
    if(this->len <= 0) return -1;
    for(i = 0; i < this->len; i++)
        if(this->data[i] > maxv) {
            maxv = this->data[i];
            maxi = i;
        }
    return maxi;
}

void IntVector_cumsum_(struct IntVector* this, Int initial) {
    Int i, sum;
    if(this->len <= 0) return;
    sum = initial;
    for(i = 0; i < this->len; i++) {
        this->data[i] = sum;
        sum += this->data[i];
    }
}

void IntVector_cumprod_(struct IntVector* this, Int initial) {
    Int i, prod;
    if(this->len <= 0) return;
    prod = initial;
    for(i = 0; i < this->len; i++) {
        this->data[i] = prod;
        prod *= this->data[i];
    }
}

void IntVector_sort_(struct IntVector* this) {
    Int i, j, t;
    if(this->len <= 0) return;
    for(i = 0; i < this->len; i++)
        for(j = i + 1; j < this->len; j++)
            if(this->data[i] > this->data[j]) {
                t = this->data[i];
                this->data[i] = this->data[j];
                this->data[j] = t;
            }
}

void IntVector_sortperm_(struct IntVector* this, struct IntVector* perm) {
    Int i, j, t;
    if(this->len <= 0) {
        IntVector_free_(perm);
        return;
    }
    if(this->len != perm->len) IntVector_alloc_(perm, this->len);
    for(i = 0; i < this->len; i++) perm->data[i] = i;
    for(i = 0; i < this->len; i++)
        for(j = i + 1; j < this->len; j++)
            if(this->data[i] > this->data[j]) {
                t = this->data[i];
                this->data[i] = this->data[j];
                this->data[j] = t;
                t = perm->data[i];
                perm->data[i] = perm->data[j];
                perm->data[j] = t;
            }
}
