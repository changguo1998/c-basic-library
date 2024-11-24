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
#include <stdarg.h>
#include <string.h>
#include "Module_Basic.h"
#include "Type_Part_math_basic.h"
#include "Type_IntVector.h"
#include "Type_FloatVector.h"
#include "Type_FloatMatrix.h"

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
    &FloatVector_linrange_,
    &FloatVector_range_,
    &FloatVector_copy_,
    &FloatVector_sum,
    &FloatVector_mean,
    &FloatVector_var,
    &FloatVector_std,
    &FloatVector_norm,
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
    &FloatVector_cross_,
    &FloatVector_map_f_ff_,
    &FloatVector_add_scalar_,
    &FloatVector_sub_scalar_,
    &FloatVector_mul_scalar_,
    &FloatVector_div_scalar_,
    &FloatVector_add_,
    &FloatVector_sub_,
    &FloatVector_mul_,
    &FloatVector_div_,
    &FloatVector_sqrt_,
    &FloatVector_root_,
    &FloatVector_pow_,
    &FloatVector_normalize_,
    &FloatVector_polyval,
    &FloatVector_polyint_,
    &FloatVector_polydiff_,
    &FloatVector_get_row_,
    &FloatVector_get_column_,
    &FloatVector_ifft_
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
    if(this == NULL) return;
    if(this->len == len) return;

    FloatVector_free_(this);
    if(len <= 0) return;

    this->data = (Float*)calloc(len, sizeof(Float));
    this->len = len;
}

Float FloatVector_get(const struct FloatVector* this, Int index) {
    if((index >= this->len) || (index < 0))
        error_index_out_of_bounds("(Vector_get) index out of bounds");
    return this->data[index];
}

void FloatVector_index_(struct FloatVector* this, struct IntVector indexs) {
    Int    i;
    Float* buf;
    if(indexs.len <= 0) {
        FloatVector_free_(this);
        return;
    }
    for(i = 0; i < indexs.len; i++)
        if(indexs.data[i] < 0 || indexs.data[i] >= this->len)
            error_index_out_of_bounds("(FloatVector_index_) index out of bounds");

    buf = (Float*)calloc(indexs.len, sizeof(Float));
    for(i = 0; i < indexs.len; i++) buf[i] = this->data[indexs.data[i]];


    FloatVector_free_(this);
    this->len = indexs.len;
    this->data = buf;
}

void FloatVector_slice_(struct FloatVector* this, Int start, Int step, Int stop) {
    Int    i, n;
    Float* buf;

    if(stop == VECTOR_INDEX_END) stop = this->len - 1;
    if(step == 0) error_invalid_argument("(FloatVector_slice_) step is 0");
    if(start < 0) error_invalid_argument("(FloatVector_slice_) start < 0");
    if(start >= this->len) error_invalid_argument("(FloatVector_slice_) start >= this->len");
    if(stop < 0) error_invalid_argument("(FloatVector_slice_) stop < 0");
    if(stop >= this->len) error_invalid_argument("(FloatVector_slice_) stop >= this->len");
    n = (stop - start) / step + 1;
    if(n <= 0) {
        FloatVector_free_(this);
        return;
    }
    if(n == this->len) return;
    buf = (Float*)calloc(n, sizeof(Float));
    for(i = 0; i < n; i++) buf[i] = this->data[start + i * step];

    FloatVector_free_(this);
    this->len = n;
    this->data = buf;
}

void FloatVector_index_flag_(struct FloatVector* this, struct IntVector flags) {
    Int    i, j, n;
    Float* buf;
    if(this->len != flags.len) error_invalid_argument("(FloatVector_index_flag_) src.len != flags.len");
    if(this->len <= 0) return;

    n = IntVector_count(&flags);
    if(n <= 0) {
        FloatVector_free_(this);
        return;
    }
    if(n == this->len) return;
    buf = (Float*)calloc(n, sizeof(Float));
    j = 0;
    for(i = 0; i < this->len; i++)
        if(flags.data[i]) {
            buf[j] = this->data[i];
            j += 1;
        }

    FloatVector_free_(this);
    this->len = n;
    this->data = buf;
}

