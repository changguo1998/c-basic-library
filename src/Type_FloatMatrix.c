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
    &FloatMatrix_hcatv_,
    &FloatMatrix_hcat_,
    &FloatMatrix_vcat_,
    &FloatMatrix_rand_,
    &FloatMatrix_rand_from_,
    &FloatMatrix_fill_,
    &FloatMatrix_copy_from_,
    &FloatMatrix_diag_,
    &FloatMatrix_add_,
    &FloatMatrix_product_
};

static inline Int _idx(Int r, Int c, Int m, Int n) { return r + m * c; }

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
    return this->data[_idx(irow, icol, this->nrow, this->ncol)];
}

void FloatMatrix_set_(struct FloatMatrix* this, Int irow, Int icol, Float value) {
    if(irow < 0 || irow >= this->nrow) error_index_out_of_bounds("(FloatMatrix_get) irow");
    if(icol < 0 || icol >= this->ncol) error_index_out_of_bounds("(FloatMatrix_get) icol");
    this->data[_idx(irow, icol, this->nrow, this->ncol)] = value;
}

void FloatMatrix_set_vector_(struct FloatMatrix* this, struct FloatVector fv) {
    if(fv.len <= 0) {
        FloatMatrix_free_(this);
        return;
    }
    FloatMatrix_alloc_(this, fv.len, 1);
    memcpy(this->data, fv.data, fv.len * sizeof(Float));
}

void FloatMatrix_hcatv_(struct FloatMatrix* this, Int n, ...) {
    Int     ir, ic, j, m;
    va_list ap;

    struct FloatVector* pvec;

    va_start(ap, n);
    pvec = (struct FloatVector*)malloc(n * sizeof(struct FloatVector));
    for(j = 0; j < n; j++) pvec[j] = va_arg(ap, struct FloatVector);
    va_end(ap);

    m = pvec[0].len;
    for(j = 0; j < n; j++)
        if(pvec[j].len != m)
            error_invalid_argument("(FloatMatrix_hcatv) vector length not equal");
    FloatMatrix_alloc_(this, m, n);
    for(ic = 0; ic < n; ic++)
        for(ir = 0; ir < m; ir++) this->data[_idx(ir, ic, m, n)] = pvec[ic].data[ir];
    free(pvec);
}

void FloatMatrix_hcat_(struct FloatMatrix* this, Int nmat, ...) {
    Int     ir, ic, jc, nrow, ncol, imat;
    va_list ap;

    struct FloatMatrix* pmat;

    va_start(ap, nmat);
    pmat = (struct FloatMatrix*)malloc(nmat * sizeof(struct FloatMatrix));
    for(imat = 0; imat < nmat; imat++) pmat[imat] = va_arg(ap, struct FloatMatrix);
    va_end(ap);

    nrow = pmat[0].nrow;
    ncol = 0;
    for(imat = 0; imat < nmat; imat++) {
        ncol += pmat[imat].ncol;
        if(nrow != pmat[imat].nrow)
            error_invalid_argument("(FloatMatrix_hcat) matrix row not equal");
    }
    FloatMatrix_alloc_(this, nrow, ncol);
    ic = 0;
    for(imat = 0; imat < nmat; imat++) {
        for(jc = 0; jc < pmat[imat].ncol; jc++) {
            for(ir = 0; ir < nrow; ir++) {
                this->data[_idx(ir, ic, nrow, ncol)] =
                    pmat[imat].data[_idx(ir, jc, pmat[imat].nrow, pmat[imat].ncol)];
            } // ir
            ic += 1;
        } // jc
    } // imat
    free(pmat);
}

void FloatMatrix_vcat_(struct FloatMatrix* this, Int nmat, ...) {
    Int     ir, ic, jr, nrow, ncol, imat;
    va_list ap;

    struct FloatMatrix* pmat;

    va_start(ap, nmat);
    pmat = (struct FloatMatrix*)malloc(nmat * sizeof(struct FloatMatrix));
    for(imat = 0; imat < nmat; imat++) pmat[imat] = va_arg(ap, struct FloatMatrix);
    va_end(ap);

    ncol = pmat[0].ncol;
    nrow = 0;
    for(imat = 0; imat < nmat; imat++) {
        nrow += pmat[imat].nrow;
        if(ncol != pmat[imat].ncol)
            error_invalid_argument("(FloatMatrix_hcat) matrix column not equal");
    }
    FloatMatrix_alloc_(this, nrow, ncol);
    ir = 0;
    for(imat = 0; imat < nmat; imat++) {
        for(jr = 0; jr < pmat[imat].nrow; jr++) {
            for(ic = 0; ic < ncol; ic++) {
                this->data[_idx(ir, ic, nrow, ncol)] =
                    pmat[imat].data[_idx(jr, ic, pmat[imat].nrow, pmat[imat].ncol)];
            } // ic
            ir += 1;
        } // jr
    } // imat
    free(pmat);
}

void FloatMatrix_rand_(struct FloatMatrix* this, Float min, Float max) {
    Int i, n;
    if(this->nrow <= 0 || this->ncol <= 0) return;
    if(max <= min) error_invalid_argument("(FloatMatrix_rand_) max <= min");
    unsigned long long* pf;

    n = this->nrow * this->ncol;
    pf = (unsigned long long*)malloc(n * sizeof(unsigned long long));
    _bm_rand_ull_(pf, n);
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

void FloatMatrix_diag_(struct FloatMatrix* this, struct FloatVector dv) {
    Int i;
    if(dv.len <= 0) {
        FloatMatrix_free_(this);
        return;
    }
    FloatMatrix_alloc_(this, dv.len, dv.len);
    for(i = 0; i < dv.len; i++) this->data[_idx(i, i, dv.len, dv.len)] = dv.data[i];
}

void FloatMatrix_add_(struct FloatMatrix* this, struct FloatMatrix X, struct FloatMatrix Y) {
    if(X.nrow != Y.nrow) error_invalid_argument("(FloatMatrix_add_) X.nrow != Y.nrow");
    if(X.ncol != Y.ncol) error_invalid_argument("(FloatMatrix_add_) X.ncol != Y.ncol");
    Int i, n;
    n = X.nrow * X.ncol;
    FloatMatrix_alloc_(this, X.nrow, X.ncol);
    for(i = 0; i < n; i++) this->data[i] = X.data[i] + Y.data[i];
}

void FloatMatrix_product_(struct FloatMatrix* this, struct FloatMatrix X, struct FloatMatrix Y) {
    Int i, j, k, li;
    if(X.ncol != Y.nrow) error_invalid_argument("(FloatMatrix_product_) matrix dimension mismatch");
    FloatMatrix_alloc_(this, X.nrow, Y.ncol);
    for(i = 0; i < X.nrow; i++)
        for(j = 0; j < Y.ncol; j++) {
            li = _idx(i, j, X.nrow, Y.ncol);
            this->data[li] = 0;
            for(k = 0; k < X.ncol; k++)
                this->data[li] +=
                    X.data[_idx(i, k, X.nrow, X.ncol)] *
                    Y.data[_idx(k, j, Y.nrow, Y.ncol)];
        }
}