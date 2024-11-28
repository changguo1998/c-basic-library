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

#include <stdlib.h>
#include <string.h>
#include "Type_String.h"

const struct StringMethods _CBL_STRING_METHODS = {
    &String_free_,
    &String_copy_,
    &String_cstr_,
    &String_read_,
    &String_readuntil_,
    &String_readline_,
    &String_readfile_,
    &String_write,
    &String_print,
    &String_println,
    &String_set_,
    &String_isequal,
    &String_append_,
    &String_join_,
    &String_nextmatch,
    &String_startswith,
    &String_endswith,
    &String_contains,
    &String_substring_,
    &String_split,
    &String_strip_,
    &String_replace_,
    &String_replaceall_,
    &String_reverse_,
    &String_repeat_
};

// # ---------------------------------------------------------------------------
// # internal functions

void String_alloc_(struct String* this, Int len) {
    if(this->len == len) return;
    if(this->more) free(this->more);
    this->more = NULL;
    if(len <= STRING_FIXED_BUFFER_LENGTH) return;
    this->len = len;
    this->more = (Char*)calloc(len - STRING_FIXED_BUFFER_LENGTH + 1,
        sizeof(Char));
}

void _append_string(Int* n1, Char* s1, Char* d1, Int n2, const Char* s2) {
    Int i;
    for(i = 0; i < n2; i++) {
        if(*n1 < STRING_FIXED_BUFFER_LENGTH) { s1[*n1] = s2[i]; }
        else { d1[*n1 - STRING_FIXED_BUFFER_LENGTH] = s2[i]; }
        *n1 += 1;
    }
}

void _get_string(const struct String* this, Int* n, Char* s) {
    Int i;
    if(this->len <= 0) return;
    if(this->len <= STRING_FIXED_BUFFER_LENGTH) {
        for(i = 0; i < this->len; i++) {
            s[*n] = this->str[i];
            *n += 1;
        }
    }
    else {
        for(i = 0; i < STRING_FIXED_BUFFER_LENGTH; i++) {
            s[*n] = this->str[i];
            *n += 1;
        }
        for(i = 0; i < this->len - STRING_FIXED_BUFFER_LENGTH; i++) {
            s[*n] = this->more[i];
            *n += 1;
        }
    }
}

Char* _cache_string(const struct String* this) {
    Char* buf = NULL;
    Int   i;
    if(this->len <= STRING_FIXED_BUFFER_LENGTH) { buf = (Char*)this->str; }
    else {
        buf = (Char*)calloc(this->len + 1, sizeof(Char));
        i = 0;
        _get_string(this, &i, buf);
    }
    return buf;
}

void _free_cached_string(const struct String* this, Char** buf) {
    if(*buf != this->str)
        free(*buf);
    *buf = NULL;
}

void _read_until_or_n(Char* str, Int* i, Int max, FILE* fp, Char flag, Int *flag_triggered) {
    Char c;
    *flag_triggered = 0;
    while(!feof(fp)) {
        if(*i >= max) break;
        c = (Char)fgetc(fp);
        if(c == flag) {
            (*flag_triggered) = 1;
            break;
        }
        str[*i] = c;
        (*i) += 1;
    }
}

// # ---------------------------------------------------------------------------
// # external functions

// struct String String_set(const char* str) {
//     struct String string;
//     String_new_(&string);
//     String_set_(&string, str);
//     return string;
// }

void String_free_(struct String* this) {
    if(this->more) free(this->more);
    this->more = NULL;
    this->str[0] = '\0';
    this->len = 0;
}

void String_copy_(struct String* this, struct String other) {
    // self reference
    if(other.more)
        if(this->more == other.more)
            return;
    if(other.len <= 0) {
        String_free_(this);
        return;
    }
    if(other.more) String_alloc_(this, other.len);
    memcpy(this->str, other.str, STRING_FIXED_BUFFER_LENGTH * sizeof(Char));
    if(other.more) memcpy(this->more, other.more, (other.len - STRING_FIXED_BUFFER_LENGTH) * sizeof(Char));
    this->len = other.len;
}

void String_cstr_(const struct String* this, Char** cstr) {
    Int i;
    if(*cstr) free(*cstr);
    if(this->len <= 0) {
        *cstr = (Char*)calloc(1, sizeof(Char));
        return;
    }
    *cstr = (Char*)calloc(this->len + 1, sizeof(Char));
    i = 0;
    _get_string(this, &i, *cstr);
}

