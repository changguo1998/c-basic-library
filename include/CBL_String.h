#ifndef _CBL_STRING_H_
#define _CBL_STRING_H_

#include <stdio.h>
#include "CBL_Basic.h"

/**
 * @brief String struct
 * @param len Int
 * @param str Char array [STR_MAX_STRING_LENGTH]
 */
typedef struct _STR_String {
    Int  len;
    Char str[STR_MAX_STRING_LENGTH];
} String;

/**
 * @brief
 * @return an empty string
 */
String STR_empty_string();

/**
 * @brief initialize a String type using C like string array
 * @param str
 * @return
 */
String STR_String(const char* str);

/**
 * @brief compare two String
 * @param str1 String
 * @param str2 String
 * @return true if equal, false if not equal or different in length
 */
Bool STR_isequal(const String str1, const String str2);

/**
 * @brief join Strings in String array into one String, with separator
 * @param string_list String*
 * @param n number of String in string_list
 * @param separator
 * @return joint String
 */
String STR_join(const String* string_list, Int n, const String separator);

/**
 * @brief find next match in str with pattern
 * @param str
 * @param pattern
 * @param start
 * @return index of the begin in str
 */
Int STR_next_match(const String str, const String pattern, Int start);

/**
 * @brief split String into Strings by delim
 * @param out stored
 * @param str
 * @param delim
 * @return number of substrings
 */
Int STR_split(String** out, const String str, const String delim);

/**
 * @brief get substring of str with index.
 * @param str
 * @param idx1
 * @param idx2
 * @return  if idx1 <= idx2, return str[idx1:idx2]; else return str[idx1:-1:idx2]
 */
String STR_slice(const String str, Int idx1, Int idx2);

/**
 * @brief remove blanks at the head and tail of str
 * @param str
 * @return
 */
String STR_strip(const String str);

/**
 * @brief replace pattern showed in str to value
 * @param str
 * @param pattern
 * @param value
 * @return replaced string
 */
String STR_replace(const String str, const String pattern, const String value);

/**
 * @brief
 * @param str
 * @param pattern
 * @param value
 * @return
 */
String STR_replace_all(const String str, const String pattern, const String value);

/**
 * @brief write binary string to file
 * @param str
 * @param fp
 * @return
 */
size_t STR_write(const String str, FILE* fp);

/**
 * @brief read binary string from file
 * @param fp
 * @return
 */
String STR_read(FILE* fp);

/**
 * @brief read one line from ascii file
 * @param fp
 * @return
 */
String STR_read_line(FILE* fp);

/**
 * @brief read all lines from ascii file, each line will be a String
 * @param string_list
 * @param fp
 */
void STR_read_lines(String** string_list, FILE* fp);

/**
 * @brief print str as a line with a '\\n' in the end
 * @param str
 * @param fp
 */
void STR_print_line(String str, FILE* fp);

/**
 * @brief print String array into ascii file with each str as a line
 * @param str
 * @param n
 * @param fp
 */
void STR_print_lines(const String* str, Int n, FILE* fp);

/**
 * @brief test if str starts with pattern
 * @param str
 * @param pattern
 * @return
 */
Bool STR_starts_with(const String str, const String pattern);

/**
 * @brief test if str ends with pattern
 * @param str
 * @param pattern
 * @return
 */
Bool STR_ends_with(const String str, const String pattern);

/**
 * @brief test if str contains pattern
 * @param str
 * @param pattern
 * @return
 */
Bool STR_contains(const String str, const String pattern);

/**
 * @brief reverse string
 * @param str
 * @return
 */
String STR_reverse(const String str);

#endif // _CBL_STRING_H_
