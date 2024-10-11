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

#include <stdlib.h>
#include "CBL_Basic.h"
#include "Type_String.h"
#include "Type_Dict.h"

struct StaticDictMethods _CBL_STATIC_DICT_METHODS = {
    &StaticDict_get,
    &StaticDict_pop_,
    &StaticDict_set_,
    &StaticDict_push_,
    &StaticDict_has_key,
    &StaticDict_n_elements,
    &StaticDict_keys
};

struct DynamicDictMethods _CBL_DYNAMIC_DICT_METHODS = {
    &DynamicDict_get,
    &DynamicDict_pop_,
    &DynamicDict_set_,
    &DynamicDict_push_,
    &DynamicDict_has_key,
    &DynamicDict_n_elements,
    &DynamicDict_keys
};

struct TableMethods _CBL_TABLE_METHODS = {
    &Table_alloc_,
    &Table_free_,
    &Table_get_kk,
    &Table_get_ik,
    &Table_get_ii,
    &Table_get_col_i,
    &Table_get_col_k,
};

/**
 * @brief get linear index from string array keys
 * @param key_list
 * @param n
 * @param key
 * @return
 */
static Int _key2index(const struct String* key_list, Int n, struct String key) {
    Int i;
    for(i = 0; i < n; i++) if(key.methods->isequal(&key, key_list[i])) return i;
    return -1;
}


// # StaticDict


Address StaticDict_get(const struct StaticDict* this, struct String key, Int* typecode) {

    Int i;
    i = _key2index(this->key, STATIC_DICT_SIZE, key);
    if(i >= 0)
        if(this->flag[i]) {
            *typecode = this->typecode[i];
            return this->address[i];
        }
    return NULL;
}

Address StaticDict_pop_(struct StaticDict* this, struct String key, Int* typecode) {
    Int     i;
    Address address = NULL;
    i = _key2index(this->key, STATIC_DICT_SIZE, key);
    if(i >= 0)
        if(this->flag[i]) {
            *typecode = this->typecode[i];
            address = this->address[i];
            this->key[i].methods->clean_(&(this->key[i]));
            this->flag[i] = false;
            this->typecode[i] = 0;
            this->address[i] = NULL;
        }
    return address;
}

Address StaticDict_set_(struct StaticDict* this, struct String key, Int typecode, Address address) {
    Int     i;
    Address previous_address = NULL;
    i = _key2index(this->key, STATIC_DICT_SIZE, key);
    if(i >= 0)
        if(this->flag[i]) {
            previous_address = this->address[i];
            this->typecode[i] = typecode;
            this->address[i] = address;
        }
    return previous_address;
}

void StaticDict_push_(struct StaticDict* this, struct String key, Int typecode, Address address) {
    Int i;
    for(i = 0; i < STATIC_DICT_SIZE; i++) if(!this->flag[i]) break;
    if(i < STATIC_DICT_SIZE) {
        this->key[i] = key;
        this->flag[i] = true;
        this->typecode[i] = typecode;
        this->address[i] = address;
    }
    else
        error_out_of_memory("(StaticDict_push_) buffer of StaticDict is full");
}

Bool StaticDict_has_key(const struct StaticDict* this, struct String key) {
    return _key2index(this->key, STATIC_DICT_SIZE, key) >= 0;
}

Int StaticDict_n_elements(const struct StaticDict* this) {
    Int i, n = 0;
    for(i = 0; i < STATIC_DICT_SIZE; i++) if(this->flag[i]) n += 1;
    return n;
}

Int StaticDict_keys(const struct StaticDict* this, struct String* key_list, Int len_key_list) {
    Int i, n_key;
    n_key = 0;
    for(i = 0; i < len_key_list; i++) String_new_(&key_list[i]);
    for(i = 0; i < STATIC_DICT_SIZE; i++)
        if(this->flag[i]) {
            if(n_key < len_key_list) {
                key_list[n_key] = this->key[i];
                n_key += 1;
            }
            else break;
        }
    return n_key;
}

// # DynamicDict


Address DynamicDict_get(const struct DynamicDict* this, struct String key, Int* typecode) {
    struct DynamicDictNode* p;
    p = this->data;
    while(p) {
        if(key.methods->isequal(&key, p->key)) {
            *typecode = p->typecode;
            return p->address;
        }
        p = p->next;
    }
    return NULL;
}

