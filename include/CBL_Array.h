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

#ifndef _CBL_ARRAY_H_
#define _CBL_ARRAY_H_

#include <stdio.h>
#include "CBL_Basic.h"
#include "CBL_Vector.h"

/**
 * @brief multi-dimension array
 * @param typecode UInt8
 * @param element_size size_t
 * @param size Vector
 * @param data Address
 */
typedef struct _ARR_array_t {
    UInt8   typecode; /**< typecode */
    size_t  element_size; /**< element_size */
    Vector  size; /**< size */
    Address data; /**< data */
} Array;

/**
 * @brief calculate products of all elements in vector, treating elements as Int
 * @param vec Int vector
 * @return product of all elements
 */
Int ARR_prod_Int_vector(const Vector vec);

/**
 * @brief allocate memory for array
 * @param element_size size of element type
 * @param typecode typecode of element
 * @param size vector defines the size of array
 * @return array with allocated memory
 */
Array ARR_allocate(size_t element_size, UInt8 typecode, const Vector size);

/**
 * @brief make a copy of Array, allocate memory and copy for pointers
 * @param arr Array will be copied
 * @return copy of arr
 */
Array ARR_copy(const Array arr);

/**
 * @brief free allocated memory in Array struct
 * @param arr address of array that will be free
 */
void ARR_free(Array* arr);

/**
 * @brief calculate linear index based on cartesidian index and size
 * @param index Int vector stored cartesian index
 * @param size Int vector stored size of array
 * @return linear index(begin with 0)
 */
Int ARR_linear_index(const Vector index, const Vector size);

/**
 * @brief return address of element specified by cartesidian index
 * @param arr array
 * @param index cartesidian index
 * @return address of element
 */
Address ARR_address(const Array arr, const Vector index);

/**
 * @brief write array to file in binary format
 * @param arr array
 * @param fp file pointer
 * @return bytes of written data
 */
size_t ARR_write(const Array arr, FILE* fp);

/**
 * @brief read binary format array from file
 * @param fp file
 * @return an array with memory already allocated
 */
Array ARR_read(FILE* fp);

#endif // _CBL_ARRAY_H_
