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

#ifndef _TYPE_COMPLEX_H_
#define _TYPE_COMPLEX_H_

#include <math.h>

#define DEFINE_COMPLEX(R, C, BIT) \
typedef struct { R re, im; } C; \
static inline C cmplx##BIT(R re, R im){\
    C t;\
    t.re = re;\
    t.im = im;\
    return t;\
}\
static inline R cmplxreal##BIT(C z){ return z.re; }\
static inline R cmplximag##BIT(C z){ return z.im; }\
static inline R cmplxabs2##BIT(C z){ return z.re*z.re+z.im*z.im;}\
static inline R cmplxabs##BIT(C z){ return sqrtl(z.re*z.re+z.im*z.im);}\
static inline R cmplxangle##BIT(C z){ return atan2l(z.im, z.re);}\
static inline C cmplxconj##BIT(C z){\
    C t;\
    t.re = z.re;\
    t.im = -z.im;\
    return t;\
}\
static inline C cmplxadd##BIT(C z1, C z2){\
    C t;\
    t.re = z1.re + z2.re;\
    t.im = z1.im + z2.im;\
    return t;\
}\
static inline C cmplxsub##BIT(C z1, C z2){\
    C t;\
    t.re = z1.re - z2.re;\
    t.im = z1.im - z2.im;\
    return t;\
}\
static inline C cmplxmul##BIT(C z1, C z2){\
    C t;\
    t.re = z1.re * z2.re - z1.im * z2.im;\
    t.im = z1.im * z2.re + z1.re * z2.im;\
    return t;\
}\
static inline C cmplxdiv##BIT(C z1, C z2){\
    C t;\
    R n;\
    n = cmplxabs2##BIT(z2);\
    t = cmplxmul##BIT(z1, cmplxconj##BIT(z2));\
    t.re /= n;\
    t.im /= n;\
    return t;\
}

DEFINE_COMPLEX(float, Complex32, 32)
DEFINE_COMPLEX(double, Complex64, 64)
DEFINE_COMPLEX(long double, Complex128, 128)


#endif // _TYPE_COMPLEX_H_
