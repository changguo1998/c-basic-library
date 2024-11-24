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
#include "Type_Part_math_basic.h"
#include "Type_IntVector.h"
#include "Type_FloatVector.h"
#include "Type_ComplexVector.h"

struct ComplexVectorMethods _CBL_COMPLEX_VECTOR_METHODS = {
    &ComplexVector_free_,
    &ComplexVector_alloc_,
    &ComplexVector_copy_,
    &ComplexVector_get,
    &ComplexVector_set_,
    &ComplexVector_set_float_,
    &ComplexVector_polyval_zeros,
    &ComplexVector_fft_,
    &ComplexVector_ifft_,
    &ComplexVector_fftr_,
};

void ComplexVector_free_(struct ComplexVector* this) {
    if(this == NULL) return;
    if(this->data) {
        free(this->data);
        this->data = NULL;
    }
    this->len = 0;
}

void ComplexVector_alloc_(struct ComplexVector* this, int len) {
    Complex* p = NULL;
    Int      n;
    if(this == NULL) return;
    if(this->len == len) return;
    if(len <= 0) {
        ComplexVector_free_(this);
        return;
    }
    if(this->len <= 0) {
        this->data = (Complex*)calloc(len, sizeof(Complex));
        this->len = len;
        return;
    }
    p = (Complex*)calloc(len, sizeof(Complex));
    n = this->len < len ? this->len : len;
    memcpy(p, this->data, n * sizeof(Complex));
    free(this->data);
    this->data = p;
    this->len = len;
}

void ComplexVector_copy_(struct ComplexVector* this, struct ComplexVector src) {
    if(src.len <= 0) {
        ComplexVector_free_(this);
        return;
    }
    if(src.len != this->len) ComplexVector_alloc_(this, src.len);
    if(this->data == src.data) return;
    memcpy(this->data, src.data, src.len * sizeof(Complex));
}

Complex ComplexVector_get(struct ComplexVector* this, Int index) {
    if((index >= this->len) || (index < 0))
        error_index_out_of_bounds("(ComplexVector_get) index out of bounds");
    return this->data[index];
}

void ComplexVector_set_(struct ComplexVector* this, Int index, Complex value) {
    if(this->len <= 0) return;
    if(index < 0 || index >= this->len) error_index_out_of_bounds("(ComplexVector_set_) index out of bounds");
    this->data[index] = value;
}

void ComplexVector_set_float_(struct ComplexVector* this, struct FloatVector res, struct FloatVector ims) {
    if(res.len != ims.len) error_invalid_argument("(ComplexVector_set_float_) res.len != ims.len");
    if(res.len <= 0) {
        ComplexVector_free_(this);
        return;
    }
    ComplexVector_alloc_(this, res.len);
    for(Int i = 0; i < res.len; i++) {
        this->data[i].re = res.data[i];
        this->data[i].im = ims.data[i];
    }

}

Complex ComplexVector_polyval_zeros(struct ComplexVector* this, Complex x) {
    Complex t;
    t.re = 0.0;
    t.im = 0.0;
    if(this->len <= 0) return t;
    t.re = 1.0;
    for(Int i = 0; i < this->len; i++) t = cmplx_mul(t, cmplx_sub(x, this->data[i]));
    return t;
}

void ComplexVector_fft_(struct ComplexVector* this, struct ComplexVector x) {
    if(x.len <= 0) {
        ComplexVector_free_(this);
        return;
    }
    ComplexVector_alloc_(this, x.len);
    _bm_fft(x.len, x.data, this->data);
}

void ComplexVector_ifft_(struct ComplexVector* this, struct ComplexVector x) {
    if(x.len <= 0) {
        ComplexVector_free_(this);
        return;
    }
    ComplexVector_alloc_(this, x.len);
    _bm_ifft(x.len, x.data, this->data);
}

void ComplexVector_fftr_(struct ComplexVector* this, struct FloatVector x) {
    if(x.len <= 0) {
        ComplexVector_free_(this);
        return;
    }
    ComplexVector_alloc_(this, x.len);
    _bm_fftr(x.len, x.data, this->data);
}
