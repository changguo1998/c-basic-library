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

#include <stdlib.h>
// #include <complex.h>
#include <stdbool.h>
#include <float.h>
#include <limits.h>


#define USE_64_BIT 1

// #define STRING_FIXED_BUFFER_LENGTH 8
// #define STRING_FIXED_BUFFER_LENGTH 256
// #define STRING_FIXED_BUFFER_LENGTH 512
#define STRING_FIXED_BUFFER_LENGTH 1024
// #define STRING_FIXED_BUFFER_LENGTH 2048
// #define STRING_FIXED_BUFFER_LENGTH 4096
// #define STRING_FIXED_BUFFER_LENGTH 8192
// #define STRING_FIXED_BUFFER_LENGTH 16384

// 10^(-n) second
// #define TIME_PRECISION 0
// #define TIME_PRECISION 3
#define TIME_PRECISION 6
// #define TIME_PRECISION 9

#define LOG_MAX_FILE_NAME_LENGTH 2048

#define STATIC_DICT_SIZE 128

#define TABLE_MAX_COLUMNS 64

// # test system

#ifdef __unix__
#define UNIX 1
#elif defined(_WIN32) || defined(_WIN64)
#define WINDOWS 1
#endif

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

#include "Type_Complex.h"

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

#define TYPECODE_INT     TYPECODE_INT64
#define TYPECODE_UINT    TYPECODE_UINT64
#define TYPECODE_FLOAT   TYPECODE_FLOAT64
#define TYPECODE_COMPLEX TYPECODE_COMPLEX64

// limits
#define CBL_INT_MIN LONG_MIN
#define CBL_INT_MAX LONG_MAX
#define CBL_FLOAT_MIN DBL_MIN
#define CBL_FLOAT_MAX DBL_MAX

#define _VECTOR_N_VA_ARG_TYPE_Int long
#define _VECTOR_N_VA_ARG_MIN_Int LONG_MIN
#define _VECTOR_N_VA_ARG_MAX_Int LONG_MAX
#define _VECTOR_N_VA_ARG_TYPE_Float double
#define _VECTOR_N_VA_ARG_MIN_Float DBL_MIN
#define _VECTOR_N_VA_ARG_MAX_Float DBL_MAX
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

#define TYPECODE_INT     TYPECODE_INT32
#define TYPECODE_UINT    TYPECODE_UINT32
#define TYPECODE_FLOAT   TYPECODE_FLOAT32
#define TYPECODE_COMPLEX TYPECODE_COMPLEX64

// limits
#define CBL_INT_MIN INT_MIN
#define CBL_INT_MAX INT_MAX
#define CBL_FLOAT_MIN FLT_MIN
#define CBL_FLOAT_MAX FLT_MAX

#define _VECTOR_N_VA_ARG_TYPE_Int int
#define _VECTOR_N_VA_ARG_MIN_Int INT_MIN
#define _VECTOR_N_VA_ARG_MAX_Int INT_MAX
#define _VECTOR_N_VA_ARG_TYPE_Float double
#define _VECTOR_N_VA_ARG_MIN_Float FLT_MIN
#define _VECTOR_N_VA_ARG_MAX_Float FLT_MAX
#endif

DEFINE_COMPLEX(Float, Complex,)

// # Error handling

void error_exit();
void error_invalid_argument(const char* msg);
void error_index_out_of_bounds(const char* msg);
void error_not_initialized(const char* msg);
void error_out_of_memory(const char* msg);
void error_unexpected_allocated_memory(const char* msg);
void error_file_not_exists(const char* msg);
void error_failed_open_file(const char* msg);

// # Flags

#define VECTOR_INDEX_END (INT_MAX)

// # type define macros

#define _CBL_MACRO_EXPAND(...) __VA_ARGS__

#define _CBL_MACRO_EMPTY(...)

#define _CBL_MACRO_SECOND_TO_END(a, ...) __VA_ARGS__

