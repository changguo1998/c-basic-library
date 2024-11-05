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
#include <stdarg.h>
#include <string.h>
#include "Module_Basic.h"
#include "Type_Part_math_basic.h"
#include "Type_IntVector.h"
#include "Type_FloatVector.h"

#include <math.h>

struct FloatVectorMethods _CBL_FLOAT_VECTOR_METHODS = {
    &FloatVector_free_,
    &FloatVector_alloc_,
    &FloatVector_get,
    &FloatVector_index_,
    &FloatVector_slice_,
    &FloatVector_index_flag_,
    &FloatVector_set_,
    &FloatVector_setas_,
    &FloatVector_vcat_,
    &FloatVector_rand_,
    &FloatVector_rand_from_,
    &FloatVector_fill_,
    &FloatVector_range_,
    &FloatVector_copy_from_,
    &FloatVector_sum,
    &FloatVector_mean,
    &FloatVector_var,
    &FloatVector_std,
    &FloatVector_prod,
    &FloatVector_min,
    &FloatVector_max,
    &FloatVector_argmin,
    &FloatVector_argmax,
    &FloatVector_cumsum_,
    &FloatVector_cumprod_,
    &FloatVector_sort_,
    &FloatVector_sortperm_,
    &FloatVector_dot,
    &FloatVector_norm
};

void FloatVector_free_(struct FloatVector* this) {
    if(this == NULL) return;
    if(this->data) {
        free(this->data);
        this->data = NULL;
    }
    this->len = 0;
}

void FloatVector_alloc_(struct FloatVector* this, Int len) {
    Float* p = NULL;
    Int    n;
    if(this == NULL) return;
    if(this->len == len) return;
    if(len <= 0) {
        FloatVector_free_(this);
        return;
    }
    if(this->len <= 0) {
        this->data = (Float*)calloc(len, sizeof(Float));
        this->len = len;
        return;
    }
    p = (Float*)calloc(len, sizeof(Float));
    n = this->len < len ? this->len : len;
    memcpy(p, this->data, n * sizeof(Float));
    free(this->data);
    this->data = p;
    this->len = len;
}

Float FloatVector_get(const struct FloatVector* this, Int index) {
    if((index >= this->len) || (index < 0))
        error_index_out_of_bounds("(Vector_get) index out of bounds");
    return this->data[index];
}

void FloatVector_index_(struct FloatVector* this, struct FloatVector src, struct IntVector indexs) {
    Int    i;
    Float* buf;
    if(indexs.len <= 0) return;
    if(src.len <= 0) return;
    buf = (Float*)calloc(indexs.len, sizeof(Float));
    for(i = 0; i < indexs.len; i++) {
        if(indexs.data[i] < 0 || indexs.data[i] >= src.len)
            error_index_out_of_bounds("(Vector_index_) index out of bounds");
        buf[i] = src.data[indexs.data[i]];
    }

    FloatVector_alloc_(this, indexs.len);
    memcpy(this->data, buf, indexs.len * sizeof(Float));
    free(buf);
}

void FloatVector_slice_(struct FloatVector* this, struct FloatVector src, Int start, Int step, Int stop) {
    Int    i, n;
    Float* buf;
    if(stop == VECTOR_INDEX_END) stop = src.len - 1;
    if(step == 0) error_invalid_argument("(Vector_slice_) step is 0");
    if(start < 0) error_invalid_argument("(Vector_slice_) start < 0");
    if(start >= src.len) error_invalid_argument("(Vector_slice_) start >= this->len");
    if(stop < 0) error_invalid_argument("(Vector_slice_) stop < 0");
    if(stop >= src.len) error_invalid_argument("(IntVector_slice_) stop >= src.len");
    n = _bm_abs_int(stop - start) / _bm_abs_int(step) + 1;
    buf = (Float*)calloc(n, sizeof(Float));

    for(i = 0; i < n; i++) buf[i] = src.data[start + i * step];

    FloatVector_alloc_(this, n);
    memcpy(this->data, buf, n * sizeof(Float));
    free(buf);
}

