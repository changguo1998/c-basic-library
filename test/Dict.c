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

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "CBL_Basic.h"
#include "CBL_Dict.h"

int main() {
    Sheet  sheet, sheet2, *ps1, *ps2;
    Int    i,     j, *     iv;
    UInt8  tc;
    Char   buf[STR_MAX_STRING_LENGTH];
    Float* fv;
    String k0, k1, bs[2], *kl = NULL;
    Dict   dict               = NULL;

    srand(time(NULL));

    printf("\n=== Initializing ===\n");
    sheet  = SHEET_allocate(TYPECODE_FLOAT, sizeof(Float), 4, 5);
    sheet2 = SHEET_allocate(TYPECODE_INT, sizeof(Int), 4, 5);
    fv     = (Float*)sheet.addr;
    iv     = (Int*)sheet2.addr;
    for(i = 0; i < sheet.n0; i++) {
        sprintf(buf, "dim0_%c", (Char)i + 'a');
        sheet.key0[i] = STR_String(buf);
        sprintf(buf, "row%d", i);
        sheet2.key0[i] = STR_String(buf);
    }
    for(i = 0; i < sheet.n1; i++) {
        sprintf(buf, "dim1_%c", (Char)i + 'i');
        sheet.key1[i] = STR_String(buf);
        sprintf(buf, "col%d", i);
        sheet2.key1[i] = STR_String(buf);
    }
    for(i = 0; i < sheet.n0 * sheet.n1; i++) {
        fv[i] = (Float)rand() / (Float)RAND_MAX;
        iv[i] = (Int)((Float)rand() * 9 / (Float)RAND_MAX);
        printf("%d %.3f\n", i, fv[i]);
    }

    printf("\n=== Sheet content ===\n");
    printf("typecode: 0x%02X\n", sheet.typecode);
    printf("element size: %lld\n", sheet.element_size);
    printf("size: %d x %d\n", sheet.n0, sheet.n1);
    printf("dim 0 keys:\n");
    for(i = 0; i < sheet.n0; i++)  printf("dim 0 key %d: %s\n", i, sheet.key0[i].str);
    printf("\ndim 1 keys:\n");
    for(i = 0; i < sheet.n1; i++) printf("dim 1 key %d: %s\n", i, sheet.key1[i].str);
    for(i = 0; i < sheet.n0; i++) {
        bs[0] = STR_empty_string();
        for(j = 0; j < sheet.n1; j++) {
            sprintf(buf, " %.3f", fv[i + sheet.n0 * j]);
            bs[1] = STR_String(buf);
            bs[0] = STR_join(bs, 2, STR_String(""));
        }
        printf("%s\n", bs[0].str);
    }

    printf("\n=== Sheet key index test ===\n");
    k0 = STR_String("dim0_c");
    k1 = STR_String("dim1_l");
    i  = SHEET_key_key2shift(sheet, k0, k1);
    if(i > 0) printf("%s %s shift: %d, value: %.3f\n", k0.str, k1.str, i, fv[i]);

    printf("\n=== Dict test ===\n");
    printf("Dict: %p\n", dict);
    printf("add sheet 0\n");
    DICT_add_element(&dict, STR_String("Sheet 0"), &sheet, TYPECODE_SHEET);
    printf("Dict: %p\n", dict);

    printf("add sheet 1\n");
    DICT_add_element(&dict, STR_String("Sheet 1"), &sheet2, TYPECODE_SHEET);
    printf("Dict: %p\n", dict);

    printf("add float\n");
    DICT_add_element(&dict, STR_String("Float 0"), &fv, TYPECODE_FLOAT);
    printf("Dict: %p\n", dict);

    i = DICT_keys(dict, &kl);
    printf("dict keys:\n");
    for(j = 0; j < i; j++) printf("%s\n", kl[j].str);

    ps1 = (Sheet*)DICT_get_element(dict, STR_String("Sheet 0"), &tc);
    printf("sheet address: %p, ps1 value: %p, typecode: 0x%02X\n", &sheet, ps1, tc);

    ps2 = (Sheet*)DICT_pop_element(&dict, STR_String("Sheet 1"), &tc);
    printf("sheet address: %p, ps2 value: %p, typecode 0x%02X\n", &sheet2, ps2, tc);
    printf("ps2 content\n");
    printf("key0:\n");
    for(i = 0; i < ps2->n0; i++) printf("%s\n", ps2->key0[i].str);
    printf("key1:\n");
    for(i = 0; i < ps2->n1; i++) printf("%s\n", ps2->key1[i].str);
    printf("data:\n");
    iv = (Int*)ps2->addr;
    for(i = 0; i < ps2->n0; i++) {
        bs[0] = STR_empty_string();
        for(j = 0; j < ps2->n1; j++) {
            sprintf(buf, " %d", iv[i + sheet.n0 * j]);
            bs[1] = STR_String(buf);
            bs[0] = STR_join(bs, 2, STR_String(""));
        }
        printf("%s\n", bs[0].str);
    }

    while(dict) DICT_pop_element(&dict, dict->key, &tc);

    SHEET_free(&sheet);
    SHEET_free(&sheet2);
    return 0;
}