void String_read_(struct String* this, FILE* fp) {
    Char* buf = NULL;
    Int   n;
    String_free_(this);
    fread(&n, sizeof(Int), 1, fp);
    if(n <= 0) return;
    buf = (Char*)calloc(n + 1, sizeof(Char));
    fread(buf, sizeof(Char), n, fp);
    String_set_(this, buf);
    free(buf);
}

void String_readuntil_(struct String* this, FILE* fp, Char c) {
    CBL_DECLARE_VARS(String, 1, buf);
    Int flag;
    flag = 0;
    String_free_(this);
    while(!flag) {
        if(feof(fp)) break;
        memset(buf.str, '\0', STRING_FIXED_BUFFER_LENGTH * sizeof(Char));
        buf.len = 0;
        _read_until_or_n(buf.str, &buf.len, STRING_FIXED_BUFFER_LENGTH, fp, c, &flag);
        String_append_(this, buf);
    }
}

void String_readline_(struct String* this, FILE* fp) { String_readuntil_(this, fp, '\n'); }

void String_readfile_(struct String* this, FILE* fp) {
    long fsize;
    Char *buf;
    fseek(fp, 0, SEEK_END);
    fsize = ftell(fp);
    if(fsize <= 0) {
        String_free_(this);
        return;
    }
    fseek(fp, 0, SEEK_SET);
    buf = (Char*)malloc(fsize + sizeof(Char));
    fread(buf, 1, fsize, fp);
    String_set_(this, buf);
    free(buf);
}

void String_write(struct String* this, FILE* fp) {
    Char* buf = NULL;
    fwrite(&this->len, sizeof(Int), 1, fp);
    if(this->len <= 0) return;
    buf = _cache_string(this);
    fwrite(buf, sizeof(Char), this->len, fp);
    _free_cached_string(this, &buf);
}

void String_print(struct String* this, FILE* fp) {
    Char* buf = NULL;
    buf = _cache_string(this);
    fwrite(buf, sizeof(Char), this->len, fp);
    _free_cached_string(this, &buf);
}

void String_println(struct String* this, FILE* fp) {
    String_print(this, fp);
    fputc('\n', fp);
}

void String_set_(struct String* this, const char* str) {
    Int n;
    // String_free_(this);
    n = (Int)strlen(str);
    if(n <= 0) {
        String_free_(this);
        return;
    }
    String_alloc_(this, n);
    if(n > STRING_FIXED_BUFFER_LENGTH) {
        memcpy(this->str, str, STRING_FIXED_BUFFER_LENGTH * sizeof(Char));
        memcpy(this->more, &str[STRING_FIXED_BUFFER_LENGTH],
            (n - STRING_FIXED_BUFFER_LENGTH) * sizeof(Char));
        this->more[n - STRING_FIXED_BUFFER_LENGTH] = '\0';
    }
    else {
        memset(this->str, '\0', STRING_FIXED_BUFFER_LENGTH * sizeof(Char));
        memcpy(this->str, str, n * sizeof(Char));
    }
    this->len = n;
}

Bool String_isequal(const struct String* this, struct String another) {
    Int i;
    // self reference
    if(this->more && another.more)
        if(this->more == another.more)
            return true;
    // length
    if(this->len != another.len) return false;
    // Char by Char
    if(this->len <= STRING_FIXED_BUFFER_LENGTH) {
        for(i = 0; i < this->len; i++)
            if(this->str[i] != another.str[i]) return false;
    }
    else {
        for(i = 0; i < STRING_FIXED_BUFFER_LENGTH; i++)
            if(this->str[i] != another.str[i]) return false;
        for(i = 0; i < this->len - STRING_FIXED_BUFFER_LENGTH; i++)
            if(this->more[i] != another.more[i]) return false;
    }
    return true;
}

void String_append_(struct String* this, struct String another) {
    Char* buf = NULL;
    Int   i, l;
    if(another.len <= 0) return;

    l = this->len + another.len;
    buf = (Char*)calloc(l+1, sizeof(Char));
    i = 0;
    _get_string(this, &i, buf);
    _get_string(&another, &i, buf);
    if(i != l) error_index_out_of_bounds("(String_append_) i != l");
    String_set_(this, buf);
    this->len = l;
    free(buf);
}

