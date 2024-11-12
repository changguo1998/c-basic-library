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

#ifndef _CBL_DICT_H_
#define _CBL_DICT_H_

#include "Module_Basic.h"
#include "Type_String.h"


// # StaticDict


struct StaticDictMethods {

    /**
     * @brief get address of saved data by key
     * @param this const struct StaticDict*
     * @param key String
     * @param typecode Int*
     * @return Address
     */
    Address (*get)(const struct StaticDict* this, struct String key, Int* typecode);

    /**
     * @brief get address of saved data by key and delete it from dict
     * @param this const struct StaticDict*
     * @param key String
     * @param typecode Int*
     * @return Address
     */
    Address (*pop_)(struct StaticDict* this, struct String key, Int* typecode);

    /**
     * @brief set new address to key, and return the address of previous data
     * @param this const struct StaticDict*
     * @param key String
     * @param typecode Int
     * @param address Address
     * @return Address of previous data
     */
    Address (*set_)(struct StaticDict* this, struct String key, Int typecode, Address address);

    /**
     * @brief append data if there is empty element, otherwise do nothing
     * @param this struct StaticDict*
     * @param key String
     * @param typecode Int
     * @param address Address
     * @return true if success
     */
    void (*push_)(struct StaticDict* this, struct String key, Int typecode, Address address);

    /**
     * @brief check if key showed in dict
     * @param this
     * @param key
     * @return Bool
     */
    Bool (*has_key)(const struct StaticDict* this, struct String key);

    /**
     * @brief count number of elements saved in dict
     * @param this
     * @return Int
     */
    Int (*n_elements)(const struct StaticDict* this);

    /**
     * @brief get first len_key_list keys of dict
     * @param this
     * @param key_list struct String*
     * @param len_key_list
     * @return true if key_list is completed, false if some keys is not saved in key_list
     */
    Int (*keys)(const struct StaticDict* this, struct String* key_list, Int len_key_list);
};

Address StaticDict_get(const struct StaticDict* this, struct String key, Int* typecode);
Address StaticDict_pop_(struct StaticDict* this, struct String key, Int* typecode);
Address StaticDict_set_(struct StaticDict* this, struct String key, Int typecode, Address address);
void    StaticDict_push_(struct StaticDict* this, struct String key, Int typecode, Address address);
Bool    StaticDict_has_key(const struct StaticDict* this, struct String key);
Int     StaticDict_n_elements(const struct StaticDict* this);
Int     StaticDict_keys(const struct StaticDict* this, struct String* key_list, Int len_key_list);


// # DynamicDict

/**
 * @brief DynamicDictNode
 * @param key String
 * @param typecode Int
 * @param address Address
 * @param next DynamicDictNode*
 */
struct DynamicDictNode {
    struct String key;

    Int     typecode;
    Address address;

    struct DynamicDictNode* next;
};

struct DynamicDictMethods {
    /**
     * @brief get address of saved data by key
     * @param this const struct StaticDict*
     * @param key String
     * @param typecode Int*
     * @return Address
     */
    Address (*get)(const struct DynamicDict* this, struct String key, Int* typecode);

    /**
     * @brief get address of saved data by key and delete it from dict
     * @param this const struct StaticDict*
     * @param key String
     * @param typecode Int*
     * @return Address
     */
    Address (*pop_)(struct DynamicDict* this, struct String key, Int* typecode);


    /**
     * @brief set new address to key, and return the address of previous data
     * @param this const struct StaticDict*
     * @param key String
     * @param typecode Int
     * @param address Address
     * @return Address of previous data
     */
    Address (*set_)(struct DynamicDict* this, struct String key, Int typecode, Address address);


    /**
     * @brief append data if there is empty element, otherwise do nothing
     * @param this struct StaticDict*
     * @param key String
     * @param typecode Int
     * @param address Address
     * @return true if success
     */
    void (*push_)(struct DynamicDict* this, struct String key, Int typecode, Address address);
    /**
     * @brief check if key showed in dict
     * @param this
     * @param key
     * @return Bool
     */
    Bool (*has_key)(const struct DynamicDict* this, struct String key);

    /**
     * @brief count number of elements saved in dict
     * @param this
     * @return Int
     */
    Int (*n_elements)(const struct DynamicDict* this);

