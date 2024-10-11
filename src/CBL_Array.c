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

#include <string.h>
#include "CBL_Array.h"
#include "CBL_Log.h"

Int ARR_prod_Int_vector(const Vector vec) {
    Int n, i, *v;
    v = (Int*)vec.data;
    n = 1;
    for(i = 0; i < vec.len; i++) n *= v[i];
    return n;
}

Array ARR_allocate(size_t element_size, Int typecode, const Vector size) {
    Array arr;
    Int   n;
    arr.element_size = element_size;
    arr.typecode     = typecode;
    arr.size         = VEC_copy(size);
    n                = ARR_prod_Int_vector(arr.size);
    arr.data         = calloc(n, element_size);
    return arr;
}

Array ARR_copy(const Array arr) {
    Array arr_copy;
    arr_copy.element_size = arr.element_size;
    arr_copy.typecode     = arr.typecode;
    arr_copy.size         = VEC_copy(arr.size);
    arr_copy.data         = calloc(ARR_prod_Int_vector(arr.size), arr.element_size);
    memcpy(arr_copy.data, arr.data, ARR_prod_Int_vector(arr.size) * arr.element_size);
    return arr_copy;
}

void ARR_free(Array* arr) {
    VEC_free(&(arr->size));
    free(arr->data);
    arr->data = NULL;
}

Int ARR_linear_index(const Vector index, const Vector size) {
    Int *s, *c, i, shift;
    if(index.len != size.len) {
        printf("(ARR_linear_index) index length mismatch\n");
        return -1;
    }
    c     = (Int*)index.data;
    s     = (Int*)size.data;
    shift = 0;
    for(i = index.len; i > 0; i--) {
        shift *= s[i - 1];
        shift += c[i - 1];
    }
    return shift;
}

Address ARR_address(const Array arr, const Vector index) {
    return arr.data + ARR_linear_index(index, arr.size) * arr.element_size;
}

size_t ARR_write(const Array arr, FILE* fp) {
    size_t bytes_written = 0;
    bytes_written += fwrite(&(arr.element_size), sizeof(size_t), 1, fp);
    bytes_written += VEC_write(arr.size, fp);
    bytes_written += fwrite(arr.data, arr.element_size, ARR_prod_Int_vector(arr.size), fp);
    return bytes_written;
}

Array ARR_read(FILE* fp) {
    Array arr;
    Int   n;
    arr.typecode = 0;
    fread(&(arr.element_size), sizeof(size_t), 1, fp);
    arr.size = VEC_read(fp);
    n        = ARR_prod_Int_vector(arr.size);
    arr.data = calloc(n, arr.element_size);
    fread(arr.data, arr.element_size, n, fp);
    return arr;
}
