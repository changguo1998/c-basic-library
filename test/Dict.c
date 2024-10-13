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
#include "Module_Basic.h"
#include "Type_Dict.h"

#define NROW 4
#define NCOL 5
#define STRSET(str, val) (str).methods->set_(&(str), (val))
#define FREE(v) (v).methods->free_(&(v))

int main() {
    Int    i, j, *pi, esize[NCOL], n_key1, n_key2, tc;
    Float  float_var;
    Char   buf[STRING_MAX_LENGTH];
    Float* pf;

    struct Table       sheet, sheet2, *ptable1, *ptable2;
    struct String      k0,    k1, bs[2], *key_list1, *key_list2;
    struct StaticDict  fdict;
    struct DynamicDict ddict;

    Table_new_(&sheet);
    Table_new_(&sheet2);
    String_new_(&k0);
    String_new_(&k1);
    String_new_(&bs[0]);
    String_new_(&bs[1]);
    StaticDict_new_(&fdict);
    DynamicDict_new_(&ddict);

    srand(time(NULL));

    printf("\n=== Initializing ===\n");
    for(i = 0; i < NCOL; i++) esize[i] = sizeof(Float);
    sheet.methods->alloc_(&sheet, esize, NROW, NCOL);
    for(i = 0; i < NCOL; i++) esize[i] = sizeof(Int);
    sheet.methods->alloc_(&sheet2, esize, NROW, NCOL);


    for(i = 0; i < NROW; i++) {
        sprintf(buf, "dim0_%c", (Char)i + 'a');
        STRSET(sheet.row_name[i], buf);
        sprintf(buf, "row%d", i);
        STRSET(sheet2.row_name[i], buf);
    }
    for(i = 0; i < NCOL; i++) {
        sprintf(buf, "dim1_%c", (Char)i + 'i');
        STRSET(sheet.col_name[i], buf);
        sprintf(buf, "col%d", i);
        STRSET(sheet2.col_name[i], buf);
    }
    sheet.linear_row = false;
    sheet2.linear_row = false;
    for(j = 0; j < NCOL; j++)
        for(i = 0; i < NROW; i++) {
            pf = (Float*)sheet.methods->get_ii(&sheet, i, j);
            *pf = (Float)rand() / (Float)RAND_MAX;
            pi = (Int*)sheet2.methods->get_ii(&sheet2, i, j);
            *pi = (Int)((Float)rand() * 9 / (Float)RAND_MAX);
            printf("%d %.3f\n", *pi, *pf);
        }

    printf("\n=== Table content ===\n");
    printf("size: %d x %d\n", sheet.nrow, sheet.ncol);
    printf("dim 0 keys:\n");
    for(i = 0; i < NROW; i++) printf("dim 0 key %d: %s\n", i, sheet.row_name[i].str);
    printf("\ndim 1 keys:\n");
    for(i = 0; i < NCOL; i++) printf("dim 1 key %d: %s\n", i, sheet.col_name[i].str);
    for(i = 0; i < NROW; i++) {
        bs[0].methods->clean_(&bs[0]);
        for(j = 0; j < NCOL; j++) {
            pf = (Float*)sheet.methods->get_ii(&sheet, i, j);
            sprintf(buf, " %.3f", *pf);
            bs[1].methods->set_(&bs[1], buf);
            k0.methods->join_(&k0, bs, 2, String_set(" "));
            bs[0] = k0;
        }
        printf("%s\n", bs[0].str);
    }

    printf("\n=== Table key index test ===\n");
    STRSET(k0, "dim0_c");
    STRSET(k1, "dim1_l");
    pf = (Float*)sheet.methods->get_kk(&sheet, k0, k1);
    printf("%s %s shift: %d, value: %.3f\n", k0.str, k1.str, i, *pf);


    printf("\n=== Dict test ===\n");
    printf("add sheet 0\n");
    printf("Dict: %p\n", ddict.data);
    ddict.methods->push_(&ddict, String_set("Table 0"), TYPECODE_TABLE, &sheet);
    fdict.methods->push_(&fdict, String_set("Table 0"), TYPECODE_TABLE, &sheet);
    printf("Dict: %p\n", ddict.data);

    printf("add sheet 1\n");
    ddict.methods->push_(&ddict, String_set("Table 1"), TYPECODE_TABLE, &sheet2);
    fdict.methods->push_(&fdict, String_set("Table 1"), TYPECODE_TABLE, &sheet2);
    printf("Dict: %p\n", ddict.data);

    printf("add float\n");
    ddict.methods->push_(&ddict, String_set("Float 0"), TYPECODE_FLOAT, &float_var);
    fdict.methods->push_(&fdict, String_set("Float 0"), TYPECODE_FLOAT, &float_var);
    printf("Dict: %p\n", ddict.data);

    n_key1 = ddict.methods->n_elements(&ddict);
    n_key2 = fdict.methods->n_elements(&fdict);
    key_list1 = (struct String*)calloc(n_key1, sizeof(struct String));
    key_list2 = (struct String*)calloc(n_key2, sizeof(struct String));
    for(i = 0; i < n_key1; i++) String_new_(&key_list1[i]);
    for(i = 0; i < n_key2; i++) String_new_(&key_list2[i]);
    ddict.methods->keys(&ddict, key_list1, n_key1);
    fdict.methods->keys(&fdict, key_list2, n_key2);
    printf("dict keys:\n");
    for(j = 0; j < n_key1; j++) printf("%s\n", key_list1[j].str);

    ptable1 = (struct Table*)ddict.methods->get(&ddict, String_set("Table 0"), &tc);
    ptable2 = (struct Table*)fdict.methods->get(&fdict, String_set("Table 0"), &tc);
    printf("sheet address: %p, ps1 value: %p, typecode: %d\n", &sheet, ptable1, tc);

    ptable1 = (struct Table*)ddict.methods->pop_(&ddict, String_set("Table 1"), &tc);
    ptable2 = (struct Table*)fdict.methods->pop_(&fdict, String_set("Table 1"), &tc);
    printf("sheet address: %p, ps2 value: %p, typecode %d\n", &sheet2, ptable2, tc);
    printf("ps2 content\n");
    printf("key0:\n");
    for(i = 0; i < ptable2->nrow; i++) printf("%s\n", ptable2->row_name[i].str);
    printf("key1:\n");
    for(i = 0; i < ptable2->ncol; i++) printf("%s\n", ptable2->col_name[i].str);
    printf("data:\n");

    for(i = 0; i < NROW; i++) {
        bs[0].methods->clean_(&bs[0]);
        for(j = 0; j < NCOL; j++) {
            pi = (Int*)ptable2->methods->get_ii(ptable2, i, j);
            sprintf(buf, "%d", *pi);
            bs[1].methods->set_(&bs[1], buf);
            k0.methods->join_(&k0, bs, 2, String_set(" "));
            bs[0] = k0;
        }
        printf("%s\n", bs[0].str);
    }

    while(ddict.data) ddict.methods->pop_(&ddict, ddict.data->key, &tc);

    FREE(sheet);
    FREE(sheet2);
    return 0;
}
