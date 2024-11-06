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
#include <complex.h>
#include <math.h>
#include "Module_Basic.h"

#include <fftw3.h>

#ifdef WINDOWS
#define _CRT_RAND_S
#include <windows.h>
#include <wincrypt.h>
#endif

#include "Type_Part_math_basic.h"

#include <math.h>

void _bm_rand_ull_(unsigned long long* buffer, long len) {
#ifdef UNIX
     FILE* fp = NULL;
     fp = fopen("/dev/urandom", "r");
     if(fp == NULL) error_file_not_exists("/dev/urandom");
     fread(pf, sizeof(unsigend long long), len, fp);
     fclose(fp);
#endif
#ifdef WINDOWS
    HCRYPTPROV hProv;
    CryptAcquireContext(&hProv, NULL, NULL,
        PROV_RSA_FULL, CRYPT_VERIFYCONTEXT);
    CryptGenRandom(hProv, len * sizeof(unsigned long long), (BYTE*)buffer);
    CryptReleaseContext(hProv, 0);
#endif
}

inline Int _bm_convert_ull_to_Int(unsigned long long ull, Int min, Int max) {
    return (Int)(ull % (max - min + 1)) + min;
}

Int _bm_round_zero_to_Int(Int x, Int m, Int* c) {
    *c = x / m;
    x %= m;
    while(x < 0) {
        x += m;
        *c -= 1;
    }
    while(x >= m) {
        x -= m;
        *c += 1;
    }
    return x;
}

Float _bm_float_sum(Float* v, Int n) {
    Float sum = 0;
    Int   i;
    for(i = 0; i < n; i++) sum += v[i];
    return sum;
}

Float _bm_float_mean(Float* v, Int n) { return _bm_float_sum(v, n) / n; }

Float _bm_float_var(Float* v, Int n) {
    Float mean, var;
    Int   i;
    mean = _bm_float_mean(v, n);
    var = 0.0;
    for(i = 0; i < n; i++) var += (v[i] - mean) * (v[i] - mean);
    return var / n;
}

Float _bm_float_std(Float* v, Int n, Int correct) {
    Float var = 0.0;
    Int   i;
    for(i = 0; i < n; i++) var += (v[i] - correct) * (v[i] - correct);
    return sqrt(var / (n - correct));
}

inline Float _bm_convert_ull_to_Float(unsigned long long ull, Float min, Float max) {
    return ((double)ull) / ((double)ULONG_LONG_MAX) * (max - min) + min;
}

Float _bm_round_zero_to_Float(Float x, Float m, Float* c) {
    modf(x / m, c);
    x -= (*c) * m;
    while(x < 0) {
        x += m;
        *c -= 1;
    }
    while(x >= m) {
        x -= m;
        *c += 1;
    }
    return x;
}

Float _bm_n_root(Float x, Int n) {
    long double root, y, o;
    y = (long double)x;
    o = (long double)n;
    root = expl(logl(y) / o);
    return (Float)root;
}

void _bm_fft(Int n, Float* x, Complex* X) {
    Int           i;
    double*       in;
    fftw_complex* out;
    fftw_plan     p;

    out = (fftw_complex*)fftw_malloc(sizeof(fftw_complex) * n);
    in = (double*)malloc(sizeof(double) * n);

    p = fftw_plan_dft_r2c_1d(n, in, out, FFTW_ESTIMATE);

    for(i = 0; i < n; i++) in[i] = x[i];
    fftw_execute(p);
    for(i = 0; i < n; i++) X[i] = out[i];

    fftw_destroy_plan(p);
    fftw_free(out);
    free(in);
}

void _bm_ifft(Int n, Float* x, Complex* X) {
    Int           i;
    double*       out;
    fftw_complex* in;
    fftw_plan     p;

    in = (fftw_complex*)fftw_malloc(sizeof(fftw_complex) * n);
    out = (double*)malloc(sizeof(double) * n);

    p = fftw_plan_dft_c2r_1d(n, in, out, FFTW_ESTIMATE);

    for(i = 0; i < n; i++) in[i] = X[i];
    fftw_execute(p);
    for(i = 0; i < n; i++) x[i] = out[i];

    fftw_destroy_plan(p);
    fftw_free(in);
    free(out);
}
