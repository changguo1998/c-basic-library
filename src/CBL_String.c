#include <stdlib.h>
#include <string.h>
#include "CBL_String.h"

String STR_empty_string() {
    String s;
    s.len = 0;
    memset(s.str, '\0', sizeof(Char) * STR_MAX_STRING_LENGTH);
    return s;
}

String STR_String(const char* str) {
    String s;
    Int    i;
    s = STR_empty_string();
    if(strlen(str) > STR_MAX_STRING_LENGTH) {
        printf("(STR_String) Warning: string is too long\n");
        s.len = STR_MAX_STRING_LENGTH;
        for(i = 0; i < s.len; i++) {
            if(str[i] == '\0') break;
            s.str[i] = str[i];
        }
    }
    else {
        s.len = (Int)strlen(str);
        strcpy(s.str, str);
    }
    return s;
}

Bool STR_isequal(const String str1, const String str2) {
    Int i;
    if(str1.len != str2.len) return false;
    for(i = 0; i < str1.len; i += 1) if(str1.str[i] != str2.str[i]) return false;
    return true;
}

String STR_join(const String* string_list, Int n, String separator) {
    String s;
    Int    total_len = 0, istr, i;
    for(istr = 0; istr < n; istr++) total_len += string_list[istr].len;
    total_len += separator.len * (n - 1);
    if(total_len > STR_MAX_STRING_LENGTH) printf("(STR_join) joined String length exceeded MAX_STRING_LENGTH\n");
    s = STR_empty_string();
    if(total_len == 0) return s;
    for(istr = 0; istr < n; istr++) {
        if(istr > 0) {
            for(i = 0; i < separator.len; i++) {
                if(s.len == STR_MAX_STRING_LENGTH) {
                    printf("(STR_join) Warning: string is too long after replace\n");
                    return s;
                }
                s.str[s.len] = separator.str[i];
                s.len++;
            }
        }
        for(i = 0; i < string_list[istr].len; i++) {
            if(s.len == STR_MAX_STRING_LENGTH) {
                printf("(STR_join) Warning: string is too long after replace\n");
                return s;
            }
            s.str[s.len] = string_list[istr].str[i];
            s.len++;
        }
    }
    return s;
}

String STR_slice(const String str, Int idx1, Int idx2) {
    String s;
    Int    i, from, to, step;
    s = STR_empty_string();
    if(str.len == 0) return s;
    if(idx1 >= str.len) {
        printf("(STR_slice) index1 exceeded String length\n");
        from = str.len - 1;
    }
    else from = idx1;
    if(idx2 >= str.len) {
        printf("(STR_slice) index2 exceeded String length\n");
        to = str.len - 1;
    }
    else to = idx2;
    if(from > to) {
        step  = -1;
        s.len = from - to + 1;
    }
    else {
        step  = 1;
        s.len = to - from + 1;
    }
    for(i = 0; i < s.len; i++) s.str[i] = str.str[from + step * i];
    return s;
}

String STR_strip(String str) {
    String s;
    Int    i, start, stop;
    s = STR_empty_string();
    if(str.len == 0) return s;
    for(start = 0; start < str.len; start++) if(str.str[start] != ' ') break;
    for(stop = str.len - 1; stop > start; stop--) if(str.str[stop] != ' ') break;
    s.len = stop - start + 1;
    if(s.len <= 0) return s;
    for(i = 0; i < s.len; i++) s.str[i] = str.str[start + i];
    return s;
}

Int STR_next_match(const String str, const String pattern, Int start) {
    Int i, j;
    if(str.len == 0) return -1;
    if(pattern.len == 0) return -1;
    j = 0;
    for(i = start; i < str.len; i++) {
        if(str.str[i] == pattern.str[j]) j++;
        else {
            i -= j;
            j = 0;
        }
        if(j == pattern.len) return i - pattern.len + 1;
    }
    return -1;
}

