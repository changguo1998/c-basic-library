// MIT License
//
// Copyright (c) 2024 Chang Guo
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.
//

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
    &IntVector_filter_,
    &IntVector_push_,
    &IntVector_isequal,
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
    &IntVector_dot,
    &IntVector_coord_linear,
    &IntVector_coord_cartesian_
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
    if(this == NULL) return;
    if(this->len == len) return;

    IntVector_free_(this);
    if(len <= 0) return;

    this->data = (Int*)calloc(len, sizeof(Int));
    this->len = len;
}

Int IntVector_get(const struct IntVector* this, Int index) {
    if((index >= this->len) || (index < 0))
        error_index_out_of_bounds("(IntVector_get) index out of bounds");
    return this->data[index];
}

void IntVector_index_(struct IntVector* this, struct IntVector indexs) {
    Int i, *buf;

    if(indexs.len <= 0) {
        IntVector_free_(this);
        return;
    }
    for(i = 0; i < indexs.len; i++)
        if(indexs.data[i] < 0 || indexs.data[i] >= this->len)
            error_index_out_of_bounds("(IntVector_index_) index out of bounds");

    buf = (Int*)calloc(indexs.len, sizeof(Int));
    for(i = 0; i < indexs.len; i++) buf[i] = this->data[indexs.data[i]];

    IntVector_free_(this);
    this->len = indexs.len;
    this->data = buf;
}

void IntVector_slice_(struct IntVector* this, Int start, Int step, Int stop) {
    Int i, n, *buf;

    if(stop == VECTOR_INDEX_END) stop = this->len - 1;
    if(step == 0) error_invalid_argument("(IntVector_slice_) step is 0");
    if(start < 0) error_invalid_argument("(IntVector_slice_) start < 0");
    if(start >= this->len) error_invalid_argument("(Vector_slice_) start >= this->len");
    if(stop < 0) error_invalid_argument("(IntVector_slice_) stop < 0");
    if(stop >= this->len) error_invalid_argument("(IntVector_slice_) stop >= this->len");

    n = (stop - start) / step + 1;
    if(n <= 0) {
        IntVector_free_(this);
        return;
    }
    if(n == this->len) return;
    buf = (Int*)calloc(n, sizeof(Int));
    for(i = 0; i < n; i++) buf[i] = this->data[start + i * step];

    IntVector_free_(this);
    this->len = n;
    this->data = buf;
}

Int IntVector_count(const struct IntVector* this) {
    Int i, n = 0;
    if(this->len <= 0) return 0;
    for(i = 0; i < this->len; i++) if(this->data[i]) n += 1;
    return n;
}

void IntVector_index_flag_(struct IntVector* this, struct IntVector flags) {
    Int i, j, n, *buf;

    if(this->len != flags.len) error_invalid_argument("(IntVector_index_flag_) src.len != flags.len");
    if(this->len <= 0) return;

    n = IntVector_count(&flags);
    if(n <= 0) {
        IntVector_free_(this);
        return;
    }
    if(n == this->len) return;
    buf = (Int*)calloc(n, sizeof(Int));
    j = 0;
    for(i = 0; i < this->len; i++)
        if(flags.data[i]) {
            buf[j] = this->data[i];
            j += 1;
        }

    IntVector_free_(this);
    this->len = n;
    this->data = buf;
}

void IntVector_set_(struct IntVector* this, Int index, Int value) {
    if(this->len <= 0) error_invalid_argument("(IntVector_set_) this->len <= 0");
    if(index < 0 || index >= this->len) error_index_out_of_bounds("(IntVector_set_) index out of bounds");
    this->data[index] = value;
}

void IntVector_setas_(struct IntVector* this, Int n, ...) {
    va_list ap;
    Int     i;

    if(n <= 0) error_invalid_argument("(IntVector_setas_) n <= 0");
    IntVector_alloc_(this, n);

    va_start(ap, n);
    for(i = 0; i < n; i++) this->data[i] = va_arg(ap, _VECTOR_N_VA_ARG_TYPE_Int);
    va_end(ap);
}

void IntVector_vcat_(struct IntVector* this, Int n, ...) {
    Int     i, j, k, row, *buf;
    va_list ap;

    struct IntVector* pvec = NULL;

    if(n <= 0) return;

    // load input data
    pvec = (struct IntVector*)malloc(n * sizeof(struct IntVector));
    va_start(ap, n);
    for(i = 0; i < n; i++) pvec[i] = va_arg(ap, struct IntVector);
    va_end(ap);

    // count buffer size
    row = this->len;
    for(i = 0; i < n; i++) row += pvec[i].len;

    if(row == this->len) {
        free(pvec);
        return;
    }
    if(row <= 0) {
        free(pvec);
        IntVector_free_(this);
        return;
    }

    // collect data
    buf = (Int*)calloc(row, sizeof(Int));
    for(k = 0; k < this->len; k++) buf[k] = this->data[k];
    for(i = 0; i < n; i++) {
        for(j = 0; j < pvec[i].len; j++) {
            buf[k] = pvec[i].data[j];
            k += 1;
        }
    }

    IntVector_free_(this);
    this->len = row;
    this->data = buf;
    free(pvec);
}

