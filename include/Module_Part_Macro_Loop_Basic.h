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

#ifndef _MODULE_PART_MACRO_LOOP_BASIC_H_
#define _MODULE_PART_MACRO_LOOP_BASIC_H_

#define _CBL_NEW_VAR(type, varname) type##_new_(&(varname))
#define _CBL_NEW_VAR_1(type, varname, ...) _CBL_NEW_VAR(type, varname)
#define _CBL_NEW_VAR_2(type, varname, ...) _CBL_NEW_VAR(type, varname); _CBL_NEW_VAR_1(type, __VA_ARGS__)
#define _CBL_NEW_VAR_3(type, varname, ...) _CBL_NEW_VAR(type, varname); _CBL_NEW_VAR_2(type, __VA_ARGS__)
#define _CBL_NEW_VAR_4(type, varname, ...) _CBL_NEW_VAR(type, varname); _CBL_NEW_VAR_3(type, __VA_ARGS__)
#define _CBL_NEW_VAR_5(type, varname, ...) _CBL_NEW_VAR(type, varname); _CBL_NEW_VAR_4(type, __VA_ARGS__)
#define _CBL_NEW_VAR_6(type, varname, ...) _CBL_NEW_VAR(type, varname); _CBL_NEW_VAR_5(type, __VA_ARGS__)
#define _CBL_NEW_VAR_7(type, varname, ...) _CBL_NEW_VAR(type, varname); _CBL_NEW_VAR_6(type, __VA_ARGS__)
#define _CBL_NEW_VAR_8(type, varname, ...) _CBL_NEW_VAR(type, varname); _CBL_NEW_VAR_7(type, __VA_ARGS__)
#define _CBL_NEW_VAR_9(type, varname, ...) _CBL_NEW_VAR(type, varname); _CBL_NEW_VAR_8(type, __VA_ARGS__)
#define _CBL_NEW_VAR_10(type, varname, ...) _CBL_NEW_VAR(type, varname); _CBL_NEW_VAR_9(type, __VA_ARGS__)
#define _CBL_NEW_VAR_11(type, varname, ...) _CBL_NEW_VAR(type, varname); _CBL_NEW_VAR_10(type, __VA_ARGS__)
#define _CBL_NEW_VAR_12(type, varname, ...) _CBL_NEW_VAR(type, varname); _CBL_NEW_VAR_11(type, __VA_ARGS__)
#define _CBL_NEW_VAR_13(type, varname, ...) _CBL_NEW_VAR(type, varname); _CBL_NEW_VAR_12(type, __VA_ARGS__)
#define _CBL_NEW_VAR_14(type, varname, ...) _CBL_NEW_VAR(type, varname); _CBL_NEW_VAR_13(type, __VA_ARGS__)
#define _CBL_NEW_VAR_15(type, varname, ...) _CBL_NEW_VAR(type, varname); _CBL_NEW_VAR_14(type, __VA_ARGS__)
#define _CBL_NEW_VAR_16(type, varname, ...) _CBL_NEW_VAR(type, varname); _CBL_NEW_VAR_15(type, __VA_ARGS__)
#define _CBL_NEW_VAR_17(type, varname, ...) _CBL_NEW_VAR(type, varname); _CBL_NEW_VAR_16(type, __VA_ARGS__)
#define _CBL_NEW_VAR_18(type, varname, ...) _CBL_NEW_VAR(type, varname); _CBL_NEW_VAR_17(type, __VA_ARGS__)
#define _CBL_NEW_VAR_19(type, varname, ...) _CBL_NEW_VAR(type, varname); _CBL_NEW_VAR_18(type, __VA_ARGS__)
#define _CBL_NEW_VAR_20(type, varname, ...) _CBL_NEW_VAR(type, varname); _CBL_NEW_VAR_19(type, __VA_ARGS__)
#define _CBL_NEW_VAR_21(type, varname, ...) _CBL_NEW_VAR(type, varname); _CBL_NEW_VAR_20(type, __VA_ARGS__)
#define _CBL_NEW_VAR_22(type, varname, ...) _CBL_NEW_VAR(type, varname); _CBL_NEW_VAR_21(type, __VA_ARGS__)
#define _CBL_NEW_VAR_23(type, varname, ...) _CBL_NEW_VAR(type, varname); _CBL_NEW_VAR_22(type, __VA_ARGS__)
#define _CBL_NEW_VAR_24(type, varname, ...) _CBL_NEW_VAR(type, varname); _CBL_NEW_VAR_23(type, __VA_ARGS__)
#define _CBL_NEW_VAR_25(type, varname, ...) _CBL_NEW_VAR(type, varname); _CBL_NEW_VAR_24(type, __VA_ARGS__)
#define _CBL_NEW_VAR_26(type, varname, ...) _CBL_NEW_VAR(type, varname); _CBL_NEW_VAR_25(type, __VA_ARGS__)
#define _CBL_NEW_VAR_27(type, varname, ...) _CBL_NEW_VAR(type, varname); _CBL_NEW_VAR_26(type, __VA_ARGS__)
#define _CBL_NEW_VAR_28(type, varname, ...) _CBL_NEW_VAR(type, varname); _CBL_NEW_VAR_27(type, __VA_ARGS__)
#define _CBL_NEW_VAR_29(type, varname, ...) _CBL_NEW_VAR(type, varname); _CBL_NEW_VAR_28(type, __VA_ARGS__)
#define _CBL_NEW_VAR_30(type, varname, ...) _CBL_NEW_VAR(type, varname); _CBL_NEW_VAR_29(type, __VA_ARGS__)
#define _CBL_NEW_VAR_31(type, varname, ...) _CBL_NEW_VAR(type, varname); _CBL_NEW_VAR_30(type, __VA_ARGS__)
#define _CBL_NEW_VAR_32(type, varname, ...) _CBL_NEW_VAR(type, varname); _CBL_NEW_VAR_31(type, __VA_ARGS__)
#define _CBL_NEW_VAR_33(type, varname, ...) _CBL_NEW_VAR(type, varname); _CBL_NEW_VAR_32(type, __VA_ARGS__)
#define _CBL_NEW_VAR_34(type, varname, ...) _CBL_NEW_VAR(type, varname); _CBL_NEW_VAR_33(type, __VA_ARGS__)
#define _CBL_NEW_VAR_35(type, varname, ...) _CBL_NEW_VAR(type, varname); _CBL_NEW_VAR_34(type, __VA_ARGS__)
#define _CBL_NEW_VAR_36(type, varname, ...) _CBL_NEW_VAR(type, varname); _CBL_NEW_VAR_35(type, __VA_ARGS__)
#define _CBL_NEW_VAR_37(type, varname, ...) _CBL_NEW_VAR(type, varname); _CBL_NEW_VAR_36(type, __VA_ARGS__)
#define _CBL_NEW_VAR_38(type, varname, ...) _CBL_NEW_VAR(type, varname); _CBL_NEW_VAR_37(type, __VA_ARGS__)
#define _CBL_NEW_VAR_39(type, varname, ...) _CBL_NEW_VAR(type, varname); _CBL_NEW_VAR_38(type, __VA_ARGS__)
#define _CBL_NEW_VAR_40(type, varname, ...) _CBL_NEW_VAR(type, varname); _CBL_NEW_VAR_39(type, __VA_ARGS__)
#define _CBL_NEW_VAR_41(type, varname, ...) _CBL_NEW_VAR(type, varname); _CBL_NEW_VAR_40(type, __VA_ARGS__)
#define _CBL_NEW_VAR_42(type, varname, ...) _CBL_NEW_VAR(type, varname); _CBL_NEW_VAR_41(type, __VA_ARGS__)
#define _CBL_NEW_VAR_43(type, varname, ...) _CBL_NEW_VAR(type, varname); _CBL_NEW_VAR_42(type, __VA_ARGS__)
#define _CBL_NEW_VAR_44(type, varname, ...) _CBL_NEW_VAR(type, varname); _CBL_NEW_VAR_43(type, __VA_ARGS__)
#define _CBL_NEW_VAR_45(type, varname, ...) _CBL_NEW_VAR(type, varname); _CBL_NEW_VAR_44(type, __VA_ARGS__)
#define _CBL_NEW_VAR_46(type, varname, ...) _CBL_NEW_VAR(type, varname); _CBL_NEW_VAR_45(type, __VA_ARGS__)
#define _CBL_NEW_VAR_47(type, varname, ...) _CBL_NEW_VAR(type, varname); _CBL_NEW_VAR_46(type, __VA_ARGS__)
#define _CBL_NEW_VAR_48(type, varname, ...) _CBL_NEW_VAR(type, varname); _CBL_NEW_VAR_47(type, __VA_ARGS__)
#define _CBL_NEW_VAR_49(type, varname, ...) _CBL_NEW_VAR(type, varname); _CBL_NEW_VAR_48(type, __VA_ARGS__)
#define _CBL_NEW_VAR_50(type, varname, ...) _CBL_NEW_VAR(type, varname); _CBL_NEW_VAR_49(type, __VA_ARGS__)
#define _CBL_NEW_VAR_51(type, varname, ...) _CBL_NEW_VAR(type, varname); _CBL_NEW_VAR_50(type, __VA_ARGS__)
#define _CBL_NEW_VAR_52(type, varname, ...) _CBL_NEW_VAR(type, varname); _CBL_NEW_VAR_51(type, __VA_ARGS__)
#define _CBL_NEW_VAR_53(type, varname, ...) _CBL_NEW_VAR(type, varname); _CBL_NEW_VAR_52(type, __VA_ARGS__)
#define _CBL_NEW_VAR_54(type, varname, ...) _CBL_NEW_VAR(type, varname); _CBL_NEW_VAR_53(type, __VA_ARGS__)
#define _CBL_NEW_VAR_55(type, varname, ...) _CBL_NEW_VAR(type, varname); _CBL_NEW_VAR_54(type, __VA_ARGS__)
#define _CBL_NEW_VAR_56(type, varname, ...) _CBL_NEW_VAR(type, varname); _CBL_NEW_VAR_55(type, __VA_ARGS__)
#define _CBL_NEW_VAR_57(type, varname, ...) _CBL_NEW_VAR(type, varname); _CBL_NEW_VAR_56(type, __VA_ARGS__)
#define _CBL_NEW_VAR_58(type, varname, ...) _CBL_NEW_VAR(type, varname); _CBL_NEW_VAR_57(type, __VA_ARGS__)
#define _CBL_NEW_VAR_59(type, varname, ...) _CBL_NEW_VAR(type, varname); _CBL_NEW_VAR_58(type, __VA_ARGS__)
#define _CBL_NEW_VAR_60(type, varname, ...) _CBL_NEW_VAR(type, varname); _CBL_NEW_VAR_59(type, __VA_ARGS__)
#define _CBL_NEW_VAR_61(type, varname, ...) _CBL_NEW_VAR(type, varname); _CBL_NEW_VAR_60(type, __VA_ARGS__)
#define _CBL_NEW_VAR_62(type, varname, ...) _CBL_NEW_VAR(type, varname); _CBL_NEW_VAR_61(type, __VA_ARGS__)
#define _CBL_NEW_VAR_63(type, varname, ...) _CBL_NEW_VAR(type, varname); _CBL_NEW_VAR_62(type, __VA_ARGS__)
#define _CBL_NEW_VAR_64(type, varname, ...) _CBL_NEW_VAR(type, varname); _CBL_NEW_VAR_63(type, __VA_ARGS__)