void String_join_(struct String*       this,
                  const struct String* list,
                  Int                  n,
                  struct String        delimiter) {
    Int   i_list, ml, nl, l, lc;

    String_free_(this);
    if(n <= 0) return;

    l = 0;
    for(i_list = 0; i_list < n; i_list++) {
        l += delimiter.len;
        l += list[i_list].len;
    }
    l -= delimiter.len;
    String_alloc_(this, l);
    lc = 0;
    // list[i]
    ml = (list[0].len <= STRING_FIXED_BUFFER_LENGTH) ? list[0].len : STRING_FIXED_BUFFER_LENGTH;
    nl = list[0].len - STRING_FIXED_BUFFER_LENGTH;
    _append_string(&lc, this->str, this->more, ml, list[0].str);
    if(nl > 0) _append_string(&lc, this->str, this->more, nl, list[0].more);
    // append
    for(i_list = 1; i_list < n; i_list++) {
        // delimiter
        ml = (delimiter.len <= STRING_FIXED_BUFFER_LENGTH) ? delimiter.len : STRING_FIXED_BUFFER_LENGTH;
        nl = delimiter.len - STRING_FIXED_BUFFER_LENGTH;
        _append_string(&lc, this->str, this->more, ml, delimiter.str);
        if(nl > 0) _append_string(&lc, this->str, this->more, nl, delimiter.more);
        // list[i]
        ml = (list[i_list].len <= STRING_FIXED_BUFFER_LENGTH) ? list[i_list].len : STRING_FIXED_BUFFER_LENGTH;
        nl = list[i_list].len - STRING_FIXED_BUFFER_LENGTH;
        _append_string(&lc, this->str, this->more, ml, list[i_list].str);
        if(nl > 0) _append_string(&lc, this->str, this->more, nl, list[i_list].more);
    }
    this->len = l;
}

Int String_nextmatch(const struct String* this,
                     struct String        pattern,
                     Int                  start) {
    Int   i,         j;
    Char *s = NULL, *t = NULL;
    if(this->len <= 0) return -1;
    if(pattern.len <= 0) return -1;
    s = _cache_string(this);
    t = _cache_string(&pattern);

    j = 0;
    for(i = start; i < this->len; i++) {
        if(s[i] == t[j]) j += 1;
        else {
            i -= j;
            j = 0;
        }
        if(j == pattern.len) {
            _free_cached_string(this, &s);
            _free_cached_string(&pattern, &t);
            return i - pattern.len + 1;
        }
    }
    _free_cached_string(this, &s);
    _free_cached_string(&pattern, &t);
    return -1;
}

Bool String_startswith(const struct String* this, struct String pattern) {
    Int   i;
    Char *s = NULL, *t = NULL;
    if(this->len < pattern.len) return false;
    s = _cache_string(this);
    t = _cache_string(&pattern);
    for(i = 0; i < pattern.len; i++)
        if(s[i] != t[i]) {
            _free_cached_string(this, &s);
            _free_cached_string(&pattern, &t);
            return false;
        }

    _free_cached_string(this, &s);
    _free_cached_string(&pattern, &t);
    return true;
}

Bool String_endswith(const struct String* this, struct String pattern) {
    Int   i;
    Char *s = NULL, *t = NULL;
    if(this->len < pattern.len) return false;
    s = _cache_string(this);
    t = _cache_string(&pattern);
    for(i = 0; i < pattern.len; i++)
        if(s[this->len - 1 - i] != t[pattern.len - 1 - i]) {
            _free_cached_string(this, &s);
            _free_cached_string(&pattern, &t);
            return false;
        }
    _free_cached_string(this, &s);
    _free_cached_string(&pattern, &t);
    return true;
}

Bool String_contains(const struct String* this, struct String pattern) {
    return String_nextmatch(this, pattern, 0) >= 0;
}

void String_substring_(struct String* this, Int start, Int stop) {
    Int   i, n_sub, start0, stop0;
    Char* buf = NULL;
    if((start < 0 && stop < 0) || (start >= this->len && stop >= this->len))
        error_index_out_of_bounds("(String_substring_) index out of bounds\n");
    start0 = start < stop ? start : stop;
    stop0 = start > stop ? start : stop;
    n_sub = stop0 - start0 + 1;
    if(n_sub <= 0) {
        String_free_(this);
        return;
    }
    buf = _cache_string(this);
    for(i = 0; i < n_sub; i++) buf[i] = buf[i + start0];
    buf[n_sub] = '\0';
    if(this->len > STRING_FIXED_BUFFER_LENGTH)
        String_set_(this, buf);
    _free_cached_string(this, &buf);
    this->len = n_sub;
    if(start > stop) String_reverse_(this);
}

