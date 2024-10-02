#ifndef _CBL_STRING_H_
#define _CBL_STRING_H_

#include "CBL_Basic.h"

typedef struct _STR_String {
    Int len;
    Char str[STR_MAX_STRING_LENGTH];
} String;

String STR_empty_string();

String STR_String(const char* str);

Bool STR_isequal(String str1, String str2);

String STR_join(String* strs, Int n, String separator);

Int STR_next_match(const String str, const String pat, Int start);

Int STR_split(String** out, String str, String delim);

String STR_slice(String str, Int idx1, Int idx2);

String STR_strip(String str);

String STR_replace(String str, String pattern, String value);

String STR_replace_all(String str, String pattern, String value);

// Int STR_write(String str, FILE* fp);
//
// String STR_read(FILE* fp);

#endif // _CBL_STRING_H_
