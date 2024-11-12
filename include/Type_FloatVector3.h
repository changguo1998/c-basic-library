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

#ifndef _TYPE_FLOATVECTOR3_H_
#define _TYPE_FLOATVECTOR3_H_

#include <math.h>
#include "Type_Part_math_basic.h"

#ifdef FloatVector3_external_methods_on
#define FloatVector3_external_methods_flag
#define FloatVector3_external_methods_append_declaration FloatVector3_external_methods_declaration
#define FloatVector3_external_methods_append_defination FloatVector3_external_methods_defination
#define FloatVector3_external_methods_append_address FloatVector3_external_methods_address
#else
#define FloatVector3_external_methods_on
#define FloatVector3_external_methods_flag FLAG ,
#define FloatVector3_external_methods_append_declaration
#define FloatVector3_external_methods_append_defination
#define FloatVector3_external_methods_append_address
#endif

#define FloatVector3_external_methods_declaration \
FloatVector3_external_methods_flag \
struct FloatVector3 (*cross)(const struct FloatVector3 *this, struct FloatVector3 b);\
Float (*norm)(const struct FloatVector3 *this, Int order);\
void (*normalize_)(struct FloatVector3 *this, Int order);

#define FloatVector3_external_methods_defination \
FloatVector3_external_methods_flag \
static inline struct FloatVector3 FloatVector3_cross(const struct FloatVector3 *this, struct FloatVector3 b){\
    CBL_DECLARE_VARS(FloatVector3, 1, result);\
    result.data[0] = this->data[1]*b.data[2] - this->data[2]*b.data[1];\
    result.data[1] = this->data[2]*b.data[0] - this->data[0]*b.data[2];\
    result.data[2] = this->data[0]*b.data[1] - this->data[1]*b.data[0];\
    return result;\
}\
static inline Float FloatVector3_norm(const struct FloatVector3 *this, Int order){\
    Int i;\
    Float m = _VECTOR_N_VA_ARG_MIN_Float;\
    if(order<0){\
        for(i=0; i < 3; i++) m = (m > fabs(this->data[i])) ? m : fabs(this->data[i]); \
        return m;\
    }\
    else if(order == 0)\
        return 3.0;\
    else if(order == 1)\
        return fabs(this->data[0])+fabs(this->data[1])+fabs(this->data[2]);\
    else if(order == 2)\
        return sqrt(this->data[0]*this->data[0]+this->data[1]*this->data[1]+this->data[2]*this->data[2]);\
    for(i=0; i < 3; i++) m += pow(fabs(this->data[i]), order);\
    return _bm_n_root(m, order);\
}\
static inline void FloatVector3_normalize_(struct FloatVector3 *this, Int order){\
    Int i;\
    Float n;\
    n = FloatVector3_norm(this, order);\
    if(n==0) error_invalid_argument("(FloatVector3_normalize_) norm is 0");\
    for(i=0; i<3; i++) this->data[i] /= n;\
}


#define FloatVector3_external_methods_address \
FloatVector3_external_methods_flag \
,&FloatVector3_cross \
,&FloatVector3_norm \
,&FloatVector3_normalize_


#endif // _TYPE_FLOATVECTOR3_H_
