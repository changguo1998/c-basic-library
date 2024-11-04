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

#ifndef _TYPE_PART_MATH_BASIC_H_
#define _TYPE_PART_MATH_BASIC_H_

#include <math.h>
#include "Module_Basic.h"

static const long double PI = 3.14159265358979323846264338327950288419716939937511L;

// # int

void _bm_rand_ull_(unsigned long long* buffer, long len);

Int _bm_convert_ull_to_Int(unsigned long long ull, Int min, Int max);

Int _bm_round_zero_to_Int(Int x, Int m, Int* c);

static inline Int _bm_abs_int(Int x) {
#if USE_64_BIT == 1
    return labs(x);
#else
    return abs(x);
#endif
}

// # float

Float _bm_float_sum(Float* v, Int n);

Float _bm_float_mean(Float* v, Int n);

Float _bm_float_var(Float* v, Int n);

Float _bm_float_std(Float* v, Int n, Int correct);

Float _bm_convert_ull_to_Float(unsigned long long ull, Float min, Float max);

Float _bm_round_zero_to_Float(Float x, Float m, Float* c);

static inline Float _bm_abs_float(Float x) {
#if USE_64_BIT == 1
    return fabs(x);
#else
    return fabsf(x);
#endif
}

static inline Float _bm_sqrt(Float x) { return sqrtl(x); }

Float _bm_n_root(Float x, Int n);

static inline Float _bm_deg2rad(Float x) { return x * PI / 180.0; }

static inline Float _bm_rad2deg(Float x) { return x * 180.0 / PI; }

static inline Float _bm_sind(Float x) { return sin(_bm_deg2rad(x)); }

static inline Float _bm_cosd(Float x) { return cos(_bm_deg2rad(x)); }

static inline Float _bm_tand(Float x) { return tan(_bm_deg2rad(x)); }

static inline Float _bm_asind(Float x) { return _bm_rad2deg(asin(x)); }

static inline Float _bm_acosd(Float x) { return _bm_rad2deg(acos(x)); }

static inline Float _bm_atand(Float x) { return _bm_rad2deg(atan(x)); }

static inline Float _bm_atan2d(Float y, Float x) { return _bm_rad2deg(atan2(y, x)); }

#endif // _TYPE_PART_MATH_BASIC_H_