void FloatVector_set_(struct FloatVector* this, Int index, Float value) {
    if(this->len <= 0) return;
    if(index < 0 || index >= this->len) error_index_out_of_bounds("(FloatVector_set_) index out of bounds");
    this->data[index] = value;
}

void FloatVector_setas_(struct FloatVector* this, Int n, ...) {
    va_list ap;
    Int     i;

    if(n <= 0) error_invalid_argument("(FloatVector_setas_) n =< 0");
    FloatVector_alloc_(this, n);

    va_start(ap, n);
    for(i = 0; i < n; i++) this->data[i] = va_arg(ap, _VECTOR_N_VA_ARG_TYPE_Float);
    va_end(ap);
}

void FloatVector_vcat_(struct FloatVector* this, Int n, ...) {
    Int     i, j, k, row;
    va_list ap;
    Float*  buf;

    struct FloatVector* pvec = NULL;

    if(n <= 0) return;

    // load input data
    pvec = (struct FloatVector*)malloc(n * sizeof(struct FloatVector));
    va_start(ap, n);
    for(i = 0; i < n; i++) pvec[i] = va_arg(ap, struct FloatVector);
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
        FloatVector_free_(this);
        return;
    }

    // collect data
    buf = (Float*)calloc(row, sizeof(Float));
    for(k = 0; k < this->len; k++) buf[k] = this->data[k];
    for(i = 0; i < n; i++) {
        for(j = 0; j < pvec[i].len; j++) {
            buf[k] = pvec[i].data[j];
            k += 1;
        }
    }

    FloatVector_free_(this);
    this->len = row;
    this->data = buf;
    free(pvec);
}

void FloatVector_rand_(struct FloatVector* this, Float a, Float b) {
    Int   i;
    Float min, max;

    unsigned long long* pf = NULL;

    if(this->len <= 0) return;
    if(a == b) {
        FloatVector_fill_(this, a);
        return;
    }
    min = (a < b) ? a : b;
    max = (a > b) ? a : b;
    pf = (unsigned long long*)malloc(this->len * sizeof(unsigned long long));
    _bm_rand_ull_(pf, this->len);
    for(i = 0; i < this->len; i++) this->data[i] = _bm_convert_ull_to_Float(pf[i], min, max);
    free(pf);
}

void FloatVector_rand_from_(struct FloatVector* this, struct FloatVector value_set) {
    Int i;
    CBL_DECLARE_VARS(IntVector, 1, idxs);

    if(value_set.len <= 0) return;
    if(this->len <= 0) return;
    if(this->data == value_set.data)
        error_invalid_argument("(FloatVector_rand_from_) this->data == value_set.data");

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

void FloatVector_linrange_(struct FloatVector* this, Float start, Float stop) {
    Float step;
    if(this->len <= 0) return;
    if(this->len == 1) {
        this->data[0] = start;
        return;
    }
    step = (stop - start) / (Float)(this->len - 1);
    for(Int i = 0; i < this->len; i++) this->data[i] = start + step * i;
}

void FloatVector_range_(struct FloatVector* this, Float start, Float step, Float stop) {
    Int i, n;
    if(step == 0) error_invalid_argument("(FloatVector_range_) step == 0");
    if(start == stop) error_invalid_argument("(FloatVector_range_) start == stop");
    if(step * (stop - start) <= 0)
        error_invalid_argument("(FloatVector_range_) step * (stop - start) <= 0");

    n = (Int)((stop - start) / step) + 1;
    if(n <= 0) {
        FloatVector_free_(this);
        return;
    }
    FloatVector_alloc_(this, n);
    for(i = 0; i < n; i++) this->data[i] = start + i * step;
}

void FloatVector_copy_(struct FloatVector* this, struct FloatVector src) {
    if(this->data == src.data)
        error_invalid_argument("(FloatVector_copy_) this->data == src.data");
    if(src.len <= 0) {
        FloatVector_free_(this);
        return;
    }
    FloatVector_alloc_(this, src.len);
    memcpy(this->data, src.data, src.len * sizeof(Float));
}

Float FloatVector_sum(const struct FloatVector* this) {
    Int   i;
    Float sum = 0.0;
    if(this->len <= 0) return sum;
    for(i = 0; i < this->len; i++) sum += this->data[i];
    return sum;
}

Float FloatVector_mean(const struct FloatVector* this) { return FloatVector_sum(this) / (Float)this->len; }

Float FloatVector_var(const struct FloatVector* this) {
    Float s, m;
    Int   i;

    if(this->len <= 0) return 0.0;
    s = 0.0;
    m = FloatVector_mean(this);
    for(i = 0; i < this->len; i++) s += (this->data[i] - m) * (this->data[i] - m);
    return s / this->len;
}

Float FloatVector_std(const struct FloatVector* this) { return _bm_sqrt(FloatVector_var(this)); }

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
    if(order == CBL_INT_MAX) {
        v = 0.0;
        for(i = 0; i < this->len; i++)
            v = v < _bm_abs_float(this->data[i]) ? _bm_abs_float(this->data[i]) : v;
        return v;
    }
    v = 0.0;
    for(i = 0; i < this->len; i++) v += pow(_bm_abs_float(this->data[i]), order);
    return _bm_n_root(v, order);
}

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
    if(this->len != b.len) error_invalid_argument("(FloatVector_dot) length mismatch");
    for(i = 0; i < this->len; i++) sum += this->data[i] * b.data[i];
    return sum;
}

