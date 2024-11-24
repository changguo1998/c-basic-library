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
#include <math.h>

static inline long double pown(long double x, double n) {
    long double y;
    y = x;
    for(long i = 0; i < n - 1; i++) y *= x;
    return y;
}

int main() {
    long double x0, r1, r2, o;
    int    n;

    x0 = 2.0l;
    printf("x0 = %g\n", x0);
    printf("sqrt(x0) = %g\n", sqrtl(x0));
    r2 = expl(logl(x0) / 2.0);
    printf("r2 = %g\n", r2);
    o = 2.0;
    n = 0;
    do {
        r1 = r2;
        r2 = ((o - 1) * pown(r1, o) + x0) / (o * pown(r1, o - 1));
        printf("r2 = %.30lf\n", r2);
        n += 1;
        if(n > 50) break;
    }
    while(fabsl(r2 - r1) > 1e-8);
    printf("cubic root: ------------------------------------\n");
    r2 = expl(logl(x0) / 3.0);
    printf("r2 = %.30lf\n", r2);
    o = 3.0;
    n = 0;
    do {
        r1 = r2;
        r2 = ((o - 1) * pown(r1, o) + x0) / (o * pown(r1, o - 1));
        printf("r2 = %.30lf\n", r2);
        n += 1;
        if(n > 50) break;
    }
    while(fabsl(r2 - r1) > 1e-10);
    printf("cubic root bitwise compare: ------------------------------------\n");
    r2 = expl(logl(x0) / 3.0);
    printf("r2 = %.30lf\n", r2);
    o = 3.0;
    n = 0;
    do {
        r1 = r2;
        r2 = ((o - 1) * pown(r1, o) + x0) / (o * pown(r1, o - 1));
        printf("r2 = %.30lf\n", r2);
        n += 1;
        if(n > 50) break;
    }
    while(r1 != r2);
    return 0;
}
