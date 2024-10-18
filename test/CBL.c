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

#include <string.h>
#include "CBL.h"

VectorN(Int, 3)
VectorN(Int, 4)

int main() {
    CBL_DECLARE_VARS(DateTime, 1, dt);
    CBL_DECLARE_VARS(String, 2, str1, str2);
    CBL_DECLARE_VARS(IntVector, 2, vec_Int, vec_size);

    Int shift, i;

    LOG_init("log_test_CBL.txt");

    CBL_CALL(vec_size, alloc_, 3);
    CBL_CALL(vec_Int, alloc_, 3);
    vec_size.data[0] = 4;
    vec_size.data[1] = 3;
    vec_size.data[2] = 2;
    vec_Int.data[0] = 2;
    vec_Int.data[1] = 1;
    vec_Int.data[2] = 0;
    shift = vec_Int.data[2];
    for (i = 1; i >=0 ; i--) {
        shift *= vec_size.data[i];
        shift += vec_Int.data[i];
    }
    sprintf(str1.str, "shift: %d", shift);
    str1.len = (Int)strlen(str1.str);
    LOG_print_info(str1.str);
    CBL_CALL(dt, now_, 1);
    str2 = CBL_CALL(dt, string);
    LOG_print_info(str2.str);

    LOG_final();
    return 0;
}
