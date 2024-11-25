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

#ifndef _TYPE_FLOATMATRIX_H_
#define _TYPE_FLOATMATRIX_H_

#include "Module_Basic.h"

struct FloatMatrixMethods {
    // memory management
    void (*free_)(struct FloatMatrix* this);
    void (*alloc_)(struct FloatMatrix* this, Int nrow, Int ncol);
    // basic
    Float (*get)(const struct FloatMatrix* this, Int irow, Int icol);
    void (* set_)(struct FloatMatrix* this, Int irow, Int icol, Float value);
    void (* set_vector_)(struct FloatMatrix* this, struct FloatVector fv);
    void (* hcatv_)(struct FloatMatrix* this, Int n, ...);
    void (* hcat_)(struct FloatMatrix* this, Int nmat, ...);
    void (* vcat_)(struct FloatMatrix* this, Int nmat, ...);
    void (* rand_)(struct FloatMatrix* this, Float min, Float max);
    void (* rand_from_)(struct FloatMatrix* this, struct FloatVector value_set);
    void (* fill_)(struct FloatMatrix* this, Float value);
    void (* copy_)(struct FloatMatrix* this, struct FloatMatrix src);
    void (* diag_)(struct FloatMatrix* this, struct FloatVector dv);
    // math
    void (*add_)(struct FloatMatrix* this, struct FloatMatrix X);
    void (*product_)(struct FloatMatrix* this, struct FloatMatrix X, struct FloatMatrix Y);
};

extern struct FloatMatrixMethods _CBL_FLOAT_MATRIX_METHODS;

static inline void FloatMatrix_new_(struct FloatMatrix* this) {
    this->nrow = 0;
    this->ncol = 0;
    this->data = NULL;
    this->methods = &_CBL_FLOAT_MATRIX_METHODS;
}

void  FloatMatrix_free_(struct FloatMatrix* this);
void  FloatMatrix_alloc_(struct FloatMatrix* this, Int nrow, Int ncol);
Float FloatMatrix_get(const struct FloatMatrix* this, Int irow, Int icol);
void  FloatMatrix_set_(struct FloatMatrix* this, Int irow, Int icol, Float value);
void  FloatMatrix_set_vector_(struct FloatMatrix* this, struct FloatVector fv);
void  FloatMatrix_hcatv_(struct FloatMatrix* this, Int n, ...);
void  FloatMatrix_hcat_(struct FloatMatrix* this, Int nmat, ...);
void  FloatMatrix_vcat_(struct FloatMatrix* this, Int nmat, ...);
void  FloatMatrix_rand_(struct FloatMatrix* this, Float min, Float max);
void  FloatMatrix_rand_from_(struct FloatMatrix* this, struct FloatVector value_set);
void  FloatMatrix_fill_(struct FloatMatrix* this, Float value);
void  FloatMatrix_copy_(struct FloatMatrix* this, struct FloatMatrix src);
void  FloatMatrix_diag_(struct FloatMatrix* this, struct FloatVector dv);
void  FloatMatrix_add_(struct FloatMatrix* this, struct FloatMatrix X);
void  FloatMatrix_product_(struct FloatMatrix* this, struct FloatMatrix X, struct FloatMatrix Y);

#endif // _TYPE_FLOATMATRIX_H_
