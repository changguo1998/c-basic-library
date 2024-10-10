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

int main() {
    DateTime dt;
    String   str1,    str2;
    Vector   vec_Int, vec_size;
    Int      shift;

    LOG_init("log_test_CBL.txt");
    vec_size                 = VEC_allocate(TYPECODE_INT, sizeof(Int), 3);
    ((Int*)vec_size.data)[0] = 4;
    ((Int*)vec_size.data)[1] = 3;
    ((Int*)vec_size.data)[2] = 2;
    vec_Int                  = VEC_allocate(TYPECODE_INT, CBL_typecode2size(TYPECODE_INT), 3);
    ((Int*)vec_Int.data)[0]  = 2;
    ((Int*)vec_Int.data)[0]  = 1;
    ((Int*)vec_Int.data)[0]  = 0;
    shift                    = ARR_linear_index(vec_Int, vec_size);
    sprintf(str1.str, "shift: %d", shift);
    str1.len = strlen(str1.str);
    LOG_print_info(str1.str);
    dt = DT_now(1);
    DT_datetime_string(dt, str2.str);
    LOG_print_info(str2.str);

    LOG_final();
    return 0;
}
