#ifndef _CBL_VECTOR_H_
#define _CBL_VECTOR_H_

#include <stdio.h>
#include "CBL_Basic.h"

typedef struct _VEC_vector_t {
    UInt8   typecode;
    size_t  element_elsize;
    Int     len;
    Address data;
} Vector;

Vector VEC_allocate(UInt8 typecode, size_t element_size, Int len);

Vector VEC_empty_vector();

Vector VEC_copy(const Vector v);

void VEC_free(Vector* v);

Address VEC_address(const Vector v, Int i);

size_t VEC_write(const Vector v, FILE* fp);

Vector VEC_read(FILE* fp);

#endif // _CBL_VECTOR_H_
