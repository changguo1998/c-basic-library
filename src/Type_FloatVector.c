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
#include <string.h>
#include <limits.h>
#include <float.h>
#include "Module_Basic.h"

#ifdef WINDOWS
#define _CRT_RAND_S
#include <windows.h>
#include <wincrypt.h>
#endif

#include "Type_FloatVector.h"

struct FloatVectorMethods _CBL_FLOAT_VECTOR_METHODS = {
    &FloatVector_free_,
    &FloatVector_alloc_,
    &FloatVector_get,
    &FloatVector_index_,
    &FloatVector_slice_,
    &FloatVector_index_flag_,
    &FloatVector_set_,
    &FloatVector_rand_,
    &FloatVector_rand_from_,
    &FloatVector_fill_,
    &FloatVector_range_,
    &FloatVector_copy_from_,
    &FloatVector_sum,
    &FloatVector_prod,
    &FloatVector_min,
    &FloatVector_max,
    &FloatVector_argmin,
    &FloatVector_argmax,
    &FloatVector_cumsum_,
    &FloatVector_cumprod_,
    &FloatVector_sort_,
    &FloatVector_sortperm_
};

void FloatVector_free_(struct FloatVector* this) {
    if(this == NULL) return;
    if(this->data) {
        free(this->data);
        this->data = NULL;
        this->len = 0;
    }
}

void FloatVector_alloc_(struct FloatVector* this, Int len) {
    Int    n;
    Float* p = NULL;
    // check parameter
    if(this == NULL) return;
    // new length is equal to current length, keep it not changed
    if(this->len == len) return;
    if(len <= 0) error_invalid_argument("(FloatVector_alloc) len <= 0");
    // this vector is not allocated before, allocate new memory
    if(this->len <= 0) {
        this->data = (Float*)malloc(len * sizeof(Float));
        this->len = len;
        return;
    }
    // new length is not equal to current length
    p = (Float*)calloc(len, sizeof(Float));
    n = this->len < len ? this->len : len;
    memcpy(p, this->data, n * sizeof(Float));
    free(this->data);
    this->data = p;
    this->len = len;
}

Float FloatVector_get(const struct FloatVector* this, Int index) {
    if((index >= this->len) || (index < 0)) error_index_out_of_bounds("(FloatVector_get) index out of bounds");
    return this->data[index];
}

void FloatVector_index_(struct FloatVector* this, struct FloatVector src, struct IntVector indexs) {
    Int i;
    if(src.len <= 0) return;
    if(indexs.len <= 0) return;
    if(this->len != indexs.len) FloatVector_alloc_(this, indexs.len);
    for(i = 0; i < indexs.len; i++) {
        if(indexs.data[i] < 0 || indexs.data[i] >= src.len) error_index_out_of_bounds("(FloatVector_index_)");
        this->data[i] = src.data[indexs.data[i]];
    }
}

void FloatVector_slice_(struct FloatVector* this, struct FloatVector src, Int start, Int step, Int stop) {
    Int i, n;
    if(stop == VECTOR_INDEX_END) stop = src.len - 1;
    if(step == 0) error_invalid_argument("(FloatVector_slice_) step is zero");
    if(start < 0) error_invalid_argument("(FloatVector_slice_) start < 0");
    if(stop >= src.len) error_invalid_argument("(FloatVector_slice_) stop >= src.len");
    n = labs(stop - start) / labs(step) + 1;
    if(n != this->len) FloatVector_alloc_(this, n);
    for(i = 0; i < n; i++) this->data[i] = src.data[start + i * step];
}

void FloatVector_index_flag_(struct FloatVector* this, struct FloatVector src, struct IntVector flags) {
    Int i, n;
    if(src.len <= 0) error_invalid_argument("(FloatVector_index_)src is empty");
    if(src.len != flags.len) error_invalid_argument("(FloatVector_index_flag_) src.len != flags.len");
    n = IntVector_count(&flags);
    if(n != this->len) FloatVector_alloc_(this, n);
    n = 0;
    for(i = 0; i < src.len; i++)
        if(flags.data[i]) {
            this->data[n] = src.data[i];
            n += 1;
        }
}

void FloatVector_set_(struct FloatVector* this, Int index, Float value) {
    if(this->len <= 0) return;
    if(index < 0 || index >= this->len) error_index_out_of_bounds("(FloatVector_set_) index out of bounds");
    this->data[index] = value;
}

void FloatVector_rand_(struct FloatVector* this, Float min, Float max) {
    Int i;
    if(this->len <= 0) return;
    if(max <= min) return;
    unsigned long long* pf;

    pf = (unsigned long long*)malloc(this->len * sizeof(unsigned long long));
#ifdef UNIX
    FILE* fp;
    fp = fopen("/dev/urandom", "r");
    if(fp == NULL) error_file_not_exists("/dev/urandom");
    fread(pf, sizeof(unsigend long long), this->len, fp);
    fclose(fp);
#endif
#ifdef WINDOWS
    HCRYPTPROV hProv;
    CryptAcquireContext(&hProv, NULL, NULL, PROV_RSA_FULL, CRYPT_VERIFYCONTEXT);
    CryptGenRandom(hProv, this->len * sizeof(unsigned long long), (BYTE*)pf);
    CryptReleaseContext(hProv, 0);
#endif
    for(i = 0; i < this->len; i++) {
        this->data[i] = (Float)(
            (double)pf[i] /
            ((double)ULONG_LONG_MAX) *
            (max - min) + min
        );
    }
    free(pf);
}

