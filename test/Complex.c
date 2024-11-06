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

#include "Module_Basic.h"
#include "Type_Complex.h"

int main() {
    Complex z1, z2, z3;

    z1 = cmplx(1, 2);
    z2 = cmplx(3, 4);

    printf("z1: %g%+gi\n", z1.re, cmplximag(z1));
    printf("z2: %g%+gi\n", z2.re, cmplximag(z2));
    printf("abs2(z2): %g\n", cmplxabs2(z2));
    printf("angle(z2): %g\n", cmplxangle(z2));

    z3 = cmplxconj(z1);
    printf("cconj(z1): %g%+gi\n", z3.re, z3.im);
    z3 = cmplxadd(z1, z2);
    printf("z1+z2: %g%+gi\n", z3.re, z3.im);
    z3 = cmplxmul(z1, z2);
    printf("z1*z2: %g%+gi\n", z3.re, z3.im);
    z3 = cmplxdiv(z1, z2);
    printf("z1/z2: %g%+gi\n", z3.re, z3.im);
    return 0;
}
