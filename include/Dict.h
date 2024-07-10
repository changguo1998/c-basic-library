#ifndef _DICT_H_
#define _DICT_H_

#include "Basic.h"

#define DICT_DEFAUTL_MAX_ELEMENTS 1024

typedef struct _DICT_DictElement{
    UInt key;
    void *addr;
} DictElement;

/// @brief struct _DICT_DictVector. contains: UInt MaxLen; DictElement *kvs;
typedef struct _DICT_DictArray{
    UInt MaxLen;
    DictElement *kvs;
} Dict;

UInt DICT_hash_memory(void * addr, UInt size);

void *DICT_get_element(Dict dict, UInt key);

#endif // _DICT_H_
