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

#ifndef _CBL_STRING_H_
#define _CBL_STRING_H_

#include <stdio.h>
#include <string.h>
#include "CBL_Basic.h"

struct String {
    Char str[STR_MAX_STRING_LENGTH];
    Int  len;

    const struct StringMethods* methods;
};

/**
 * @brief StringMethods
 */
struct StringMethods {

    /**
     * @brief set String to empty
     * @param this struct String*
     * @return struct String
     */
    struct String (*clean_)(struct String* this);

    /**
     * @brief initialize a String type using C like string array
     * @param this struct String*
     * @param str const char*
     * @return struct String
     */
    struct String (*set_)(struct String* this, const char* str);

    /**
     * @brief compare two String
     * @param this const struct String*
     * @param another struct String*
     * @return true if equal, false if not equal or different in length
     */
    Bool (*isequal)(const struct String* this, struct String another);

    /**
     * @brief append a string to the current string
     * @param this struct String*
     * @param another struct String*
     * @return struct String
     */
    struct String (*append_)(struct String* this, struct String another);

    /**
     * @brief join a list of string and store in current string
     * @param this struct String*
     * @param list struct String*
     * @param n Int
     * @param delimiter struct String
     * @return struct String
     */
    struct String (*join_)(struct String*       this,
                           const struct String* list,
                           Int                  n,
                           struct String        delimiter);

    /**
     * @brief find next match in str with pattern
     * @param this const struct String*
     * @param pattern struct String
     * @param start Int
     * @return index of the beginning in this string
     */
    Int (*next_match)(const struct String* this,
                      struct String        pattern,
                      Int                  start);

    /**
     * @brief test if this string starts with pattern
     * @param this
     * @param pattern struct String
     */
    Bool (*starts_with)(const struct String* this, struct String pattern);

    /**
     * @brief test if this string ends with pattern
     * @param this
     * @param pattern struct String
     */
    Bool (*ends_with)(const struct String* this, struct String pattern);

    /**
     * @brief test if str contains pattern
     * @param this
     * @param pattern struct String
     */
    Bool (*contains)(const struct String* this, struct String pattern);

    /**
     * @brief get substring with from start to stop
     * @param this const struct String*
     * @param start Int
     * @param stop Int
     * @return struct String
     */
    struct String (*substring_)(struct String* this, Int start, Int stop);

    /**
     * @brief split String into Strings by delimiter, stored in list
     * @param this const struct String*
     * @param delimiter struct String
     * @param list struct String**
     * @param n Int*
     */
    void (*split)(const struct String* this,
                  struct String        delimiter,
                  struct String**      list,
                  Int*                 n);

    /**
     * @brief remove blanks at the head and tail of str
     * @param this const struct String*
     * @return struct String
     */
    struct String (*strip_)(struct String* this);

    /**
     * @brief replace first pattern showed in this using replacement
     * @param this struct String*
     * @param pattern struct String
     * @param replacement struct String
     * @return struct String
     */
    struct String (*replace_)(struct String* this,
                              struct String  pattern,
                              struct String  replacement);

    /**
     * @brief replace all pattern showed in this using replacement
     * @param this struct String*
     * @param pattern struct String
     * @param replacement struct String
     * @return struct String
     */
    struct String (*replace_all_)(struct String* this,
                                  struct String  pattern,
                                  struct String  replacement);

    /**
     * @brief reverse string
     * @param this
     * @return struct String
     */
    struct String (*reverse_)(struct String* this);
};


extern const struct StringMethods _CBL_STRING_METHODS;


struct String String_empty();
struct String String_clean_(struct String* this);
struct String String_set_(struct String* this, const char* str);
Bool          String_isequal(const struct String* this, struct String another);
struct String String_append_(struct String* this, struct String another);
struct String String_join_(struct String*       this,
                           const struct String* list,
                           Int                  n,
                           struct String        delimiter);
Int String_next_match(const struct String* this,
                      struct String        pattern,
                      Int                  start);
Bool String_starts_with(const struct String* this, struct String pattern);
Bool String_ends_with(const struct String* this, struct String pattern);
Bool String_contains(const struct String* this, struct String pattern);
struct String String_substring_(struct String* this, Int start, Int stop);
void String_split(const struct String* this,
                  struct String        delimiter,
                  struct String**      list,
                  Int*                 n);
struct String String_strip_(struct String* this);
struct String String_replace_(struct String* this,
                              struct String  pattern,
                              struct String  replacement);
struct String String_replace_all_(struct String* this,
                                  struct String  pattern,
                                  struct String  replacement);
struct String String_reverse_(struct String* this);

static inline void String_new_(struct String* this) {
    this->len = 0;
    memset(this->str, '\0', STR_MAX_STRING_LENGTH * sizeof(Char));
    this->methods = &_CBL_STRING_METHODS;
}

// static inline void StringMethods_new(struct StringMethods* this) {
//     this->clean_ = &String_clean_;
//     this->set_ = &String_set_;
//     this->isequal = &String_isequal;
//     this->append_ = &String_append_;
//     this->join_ = &String_join_;
//     this->next_match = &String_next_match;
//     this->starts_with = &String_starts_with;
//     this->ends_with = &String_ends_with;
//     this->contains = &String_contains;
//     this->split = &String_split;
//     this->substring_ = &String_substring_;
//     this->strip_ = &String_strip_;
//     this->replace_ = &String_replace_;
//     this->replace_all_ = &String_replace_all_;
//     this->reverse_ = &String_reverse_;
// }

// /**
//  * @brief read one line from ascii file
//  * @param fp
//  * @return
//  */
// String STR_read_line(FILE* fp);
//
// /**
//  * @brief read all lines from ascii file, each line will be a String
//  * @param string_list
//  * @param fp
//  */
// void STR_read_lines(String** string_list, FILE* fp);
//
// /**
//  * @brief print str as a line with a '\\n' in the end
//  * @param str
//  * @param fp
//  */
// void STR_print_line(String str, FILE* fp);
//
// /**
//  * @brief print String array into ascii file with each str as a line
//  * @param str
//  * @param n
//  * @param fp
//  */
// void STR_print_lines(const String* str, Int n, FILE* fp);


#endif // _CBL_STRING_H_
