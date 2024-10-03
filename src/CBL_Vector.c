#include <stdlib.h>
#include <string.h>
#include "CBL_Vector.h"

Vector VEC_allocate(UInt8 typecode, size_t element_size, Int len) {
    Vector v;
    v.typecode       = typecode;
    v.element_elsize = element_size;
    v.len            = len;
    v.data           = calloc(len, element_size);
    return v;
}

Vector VEC_empty_vector() {
    Vector v;
    v.typecode       = TYPECODE_UNKNOWN;
    v.element_elsize = sizeof(Int);
    v.len            = 0;
    v.data           = NULL;
    return v;
}

Vector VEC_copy(const Vector v) {
    Vector w;
    w.typecode       = v.typecode;
    w.element_elsize = v.element_elsize;
    w.len            = v.len;
    w.data           = calloc(v.len, w.element_elsize);
    memcpy(w.data, v.data, v.len * v.element_elsize);
    return w;
}

void VEC_free(Vector* v) {
    if(v->data != NULL) {
        free(v->data);
        v->data = NULL;
        v->len  = 0;
    }
}

void* VEC_address(const Vector v, Int i) { return v.data + i * v.element_elsize; }

size_t VEC_write(const Vector v, FILE* fp) {
    size_t count = 0;
    count += fwrite(&(v.element_elsize), sizeof(size_t), 1, fp);
    count += fwrite(&(v.len), sizeof(Int), 1, fp);
    count += fwrite(v.data, v.element_elsize, v.len, fp);
    return count;
}

Vector VEC_read(FILE* fp) {
    Vector v;
    v = VEC_empty_vector();
    fread(&(v.element_elsize), sizeof(size_t), 1, fp);
    fread(&(v.len), sizeof(Int), 1, fp);
    v.data = calloc(v.len, v.element_elsize);
    fread(v.data, v.element_elsize, v.len, fp);
    return v;
}