#include "Module_Part_Macro_Loop_Basic.h"

#define _CBL_CALL_METHOD(obj, f, ...) ((obj).methods->f(&(obj), ##__VA_ARGS__))

#define CBL_CALL(...) _CBL_CALL_METHOD(__VA_ARGS__)

// newly defined types

/**
 * @brief Date: year; month; day;
 */
struct Date {
    Int year, month, day;

    struct DateMethods* methods;
};

struct Time {
    Int hour;
    Int minute;
    Int second;
#if TIME_PRECISION > 0
    Int millisecond;
#endif
#if TIME_PRECISION > 3
    Int macrosecond;
#endif
#if TIME_PRECISION > 6
 Int nanosecond;
#endif
    struct TimeMethods* methods;
};

struct DateTime {
    struct Date date;
    struct Time time;

    struct DateTimeMethods* methods;
};

struct String {
    Char  str[STRING_FIXED_BUFFER_LENGTH];
    Int   len;
    Char* more;

    const struct StringMethods* methods;
};

/**
 * @brief struct StaticDict
 * @param key String[]
 * @param flag Bool[]
 * @param typecode Int[]
 * @param address Address[]
 * @param methods
 */
struct StaticDict {
    struct String key[STATIC_DICT_SIZE];

    Bool    flag[STATIC_DICT_SIZE];
    Int     typecode[STATIC_DICT_SIZE];
    Address address[STATIC_DICT_SIZE];

    struct StaticDictMethods* methods;
};

struct DynamicDict {
    struct DynamicDictNode*    data;
    struct DynamicDictMethods* methods;
};

struct Table {
    Int  nrow, ncol;
    Bool linear_row;
    Int  elsize[TABLE_MAX_COLUMNS];

    Address addr[TABLE_MAX_COLUMNS];

    struct String* row_name;
    struct String  col_name[TABLE_MAX_COLUMNS];

    struct TableMethods* methods;
};

// Vectors

struct IntVector {
    Int  len;
    Int* data;

    struct IntVectorMethods* methods;
};

struct FloatVector {
    Int    len;
    Float* data;

    struct FloatVectorMethods* methods;
};

struct ComplexVector {
    Int      len;
    Complex* data;

    struct ComplexVectorMethods* methods;
};

// Matrixs

struct FloatMatrix {
    Int    nrow, ncol;
    Float* data;

    struct FloatMatrixMethods* methods;
};

struct ComplexMatrix {
    Int      nrow, ncol;
    Complex* data;

    struct ComplexMatrixMethods* methods;
};

// general function types

#define _CBL_GENERAL_FUNCTION_TYPEDEFINE(S, s, T, t, ...)\
    typedef S (*s##_Func_##t)(T);\
    typedef S (*s##_Func_##t##t)(T, T);

/*
 * abbreviations
 * i - Int
 * u - UInt
 * a - Address(void*)
 * f - Float
 * c - Complex
 * d - Date
 * t - Time
 * s - String
 */

_CBL_GENERAL_FUNCTION_TYPEDEFINE(Int, i, Int, i)
_CBL_GENERAL_FUNCTION_TYPEDEFINE(Float, f, Float, f)
_CBL_GENERAL_FUNCTION_TYPEDEFINE(Complex, c, Complex, c)
_CBL_GENERAL_FUNCTION_TYPEDEFINE(Float, f, Complex, c)
_CBL_GENERAL_FUNCTION_TYPEDEFINE(Complex, c, Float, f)
_CBL_GENERAL_FUNCTION_TYPEDEFINE(Int, i, struct Date, d)
_CBL_GENERAL_FUNCTION_TYPEDEFINE(Int, i, struct Time, t)
_CBL_GENERAL_FUNCTION_TYPEDEFINE(Int, i, struct String, s)
_CBL_GENERAL_FUNCTION_TYPEDEFINE(Float, f, struct String, s)

#endif // _CBL_BASIC_H_
