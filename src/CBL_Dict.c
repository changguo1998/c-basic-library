#include <stdlib.h>
#include "CBL_Dict.h"

Address DICT_get_element(const Dict dict, const String key, UInt8* typecode) {
    DictNode* p;
    p = dict;
    while(p) {
        if(STR_isequal(p->key, key)) {
            *typecode = p->typecode;
            return p->address;
        }
        p = p->next;
    }
    return NULL;
}

Address DICT_add_element(Dict* dict, const String key, const Address address, UInt8 typecode) {
    DictNode* p;
    // check key exist
    p = *dict;
    while(p) {
        if(STR_isequal(p->key, key)) return NULL;
        p = p->next;
    }
    // create a node
    p           = (DictNode*)malloc(sizeof(DictNode));
    p->typecode = typecode;
    p->key      = key;
    p->address  = address;
    p->next     = *dict;
    *dict       = p;
    return p;
}

Address DICT_pop_element(Dict* dict, const String key, UInt8* typecode) {
    DictNode* p;
    Dict*     q;
    Address   address = NULL;
    // check key exist
    q = dict;
    while(*q)
        if(!STR_isequal((*q)->key, key)) q = &((*q)->next);
        else break;
    // rm node
    if(*q) {
        p         = *q;
        *q        = p->next;
        address   = p->address;
        *typecode = p->typecode;
        free(p);
    }
    return address;
}

Int DICT_keys(const Dict dict, String** keys) {
    DictNode* p;
    Int       n_node = 0, i;
    if(dict == NULL) return 0;
    if(*keys != NULL) return 0;
    p = dict;
    while(p) {
        p = p->next;
        n_node++;
    }
    *keys = (String*)malloc(sizeof(String) * n_node);
    for(i = 0, p = dict; i < n_node; i++, p = p->next) (*keys)[i] = p->key;
    return n_node;
}

Sheet SHEET_allocate(UInt8 typecode, size_t element_size, Int n0, Int n1) {
    Sheet sheet;
    sheet.typecode     = typecode;
    sheet.element_size = element_size;
    sheet.n0           = n0;
    sheet.n1           = n1;
    sheet.key0         = (String*)calloc(n0, sizeof(String));
    sheet.key1         = (String*)calloc(n1, sizeof(String));
    sheet.addr         = (Address)calloc(n0 * n1, element_size);
    return sheet;
}

void SHEET_free(Sheet* sheet) {
    if(sheet == NULL) return;
    sheet->n0 = sheet->n1 = 0;
    free(sheet->key0);
    free(sheet->key1);
    free(sheet->addr);
    sheet->key0 = sheet->key1 = sheet->addr = NULL;
}

Int SHEET_key2index(const String* sheet_keys, Int n, const String key) {
    Int i;
    for(i = 0; i < n; i++) if(STR_isequal(sheet_keys[i], key)) return i;
    return -1;
}

Int SHEET_key_key2shift(const Sheet sheet, const String key0, const String key1) {
    Int i, j;
    i = SHEET_key2index(sheet.key0, sheet.n0, key0);
    j = SHEET_key2index(sheet.key1, sheet.n1, key1);
    if((i < 0) || (j < 0)) return -1;
    return i + sheet.n0 * j;
}

Int SHEET_index_key2shift(const Sheet sheet, Int index0, const String key1) {
    Int j;
    j = SHEET_key2index(sheet.key1, sheet.n1, key1);
    if(j < 0) return -1;
    return index0 + sheet.n0 * j;
}
