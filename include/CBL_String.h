#ifndef _CBL_STRING_H_
#define _CBL_STRING_H_

#include <stdio.h>
#include "CBL_Basic.h"

typedef struct _STR_String {
    Int  len;
    Char str[STR_MAX_STRING_LENGTH];
} String;

String STR_empty_string();

String STR_String(const char* str);

Bool STR_isequal(String str1, String str2);

String STR_join(const String* string_list, Int n, String separator);

Int STR_next_match(const String str, const String pattern, Int start);

Int STR_split(String** out, const String str, const String delim);

String STR_slice(String str, Int idx1, Int idx2);

String STR_strip(String str);

String STR_replace(String str, String pattern, String value);

String STR_replace_all(String str, String pattern, String value);

size_t STR_write(String str, FILE* fp);

String STR_read(FILE* fp);

String STR_read_line(FILE* fp);

void STR_read_lines(String** string_list, FILE* fp);

void STR_print_line(String str, FILE* fp);

void STR_print_lines(const String* str, Int n, FILE* fp);

Bool STR_starts_with(String str, String pattern);

Bool STR_ends_with(String str, String pattern);

Bool STR_contains(String str, String pattern);

String STR_reverse(String str);

#endif // _CBL_STRING_H_
