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
#include <string.h>
#include <math.h>

//#include <complex.h>
#include <fftw3.h>

int main() {
    int     m,   n, i;
    double *in, *in_ref;

    fftw_complex* out;
    fftw_plan     p;

    printf("Begin\n");
    n = 16;
    m = n / 2 + 1;
    printf("m = %d, n = %d\n", m, n);
    in_ref = (double*)malloc(n * sizeof(double));
    in = fftw_alloc_real(n);
    out = fftw_alloc_complex(m);

    p = fftw_plan_dft_r2c_1d(n, in, out, FFTW_ESTIMATE);

    for(i = 0; i < n; i++)
        in_ref[i] = sin(M_2_PI * 2.0 * i / m);
    memcpy(in, in_ref, n * sizeof(double));

    fftw_execute(p);

    for(i = 0; i < n; i++) {
        printf("%.4f %.4f", in_ref[i], in[i]);
        if(i < m) printf(" %.4f%+.4fi", out[i][0], out[i][1]);
        printf("\n");
    }

    free(in_ref);
    fftw_destroy_plan(p);
    fftw_free(in);
    fftw_free(out);
    return 0;
}