Address DynamicDict_pop_(struct DynamicDict* this, struct String key, Int* typecode) {
    struct DynamicDictNode *p, **q;
    Address                 address = NULL;
    // check key exist
    q = &(this->data);
    while(*q)
        if(!(key.methods->isequal(&key, (*q)->key))) q = &((*q)->next);
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

Address DynamicDict_set_(struct DynamicDict* this, struct String key, Int typecode, Address address) {
    struct DynamicDictNode* p;
    Address                 previous_address = NULL;
    p = this->data;
    while(p) {
        if(key.methods->isequal(&key, p->key)) break;
        p = p->next;
    }
    if(p == NULL) return NULL;
    previous_address = p->address;
    p->typecode = typecode;
    p->address = address;
    return previous_address;
}

void DynamicDict_push_(struct DynamicDict* this, struct String key, Int typecode, Address address) {
    struct DynamicDictNode* p;
    // check key exist
    p = this->data;
    while(p) {
        if(key.methods->isequal(&key, p->key)) {
            error_unexpected_allocated_memory("(DynamicDict_push_) Dict already has key");
        }
        p = p->next;
    }
    // create a node
    p = (struct DynamicDictNode*)malloc(sizeof(struct DynamicDictNode));
    String_new_(&(p->key));
    p->key = key;
    p->typecode = typecode;
    p->address = address;
    p->next = this->data;
    this->data = p;
}

Bool DynamicDict_has_key(const struct DynamicDict* this, struct String key) {
    struct DynamicDictNode* p;
    p = this->data;
    while(p) {
        if(key.methods->isequal(&key, p->key)) return true;
        p = p->next;
    }
    return false;
}

Int DynamicDict_n_elements(const struct DynamicDict* this) {
    Int                     n = 0;
    struct DynamicDictNode* p;
    p = this->data;
    while(p) {
        n += 1;
        p = p->next;
    }
    return n;
}

Int DynamicDict_keys(const struct DynamicDict* this, struct String* key_list, Int len_key_list) {
    Int                     i, n_key;
    struct DynamicDictNode* p;
    for(i = 0; i < len_key_list; i++) String_new_(&key_list[i]);

    n_key = 0;
    p = this->data;
    while(p) {
        key_list[n_key] = p->key;
        n_key += 1;
        p = p->next;
    }
    return n_key;
}

void Table_alloc_(struct Table* this, Int* elsize, Int nrow, Int ncol) {
    Int i;
    // check arguments
    // set values
    this->nrow = nrow;
    this->ncol = ncol;
    this->linear_row = true;
    for(i = 0; i < ncol; i++) {
        this->elsize[i] = elsize[i];
        this->addr[i] = calloc(nrow, elsize[i]);
    }
    this->row_name = (struct String*)malloc(sizeof(struct String) * nrow);
    for(i=0; i<nrow; i++) String_new_(&(this->row_name[i]));
}

void Table_free_(struct Table* this) {
    Int i;
    for(i = 0; i < TABLE_MAX_COLUMNS; i++)
        if(this->addr[i]) {
            free(this->addr[i]);
            this->addr[i] = NULL;
        }
    if(this->row_name) free(this->row_name);
    this->row_name = NULL;
}

Address Table_get_kk(const struct Table* this, struct String row, struct String col) {
    Int i, j;
    if(this->linear_row) error_invalid_argument("(Table_get_kk) row of Table is linear indexed");
    i = _key2index(this->row_name, this->nrow, row);
    j = _key2index(this->col_name, this->ncol, col);
    if(i < 0) error_index_out_of_bounds("(Table_get_kk) key not exit in row");
    if(j < 0) error_index_out_of_bounds("(Table_get_kk) key not exit in column");
    return this->addr[j] + (i * this->elsize[j]);
}

Address Table_get_ik(const struct Table* this, Int row, struct String col) {
    Int j;
    j = _key2index(this->col_name, this->ncol, col);

    if(row < 0 || row >= this->nrow) error_index_out_of_bounds("(Table_get_kk) row index out of bound");
    if(j < 0) error_index_out_of_bounds("(Table_get_kk) key not exit in column");
    return this->addr[j] + (row * this->elsize[j]);
}

Address Table_get_ii(const struct Table* this, Int row, Int col) {
    if(row < 0 || row >= this->nrow) error_index_out_of_bounds("(Table_get_kk) row index out of bound");
    if(col < 0 || col >= this->ncol) error_index_out_of_bounds("(Table_get_kk) col index out of bound");
    return this->addr[col] + (row * this->elsize[col]);
}

Address Table_get_col_i(const struct Table* this, Int col) {
    if(col < 0 || col >= this->ncol) error_index_out_of_bounds("(Table_get_kk) col index out of bound");
    return this->addr[col];
}

Address Table_get_col_k(const struct Table* this, struct String col) {
    Int j;
    j = _key2index(this->col_name, this->ncol, col);
    if(j < 0) error_index_out_of_bounds("(Table_get_kk) key not exit in column");
    return this->addr[j];
}
