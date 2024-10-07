#ifndef _CBL_DICT_H_
#define _CBL_DICT_H_

#include "CBL_Basic.h"
#include "CBL_String.h"

/**
 * @brief DictNode struct
 * @param typecode UInt8
 * @param key String
 * @param address Address
 * @param next DictNode*
 */
typedef struct _DICT_DictNode_t {
    UInt8                    typecode;
    String                   key;
    Address                  address;
    struct _DICT_DictNode_t* next;
} DictNode;

/**
 * @brief DictNode struct
 * @param typecode UInt8
 * @param key String
 * @param address Address
 * @param next DictNode*
 */
typedef DictNode* Dict;

/**
 * @brief get address and typecode to the element
 * @param dict
 * @param key
 * @param typecode
 * @return
 */
Address DICT_get_element(const Dict dict, const String key, UInt8* typecode);

/**
 * @brief create a new node and save the address to the node
 * @param dict
 * @param key
 * @param address
 * @param typecode
 * @return
 */
Address DICT_add_element(Dict* dict, const String key, const Address address, UInt8 typecode);

/**
 * @brief delete the node with the key
 * @param dict
 * @param key
 * @param typecode
 * @return address to the element of deleted node
 */
Address DICT_pop_element(Dict* dict, const String key, UInt8* typecode);

/**
 * @brief get all keys of dict
 * @param dict
 * @param keys
 * @return number of keys in dict
 */
Int DICT_keys(const Dict dict, String** keys);

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
typedef struct _DICT_Sheet {
    UInt8   typecode;
    size_t  element_size;
    Int     n0, n1;
    String* key0;
    String* key1;
    Address addr;
} Sheet;

/**
 * @brief allocate memory for sheet
 * @param typecode
 * @param element_size
 * @param n0
 * @param n1
 * @return
 */
Sheet SHEET_allocate(UInt8 typecode, size_t element_size, Int n0, Int n1);

/**
 * @brief free memory allocated for sheet
 * @param sheet
 */
void SHEET_free(Sheet* sheet);

/**
 * @brief get linear index from string array keys
 * @param sheet_keys
 * @param n
 * @param key
 * @return
 */
Int SHEET_key2index(const String* sheet_keys, Int n, const String key);

/**
 * @brief index in sheet with both keys in String
 * @param sheet
 * @param key0
 * @param key1
 * @return
 */
Int SHEET_key_key2shift(const Sheet sheet, const String key0, const String key1);

/**
 * @brief index in sheet with linear index number in dimension 0 and String key in dimension 1
 * @param sheet
 * @param index0
 * @param key1
 * @return
 */
Int SHEET_index_key2shift(const Sheet sheet, Int index0, const String key1);

#endif // _CBL_DICT_H_
