#ifndef _CBL_VECTOR_H_
#define _CBL_VECTOR_H_

#include "CBL_Basic.h"

typedef struct _VEC_vector_t {
    size_t elsize;
    UInt8 typecode;
    Int len;
    void* value;
} Vector;

Vector VEC_new(size_t elsize, UInt8 typecode, Int len);

Vector VEC_empty_vector();

Vector VEC_copy(Vector v);

void VEC_free(Vector* v);

void* VEC_addr(Vector v, UInt i);

size_t VEC_write(Vector v, FILE* fp);

Vector VEC_read(FILE* fp);

#endif // _CBL_VECTOR_H_
