#ifndef _CBL_DICT_H_
#define _CBL_DICT_H_

#include "CBL_Basic.h"
#include "CBL_String.h"

typedef struct _DICT_DictNode_t {
    UInt8                    typecode;
    String                   key;
    Address                  address;
    struct _DICT_DictNode_t* next;
} DictNode;

typedef DictNode* Dict;

Address DICT_get_element(const Dict dict, const String key, UInt8* typecode);

Address DICT_add_element(Dict* dict, const String key, const Address address, UInt8 typecode);

Address DICT_pop_element(Dict* dict, const String key, UInt8* typecode);

Int DICT_keys(const Dict dict, String** keys);

typedef struct _DICT_Sheet {
    UInt8   typecode;
    size_t  element_size;
    Int     n0, n1;
    String* key0;
    String* key1;
    Address addr;
} Sheet;

Sheet SHEET_allocate(UInt8 typecode, size_t element_size, Int n0, Int n1);

void SHEET_free(Sheet* sheet);

Int SHEET_key2index(const String* sheet_keys, Int n, const String key);

Int SHEET_key_key2shift(const Sheet sheet, const String key0, const String key1);

Int SHEET_index_key2shift(const Sheet sheet, Int index0, const String key1);

#endif // _CBL_DICT_H_