void FloatVector_index_flag_(struct FloatVector* this, struct FloatVector src, struct IntVector flags) {
    Int    i, j, n;
    Float* buf;
    if(src.len != flags.len) error_invalid_argument("(Vector_index_flag_) src.len != flags.len");
    if(src.len <= 0) {
        FloatVector_free_(this);
        return;
    }
    n = IntVector_count(&flags);
    if(n <= 0) {
        FloatVector_free_(this);
        return;
    }
    buf = (Float*)calloc(n, sizeof(Float));
    j = 0;
    for(i = 0; i < src.len; i++)
        if(flags.data[i]) {
            buf[j] = src.data[i];
            j += 1;
        }
    FloatVector_alloc_(this, n);
    memcpy(this->data, buf, n * sizeof(Float));
    free(buf);
}

void FloatVector_set_(struct FloatVector* this, Int index, Float value) {
    if(this->len <= 0) return;
    if(index < 0 || index >= this->len) error_index_out_of_bounds("(FloatVector_set_) index out of bounds");
    this->data[index] = value;
}

void FloatVector_setas_(struct FloatVector* this, Int n, ...) {
    va_list ap;
    Int     i;
    va_start(ap, n);
    FloatVector_alloc_(this, n);
    for(i = 0; i < n; i++) this->data[i] = va_arg(ap, _VECTOR_N_VA_ARG_TYPE_Float);
    va_end(ap);
}

void FloatVector_vcat_(struct FloatVector* this, Int n, ...) {
    Int     i, j, k, row;
    va_list ap;
    Float*  buf;

    struct FloatVector* pvec = NULL;
    va_start(ap, n);
    pvec = (struct FloatVector*)malloc(n * sizeof(struct FloatVector));
    row = 0;
    for(i = 0; i < n; i++) {
        pvec[i] = va_arg(ap, struct FloatVector);
        row += pvec[i].len;
    }
    va_end(ap);

    if(row <= 0) {
        FloatVector_free_(this);
        return;
    }
    buf = (Float*)calloc(row, sizeof(Float));
    k = 0;
    for(i = 0; i < n; i++) {
        for(j = 0; j < pvec[i].len; j++) {
            buf[k] = pvec[i].data[j];
            k += 1;
        }
    }
    FloatVector_alloc_(this, row);
    memcpy(this->data, buf, row * sizeof(Float));
    free(buf);
    free(pvec);
}

void FloatVector_rand_(struct FloatVector* this, Float min, Float max) {
    Int i;
    if(this->len <= 0) return;
    if(max <= min) error_invalid_argument("(Vector_rand_) min >= max");
    unsigned long long* pf = NULL;
    pf = (unsigned long long*)malloc(this->len * sizeof(unsigned long long));
    _bm_rand_ull_(pf, this->len);
    for(i = 0; i < this->len; i++) this->data[i] = _bm_convert_ull_to_Float(pf[i], min, max);
    free(pf);
}

void FloatVector_rand_from_(struct FloatVector* this, struct FloatVector value_set) {
    Int    i;
    Float* buf;
    CBL_DECLARE_VARS(IntVector, 1, idxs);
    if(value_set.len <= 0) return;
    if(this->len <= 0) return;
    buf = (Float*)calloc(this->len, sizeof(Float));
    IntVector_alloc_(&idxs, this->len);
    IntVector_rand_(&idxs, 0, value_set.len - 1);
    for(i = 0; i < this->len; i++) buf[i] = value_set.data[idxs.data[i]];
    IntVector_free_(&idxs);
    memcpy(this->data, buf, this->len * sizeof(Float));
    free(buf);
}

void FloatVector_fill_(struct FloatVector* this, Float value) {
    Int i;
    if(this->len <= 0) return;
    for(i = 0; i < this->len; i++) this->data[i] = value;
}

void FloatVector_range_(struct FloatVector* this, Float start, Float step, Float stop) {
    Int i, n;
    if(step == 0) error_invalid_argument("(FloatVector_range_) step == 0");
    if(start == stop) error_invalid_argument("(FloatVector_range_) start == stop");
    n = (stop - start) / step + 1;
    if(n <= 0) return;
    FloatVector_alloc_(this, n);
    if(n == 1) {
        this->data[0] = start;
        return;
    }
    for(i = 0; i < this->len; i++) this->data[i] = start + i * step;
}

