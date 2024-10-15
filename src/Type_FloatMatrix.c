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
#include <limits.h>
#include <float.h>
#include "Type_Part_math_basic.h"
#include "Type_IntVector.h"
#include "Type_FloatMatrix.h"

struct FloatMatrixMethods _CBL_FLOAT_MATRIX_METHODS = {
    &FloatMatrix_free_,
    &FloatMatrix_alloc_,
    &FloatMatrix_get,
    &FloatMatrix_set_,
    &FloatMatrix_set_vector_,
    &FloatMatrix_hcat_,
    &FloatMatrix_vcat_,
    &FloatMatrix_rand_,
    &FloatMatrix_rand_from_,
    &FloatMatrix_fill_,
    &FloatMatrix_copy_from_
};

void FloatMatrix_free_(struct FloatMatrix* this) {
    if(this->data != NULL) {
        free(this->data);
        this->data = NULL;
        this->nrow = 0;
        this->ncol = 0;
    }
}

void FloatMatrix_alloc_(struct FloatMatrix* this, Int nrow, Int ncol) {
    if(this->nrow == nrow && this->ncol == ncol) return;
    if(nrow <= 0) error_invalid_argument("nrow <= 0");
    if(ncol <= 0) error_invalid_argument("ncol <= 0");
    if(nrow * ncol > 0) FloatMatrix_free_(this);
    this->data = (Float*)calloc(nrow * ncol, sizeof(Float));
    this->nrow = nrow;
    this->ncol = ncol;
}

Float FloatMatrix_get(const struct FloatMatrix* this, Int irow, Int icol) {
    if(irow < 0 || irow >= this->nrow) error_index_out_of_bounds("(FloatMatrix_get) irow");
    if(icol < 0 || icol >= this->ncol) error_index_out_of_bounds("(FloatMatrix_get) icol");
    return this->data[irow + icol * this->nrow];
}

void FloatMatrix_set_(struct FloatMatrix* this, Int irow, Int icol, Float value) {
    if(irow < 0 || irow >= this->nrow) error_index_out_of_bounds("(FloatMatrix_get) irow");
    if(icol < 0 || icol >= this->ncol) error_index_out_of_bounds("(FloatMatrix_get) icol");
    this->data[irow + icol * this->nrow] = value;
}

void FloatMatrix_set_vector_(struct FloatMatrix* this, struct FloatVector fv) {
    if(fv.len <= 0) {
        FloatMatrix_free_(this);
        return;
    }
    FloatMatrix_alloc_(this, fv.len, 1);
    memcpy(this->data, fv.data, fv.len * sizeof(Float));
}

void FloatMatrix_hcat_(struct FloatMatrix* this, struct FloatMatrix A, struct FloatMatrix B) {
    Int ir, ic, i, j;;
    if(A.nrow != B.nrow) error_invalid_argument("A.nrow != B.nrow");
    FloatMatrix_alloc_(this, A.nrow, A.ncol + B.ncol);
    ic = 0;
    for(j = 0; j < A.ncol; j++) {
        ir = 0;
        for(i = 0; i < A.nrow; i++) {
            this->data[ir + ic * this->nrow] = A.data[i + A.nrow * j];
            ir += 1;
        }
        ic += 1;
    }
    for(j = 0; j < B.ncol; j++) {
        ir = 0;
        for(i = 0; i < B.nrow; i++) {
            this->data[ir + ic * this->nrow] = B.data[i + B.nrow * j];
            ir += 1;
        }
        ic += 1;
    }
}

void FloatMatrix_vcat_(struct FloatMatrix* this, struct FloatMatrix A, struct FloatMatrix B) {
    Int ir, i, j;
    if(A.ncol != B.ncol) error_invalid_argument("A.ncol != B.ncol");
    FloatMatrix_alloc_(this, A.nrow + B.nrow, A.ncol);
    for(j = 0; j < A.ncol; j++) {
        ir = 0;
        for(i = 0; i < A.nrow; i++) {
            this->data[ir + j * this->nrow] = A.data[i + A.nrow * j];
            ir += 1;
        }
        for(i = 0; i < B.nrow; i++) {
            this->data[ir + j * this->nrow] = B.data[i + B.nrow * j];
            ir += 1;
        }
    }
}

void FloatMatrix_rand_(struct FloatMatrix* this, Float min, Float max) {
    Int i, n;
    if(this->nrow <= 0 || this->ncol <= 0) return;
    if(max <= min) error_invalid_argument("(FloatMatrix_rand_) max <= min");
    unsigned long long* pf;

    n = this->nrow * this->ncol;
    pf = (unsigned long long*)malloc(n * sizeof(unsigned long long));
    _bm_rand_ull_(&pf, n);
    for(i = 0; i < n; i++) {
        this->data[i] = (
            (double)pf[i] /
            ((double)ULONG_LONG_MAX) *
            (max - min) + min
        );
    }
    free(pf);
}

void FloatMatrix_rand_from_(struct FloatMatrix* this, struct FloatVector value_set) {
    Int i;

    struct IntVector idxs;

    if(value_set.len <= 0) return;
    if(this->nrow <= 0 || this->ncol <= 0) return;
    IntVector_new_(&idxs);
    IntVector_alloc_(&idxs, this->nrow * this->ncol);
    IntVector_rand_(&idxs, 0, value_set.len - 1);
    for(i = 0; i < this->nrow * this->ncol; i++) this->data[i] = value_set.data[idxs.data[i]];
    IntVector_free_(&idxs);
}

void FloatMatrix_fill_(struct FloatMatrix* this, Float value) {
    Int i;
    if(this->nrow <= 0 || this->ncol <= 0) return;
    for(i = 0; i < this->nrow * this->ncol; i++) this->data[i] = value;
}

void FloatMatrix_copy_from_(struct FloatMatrix* this, struct FloatMatrix src) {
    FloatMatrix_alloc_(this, src.nrow, src.ncol);
    memcpy(this->data, src.data, src.nrow * src.ncol * sizeof(Float));
}
