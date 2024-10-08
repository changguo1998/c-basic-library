#ifndef _CBL_FLOATVECTOR_H_
#define _CBL_FLOATVECTOR_H_

#include "CBL_Basic.h"

void _FLOAT_VECTOR_level0_fill(Float* a, Int n, Float val);

void _FLOAT_VECTOR_level0_rand(Float* a, Int n);

void _FLOAT_VECTOR_level0_randn(Float* a, Int n, Float mean, Float std);

Float _FLOAT_VECTOR_level0_sum(Float* a, Int n);

Float _FLOAT_VECTOR_level0_prod(Float* a, Int n);

void _FLOAT_VECTOR_level0_cumsum(Float* a, Int n);

void _FLOAT_VECTOR_level0_cumprod(Float* a, Int n);

Float _FLOAT_VECTOR_level0_min(Float* a, Int n, Int* mi);

Float _FLOAT_VECTOR_level0_max(Float* a, Int n, Int* mi);

Float _FLOAT_VECTOR_level0_mean(Float* a, Int n);

Float _FLOAT_VECTOR_level0_var(Float* a, Int n);

Float _FLOAT_VECTOR_level0_std(Float* a, Int n);

void _FLOAT_VECTOR_level0_sort(Float* a, Int* perm, Int n);

struct FloatVector {
    Int    len;
    Float* data;
};

#endif // _CBL_FLOATVECTOR_H_
