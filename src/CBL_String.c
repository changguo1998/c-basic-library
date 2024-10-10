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

#include <stdlib.h>
#include <string.h>
#include "CBL_String.h"

const struct StringMethods _CBL_STRING_METHODS = {
    &String_clean_,
    &String_set_,
    &String_isequal,
    &String_append_,
    &String_join_,
    &String_next_match,
    &String_starts_with,
    &String_ends_with,
    &String_contains,
    &String_substring_,
    &String_split,
    &String_strip_,
    &String_replace_,
    &String_replace_all_,
    &String_reverse_
};

struct String String_empty() {
    struct String str;
    String_new_(&str);
    return str;
}

struct String String_clean_(struct String* this) {
    this->len = 0;
    memset(this->str, '\0', sizeof(Char) * STR_MAX_STRING_LENGTH);
    return *this;
}

struct String String_set_(struct String* this, const char* str) {
    String_clean_(this);
    if(strlen(str) > STR_MAX_STRING_LENGTH)
        error_out_of_memory("(STR_String) Warning: string is too long\n");
    else {
        this->len = (Int)strlen(str);
        strcpy(this->str, str);
    }
    return *this;
}

Bool String_isequal(const struct String* this, struct String another) {
    Int i;
    if(this->len != another.len) return false;
    for(i = 0; i < this->len; i++)
        if(this->str[i] != another.str[i])
            return false;
    return true;
}

void _append_string(Char* str1, Int* n1, const Char* str2, Int n2) {
    Int i;
    for(i = 0; i < n2; i++)
        if(*n1 >= STR_MAX_STRING_LENGTH)
            error_out_of_memory("(_append_string) string is too long\n");
        else {
            str1[*n1] = str2[i];
            *n1 += 1;
        }
}

struct String String_append_(struct String* this, struct String another) {
    _append_string(this->str, &(this->len), another.str, another.len);
    return *this;
}

struct String String_join_(struct String*       this,
                           const struct String* list,
                           Int                  n,
                           struct String        delimiter) {
    Int i_list;
    String_clean_(this);
    if(n <= 0) return *this;
    _append_string(this->str, &(this->len), list[0].str, list[0].len);
    for(i_list = 1; i_list < n; i_list++) {
        _append_string(this->str, &(this->len),
            delimiter.str, delimiter.len);
        _append_string(this->str, &(this->len),
            list[i_list].str, list[i_list].len);
    }
    return *this;
}

Int String_next_match(const struct String* this,
                      struct String        pattern,
                      Int                  start) {
    Int i, j;
    if(this->len == 0) return -1;
    if(pattern.len == 0) return -1;
    j = 0;
    for(i = start; i < this->len; i++) {
        if(this->str[i] == pattern.str[j]) j += 1;
        else {
            i -= j;
            j = 0;
        }
        if(j == pattern.len) return i - pattern.len + 1;
    }
    return -1;
}

Bool String_starts_with(const struct String* this, struct String pattern) {
    Int i;
    if(this->len < pattern.len) return false;
    for(i = 0; i < pattern.len; i++)
        if(this->str[i] != pattern.str[i])
            return false;
    return true;
}

Bool String_ends_with(const struct String* this, struct String pattern) {
    Int i;
    if(this->len < pattern.len) return false;
    for(i = 0; i < pattern.len; i++)
        if(this->str[this->len - 1 - i] != pattern.str[pattern.len - 1 - i])
            return false;
    return true;
}

Bool String_contains(const struct String* this, struct String pattern) {
    return String_next_match(this, pattern, 0) >= 0;
}

struct String String_substring_(struct String* this, Int start, Int stop) {
    Int i, n_sub, start0, stop0;
    if((start < 0 && stop < 0) || (start >= this->len && stop >= this->len))
        error_index_out_of_bounds(
            "(String_substring_) index out of bounds\n");
    if(start > stop) {
        String_clean_(this);
        return *this;
    }
    start0 = start < 0 ? 0 : start;
    start0 = start0 < this->len ? start0 : this->len - 1;
    stop0 = stop < 0 ? 0 : stop;
    stop0 = stop0 < this->len ? stop0 : this->len - 1;
    n_sub = stop0 - start0 + 1;
    for(i = 0; i < n_sub; i++) this->str[i] = this->str[i + start];
    for(i = n_sub; i < this->len; i++) this->str[i] = '\0';
    this->len = n_sub;
    return *this;
}

