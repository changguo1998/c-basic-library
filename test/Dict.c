#include <time.h>
#include "CBL_Basic.h"
#include "CBL_Log.h"
#include "CBL_Dict.h"

int main() {
    Sheet  sheet, sheet2, *ps1, *ps2;
    Int    i,     j, *     iv;
    UInt8  tc;
    Char   buf[STR_MAX_STRING_LENGTH];
    Float* fv;
    String k0, k1, bs[2], *kl = NULL;
    Dict   dict               = NULL;

    LOG_init();
    srand(time(NULL));

    LOG_print_info("\n=== Initializing ===\n");
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
        sprintf(buf, "%d %.3f", i, fv[i]);
        // LOG_print_info(buf);
    }

    LOG_print_info("\n=== Sheet content ===\n");
    sprintf(buf, "typecode: 0x%02X", sheet.typecode);
    LOG_print_info(buf);
    sprintf(buf, "element size: %lld", sheet.element_size);
    LOG_print_info(buf);
    sprintf(buf, "size: %d x %d", sheet.n0, sheet.n1);
    LOG_print_info(buf);
    LOG_print_info("dim 0 keys:");
    for(i = 0; i < sheet.n0; i++) {
        sprintf(buf, "dim 0 key %d: %s", i, sheet.key0[i].str);
        LOG_print_info(buf);
    }
    LOG_print_info("\ndim 1 keys:");
    for(i = 0; i < sheet.n1; i++) {
        sprintf(buf, "dim 1 key %d: %s", i, sheet.key1[i].str);
        LOG_print_info(buf);
    }
    LOG_print_info("\nvalues");
    for(i = 0; i < sheet.n0; i++) {
        bs[0] = STR_empty_string();
        for(j = 0; j < sheet.n1; j++) {
            sprintf(buf, " %.3f", fv[i + sheet.n0 * j]);
            bs[1] = STR_String(buf);
            bs[0] = STR_join(bs, 2, STR_String(""));
        }
        LOG_print_info(bs[0].str);
    }

    LOG_print_info("\n=== Sheet key index test ===\n");
    k0 = STR_String("dim0_c");
    k1 = STR_String("dim1_l");
    i  = SHEET_key_key2shift(sheet, k0, k1);
    if(i > 0) {
        sprintf(buf, "%s %s shift: %d, value: %.3f", k0.str, k1.str, i, fv[i]);
        LOG_print_info(buf);
    }

    LOG_print_info("\n=== Dict test ===\n");
    sprintf(buf, "Dict: %p", dict);
    LOG_print_info(buf);
    LOG_print_info("add sheet 0");
    DICT_add_element(&dict, STR_String("Sheet 0"), &sheet, TYPECODE_SHEET);
    sprintf(buf, "Dict: %p", dict);
    LOG_print_info(buf);
    LOG_print_info("add sheet 1");
    DICT_add_element(&dict, STR_String("Sheet 1"), &sheet2, TYPECODE_SHEET);
    sprintf(buf, "Dict: %p", dict);
    LOG_print_info(buf);
    LOG_print_info("add float");
    DICT_add_element(&dict, STR_String("Float 0"), &fv, TYPECODE_FLOAT);
    sprintf(buf, "Dict: %p", dict);
    LOG_print_info(buf);

    i = DICT_keys(dict, &kl);
    LOG_print_info("dict keys:");
    for(j = 0; j < i; j++) LOG_print_info(kl[j].str);

    ps1 = (Sheet*)DICT_get_element(dict, STR_String("Sheet 0"), &tc);
    sprintf(buf, "sheet address: %p, ps1 value: %p, typecode: 0x%02X", &sheet, ps1, tc);
    LOG_print_info(buf);

    ps2 = (Sheet*)DICT_pop_element(&dict, STR_String("Sheet 1"), &tc);
    sprintf(buf, "sheet address: %p, ps2 value: %p, typecode 0x%02X", &sheet2, ps2, tc);
    LOG_print_info(buf);
    LOG_print_info("ps2 content");
    LOG_print_info("key0:");
    for(i = 0; i < ps2->n0; i++) LOG_print_info(ps2->key0[i].str);
    LOG_print_info("key1:");
    for(i = 0; i < ps2->n1; i++) LOG_print_info(ps2->key1[i].str);
    LOG_print_info("data:");
    iv = (Int*)ps2->addr;
    for(i = 0; i < ps2->n0; i++) {
        bs[0] = STR_empty_string();
        for(j = 0; j < ps2->n1; j++) {
            sprintf(buf, " %d", iv[i + sheet.n0 * j]);
            bs[1] = STR_String(buf);
            bs[0] = STR_join(bs, 2, STR_String(""));
        }
        LOG_print_info(bs[0].str);
    }

    while(dict) DICT_pop_element(&dict, dict->key, &tc);

    SHEET_free(&sheet);
    SHEET_free(&sheet2);
    LOG_final();
    return 0;
}
