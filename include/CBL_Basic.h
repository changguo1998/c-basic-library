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

#ifndef _CBL_BASIC_H_
#define _CBL_BASIC_H_

#include <complex.h>
#include <stdbool.h>


#define USE_64_BIT 1

// #define STRING_MAX_LENGTH 256
// #define STRING_MAX_LENGTH 512
#define STRING_MAX_LENGTH 1024
// #define STRING_MAX_LENGTH 2048

// 10^(-n) second
// #define TIME_PRECISION 0
// #define TIME_PRECISION 3
#define TIME_PRECISION 6
// #define TIME_PRECISION 9

#define LOG_MAX_FILE_NAME_LENGTH 2048

#define STATIC_DICT_SIZE 128

#define TABLE_MAX_COLUMNS 64

// # Type define

// Bool
/**
 * @brief true/false
 */
typedef bool Bool;

// Char
/**
 * @brief signed char
 */
typedef char Char;

// Integer

/**
 * @brief unsigned 8-bit integer
 */
typedef unsigned char UInt8;

/**
 * @brief signed 8-bit integer
 */
typedef signed char Int8;

/**
 * @brief unsigned 32-bit integer
 */
typedef unsigned int UInt32;

/**
 * @brief signed 32-bit integer
 */
typedef int Int32;

/**
 * @brief unsigned 64-bit integer
 */
typedef unsigned long int UInt64;

/**
 * @brief signed 64-bit integer
 */
typedef signed long int Int64;

/**
 * @brief unsigned 128-bit integer
 */
typedef unsigned long long int UInt128;

/**
 * @brief signed 128-bit integer
 */
typedef signed long long int Int128;

// Float

/**
 * @brief 32-bit float
 */
typedef float Float32;

/**
 * @brief 64-bit float
 */
typedef double Float64;

/**
 * @brief 128-bit float
 */
typedef long double Float128;

// Complex

typedef float complex       Complex32;
typedef double complex      Complex64;
typedef long double complex Complex128;

// Pointer
typedef void* Address;

// type code
// 7 single 0 / array 1
// 6 \.
// 5  \.
// 4   \.
// 3    - bit type
// 2   /
// 1  /
// 0 /


#define TYPECODE_UNKNOWN    0
#define TYPECODE_INT8       1
#define TYPECODE_UINT8      2
#define TYPECODE_INT32      3
#define TYPECODE_UINT32     4
#define TYPECODE_INT64      5
#define TYPECODE_UINT64     6
#define TYPECODE_INT128     7
#define TYPECODE_UINT128    8
#define TYPECODE_FLOAT32    9
#define TYPECODE_FLOAT64    10
#define TYPECODE_FLOAT128   11
#define TYPECODE_COMPLEX32  12
#define TYPECODE_COMPLEX64  13
#define TYPECODE_COMPLEX128 14
#define TYPECODE_STRING     15
#define TYPECODE_DATE       16
#define TYPECODE_TIME       17
#define TYPECODE_DATETIME   18
#define TYPECODE_TABLE      19


#if USE_64_BIT == 1

/**
 * @brief 64-bit integer
 */
typedef Int64 Int;

/**
 * @brief 64-bit unsigned integer
 */
typedef UInt64 UInt;

/**
 * @brief 64-bit float
 */
typedef Float64 Float;

/**
 * @brief 64-bit complex
 */
typedef Complex64 Complex;
#define TYPECODE_INT     TYPECODE_INT64
#define TYPECODE_UINT    TYPECODE_UINT64
#define TYPECODE_FLOAT   TYPECODE_FLOAT64
#define TYPECODE_COMPLEX TYPECODE_COMPLEX64
#else
/**
 * @brief 32-bit integer
 */
typedef Int32     Int;

/**
 * @brief 32-bit unsigned integer
 */
typedef UInt32    UInt;
/**
 * @brief 32-bit float
 */
typedef Float32   Float;

/**
 * @brief 32-bit complex
 */
typedef Complex32 Complex;
#define TYPECODE_INT     TYPECODE_INT32
#define TYPECODE_UINT    TYPECODE_UINT32
#define TYPECODE_FLOAT   TYPECODE_FLOAT32
#define TYPECODE_COMPLEX TYPECODE_COMPLEX64
#endif

// # Error handling

void error_exit();

void error_invalid_argument(const char* msg);

void error_index_out_of_bounds(const char* msg);

void error_not_initialized(const char* msg);

void error_out_of_memory(const char* msg);

void error_unexpected_allocated_memory(const char* msg);

#endif // _CBL_BASIC_H_
