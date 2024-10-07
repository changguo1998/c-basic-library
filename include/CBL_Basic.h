#ifndef _CBL_BASIC_H_
#define _CBL_BASIC_H_

#include <complex.h>
#include <stdbool.h>

#include "config.h"

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
typedef unsigned char          UInt8;

/**
 * @brief signed 8-bit integer
 */
typedef signed char            Int8;

/**
 * @brief unsigned 32-bit integer
 */
typedef unsigned int           UInt32;

/**
 * @brief signed 32-bit integer
 */
typedef int                    Int32;

/**
 * @brief unsigned 64-bit integer
 */
typedef unsigned long int      UInt64;

/**
 * @brief signed 64-bit integer
 */
typedef signed long int        Int64;

/**
 * @brief unsigned 128-bit integer
 */
typedef unsigned long long int UInt128;

/**
 * @brief signed 128-bit integer
 */
typedef signed long long int   Int128;

// Float

/**
 * @brief 32-bit float
 */
typedef float       Float32;

/**
 * @brief 64-bit float
 */
typedef double      Float64;

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


#define TYPECODE_UNKNOWN    0b00000000
#define TYPECODE_INT8       0b00000001
#define TYPECODE_UINT8      0b00000010
#define TYPECODE_INT32      0b00000011
#define TYPECODE_UINT32     0b00000100
#define TYPECODE_INT64      0b00000101
#define TYPECODE_UINT64     0b00000110
#define TYPECODE_INT128     0b00000111
#define TYPECODE_UINT128    0b00001000
#define TYPECODE_FLOAT32    0b00001001
#define TYPECODE_FLOAT64    0b00001010
#define TYPECODE_FLOAT128   0b00001011
#define TYPECODE_COMPLEX32  0b00001100
#define TYPECODE_COMPLEX64  0b00001101
#define TYPECODE_COMPLEX128 0b00001110
#define TYPECODE_STRING     0b00001111
#define TYPECODE_DATE       0b00010000
#define TYPECODE_TIME       0b00010001
#define TYPECODE_DATETIME   0b00010010
#define TYPECODE_SHEET      0b00010011


#if USE_64_BIT == 1

/**
 * @brief 64-bit integer
 */
typedef Int64     Int;

/**
 * @brief 64-bit unsigned integer
 */
typedef UInt64    UInt;

/**
 * @brief 64-bit float
 */
typedef Float64   Float;

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

#endif // _CBL_BASIC_H_
