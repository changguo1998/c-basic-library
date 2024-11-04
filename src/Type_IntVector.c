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
#include <string.h>
#include <stdarg.h>
#include "Module_Basic.h"
#include "Type_Part_math_basic.h"
#include "Type_IntVector.h"

struct IntVectorMethods _CBL_INT_VECTOR_METHODS = {
    &IntVector_free_,
    &IntVector_alloc_,
    &IntVector_get,
    &IntVector_index_,
    &IntVector_slice_,
    &IntVector_count,
    &IntVector_index_flag_,
    &IntVector_set_,
    &IntVector_setas_,
    &IntVector_vcat_,
    &IntVector_rand_,
    &IntVector_rand_from_,
    &IntVector_fill_,
    &IntVector_range_,
    &IntVector_copy_from_,
    &IntVector_find_trues_,
    &IntVector_sum,
    &IntVector_prod,
    &IntVector_min,
    &IntVector_max,
    &IntVector_argmin,
    &IntVector_argmax,
    &IntVector_cumsum_,
    &IntVector_cumprod_,
    &IntVector_sort_,
    &IntVector_sortperm_,
    &IntVector_dot
};

void IntVector_free_(struct IntVector* this) {
    if(this == NULL) return;
    if(this->data) {
        free(this->data);
        this->data = NULL;
    }
    this->len = 0;
}

void IntVector_alloc_(struct IntVector* this, Int len) {
    Int* p = NULL;
    Int  n;
    if(this == NULL) return;
    if(this->len == len) return;
    if(len <= 0) {
        IntVector_free_(this);
        return;
    }
    if(this->len <= 0) {
        this->data = (Int*)calloc(len, sizeof(Int));
        this->len = len;
        return;
    }
    p = (Int*)calloc(len, sizeof(Int));
    n = this->len < len ? this->len : len;
    memcpy(p, this->data, n * sizeof(Int));
    free(this->data);
    this->data = p;
    this->len = len;
}

Int IntVector_get(const struct IntVector* this, Int index) {
    if((index >= this->len) || (index < 0))
        error_index_out_of_bounds("(IntVector_get) index out of bounds");
    return this->data[index];
}

void IntVector_index_(struct IntVector* this, struct IntVector src, struct IntVector indexs) {
    Int i;
    if(indexs.len <= 0) return;
    IntVector_alloc_(this, indexs.len);
    if(src.len <= 0) return;
    for(i = 0; i < indexs.len; i++) {
        if(indexs.data[i] < 0 || indexs.data[i] >= src.len)
            error_index_out_of_bounds("(IntVector_index_) index out of bounds");
        this->data[i] = src.data[indexs.data[i]];
    }
}

void IntVector_slice_(struct IntVector* this, struct IntVector src, Int start, Int step, Int stop) {
    Int i, n;
    if(stop == VECTOR_INDEX_END) stop = src.len - 1;
    if(step == 0) error_invalid_argument("(IntVector_slice_) step is 0");
    if(start < 0) error_invalid_argument("(IntVector_slice_) start < 0");
    if(start >= src.len) error_invalid_argument("(Vector_slice_) start >= this->len");
    if(stop < 0) error_invalid_argument("(IntVector_slice_) stop < 0");
    if(stop >= src.len) error_invalid_argument("(IntVector_slice_) stop >= src.len");
    n = _bm_abs_int(stop - start) / _bm_abs_int(step) + 1;
    IntVector_alloc_(this, n);
    for(i = 0; i < n; i++) this->data[i] = src.data[start + i * step];
}

Int IntVector_count(const struct IntVector* this) {
    Int i, n = 0;
    if(this->len <= 0) return 0;
    for(i = 0; i < this->len; i++) if(this->data[i]) n += 1;
    return n;
}