String STR_replace(String str, String pattern, String value) {
    String s;
    Int    i, j;
    s = STR_empty_string();
    if(str.len == 0) return s;
    if(pattern.len == 0) return str;
    i = STR_next_match(str, pattern, 0);
    if(i < 0) return str;
    for(j = 0; j < i; j++) {
        if(s.len == STR_MAX_STRING_LENGTH) {
            printf("(STR_replace) Warning: string is too long after replace\n");
            return s;
        }
        s.str[s.len] = str.str[j];
        s.len++;
    }
    for(j = 0; j < value.len; j++) {
        if(s.len == STR_MAX_STRING_LENGTH) {
            printf("(STR_replace) Warning: string is too long after replace\n");
            return s;
        }
        s.str[s.len] = value.str[j];
        s.len++;
    }
    for(j = i + pattern.len; j < str.len; j++) {
        if(s.len == STR_MAX_STRING_LENGTH) {
            printf("(STR_replace) Warning: string is too long after replace\n");
            return s;
        }
        s.str[s.len] = str.str[j];
        s.len++;
    }
    return s;
}

String STR_replace_all(const String str, const String pattern, const String value) {
    String s;
    Bool   exit_after_copy;
    Int    i, next_start, search_start;
    s = STR_empty_string();
    if(str.len == 0) return s;
    if(pattern.len == 0) return str;
    search_start = 0;
    while(true) {
        next_start = STR_next_match(str, pattern, search_start);
        if(next_start < 0) {
            exit_after_copy = true;
            next_start      = str.len;
        }
        else exit_after_copy = false;
        for(i = search_start; i < next_start; i++) {
            if(s.len == STR_MAX_STRING_LENGTH) {
                printf("(STR_replace) Warning: string is too long after replace\n");
                return s;
            }
            s.str[s.len] = str.str[i];
            s.len++;
        }
        if(exit_after_copy) break;
        for(i = 0; i < value.len; i++) {
            if(s.len == STR_MAX_STRING_LENGTH) {
                printf("(STR_replace) Warning: string is too long after replace\n");
                return s;
            }
            s.str[s.len] = value.str[i];
            s.len++;
        }
        search_start = next_start + pattern.len;
    }
    return s;
}

Int STR_split(String** out, const String str, const String delim) {
    Int n_slice          = 0, *slice_index = NULL, next_slice, i_slice, i;
    slice_index          = (Int*)malloc(sizeof(Int) * str.len);
    slice_index[n_slice] = 0;
    n_slice++;
    while(true) {
        next_slice = STR_next_match(str, delim, slice_index[n_slice - 1]);
        if(next_slice < 0) break;
        slice_index[n_slice] = next_slice + delim.len;
        n_slice++;
    }
    *out = (String*)malloc(sizeof(String) * n_slice);
    for(i_slice = 0; i_slice < n_slice; i_slice++) {
        (*out)[i_slice] = STR_empty_string();
        if(i_slice < n_slice - 1) (*out)[i_slice].len = slice_index[i_slice + 1] - slice_index[i_slice] - delim.len;
        else (*out)[i_slice].len                      = str.len - slice_index[i_slice];
        for(i = 0; i < (*out)[i_slice].len; i++) (*out)[i_slice].str[i] = str.str[slice_index[i_slice] + i];
    }
    free(slice_index);
    return n_slice;
}

size_t STR_write(String str, FILE* fp) {
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
        s                 = STR_read_line(fp);
        *head_addr        = (struct _simple_link_list*)malloc(sizeof(struct _simple_link_list));
        (*head_addr)->str = s;
        head_addr         = &((*head_addr)->next);
        n_lines++;
    }
    *string_list = (String*)malloc(sizeof(String) * n_lines);
    for(i = 0; i < n_lines; i++) {
        (*string_list)[i] = buffer_head->str;
        node              = buffer_head;
        buffer_head       = buffer_head->next;
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

Bool STR_starts_with(String str, String pattern) {
    Int i;
    if(str.len < pattern.len) return false;
    for(i = 0; i < pattern.len; i++) if(str.str[i] != pattern.str[i]) return false;
    return true;
}

Bool STR_ends_with(String str, String pattern) {
    Int i;
    if(str.len < pattern.len) return false;
    for(i = 0; i < pattern.len; i++) if(str.str[str.len - 1 - i] != pattern.str[pattern.len - 1 - i]) return false;
    return true;
}

Bool STR_contains(String str, String pattern) { return STR_next_match(str, pattern, 0) >= 0; }

String STR_reverse(String str) {
    String s;
    Int    i;
    s     = STR_empty_string();
    s.len = str.len;
    for(i = 0; i < s.len; i++) s.str[i] = str.str[str.len - i - 1];
    return s;
}
