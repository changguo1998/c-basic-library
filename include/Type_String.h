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
#include "Module_Basic.h"

/**
 * @brief StringMethods
 */
struct StringMethods {
    void (*free_)(struct String* this);
    void (*copy_)(struct String* this, struct String other);
    void (*cstr_)(const struct String* this, Char** cstr);
    void (*read_)(struct String* this, FILE* fp);
    void (*readuntil_)(struct String* this, FILE* fp, Char c);
    void (*readline_)(struct String* this, FILE* fp);
    void (*readfile_)(struct String* this, FILE* fp);
    void (*write)(struct String* this, FILE* fp);
    void (*print)(struct String* this, FILE* fp);
    void (*println)(struct String*this, FILE* fp);
    void (*set_)(struct String* this, const char* str);
    Bool (*isequal)(const struct String* this, struct String another);
    void (*append_)(struct String* this, struct String another);
    void (*join_)(struct String*       this,
                  const struct String* list,
                  Int                  n,
                  struct String        delimiter);
    Int (*nextmatch)(const struct String* this,
                     struct String        pattern,
                     Int                  start);
    Bool (*startswith)(const struct String* this, struct String pattern);
    Bool (*endswith)(const struct String* this, struct String pattern);
    Bool (*contains)(const struct String* this, struct String pattern);
    void (*substring_)(struct String* this, Int start, Int stop);
    void (*split)(const struct String* this,
                  struct String        delimiter,
                  struct String**      list,
                  Int*                 n);
    void (*strip_)(struct String* this);
    void (*replace_)(struct String* this,
                     struct String  pattern,
                     struct String  replacement);
    void (*replaceall_)(struct String* this,
                        struct String  pattern,
                        struct String  replacement);
    void (*reverse_)(struct String* this);
};


extern const struct StringMethods _CBL_STRING_METHODS;


// struct String String_set(const char* str);
void String_free_(struct String* this);
void String_copy_(struct String* this, struct String other);
void String_cstr_(const struct String* this, Char** cstr);
void String_read_(struct String* this, FILE* fp);
void String_readuntil_(struct String* this, FILE* fp, Char c);
void String_readline_(struct String* this, FILE* fp);
void String_readfile_(struct String* this, FILE* fp);
void String_write(struct String* this, FILE* fp);
void String_print(struct String* this, FILE* fp);
void String_println(struct String* this, FILE* fp);
void String_set_(struct String* this, const char* str);
Bool String_isequal(const struct String* this, struct String another);
void String_append_(struct String* this, struct String another);
void String_join_(struct String*       this,
                  const struct String* list,
                  Int                  n,
                  struct String        delimiter);
Int String_nextmatch(const struct String* this,
                     struct String        pattern,
                     Int                  start);
Bool String_startswith(const struct String* this, struct String pattern);
Bool String_endswith(const struct String* this, struct String pattern);
Bool String_contains(const struct String* this, struct String pattern);
void String_substring_(struct String* this, Int start, Int stop);
void String_split(const struct String* this,
                  struct String        delimiter,
                  struct String**      list,
                  Int*                 n);
void String_strip_(struct String* this);
void String_replace_(struct String* this,
                     struct String  pattern,
                     struct String  replacement);
void String_replaceall_(struct String* this,
                        struct String  pattern,
                        struct String  replacement);
void String_reverse_(struct String* this);

static inline void String_new_(struct String* this) {
    this->len = 0;
    memset(this->str, '\0', STRING_FIXED_BUFFER_LENGTH * sizeof(Char));
    this->more = NULL;
    this->methods = &_CBL_STRING_METHODS;
}


// String STR_read_line(FILE* fp);

// void STR_read_lines(String** string_list, FILE* fp);

// void STR_print_line(String str, FILE* fp);

// void STR_print_lines(const String* str, Int n, FILE* fp);


#endif // _CBL_STRING_H_