void IntVector_index_flag_(struct IntVector* this, struct IntVector src, struct IntVector flags) {
    Int i, n;
    if(src.len != flags.len) error_invalid_argument("(IntVector_index_flag_) src.len != flags.len");
    if(src.len <= 0) {
        IntVector_free_(this);
        return;
    }
    n = IntVector_count(&flags);
    IntVector_alloc_(this, n);
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

void IntVector_setas_(struct IntVector* this, Int n, ...) {
    va_list ap;
    Int     i;
    va_start(ap, n);
    IntVector_alloc_(this, n);
    for(i = 0; i < n; i++) this->data[i] = va_arg(ap, _VECTOR_N_VA_ARG_TYPE_Int);
    va_end(ap);
}

void IntVector_vcat_(struct IntVector* this, Int n, ...) {
    Int               i, j, row;
    va_list           ap;
    struct IntVector* pvec = NULL;
    va_start(ap, n);
    pvec = (struct IntVector*)malloc(n * sizeof(struct IntVector));
    row = 0;
    for(i = 0; i < n; i++) {
        pvec[i] = va_arg(ap, struct IntVector);
        row += pvec[i].len;
    }
    IntVector_alloc_(this, row);
    row = 0;
    for(i = 0; i < n; i++) {
        for(j = 0; j < pvec[i].len; j++) {
            this->data[row] = pvec[i].data[j];
            row += 1;
        }
    }
    va_end(ap);
    free(pvec);
}

void IntVector_rand_(struct IntVector* this, Int min, Int max) {
    Int i;
    if(this->len <= 0) return;
    if(max <= min) error_invalid_argument("(IntVector_rand_) min >= max");
    unsigned long long* pf = NULL;
    pf = (unsigned long long*)malloc(this->len * sizeof(unsigned long long));
    _bm_rand_ull_(pf, this->len);
    for(i = 0; i < this->len; i++) this->data[i] = _bm_convert_ull_to_Int(pf[i], min, max);
    free(pf);
}

void IntVector_rand_from_(struct IntVector* this, struct IntVector value_set) {
    Int i;
    CBL_DECLARE_VARS(IntVector, 1, idxs);
    if(value_set.len <= 0) return;
    if(this->len <= 0) return;
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
    if(this->len <= 0) return;
    if(this->len == 1) {
        this->data[0] = start;
        return;
    }
    if(step == 0)
        if(start != stop) step = (stop - start) / (this->len - 1);
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

Int IntVector_sum(const struct IntVector* this) {
    Int i;
    Int sum = 0;
    if(this->len <= 0) return sum;
    for(i = 0; i < this->len; i++) sum += this->data[i];
    return sum;
}

Int IntVector_prod(const struct IntVector* this) {
    Int i = 0;
    Int prod = 1;
    if(this->len <= 0) return 0;
    for(i = 0; i < this->len; i++) prod *= this->data[i];
    return prod;
}

Int IntVector_min(const struct IntVector* this) {
    Int i;
    Int min = _VECTOR_N_VA_ARG_MAX_Int;
    if(this->len <= 0) return min;
    for(i = 0; i < this->len; i++) min = (this->data[i] < min) ? this->data[i] : min;
    return min;
}

Int IntVector_max(const struct IntVector* this) {
    Int i;
    Int max = _VECTOR_N_VA_ARG_MIN_Int;
    if(this->len <= 0) return max;
    for(i = 0; i < this->len; i++) max = (max < this->data[i]) ? this->data[i] : max;
    return max;
}

Int IntVector_argmin(const struct IntVector* this) {
    Int i, mini = -1;
    Int minv = _VECTOR_N_VA_ARG_MAX_Int;
    if(this->len <= 0) return -1;
    for(i = 0; i < this->len; i++)
        if(this->data[i] < minv) {
            minv = this->data[i];
            mini = i;
        }
    return mini;
}

Int IntVector_argmax(const struct IntVector* this) {
    Int i, maxi;
    Int maxv = _VECTOR_N_VA_ARG_MIN_Int;
    maxi = -1;
    if(this->len <= 0) return -1;
    for(i = 0; i < this->len; i++)
        if(this->data[i] > maxv) {
            maxv = this->data[i];
            maxi = i;
        }
    return maxi;
}

void IntVector_cumsum_(struct IntVector* this, Int initial) {
    Int i;
    Int sum = initial;
    for(i = 0; i < this->len; i++) {
        sum += this->data[i];
        this->data[i] = sum;
    }
}

void IntVector_cumprod_(struct IntVector* this, Int initial) {
    Int i;
    Int prod = initial;
    for(i = 0; i < this->len; i++) {
        prod *= this->data[i];
        this->data[i] = prod;
    }
}

void IntVector_sort_(struct IntVector* this) {
    Int i, j;
    Int tv;
    for(i = 0; i < this->len; i++)
        for(j = i + 1; j < this->len; j++)
            if(this->data[i] > this->data[j]) {
                tv = this->data[i];
                this->data[i] = this->data[j];
                this->data[j] = tv;
            }
}

void IntVector_sortperm_(struct IntVector* this, struct IntVector* perm) {
    Int i, j, ti;
    Int tv;
    if(this->len <= 0) return;
    IntVector_alloc_(perm, this->len);
    IntVector_range_(perm, 0, 1, this->len - 1);
    for(i = 0; i < this->len; i++)
        for(j = i + 1; j < this->len; j++)
            if(this->data[i] > this->data[j]) {
                tv = this->data[i];
                this->data[i] = this->data[j];
                this->data[j] = tv;
                ti = perm->data[i];
                perm->data[i] = perm->data[j];
                perm->data[j] = ti;
            }
}

Int IntVector_dot(const struct IntVector* this, struct IntVector b) {
    Int i;
    Int sum = 0;
    if(this->len != b.len) error_invalid_argument("(IntVector_dot) length mismatch");
    for(i = 0; i < this->len; i++) sum += this->data[i] * b.data[i];
    return sum;
}
