#
# MIT License
#
# Copyright (c) 2024 Chang Guo
#
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in all
# copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
# SOFTWARE.
#
#

target="../include/Module_Part_Macro_Loop_Basic.h"
Max_macro_expansion=64
header_guard="_MODULE_PART_MACRO_LOOP_BASIC_H_"

echo "#ifndef ${header_guard}" > ${target}
echo "#define ${header_guard}" >> ${target}
echo "" >> ${target}

echo "#define _CBL_NEW_VAR(type, varname) type##_new_(&(varname))" >> ${target}
echo "#define _CBL_NEW_VAR_1(type, varname, ...) _CBL_NEW_VAR(type, varname)" >> ${target}
for((i=2; i<=${Max_macro_expansion}; i++)); do
    echo "#define _CBL_NEW_VAR_${i}(type, varname, ...) _CBL_NEW_VAR(type, varname); _CBL_NEW_VAR_$((i-1))(type, __VA_ARGS__)" >> ${target}
done

echo """
/**
 * @brief declear and assign methods to vars defined in CBL
 * @param type
 * @param N
 * @param var_list
 */
#define CBL_DECLARE_VARS(type, N, ...) struct type __VA_ARGS__; _CBL_NEW_VAR_##N(type, __VA_ARGS__)
""" >> ${target}

echo "#define _CBL_FREE_VAR(type, varname) type##_free_(&(varname))" >> ${target}
echo "#define _CBL_FREE_VAR_1(type, varname, ...) _CBL_FREE_VAR(type, varname)" >> ${target}
for((i=2; i<=${Max_macro_expansion}; i++)); do
    echo "#define _CBL_FREE_VAR_${i}(type, varname, ...) _CBL_FREE_VAR(type, varname); _CBL_FREE_VAR_$((i-1))(type, __VA_ARGS__)" >> ${target}
done

echo """
/**
 * @brief free allocated memories of vars defined in CBL. Types need to free:\n
 * Table,\n IntVector,\n FloatVector,\n IntMatrix,\n FloatMatrix
 * @param type
 * @param N
 * @param var_list
 */
#define CBL_FREE_VARS(type, N, ...) _CBL_FREE_VAR_##N(type, __VA_ARGS__)
""" >> ${target}
echo "#endif // ${header_guard}" >> ${target}
