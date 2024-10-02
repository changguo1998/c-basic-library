#ifndef _CBL_BASIC_H_
#define _CBL_BASIC_H_

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>
#include <limits.h>
#include <complex.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>
#include <time.h>
#include <wchar.h>

#include "config.h"

// Bool

typedef bool Bool;

// Char

typedef char Char;

// Integer

typedef unsigned char UInt8;
typedef signed char Int8;
typedef unsigned int UInt32;
typedef int Int32;
typedef unsigned long int UInt64;
typedef signed long int Int64;
typedef unsigned long long int UInt128;
typedef signed long long int Int128;

// Float

typedef float Float32;
typedef double Float64;
typedef long double Float128;

// Complex

typedef float complex Complex32;
typedef double complex Complex64;
typedef long double complex Complex128;

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
#define TYPECODE_String     0b00001111
#define TYPECODE_DateTime   0b00010000

#if USE_64_BIT == 1
typedef Int64 Int;
typedef UInt64 UInt;
typedef Float64 Float;
typedef Complex64 Complex;
#define TYPECODE_INT TYPECODE_INT64
#define TYPECODE_UINT TYPECODE_UINT64
#define TYPECODE_FLOAT TYPECODE_FLOAT64
#define TYPECODE_COMPLEX TYPECODE_COMPLEX64
#else
typedef Int32 Int;
typedef UInt32 UInt;
typedef Float32 Float;
typedef Complex32 Complex;
#define TYPECODE_INT TYPECODE_INT32
#define TYPECODE_UINT TYPECODE_UINT32
#define TYPECODE_FLOAT TYPECODE_FLOAT32
#define TYPECODE_COMPLEX TYPECODE_COMPLEX64
#endif

#endif // _CBL_BASIC_H_