void FloatVector_cross_(struct FloatVector* this, struct FloatVector x, struct FloatVector y) {
    if(x.len != 3) error_invalid_argument("(FloatVector_cross) x.len != 3");
    if(y.len != 3) error_invalid_argument("(FloatVector_cross) y.len != 3");
    FloatVector_alloc_(this, 3);
    this->data[0] = x.data[1] * y.data[2] - x.data[2] * y.data[1];
    this->data[1] = x.data[2] * y.data[0] - x.data[0] * y.data[2];
    this->data[2] = x.data[0] * y.data[1] - x.data[1] * y.data[0];
}

void FloatVector_map_f_ff_(struct FloatVector* this, f_Func_ff func, struct FloatVector x) {
    if(this->len <= 0) return;
    for(Int i = 0; i < this->len; i++) this->data[i] = func(this->data[i], x.data[i]);
}

void FloatVector_add_scalar_(struct FloatVector* this, Float value) {
    if(this->len <= 0) return;
    for(Int i = 0; i < this->len; i++) this->data[i] += value;
}

void FloatVector_sub_scalar_(struct FloatVector* this, Float value) {
    if(this->len <= 0) return;
    for(Int i = 0; i < this->len; i++) this->data[i] -= value;
}

void FloatVector_mul_scalar_(struct FloatVector* this, Float value) {
    if(this->len <= 0) return;
    for(Int i = 0; i < this->len; i++) this->data[i] *= value;
}

void FloatVector_div_scalar_(struct FloatVector* this, Float value) {
    if(this->len <= 0) return;
    if(value == 0) error_invalid_argument("(FloatVector_div_scalar) division by zero");
    for(Int i = 0; i < this->len; i++) this->data[i] /= value;
}

void FloatVector_add_(struct FloatVector* this, struct FloatVector b) {
    if(this->len <= 0) return;
    if(this->len != b.len) error_invalid_argument("(FloatVector_add) length mismatch");
    for(Int i = 0; i < this->len; i++) this->data[i] += b.data[i];
}

void FloatVector_sub_(struct FloatVector* this, struct FloatVector b) {
    if(this->len <= 0) return;
    if(this->len != b.len) return;
    for(Int i = 0; i < this->len; i++) this->data[i] -= b.data[i];
}

void FloatVector_mul_(struct FloatVector* this, struct FloatVector b) {
    if(this->len <= 0) return;
    if(this->len != b.len) return;
    for(Int i = 0; i < this->len; i++) this->data[i] *= b.data[i];
}

