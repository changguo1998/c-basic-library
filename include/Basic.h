#ifndef _BASIC_H_
#define _BASIC_H_

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>
#include <complex.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>
#include <time.h>

#define USE_64_BIT 1

// Integer

typedef unsigned char uint8;
typedef signed char int8;
typedef unsigned int uint32;
typedef int int32;
typedef unsigned long int uint64;
typedef signed long int int64;
typedef unsigned long long int uint128;
typedef signed long long int int128;

// Float

typedef float float32;
typedef double float64;
typedef long double float128;

// Complex

typedef float complex complex32;
typedef double complex complex64;
typedef long double complex complex128;

#if USE_64_BIT == 1
typedef int64 Int;
typedef uint64 UInt;
typedef float64 Float;
typedef complex64 Complex;
#else
typedef int32 Int;
typedef uint32 UInt;
typedef float32 Float;
typedef complex32 Complex;
#endif

#endif // _BASIC_H_
