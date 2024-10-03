#ifndef _CBL_ARRAY_H_
#define _CBL_ARRAY_H_

#include <stdio.h>
#include "CBL_Basic.h"
#include "CBL_Vector.h"

typedef struct _ARR_array_t {
    UInt8   typecode;
    size_t  element_size;
    Vector  size;
    Address data;
} Array;

Int ARR_prod_Int_vector(const Vector vec);

Array ARR_allocate(size_t element_size, UInt8 typecode, const Vector size);

Array ARR_copy(const Array arr);

void ARR_free(Array* arr);

Int ARR_linear_index(const Vector index, const Vector size);

Address ARR_address(const Array arr, const Vector index);

size_t ARR_write(const Array arr, FILE* fp);

Array ARR_read(FILE* fp);

#endif // _CBL_ARRAY_H_
