#include "CBL_Vector.h"


Vector VEC_new(size_t elsize, UInt8 typecode, Int len) {
    Vector v;
    v.elsize = elsize;
    v.typecode = typecode;
    v.len = len;
    v.value = calloc(len, elsize);
    return v;
}

Vector VEC_empty_vector() {
    Vector v;
    v.elsize = sizeof(Int);
    v.len = 0;
    v.typecode = TYPECODE_INT;
    v.value = NULL;
    return v;
}

Vector VEC_copy(Vector v) {
    Vector w;
    w.elsize = v.elsize;
    w.typecode = v.typecode;
    w.len = v.len;
    w.value = calloc(v.len, w.elsize);
    memcpy(w.value, v.value, v.len * v.elsize);
    return w;
}

void VEC_free(Vector* v) {
    if(v->value != NULL) {
        free(v->value);
        v->len = 0;
    }
}

void* VEC_addr(Vector v, UInt i) { return (void*)((Int*)v.value + i * v.elsize); }

size_t VEC_write(Vector v, FILE* fp) {
    size_t count = 0;
    count += fwrite(&(v.elsize), sizeof(size_t), 1, fp);
    count += fwrite(&(v.typecode), sizeof(UInt8), 1, fp);
    count += fwrite(&(v.len), sizeof(Int), 1, fp);
    count += fwrite(v.value, v.elsize, v.len, fp);
    return count;
}

Vector VEC_read(FILE* fp) {
    Vector v;
    v = VEC_empty_vector();
    fread(&(v.elsize), sizeof(size_t), 1, fp);
    fread(&(v.typecode), sizeof(UInt8), 1, fp);
    fread(&(v.len), sizeof(Int), 1, fp);
    v.value = calloc(v.len, v.elsize);
    fread(v.value, v.elsize, v.len, fp);
    return v;
}