/**
 * @brief declear and assign methods to vars defined in CBL
 * @param type
 * @param N
 * @param var_list
 */
#define CBL_DECLARE_VARS(type, N, ...) struct type __VA_ARGS__; _CBL_NEW_VAR_##N(type, __VA_ARGS__)

#define _CBL_FREE_VAR(type, varname) type##_free_(&(varname))
#define _CBL_FREE_VAR_1(type, varname, ...) _CBL_FREE_VAR(type, varname)
#define _CBL_FREE_VAR_2(type, varname, ...) _CBL_FREE_VAR(type, varname); _CBL_FREE_VAR_1(type, __VA_ARGS__)
#define _CBL_FREE_VAR_3(type, varname, ...) _CBL_FREE_VAR(type, varname); _CBL_FREE_VAR_2(type, __VA_ARGS__)
#define _CBL_FREE_VAR_4(type, varname, ...) _CBL_FREE_VAR(type, varname); _CBL_FREE_VAR_3(type, __VA_ARGS__)
#define _CBL_FREE_VAR_5(type, varname, ...) _CBL_FREE_VAR(type, varname); _CBL_FREE_VAR_4(type, __VA_ARGS__)
#define _CBL_FREE_VAR_6(type, varname, ...) _CBL_FREE_VAR(type, varname); _CBL_FREE_VAR_5(type, __VA_ARGS__)
#define _CBL_FREE_VAR_7(type, varname, ...) _CBL_FREE_VAR(type, varname); _CBL_FREE_VAR_6(type, __VA_ARGS__)
#define _CBL_FREE_VAR_8(type, varname, ...) _CBL_FREE_VAR(type, varname); _CBL_FREE_VAR_7(type, __VA_ARGS__)
#define _CBL_FREE_VAR_9(type, varname, ...) _CBL_FREE_VAR(type, varname); _CBL_FREE_VAR_8(type, __VA_ARGS__)
#define _CBL_FREE_VAR_10(type, varname, ...) _CBL_FREE_VAR(type, varname); _CBL_FREE_VAR_9(type, __VA_ARGS__)
#define _CBL_FREE_VAR_11(type, varname, ...) _CBL_FREE_VAR(type, varname); _CBL_FREE_VAR_10(type, __VA_ARGS__)
#define _CBL_FREE_VAR_12(type, varname, ...) _CBL_FREE_VAR(type, varname); _CBL_FREE_VAR_11(type, __VA_ARGS__)
#define _CBL_FREE_VAR_13(type, varname, ...) _CBL_FREE_VAR(type, varname); _CBL_FREE_VAR_12(type, __VA_ARGS__)
#define _CBL_FREE_VAR_14(type, varname, ...) _CBL_FREE_VAR(type, varname); _CBL_FREE_VAR_13(type, __VA_ARGS__)
#define _CBL_FREE_VAR_15(type, varname, ...) _CBL_FREE_VAR(type, varname); _CBL_FREE_VAR_14(type, __VA_ARGS__)
#define _CBL_FREE_VAR_16(type, varname, ...) _CBL_FREE_VAR(type, varname); _CBL_FREE_VAR_15(type, __VA_ARGS__)
#define _CBL_FREE_VAR_17(type, varname, ...) _CBL_FREE_VAR(type, varname); _CBL_FREE_VAR_16(type, __VA_ARGS__)
#define _CBL_FREE_VAR_18(type, varname, ...) _CBL_FREE_VAR(type, varname); _CBL_FREE_VAR_17(type, __VA_ARGS__)
#define _CBL_FREE_VAR_19(type, varname, ...) _CBL_FREE_VAR(type, varname); _CBL_FREE_VAR_18(type, __VA_ARGS__)
#define _CBL_FREE_VAR_20(type, varname, ...) _CBL_FREE_VAR(type, varname); _CBL_FREE_VAR_19(type, __VA_ARGS__)
#define _CBL_FREE_VAR_21(type, varname, ...) _CBL_FREE_VAR(type, varname); _CBL_FREE_VAR_20(type, __VA_ARGS__)
#define _CBL_FREE_VAR_22(type, varname, ...) _CBL_FREE_VAR(type, varname); _CBL_FREE_VAR_21(type, __VA_ARGS__)
#define _CBL_FREE_VAR_23(type, varname, ...) _CBL_FREE_VAR(type, varname); _CBL_FREE_VAR_22(type, __VA_ARGS__)
#define _CBL_FREE_VAR_24(type, varname, ...) _CBL_FREE_VAR(type, varname); _CBL_FREE_VAR_23(type, __VA_ARGS__)
#define _CBL_FREE_VAR_25(type, varname, ...) _CBL_FREE_VAR(type, varname); _CBL_FREE_VAR_24(type, __VA_ARGS__)
#define _CBL_FREE_VAR_26(type, varname, ...) _CBL_FREE_VAR(type, varname); _CBL_FREE_VAR_25(type, __VA_ARGS__)
#define _CBL_FREE_VAR_27(type, varname, ...) _CBL_FREE_VAR(type, varname); _CBL_FREE_VAR_26(type, __VA_ARGS__)
#define _CBL_FREE_VAR_28(type, varname, ...) _CBL_FREE_VAR(type, varname); _CBL_FREE_VAR_27(type, __VA_ARGS__)
#define _CBL_FREE_VAR_29(type, varname, ...) _CBL_FREE_VAR(type, varname); _CBL_FREE_VAR_28(type, __VA_ARGS__)
#define _CBL_FREE_VAR_30(type, varname, ...) _CBL_FREE_VAR(type, varname); _CBL_FREE_VAR_29(type, __VA_ARGS__)
#define _CBL_FREE_VAR_31(type, varname, ...) _CBL_FREE_VAR(type, varname); _CBL_FREE_VAR_30(type, __VA_ARGS__)
#define _CBL_FREE_VAR_32(type, varname, ...) _CBL_FREE_VAR(type, varname); _CBL_FREE_VAR_31(type, __VA_ARGS__)
#define _CBL_FREE_VAR_33(type, varname, ...) _CBL_FREE_VAR(type, varname); _CBL_FREE_VAR_32(type, __VA_ARGS__)
#define _CBL_FREE_VAR_34(type, varname, ...) _CBL_FREE_VAR(type, varname); _CBL_FREE_VAR_33(type, __VA_ARGS__)
#define _CBL_FREE_VAR_35(type, varname, ...) _CBL_FREE_VAR(type, varname); _CBL_FREE_VAR_34(type, __VA_ARGS__)
#define _CBL_FREE_VAR_36(type, varname, ...) _CBL_FREE_VAR(type, varname); _CBL_FREE_VAR_35(type, __VA_ARGS__)
#define _CBL_FREE_VAR_37(type, varname, ...) _CBL_FREE_VAR(type, varname); _CBL_FREE_VAR_36(type, __VA_ARGS__)
#define _CBL_FREE_VAR_38(type, varname, ...) _CBL_FREE_VAR(type, varname); _CBL_FREE_VAR_37(type, __VA_ARGS__)
#define _CBL_FREE_VAR_39(type, varname, ...) _CBL_FREE_VAR(type, varname); _CBL_FREE_VAR_38(type, __VA_ARGS__)
#define _CBL_FREE_VAR_40(type, varname, ...) _CBL_FREE_VAR(type, varname); _CBL_FREE_VAR_39(type, __VA_ARGS__)
#define _CBL_FREE_VAR_41(type, varname, ...) _CBL_FREE_VAR(type, varname); _CBL_FREE_VAR_40(type, __VA_ARGS__)
#define _CBL_FREE_VAR_42(type, varname, ...) _CBL_FREE_VAR(type, varname); _CBL_FREE_VAR_41(type, __VA_ARGS__)
#define _CBL_FREE_VAR_43(type, varname, ...) _CBL_FREE_VAR(type, varname); _CBL_FREE_VAR_42(type, __VA_ARGS__)
#define _CBL_FREE_VAR_44(type, varname, ...) _CBL_FREE_VAR(type, varname); _CBL_FREE_VAR_43(type, __VA_ARGS__)
#define _CBL_FREE_VAR_45(type, varname, ...) _CBL_FREE_VAR(type, varname); _CBL_FREE_VAR_44(type, __VA_ARGS__)
#define _CBL_FREE_VAR_46(type, varname, ...) _CBL_FREE_VAR(type, varname); _CBL_FREE_VAR_45(type, __VA_ARGS__)
#define _CBL_FREE_VAR_47(type, varname, ...) _CBL_FREE_VAR(type, varname); _CBL_FREE_VAR_46(type, __VA_ARGS__)
#define _CBL_FREE_VAR_48(type, varname, ...) _CBL_FREE_VAR(type, varname); _CBL_FREE_VAR_47(type, __VA_ARGS__)
#define _CBL_FREE_VAR_49(type, varname, ...) _CBL_FREE_VAR(type, varname); _CBL_FREE_VAR_48(type, __VA_ARGS__)
#define _CBL_FREE_VAR_50(type, varname, ...) _CBL_FREE_VAR(type, varname); _CBL_FREE_VAR_49(type, __VA_ARGS__)
#define _CBL_FREE_VAR_51(type, varname, ...) _CBL_FREE_VAR(type, varname); _CBL_FREE_VAR_50(type, __VA_ARGS__)
#define _CBL_FREE_VAR_52(type, varname, ...) _CBL_FREE_VAR(type, varname); _CBL_FREE_VAR_51(type, __VA_ARGS__)
#define _CBL_FREE_VAR_53(type, varname, ...) _CBL_FREE_VAR(type, varname); _CBL_FREE_VAR_52(type, __VA_ARGS__)
#define _CBL_FREE_VAR_54(type, varname, ...) _CBL_FREE_VAR(type, varname); _CBL_FREE_VAR_53(type, __VA_ARGS__)
#define _CBL_FREE_VAR_55(type, varname, ...) _CBL_FREE_VAR(type, varname); _CBL_FREE_VAR_54(type, __VA_ARGS__)
#define _CBL_FREE_VAR_56(type, varname, ...) _CBL_FREE_VAR(type, varname); _CBL_FREE_VAR_55(type, __VA_ARGS__)
#define _CBL_FREE_VAR_57(type, varname, ...) _CBL_FREE_VAR(type, varname); _CBL_FREE_VAR_56(type, __VA_ARGS__)
#define _CBL_FREE_VAR_58(type, varname, ...) _CBL_FREE_VAR(type, varname); _CBL_FREE_VAR_57(type, __VA_ARGS__)
#define _CBL_FREE_VAR_59(type, varname, ...) _CBL_FREE_VAR(type, varname); _CBL_FREE_VAR_58(type, __VA_ARGS__)
#define _CBL_FREE_VAR_60(type, varname, ...) _CBL_FREE_VAR(type, varname); _CBL_FREE_VAR_59(type, __VA_ARGS__)
#define _CBL_FREE_VAR_61(type, varname, ...) _CBL_FREE_VAR(type, varname); _CBL_FREE_VAR_60(type, __VA_ARGS__)
#define _CBL_FREE_VAR_62(type, varname, ...) _CBL_FREE_VAR(type, varname); _CBL_FREE_VAR_61(type, __VA_ARGS__)
#define _CBL_FREE_VAR_63(type, varname, ...) _CBL_FREE_VAR(type, varname); _CBL_FREE_VAR_62(type, __VA_ARGS__)
#define _CBL_FREE_VAR_64(type, varname, ...) _CBL_FREE_VAR(type, varname); _CBL_FREE_VAR_63(type, __VA_ARGS__)

/**
 * @brief free allocated memories of vars defined in CBL. Types need to free:\n
 * Table,\n IntVector,\n FloatVector,\n IntMatrix,\n FloatMatrix
 * @param type
 * @param N
 * @param var_list
 */
#define CBL_FREE_VARS(type, N, ...) _CBL_FREE_VAR_##N(type, __VA_ARGS__)

#endif // _MODULE_PART_MACRO_LOOP_BASIC_H_