void String_split(const struct String* this,
                  struct String        delimiter,
                  struct String**      list,
                  Int*                 n) {
    Int * slice_start = NULL, *slice_stop = NULL, next_slice, i_slice, i, j;
    Char* buf = NULL;

    if(*list != NULL)
        error_unexpected_allocated_memory(
            "(String_split) buffer already allocated");
    *n = 1;
    i = 0;
    while(i < this->len) {
        next_slice = String_nextmatch(this, delimiter, i);
        if(next_slice < 0) break;
        *n += 1;
        i = next_slice + delimiter.len;
    }
    // printf("(String_split) nslice: %d\n", *n);
    slice_start = (Int*)malloc(sizeof(Int) * (*n));
    slice_stop = (Int*)malloc(sizeof(Int) * (*n));
    slice_start[0] = 0;
    slice_stop[(*n) - 1] = this->len - 1;
    next_slice = 0;
    for(i = 1; i < *n; i++) {
        j = String_nextmatch(this, delimiter, next_slice);
        slice_start[i] = j + delimiter.len;
        slice_stop[i - 1] = j - 1;
        next_slice = slice_start[i];
    }
    // printf("(String_split) slice_index: ");
    // for(i = 0; i < *n; i++) printf("(%d, %d), ", slice_start[i], slice_stop[i]);
    // printf("\n(String_split) allocate list");
    *list = (struct String*)malloc(sizeof(struct String) * (*n));
    for(i_slice = 0; i_slice < *n; i_slice++) String_new_(&((*list)[i_slice]));

    // printf("\n(String_split) allocate list done");
    buf = _cache_string(this);
    // printf("\n(String_split) src string: \"%s\"\n", buf);
    for(i_slice = 0; i_slice < *n; i_slice++) {
        // printf("(String_split) process slice %d\n", i_slice);
        i = slice_start[i_slice];
        j = slice_stop[i_slice];
        // printf("(String_split) i: %d, j: %d\n ", i, j);
        (*list)[i_slice].len = 0;
        String_alloc_(&((*list)[i_slice]), j - i + 1);
        _append_string(&((*list)[i_slice].len), (*list)[i_slice].str, (*list)[i_slice].more, j - i + 1, &(buf[i]));
    }
    _free_cached_string(this, &buf);
    free(slice_start);
    free(slice_stop);
}

void String_strip_(struct String* this) {
    Int   i, j;
    Char* buf = NULL;
    buf = _cache_string(this);
    for(i = 0; i < this->len; i++) if(buf[i] != ' ') break;
    for(j = this->len - 1; j >= 0; j--) if(buf[j] != ' ') break;
    _free_cached_string(this, &buf);
    if(i > j) return;
    String_substring_(this, i, j);
}

void String_replace_(struct String* this,
                     struct String  pattern,
                     struct String  replacement) {
    Int p;
    CBL_DECLARE_VARS(String, 2, del, pos);

    p = String_nextmatch(this, pattern, 0);
    if(p < 0) return;
    String_copy_(&pos, *this);
    String_substring_(&pos, p + pattern.len, this->len - 1);
    String_substring_(this, 0, p - 1);
    String_append_(this, replacement);
    String_append_(this, pos);
    CBL_FREE_VARS(String, 2, del, pos);
}

void String_replaceall_(struct String* this,
                        struct String  pattern,
                        struct String  replacement) {
    struct String* buffer = NULL;
    Int            n_slice, i;

    String_split(this, pattern, &buffer, &n_slice);
    String_free_(this);
    String_join_(this, buffer, n_slice, replacement);
    for(i = 0; i < n_slice; i++) String_free_(&(buffer[i]));
    free(buffer);
}

void String_reverse_(struct String* this) {
    Int  i,  h;
    Char c, *buf = NULL;
    buf = _cache_string(this);
    h = this->len / 2;
    for(i = 0; i < h; i++) {
        c = buf[i];
        buf[i] = buf[this->len - 1 - i];
        buf[this->len - 1 - i] = c;
    }
    if(this->len > STRING_FIXED_BUFFER_LENGTH) String_set_(this, buf);
    _free_cached_string(this, &buf);
}

void String_repeat_(struct String* this, Int n) {
    struct String buf;
    Int i;

    String_new_(&buf);
    if(n < 0) error_invalid_argument("(String_repeat_) n < 0");
    if(n == 0) {
        String_free_(this);
        return;
    }
    String_copy_(&buf, *this);
    String_free_(this);
    for(i = 0; i < n; i++) String_append_(this, buf);
    String_free_(&buf);
}

// ! ==========================================================================
/*

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

void STR_print_lines(const String* str, Int n, FILE* fp) {
    Int i;
    if(fp == NULL) return;
    if(str == NULL) return;
    if(n <= 0) return;
    for(i = 0; i < n; i++) STR_print_line(str[i], fp);
}

*/