void FloatVector_div_(struct FloatVector* this, struct FloatVector b) {
    if(this->len <= 0) return;
    if(this->len != b.len) return;
    Int i = 0;
    for(i = 0; i < b.len; i++) if(b.data[i] == 0) error_invalid_argument("(FloatVector_div) division by zero");
    for(i = 0; i < this->len; i++) this->data[i] /= b.data[i];
}

void FloatVector_sqrt_(struct FloatVector* this) {
    if(this->len <= 0) return;
    for(Int i = 0; i < this->len; i++) this->data[i] = _bm_sqrt(this->data[i]);
}

void FloatVector_root_(struct FloatVector* this, Int order) {
    if(this->len <= 0) return;
    for(Int i = 0; i < this->len; i++) this->data[i] = _bm_n_root(this->data[i], order);
}

void FloatVector_pow_(struct FloatVector* this, Int order) {
    if(this->len <= 0) return;
    for(Int i = 0; i < this->len; i++) this->data[i] = pow(this->data[i], order);
}

void FloatVector_normalize_(struct FloatVector* this) {
    if(this->len <= 0) return;
    Float nm;
    nm = FloatVector_norm(this, 2);
    if(nm == 0) error_invalid_argument("(FloatVector_normalize) norm is zero");
    FloatVector_div_scalar_(this, nm);
}

Float FloatVector_polyval(const struct FloatVector* this, Float x) {
    Float v;
    Int   i;
    if(this->len <= 0) error_invalid_argument("(FloatVector_polyval) polynomial is empty");
    v = 0.0;
    for(i = 0; i < this->len; i++) {
        v *= x;
        v += this->data[this->len - 1 - i];
    }
    return v;
}

void FloatVector_polyint_(struct FloatVector* this, Float y0) {
    Float* buf;
    Int    i, n;

    if(this->len < 0) return;
    if(this->len == 0) {
        FloatVector_alloc_(this, 1);
        this->data[0] = y0;
        return;
    }
    n = this->len + 1;
    buf = (Float*)calloc(n, sizeof(Float));
    buf[0] = y0;
    for(i = 1; i < n; i++) buf[i] = this->data[i - 1] / i;

    FloatVector_alloc_(this, n);
    memcpy(this->data, buf, n * sizeof(Float));
    free(buf);
}

void FloatVector_polydiff_(struct FloatVector* this) {
    Float* buf;
    Int    i, n;

    if(this->len <= 0) return;
    if(this->len == 1) {
        this->data[0] = 0.0;
        return;
    }
    n = this->len - 1;
    buf = (Float*)calloc(n, sizeof(Float));
    for(i = 0; i < n; i++) buf[i] = this->data[i + 1] * (i + 1);

    FloatVector_alloc_(this, n);
    memcpy(this->data, buf, n * sizeof(Float));
    free(buf);
}

void FloatVector_get_row_(struct FloatVector* this, struct FloatMatrix M, Int r) {
    if(r >= M.nrow) error_index_out_of_bounds("(FloatMatrix_get_row) irow >= this->nrow");
    if(r < 0) error_invalid_argument("(FloatMatrix_get_row) irow < 0");
    if(M.ncol <= 0) {
        FloatVector_free_(this);
        return;
    }
    FloatVector_alloc_(this, M.ncol);
    for(Int i = 0; i < M.nrow; i++) this->data[i] = CBL_CALL(M, get, r, i);
}

void FloatVector_get_column_(struct FloatVector* this, struct FloatMatrix M, Int c) {
    if(c >= M.ncol) error_invalid_argument("(FloatMatrix_get_column) icol >= this->ncol");
    if(c < 0) error_invalid_argument("(FloatMatrix_get_column) icol < 0");
    if(M.nrow <= 0) {
        FloatVector_free_(this);
        return;
    }
    FloatVector_alloc_(this, M.nrow);
    for(Int i = 0; i < M.nrow; i++) this->data[i] = CBL_CALL(M, get, i, c);
}

void FloatVector_ifft_(struct FloatVector* this, struct ComplexVector X) {
    if(X.len <= 0) {
        FloatVector_free_(this);
        return;
    }
    FloatVector_alloc_(this, X.len);
    _bm_ifftr(X.len, this->data, X.data);
}
