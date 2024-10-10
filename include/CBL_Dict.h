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

#ifndef _CBL_DICT_H_
#define _CBL_DICT_H_

#include <string.h>

#include "CBL_Basic.h"
#include "CBL_String.h"

/* * * * * * * * * * * * * * * * *
 * StaticDict
 * * * * * * * * * * * * * * * * */

/**
 * @brief struct StaticDict
 * @param key String[]
 * @param flag Bool[]
 * @param typecode UInt8[]
 * @param address Address[]
 */
struct StaticDict {
    String  key[STATIC_DICT_SIZE];
    Bool    flag[STATIC_DICT_SIZE];
    UInt8   typecode[STATIC_DICT_SIZE];
    Address address[STATIC_DICT_SIZE];

    /**
     * @brief get address of saved data by key
     * @param this const struct StaticDict*
     * @param key String
     * @param typecode UInt8*
     * @return Address
     */
    Address (*get)(const struct StaticDict* this, String key, UInt8* typecode);

    /**
     * @brief get address of saved data by key and delete it from dict
     * @param this const struct StaticDict*
     * @param key String
     * @param typecode UInt8*
     * @return Address
     */
    Address (*pop_)(struct StaticDict* this, String key, UInt8* typecode);

    /**
     * @brief set new address to key, and return the address of previous data
     * @param this const struct StaticDict*
     * @param key String
     * @param typecode UInt8
     * @param address Address
     * @return Address of previous data
     */
    Address (*set_)(
        struct StaticDict* this,
        String             key,
        UInt8              typecode,
        Address            address);

    /**
     * @brief append data if there is empty element, otherwise do nothing
     * @param this struct StaticDict*
     * @param key String
     * @param typecode UInt8
     * @param address Address
     * @return true if success
     */
    Bool (*push_)(
        struct StaticDict* this,
        String             key,
        UInt8              typecode,
        Address            address);
};

Address StaticDict_get(
    const struct StaticDict* this,
    String                   key,
    UInt8*                   typecode);

Address StaticDict_pop_(struct StaticDict* this, String key, UInt8* typecode);

Address StaticDict_set_(
    struct StaticDict* this,
    String             key,
    UInt8              typecode,
    Address            address);

Bool StaticDict_push_(
    struct StaticDict* this,
    String             key,
    UInt8              typecode,
    Address            address);

/**
 * @brief bind methods for struct to behave like an object
 * @param dict struct StaticDict*
 */
static inline void StaticDict_new(struct StaticDict* dict) {
    memset(dict, 0, sizeof(Bool) * STATIC_DICT_SIZE);
    dict->get = &StaticDict_get;
    dict->pop_ = &StaticDict_pop_;
    dict->set_ = &StaticDict_set_;
    dict->push_ = &StaticDict_push_;
}

/* * * * * * * * * * * * * * * * *
 * DynamicDict
 * * * * * * * * * * * * * * * * */

/**
 * @brief DictNode
 * @param typecode UInt8
 * @param key String
 * @param address Address
 * @param next DictNode*
 */
struct DictNode {
    UInt8            typecode;
    String           key;
    Address          address;
    struct DictNode* next;
};

/**
 * @brief struct Dict\n
 * Address get(Dict* this, String key, UInt8* typecode);
 */
struct DynamicDict {
    struct DictNode* head = NULL;

    Address (*get)(const struct DynamicDict* this, String key, UInt8* typecode);

    Address (*pop_)(struct DynamicDict* this, String key, UInt8* typecode);

    Address (*set_)(
        struct DynamicDict* this,
        String              key,
        UInt8               typecode,
        Address             address);

    void (*push_)(
        struct DynamicDict* this,
        String              key,
        UInt8               typecode,
        Address             address);
};

Address DynamicDict_get(const struct DynamicDict* this,
                        String                    key,
                        UInt8*                    typecode);

Address DynamicDict_pop_(struct DynamicDict* this, String key, UInt8* typecode);

Address DynamicDict_set_(struct DynamicDict* this,
                         String              key,
                         UInt8               typecode,
                         Address             address);

void DynamicDict_push_(struct DynamicDict* this,
                       String              key,
                       UInt8               typecode,
                       Address             address);

static inline void DynamicDict_new(struct DynamicDict* this) {
    this->head = NULL;
    this->get = &DynamicDict_get;
    this->pop_ = &DynamicDict_pop_;
    this->set_ = &DynamicDict_set_;
    this->push_ = &DynamicDict_push_;
}

Address DICT_get_element(struct DictNode* dict, String key, UInt8* typecode);

Address DICT_add_element(
    struct DictNode** dict,
    String            key,
    Address           address,
    UInt8             typecode);

Address DICT_pop_element(struct DictNode** dict, String key, UInt8* typecode);

Int DICT_keys(struct DictNode* dict, String** keys);

/* * * * * * * * * * * * * * * * *
 * DynamicDict
 * * * * * * * * * * * * * * * * */

/**
 * @brief Sheet struct
 * @param typecode UInt8
 * @param element_size size_t
 * @param n0 Int, size in dimension 0
 * @param n1 Int, size in dimension 1
 * @param key0 String*
 * @param key1 String*
 * @param addr Address
 */
struct Sheet {
    UInt8   typecode;
    size_t  element_size;
    Int     n0, n1;
    String* key0;
    String* key1;
    Address addr;
};

/**
 * @brief allocate memory for sheet
 * @param typecode
 * @param element_size
 * @param n0
 * @param n1
 * @return
 */
void SHEET_allocate(
    struct Sheet* sheet,
    UInt8         typecode,
    size_t        element_size,
    Int           n0,
    Int           n1);

/**
 * @brief free memory allocated for sheet
 * @param sheet
 */
void SHEET_free(struct Sheet* sheet);

/**
 * @brief index in sheet with both keys in String
 * @param sheet
 * @param key0
 * @param key1
 * @return
 */
Int SHEET_key_key2shift(
    struct Sheet sheet,
    const String key0,
    const String key1);

/**
 * @brief index in sheet with linear index number in dimension 0 and String key in dimension 1
 * @param sheet
 * @param index0
 * @param key1
 * @return
 */
Int SHEET_index_key2shift(struct Sheet sheet, Int index0, const String key1);

#endif // _CBL_DICT_H_
