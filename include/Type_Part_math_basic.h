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

#include "Module_Basic.h"

// # int

void _bm_rand_ull_(unsigned long long* buffer, long len);
Int _bm_convert_ull_to_Int(unsigned long long ull, Int min, Int max);

// # float

Float _bm_float_sum(Float* v, Int n);
Float _bm_float_mean(Float* v, Int n);
Float _bm_float_var(Float* v, Int n);
Float _bm_float_std(Float* v, Int n, Int correct);
Float _bm_convert_ull_to_Float(unsigned long long ull, Float min, Float max);

Float _bm_n_root(Float x, Int n);

#endif // _TYPE_PART_MATH_BASIC_H_
