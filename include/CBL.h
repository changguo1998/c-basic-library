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
#ifndef _CBL_H_
#define _CBL_H_

#include "config.h"
#include "CBL_Basic.h"
#include "CBL_DateTime.h"
#include "CBL_String.h"
#include "CBL_Log.h"
#include "CBL_Vector.h"
#include "CBL_Array.h"
#include "CBL_Dict.h"
#include "CBL_IntVector.h"
#include "CBL_FloatVector.h"
#include "CBL_FloatMatrix.h"
// #include "CBL_TypeArray.h"

/**
 * @brief get sizeof(type) by typecode
 * @param type typecode defined in `CBL_Basic.h` header file
 * @return bytes of type
 */
size_t CBL_typecode2size(UInt8 type);

#endif // _CBL_H_
