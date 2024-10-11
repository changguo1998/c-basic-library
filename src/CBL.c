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
#include "CBL.h"

size_t CBL_typecode2size(Int type) {
    switch(type) {
    case TYPECODE_INT8 : return sizeof(Int8);
    case TYPECODE_UINT8 : return sizeof(UInt8);
    case TYPECODE_INT32 : return sizeof(Int32);
    case TYPECODE_UINT32 : return sizeof(UInt32);
    case TYPECODE_INT64 : return sizeof(Int64);
    case TYPECODE_UINT64 : return sizeof(UInt64);
    case TYPECODE_INT128 : return sizeof(Int128);
    case TYPECODE_UINT128 : return sizeof(UInt128);
    case TYPECODE_FLOAT32 : return sizeof(Float32);
    case TYPECODE_FLOAT64 : return sizeof(Float64);
    case TYPECODE_FLOAT128 : return sizeof(Float128);
    case TYPECODE_COMPLEX32 : return sizeof(Complex32);
    case TYPECODE_COMPLEX64 : return sizeof(Complex64);
    case TYPECODE_COMPLEX128 : return sizeof(Complex128);
    case TYPECODE_STRING : return sizeof(struct String);
    case TYPECODE_DATE : return sizeof(struct Date);
    case TYPECODE_TIME : return sizeof(struct Time);
    case TYPECODE_DATETIME : return sizeof(struct DateTime);
    default : return 0;
    }
}
