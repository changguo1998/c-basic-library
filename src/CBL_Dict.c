/******************************************************************************
 * MIT License                                                                *
 *                                                                            *
 * Copyright (c) 2024 Chang Guo                                               *
 *                                                                            *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell  *
 * copies of the Software, and to permit persons to whom the Software is      *
 * furnished to do so, subject to the following conditions:                   *
 *                                                                            *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.                            *
 *                                                                            *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR *
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,   *
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE*
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER     *
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.                                                                  *
 *                                                                            *
 ******************************************************************************/

#include <stdlib.h>
#include "CBL_Basic.h"
#include "CBL_String.h"
#include "CBL_Dict.h"

/**
 * @brief get linear index from string array keys
 * @param key_list
 * @param n
 * @param key
 * @return
 */
Int _DICT_key2index(const String* key_list, Int n, String key) {
    Int i;
    for(i = 0; i < n; i++) if(STR_isequal(key_list[i], key)) return i;
    return -1;
}

Address StaticDict_get(
    const struct StaticDict* this,
    String                   key,
    UInt8*                   typecode) {

    Int i;
    i = _DICT_key2index(this->key, STATIC_DICT_SIZE, key);
    if(i >= 0)
        if(this->flag[i]) {
            *typecode = this->typecode[i];
            return this->address[i];
        }
    return NULL;
}

Address StaticDict_pop_(struct StaticDict* this, String key, UInt8* typecode) {
    Int     i;
    Address address = NULL;
    i = _DICT_key2index(this->key, STATIC_DICT_SIZE, key);
    if(i >= 0)
        if(this->flag[i]) {
            *typecode = this->typecode[i];
            address = this->address[i];
            this->key[i] = STR_empty_string();
            this->flag[i] = false;
            this->typecode[i] = 0;
            this->address[i] = NULL;
        }
    return address;
}

Address StaticDict_set_(
    struct StaticDict* this,
    String             key,
    UInt8              typecode,
    Address            address) {
    Int     i;
    Address previous_address = NULL;
    i = _DICT_key2index(this->key, STATIC_DICT_SIZE, key);
    if(i >= 0)
        if(this->flag[i]) {
            previous_address = this->address[i];
            this->typecode[i] = typecode;
            this->address[i] = address;
        }
    return previous_address;
}

Bool StaticDict_push_(
    struct StaticDict* this,
    String             key,
    UInt8              typecode,
    Address            address) {
    Int i;
    for(i = 0; i < STATIC_DICT_SIZE; i++) if(!this->flag[i]) break;
    if(i < STATIC_DICT_SIZE) {
        this->key[i] = key;
        this->flag[i] = true;
        this->typecode[i] = typecode;
        this->address[i] = address;
        return true;
    }
    return false;
}

Address DynamicDict_get(const struct DynamicDict* this,
                        String                    key,
                        UInt8*                    typecode) {
    struct DictNode* p;
    p = this->head;
    while(p) {}
}

// ! ==========================================================================

Address DICT_get_element(
    const struct DictNode* dict,
    const String           key,
    UInt8*                 typecode) {
    struct DictNode* p;
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

Address DICT_add_element(
    struct DictNode** dict,
    const String      key,
    const Address     address,
    UInt8             typecode) {
    struct DictNode* p;
    // check key exist
    p = *dict;
    while(p) {
        if(STR_isequal(p->key, key)) return NULL;
        p = p->next;
    }
    // create a node
    p = (DictNode*)malloc(sizeof(DictNode));
    p->typecode = typecode;
    p->key = key;
    p->address = address;
    p->next = *dict;
    *dict = p;
    return p;
}

Address DICT_pop_element(
    struct DictNode** dict,
    const String      key,
    UInt8*            typecode) {
    DictNode*         p;
    struct DictNode** q;
    Address           address = NULL;
    // check key exist
    q = dict;
    while(*q)
        if(!STR_isequal((*q)->key, key)) q = &((*q)->next);
        else break;
    // rm node
    if(*q) {
        p = *q;
        *q = p->next;
        address = p->address;
        *typecode = p->typecode;
        free(p);
    }
    return address;
}

Int DICT_keys(const struct DictNode* dict, String** keys) {
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
    sheet.typecode = typecode;
    sheet.element_size = element_size;
    sheet.n0 = n0;
    sheet.n1 = n1;
    sheet.key0 = (String*)calloc(n0, sizeof(String));
    sheet.key1 = (String*)calloc(n1, sizeof(String));
    sheet.addr = (Address)calloc(n0 * n1, element_size);
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

Int SHEET_key_key2shift(
    const Sheet  sheet,
    const String key0,
    const String key1) {
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