void FloatVector_copy_from_(struct FloatVector* this, struct FloatVector src) {
    if(src.len <= 0) {
        FloatVector_free_(this);
        return;
    }
    if(this->data == src.data) return;
    if(src.len != this->len) FloatVector_alloc_(this, src.len);
    memcpy(this->data, src.data, src.len * sizeof(Float));
}

Float FloatVector_sum(const struct FloatVector* this) {
    Int   i;
    Float sum = 0;
    if(this->len <= 0) return sum;
    for(i = 0; i < this->len; i++) sum += this->data[i];
    return sum;
}

Float FloatVector_mean(const struct FloatVector* this) { return FloatVector_sum(this) / this->len; }

Float FloatVector_var(const struct FloatVector* this) {
    Float s, m;
    Int   i;

    m = FloatVector_mean(this);
    s = 0;
    for(i = 0; i < this->len; i++) s += (this->data[i] - m) * (this->data[i] - m);
    return s / this->len;
}

Float FloatVector_std(const struct FloatVector* this) { return _bm_sqrt(FloatVector_var(this)); }

Float FloatVector_prod(const struct FloatVector* this) {
    Int   i = 0;
    Float prod = 1;
    if(this->len <= 0) return 0;
    for(i = 0; i < this->len; i++) prod *= this->data[i];
    return prod;
}

Float FloatVector_min(const struct FloatVector* this) {
    Int   i;
    Float min = CBL_FLOAT_MAX;
    if(this->len <= 0) return min;
    for(i = 0; i < this->len; i++) min = (this->data[i] < min) ? this->data[i] : min;
    return min;
}

Float FloatVector_max(const struct FloatVector* this) {
    Int   i;
    Float max = CBL_FLOAT_MIN;
    if(this->len <= 0) return max;
    for(i = 0; i < this->len; i++) max = (max < this->data[i]) ? this->data[i] : max;
    return max;
}

Int FloatVector_argmin(const struct FloatVector* this) {
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

Int FloatVector_argmax(const struct FloatVector* this) {
    Int   i, maxi;
    Float maxv = CBL_FLOAT_MIN;
    maxi = -1;
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
    Float sum = initial;
    for(i = 0; i < this->len; i++) {
        sum += this->data[i];
        this->data[i] = sum;
    }
}

void FloatVector_cumprod_(struct FloatVector* this, Float initial) {
    Int   i;
    Float prod = initial;
    for(i = 0; i < this->len; i++) {
        prod *= this->data[i];
        this->data[i] = prod;
    }
}

void FloatVector_sort_(struct FloatVector* this) {
    Int   i, j;
    Float tv;
    for(i = 0; i < this->len; i++)
        for(j = i + 1; j < this->len; j++)
            if(this->data[i] > this->data[j]) {
                tv = this->data[i];
                this->data[i] = this->data[j];
                this->data[j] = tv;
            }
}

void FloatVector_sortperm_(struct FloatVector* this, struct IntVector* perm) {
    Int   i, j, ti;
    Float tv;
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

Float FloatVector_dot(const struct FloatVector* this, struct FloatVector b) {
    Int   i;
    Float sum = 0;
    if(this->len != b.len) error_invalid_argument("(Vector_dot) length mismatch");
    for(i = 0; i < this->len; i++) sum += this->data[i] * b.data[i];
    return sum;
}

Float FloatVector_norm(const struct FloatVector* this, Int order) {
    Float v = 0.0;
    Int   i;
    if(this->len <= 0) return v;
    if(order < 0) error_invalid_argument("(FloatVector_norm) order < 0");
    if(order == 0) return this->len;
    if(order == 1) {
        v = 0.0;
        for(i = 0; i < this->len; i++) v += _bm_abs_float(this->data[i]);
        return v;
    }
    if(order == 2) {
        v = 0.0;
        for(i = 0; i < this->len; i++) v += this->data[i] * this->data[i];
        return _bm_sqrt(v);
    }
    if(order == CBL_INT_MAX) return FloatVector_max(this);
    v = 0.0;
    for(i = 0; i < this->len; i++) v += pow(this->data[i], order);
    return _bm_n_root(v, order);
}
