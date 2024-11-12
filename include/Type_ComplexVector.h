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

#ifndef _TYPE_COMPLEXVECTOR_H_
#define _TYPE_COMPLEXVECTOR_H_

#include "Module_Basic.h"

struct ComplexVector {
    Int      len;
    Complex* data;

    struct ComplexVectorMethods* methods;
};

struct ComplexVectorMethods {
    // memory manage
    void (*free_)(struct ComplexVector* this);
    void (*alloc_)(struct ComplexVector* this, int len);
    // basic
    void (*   copy_from_)(struct ComplexVector* this, struct ComplexVector src);
    Complex (*get)(struct ComplexVector* this, Int index);
    void (*   set_)(struct ComplexVector* this, Int index, Complex value);
    void (*   set_float_)(struct ComplexVector* this, struct FloatVector res, struct FloatVector ims);
    // math
    Complex (*polyval_zeros)(struct ComplexVector* this, Complex x);
    void (*   fft_)(struct ComplexVector* this, struct ComplexVector x);
    void (*   ifft_)(struct ComplexVector* this, struct ComplexVector x);
    void (*   fft_rc_)(struct ComplexVector* this, struct FloatVector x);
    void (*   ifft_cr_)(struct ComplexVector* this, struct FloatVector x);
};

extern struct ComplexVectorMethods _CBL_COMPLEX_VECTOR_METHODS;

static inline void ComplexVector_new_(struct ComplexVector* this) {
    this->len = 0;
    this->data = NULL;
    this->methods = &_CBL_COMPLEX_VECTOR_METHODS;
}

void    ComplexVector_free_(struct ComplexVector* this);
void    ComplexVector_alloc_(struct ComplexVector* this, int len);
void    ComplexVector_copy_from_(struct ComplexVector* this, struct ComplexVector src);
Complex ComplexVector_get(struct ComplexVector* this, Int index);
void    ComplexVector_set_(struct ComplexVector* this, Int index, Complex value);
void    ComplexVector_set_float_(struct ComplexVector* this, struct FloatVector res, struct FloatVector ims);
Complex ComplexVector_polyval_zeros(struct ComplexVector* this, Complex x);
void    ComplexVector_fft_(struct ComplexVector* this, struct ComplexVector x);
void    ComplexVector_ifft_(struct ComplexVector* this, struct ComplexVector x);
void    ComplexVector_fft_rc_(struct ComplexVector* this, struct FloatVector x);
void    ComplexVector_ifft_cr_(struct ComplexVector* this, struct FloatVector x);

#endif // _TYPE_COMPLEXVECTOR_H_
