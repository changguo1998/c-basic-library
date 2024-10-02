#ifndef _DICT_H_
#define _DICT_H_

#include "CBL_Basic.h"

typedef struct _DICT_DictElement {
    char key[DICT_MAX_KEY_LENGTH];
    void* addr;
} DictElement;

/// @brief struct _DICT_DictVector. contains: UInt MaxLen; DictElement kvs[DICT_DEFAULT_MAX_ELEMENTS];
typedef struct _DICT_DictArray {
    UInt MaxLen;
    DictElement kvs[DICT_DEFAULT_MAX_ELEMENTS];
} Dict;

void* DICT_get_element(Dict dict, const char* key);

#endif // _DICT_H_