    /**
     * @brief get first len_key_list keys of dict
     * @param this
     * @param key_list struct String*
     * @param len_key_list
     * @return true if key_list is completed, false if some keys is not saved in key_list
     */
    Int (*keys)(const struct DynamicDict* this, struct String* key_list, Int len_key_list);
};

Address DynamicDict_get(const struct DynamicDict* this, struct String key, Int* typecode);
Address DynamicDict_pop_(struct DynamicDict* this, struct String key, Int* typecode);
Address DynamicDict_set_(struct DynamicDict* this, struct String key, Int typecode, Address address);
void    DynamicDict_push_(struct DynamicDict* this, struct String key, Int typecode, Address address);
Bool    DynamicDict_has_key(const struct DynamicDict* this, struct String key);
Int     DynamicDict_n_elements(const struct DynamicDict* this);
Int     DynamicDict_keys(const struct DynamicDict* this, struct String* key_list, Int len_key_list);

// # Table

struct TableMethods {
    /**
     * @brief allocate memory for sheet
     * @param this
     * @param elsize
     * @param nrow
     * @param ncol
     */
    void (*alloc_)(struct Table* this, Int* elsize, Int nrow, Int ncol);

    /**
     * @brief
     * @param this
     */
    void (*free_)(struct Table* this);

    /**
     * @brief index in sheet with both keys in String
     * @param this
     * @param row struct String
     * @param col struct String
     * @return Address
     */
    Address (*get_kk)(const struct Table* this, struct String row, struct String col);

    /**
     * @brief index in sheet with both keys in String
     * @param this
     * @param row Int
     * @param col struct String
     * @return Address
     */
    Address (*get_ik)(const struct Table* this, Int row, struct String col);

    /**
     * @brief index in sheet with both keys in String
     * @param this
     * @param row Int
     * @param col Int
     * @return Address
     */
    Address (*get_ii)(const struct Table* this, Int row, Int col);

    /**
     * @brief index in sheet with both keys in String
     * @param this
     * @param col Int
     * @return Address
     */
    Address (*get_col_i)(const struct Table* this, Int col);

    /**
     * @brief index in sheet with both keys in String
     * @param this
     * @param col struct String
     * @return Address
     */
    Address (*get_col_k)(const struct Table* this, struct String col);
};

void    Table_alloc_(struct Table* this, Int* elsize, Int nrow, Int ncol);
void    Table_free_(struct Table* this);
Address Table_get_kk(const struct Table* this, struct String row, struct String col);
Address Table_get_ik(const struct Table* this, Int row, struct String col);
Address Table_get_ii(const struct Table* this, Int row, Int col);
Address Table_get_col_i(const struct Table* this, Int col);
Address Table_get_col_k(const struct Table* this, struct String col);


extern struct StaticDictMethods  _CBL_STATIC_DICT_METHODS;
extern struct DynamicDictMethods _CBL_DYNAMIC_DICT_METHODS;
extern struct TableMethods       _CBL_TABLE_METHODS;

/**
 * @brief bind methods for struct to behave like an object
 * @param dict struct StaticDict*
 */
static inline void StaticDict_new_(struct StaticDict* dict) {
    Int i;
    for(i = 0; i < STATIC_DICT_SIZE; i++) {
        String_new_(&(dict->key[i]));
        dict->flag[i] = false;
        dict->typecode[i] = TYPECODE_UNKNOWN;
        dict->address[i] = NULL;
    }
    dict->methods = &_CBL_STATIC_DICT_METHODS;
}

static inline void DynamicDict_new_(struct DynamicDict* this) {
    this->data = NULL;
    this->methods = &_CBL_DYNAMIC_DICT_METHODS;
}

static inline void Table_new_(struct Table* this) {
    Int i;
    this->nrow = this->ncol = 0;
    this->linear_row = true;
    for(i = 0; i < TABLE_MAX_COLUMNS; i++) {
        this->elsize[i] = 0;
        this->addr[i] = NULL;
        String_new_(&(this->col_name[i]));
    }
    this->row_name = NULL;
    this->methods = &_CBL_TABLE_METHODS;
}

#endif // _CBL_DICT_H_