void FloatVector_rand_from_(struct FloatVector* this, struct FloatVector value_set) {
    Int i;

    struct IntVector idxs;

    if(value_set.len <= 0) return;
    if(this->len <= 0) return;
    IntVector_new_(&idxs);
    IntVector_alloc_(&idxs, this->len);
    IntVector_rand_(&idxs, 0, value_set.len - 1);
    for(i = 0; i < this->len; i++) this->data[i] = value_set.data[idxs.data[i]];
    IntVector_free_(&idxs);
}

void FloatVector_fill_(struct FloatVector* this, Float value) {
    Int i;
    if(this->len <= 0) return;
    for(i = 0; i < this->len; i++) this->data[i] = value;
}

void FloatVector_range_(struct FloatVector* this, Float start, Float stop) {
    Int   i;
    Float step;
    if(this->len <= 0) return;
    if(this->len == 1) {
        this->data[0] = start;
        return;
    }
    step = (stop - start) / (this->len - 1);

    for(i = 0; i < this->len; i++) this->data[i] = start + i * step;
}

void FloatVector_copy_from_(struct FloatVector* this, struct FloatVector src) {
    if(src.len <= 0) {
        FloatVector_free_(this);
        return;
    }
    if(src.len != this->len) FloatVector_alloc_(this, src.len);
    memcpy(this->data, src.data, src.len * sizeof(Float));
}

Float FloatVector_sum(struct FloatVector* this) {
    Int   i;
    Float sum = 0;
    if(this->len <= 0) return 0;
    for(i = 0; i < this->len; i++) sum += this->data[i];
    return sum;
}

Float FloatVector_prod(struct FloatVector* this) {
    Int   i = 0;
    Float prod = 1.0;
    if(this->len <= 0) return 0;
    for(i = 0; i < this->len; i++) prod *= this->data[i];
    return prod;
}

Float FloatVector_min(struct FloatVector* this) {
    Int   i;
    Float min = CBL_FLOAT_MAX;
    if(this->len <= 0) return min;
    for(i = 0; i < this->len; i++) if(this->data[i] < min) min = this->data[i];
    return min;
}

Float FloatVector_max(struct FloatVector* this) {
    Int   i;
    Float max = CBL_FLOAT_MIN;
    if(this->len <= 0) return max;
    for(i = 0; i < this->len; i++) if(this->data[i] > max) max = this->data[i];
    return max;
}

Int FloatVector_argmin(struct FloatVector* this) {
    Int   i, mini = -1;
    Float minv = CBL_FLOAT_MAX;
    if(this->len <= 0) return -1;
    for(i = 0; i < this->len; i++)
        if(this->data[i] < minv) {
            minv = this->data[i];
            mini = i;
        }
    return mini;
}

Int FloatVector_argmax(struct FloatVector* this) {
    Int   i, maxi = -1;
    Float maxv = CBL_FLOAT_MIN;
    if(this->len <= 0) return -1;
    for(i = 0; i < this->len; i++)
        if(this->data[i] > maxv) {
            maxv = this->data[i];
            maxi = i;
        }
    return maxi;
}

void FloatVector_cumsum_(struct FloatVector* this, Float initial) {
    Int   i;
    Float sum;
    if(this->len <= 0) return;
    sum = initial;
    for(i = 0; i < this->len; i++) {
        this->data[i] = sum;
        sum += this->data[i];
    }
}

void FloatVector_cumprod_(struct FloatVector* this, Float initial) {
    Int   i;
    Float prod;
    if(this->len <= 0) return;
    prod = initial;
    for(i = 0; i < this->len; i++) {
        this->data[i] = prod;
        prod *= this->data[i];
    }
}

void FloatVector_sort_(struct FloatVector* this) {
    Int   i, j;
    Float tf;
    if(this->len <= 0) return;
    for(i = 0; i < this->len; i++)
        for(j = i + 1; j < this->len; j++)
            if(this->data[i] > this->data[j]) {
                tf = this->data[i];
                this->data[i] = this->data[j];
                this->data[j] = tf;
            }
}

void FloatVector_sortperm_(struct FloatVector* this, struct IntVector* perm) {
    Int   i, j, ti;
    Float tf;
    if(this->len <= 0) {
        IntVector_free_(perm);
        return;
    }
    if(this->len != perm->len) IntVector_alloc_(perm, this->len);
    for(i = 0; i < this->len; i++) perm->data[i] = i;
    for(i = 0; i < this->len; i++)
        for(j = i + 1; j < this->len; j++)
            if(this->data[i] > this->data[j]) {
                tf = this->data[i];
                this->data[i] = this->data[j];
                this->data[j] = tf;
                ti = perm->data[i];
                perm->data[i] = perm->data[j];
                perm->data[j] = ti;
            }
}
