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

#ifndef {{INCLUDE_GUARD}}
#define {{INCLUDE_GUARD}}

#include "CBL_Basic.h"

struct {{array_type}}{
    Int {{dimension_variables_list}};
    {{dimension_weight}}
    {{element_type}}* data;
    struct {{array_type}}Methods *methods;
};

struct {{array_type}}Methods {

{{methods_function_pointer_list}}

};

{{methods_function_declaration_list}}

extern struct {{array_type}}Methods {{global_method_struct}};

static inline void {{array_type}}_new_(struct {{array_type}} *this){
    {{dimension_variables_initialization}}
    this->data = NULL;
    this->methods = &{{global_method_struct}};
}

#endif // {{INCLUDE_GUARD}}