void String_split(const struct String* this,
                  struct String        delimiter,
                  struct String**      list,
                  Int*                 n) {
    Int *slice_index = NULL, next_slice, i_slice, i;

    if(*list != NULL)
        error_unexpected_allocated_memory(
            "(String_split) buffer already allocated");
    *n = 1;
    i = 0;
    while(i < this->len) {
        next_slice = String_next_match(this, delimiter, i);
        if(next_slice < 0) break;
        *n += 1;
        i = next_slice + delimiter.len;
    }
    slice_index = (Int*)malloc(sizeof(Int) * (*n));
    slice_index[0] = 0;
    next_slice = 0;
    for(i = 1; i < *n; i++) {
        slice_index[i] = String_next_match(this, delimiter, next_slice);
        next_slice = slice_index[i] + delimiter.len;
    }

    *list = (struct String*)malloc(sizeof(struct String) * (*n));

    for(i_slice = 0; i_slice < *n; i_slice++) {
        memcpy(&((*list)[i_slice]), this, sizeof(struct String));
        if(i_slice < *n - 1)
            String_substring_(&((*list)[i_slice]),
                slice_index[i_slice] + delimiter.len,
                slice_index[i_slice + 1] - 1);
        else
            String_substring_(&((*list)[i_slice]),
                slice_index[i_slice] + delimiter.len,
                this->len - 1);
    }
    free(slice_index);
}

struct String String_strip_(struct String* this) {
    Int i, j;
    for(i = 0; i < this->len; i++) if(this->str[i] != ' ') break;
    for(j = this->len - 1; j >= 0; j--) if(this->str[j] != ' ') break;
    if(j > i) return *this;
    return String_substring_(this, i, j);
}

struct String String_replace_(struct String* this,
                              struct String  pattern,
                              struct String  replacement) {
    Int           p;
    struct String buffer[3];
    p = String_next_match(this, pattern, 0);
    if(p < 0) return *this;
    buffer[0] = *this;
    // printf("(String_replace) this: %s\n", this->str);
    // printf("(String_replace) pattern: %s\n", pattern.str);
    // printf("(String_replace) replacement: %s\n", replacement.str);
    // printf("(String_replace) p: %d\n", p);
    String_substring_(&(buffer[0]), 0, p - 1);
    buffer[1] = replacement;
    buffer[2] = *this;
    String_substring_(&(buffer[2]), p + pattern.len, this->len - 1);
    String_join_(this, buffer, 3, String_empty());
    return *this;
}

struct String String_replace_all_(struct String* this,
                                  struct String  pattern,
                                  struct String  replacement) {
    struct String* buffer = NULL;
    Int            n_slice;
    String_split(this, pattern, &buffer, &n_slice);
    String_join_(this, buffer, n_slice, replacement);
    free(buffer);
    return *this;
}

struct String String_reverse_(struct String* this) {
    Int  i, h;
    Char c;
    h = this->len / 2;
    for(i = 0; i < h; i++) {
        c = this->str[i];
        this->str[i] = this->str[this->len - 1 - i];
        this->str[this->len - 1 - i] = c;
    }
    return *this;
}

// ! ==========================================================================
/*
size_t STR_write(const String str, FILE* fp) {
    size_t bytes_written = 0;
    bytes_written += fwrite(&str.len, sizeof(Int), 1, fp);
    bytes_written += fwrite(str.str, sizeof(Char), str.len, fp);
    return bytes_written;
}

String STR_read(FILE* fp) {
    String s;
    fread(&s.len, sizeof(Int), 1, fp);
    fread(s.str, sizeof(Char), s.len, fp);
    return s;
}

String STR_read_line(FILE* fp) {
    String s;
    Char   c;
    s = STR_empty_string();
    if(fp == NULL) return s;
    if(feof(fp)) return s;
    while(!feof(fp)) {
        c = (Char)fgetc(fp);
        if(c == '\n') break;
        if(s.len == STR_MAX_STRING_LENGTH) {
            printf("(STR_read_line) Warning: line is too long\n");
            break;
        }
        s.str[s.len] = c;
        s.len++;
    }
    return s;
}

struct _simple_link_list {
    String                    str;
    struct _simple_link_list* next;
};

void STR_read_lines(String** string_list, FILE* fp) {
    struct _simple_link_list * buffer_head = NULL, *node;
    struct _simple_link_list** head_addr;
    String                     s;
    Int                        n_lines = 0, i;
    if(*string_list != NULL) return;
    if(fp == NULL) return;
    head_addr = &buffer_head;
    while(!feof(fp)) {
        s = STR_read_line(fp);
        *head_addr = (struct _simple_link_list*)malloc(
            sizeof(struct _simple_link_list));
        (*head_addr)->str = s;
        head_addr = &((*head_addr)->next);
        n_lines++;
    }
    *string_list = (String*)malloc(sizeof(String) * n_lines);
    for(i = 0; i < n_lines; i++) {
        (*string_list)[i] = buffer_head->str;
        node = buffer_head;
        buffer_head = buffer_head->next;
        free(node);
    }
}

void STR_print_line(String str, FILE* fp) {
    Char buffer[STR_MAX_STRING_LENGTH + 1];
    if(fp == NULL) return;
    memcpy(buffer, str.str, str.len * sizeof(Char));
    buffer[STR_MAX_STRING_LENGTH] = '\0';
    fprintf(fp, "%s\n", buffer);
}

void STR_print_lines(const String* str, Int n, FILE* fp) {
    Int i;
    if(fp == NULL) return;
    if(str == NULL) return;
    if(n <= 0) return;
    for(i = 0; i < n; i++) STR_print_line(str[i], fp);
}

*/