void IntVector_rand_(struct IntVector* this, Int a, Int b) {
    Int i, min, max;

    unsigned long long* pf = NULL;

    if(this->len <= 0) return;
    if(a == b) {
        IntVector_fill_(this, a);
        return;
    }
    min = (a < b) ? a : b;
    max = (a > b) ? a : b;
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
    if(this->data == value_set.data) error_invalid_argument("(IntVector_rand_from_) this->data == value_set.data");

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
    Int i, n;
    if(this->len <= 0) return;
    if(start == stop) error_invalid_argument("(IntVector_range_) start == stop");
    if(this->len == 1) {
        this->data[0] = start;
        return;
    }
    if(step == 0) step = (stop - start) / (this->len - 1);
    if(step == 0) if(start > stop) step = -1; else step = 1;
    n = (stop - start) / step + 1;
    n = (n > this->len) ? this->len : n;
    for(i = 0; i < n; i++) this->data[i] = start + i * step;
}

void IntVector_copy_from_(struct IntVector* this, struct IntVector src) {
    if(this->data == src.data) error_invalid_argument("(IntVector_copy_from_) data == src.data: copy from self");
    if(src.len <= 0) {
        IntVector_free_(this);
        return;
    }
    IntVector_alloc_(this, src.len);
    memcpy(this->data, src.data, src.len * sizeof(Int));
}

void IntVector_find_trues_(struct IntVector* this, struct IntVector flags) {
    Int i, j, n, *buf;
    if(flags.len <= 0) {
        IntVector_free_(this);
        return;
    }
    n = IntVector_count(&flags);
    if(n <= 0) {
        IntVector_free_(this);
        return;
    }
    if(n == flags.len) {
        IntVector_alloc_(this, flags.len);
        IntVector_range_(this, 0, 1, flags.len - 1);
        return;
    }
    buf = (Int*)calloc(n, sizeof(Int));
    j = 0;
    for(i = 0; i < flags.len; i++)
        if(flags.data[i]) {
            buf[j] = i;
            j += 1;
        }
    IntVector_free_(this);
    this->len = n;
    this->data = buf;
}

void IntVector_filter_(struct IntVector* this, i_Func_i isOK) {
    Int i, j, n, *buf=NULL;

    if(this->len <= 0) return;
    n = 0;
    for(i = 0; i < this->len; i++) if(isOK(this->data[i])) n += 1;
    if(n <= 0) {
        IntVector_free_(this);
        return;
    }
    if(n == this->len) return;
    buf = (Int*)calloc(n, sizeof(Int));
    j = 0;
    for(i = 0; i < this->len; i++) if(isOK(this->data[i])) {
        buf[j] = this->data[i];
        j += 1;
    }
    IntVector_free_(this);
    this->len = n;
    this->data = buf;
}

void IntVector_push_(struct IntVector* this, Int value) {
    Int n, *buf;
    if(this->len <= 0)
        n = 1;
    else
        n = this->len + 1;
    buf = (Int*)calloc(n, sizeof(Int));
    if(n > 1) memcpy(buf, this->data, n * sizeof(Int));
    buf[n - 1] = value;
    IntVector_free_(this);
    this->len = n;
    this->data = buf;
}

Bool IntVector_isequal(struct IntVector* this, struct IntVector other) {
    if((this->len==0)&&(other.len==0)) return true;
    if(this->len != other.len) return false;
    for(Int i=0; i<this->len; i++) if(this->data[i] != other.data[i]) return false;
    return true;
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
    if(this == perm) error_invalid_argument("(IntVector_sortperm_) perm == perm");
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
    Int i, sum = 0;
    if(this->len != b.len) error_invalid_argument("(IntVector_dot) length mismatch");
    for(i = 0; i < this->len; i++) sum += this->data[i] * b.data[i];
    return sum;
}

Int IntVector_coord_linear(const struct IntVector* this, struct IntVector size) {
    Int i, idx, n;
    if(this->len <= 0) error_invalid_argument("(IntVector_coord_linear) coordinate is empty");
    if(size.len <= 0) error_invalid_argument("(IntVector_coord_linear) size is empty");
    if(this->len != size.len) error_invalid_argument("(IntVector_coord_linear) length mismatch");
    idx = 0;
    n = size.len;
    for(i = 0; i < n; i++) {
        idx *= size.data[n - 1 - i];
        idx += this->data[n - 1 - i];
    }
    return idx;
}

void IntVector_coord_cartesian_(struct IntVector* this, struct IntVector size, Int linear_index) {
    Int i, rem, dv;
    if(size.len <= 0) error_invalid_argument("(IntVector_coord_cartesian_) size is empty");
    if(linear_index < 0) error_index_out_of_bounds("(IntVector_coord_cartesian_) linear_index < 0");
    if(linear_index >= IntVector_prod(&size))
        error_index_out_of_bounds("(IntVector_coord_cartesian_) linear_index >= max element");
    IntVector_alloc_(this, size.len);
    IntVector_fill_(this, 0);
    dv = linear_index;
    for(i = 0; i < size.len; i++) {
        rem = _bm_round_zero_to_Int(dv, size.data[i], &dv);
        this->data[i] = rem;
    }
}
