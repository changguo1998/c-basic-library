#include "CBL_String.h"

String STR_empty_string() {
    String s;
    Int i;
    s.len = 0;
    memset(s.str, '\0', sizeof(Char) * STR_MAX_STRING_LENGTH);
    return s;
}

String STR_String(const char* str) {
    String s;
    Int i;
    s = STR_empty_string();
    if(strlen(str) > STR_MAX_STRING_LENGTH) {
        printf("(STR_String) Possible error: string is too long\n");
        s.len = STR_MAX_STRING_LENGTH;
        for(i = 0; i < s.len; i++) {
            if(str[i] == '\0') break;
            s.str[i] = str[i];
        }
    }
    else {
        s.len = strlen(str);
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

String STR_join(String* strs, Int n, String separator) {
    String s;
    Int total_len = 0, istr, i;
    for(istr = 0; istr < n; istr++) total_len += strs[istr].len;
    total_len += separator.len * (n - 1);
    if(total_len > STR_MAX_STRING_LENGTH) printf("(STR_join) joined String length exceeded MAX_STRING_LENGTH\n");
    s = STR_empty_string();
    if(total_len == 0) return s;
    for(istr = 0; istr < n; istr++) {
        if(istr > 0) {
            for(i = 0; i < separator.len; i++) {
                if(s.len == STR_MAX_STRING_LENGTH) {
                    printf("(STR_join) Possible error: string is too long after replace\n");
                    return s;
                }
                s.str[s.len] = separator.str[i];
                s.len++;
            }
        }
        for(i = 0; i < strs[istr].len; i++) {
            if(s.len == STR_MAX_STRING_LENGTH) {
                printf("(STR_join) Possible error: string is too long after replace\n");
                return s;
            }
            s.str[s.len] = strs[istr].str[i];
            s.len++;
        }
    }
    return s;
}

String STR_slice(const String str, Int idx1, Int idx2) {
    String s;
    Int i, from, to, step;
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
        step = -1;
        s.len = from - to + 1;
    }
    else {
        step = 1;
        s.len = to - from + 1;
    }
    for(i = 0; i < s.len; i++) s.str[i] = str.str[from + step * i];
    return s;
}

String STR_strip(String str) {
    String s;
    Int i, start, stop;
    s = STR_empty_string();
    if(str.len == 0) return s;
    for(start = 0; start < str.len; start++) if(str.str[start] != ' ') break;
    for(stop = str.len - 1; stop > start; stop--) if(str.str[stop] != ' ') break;
    s.len = stop - start + 1;
    if(s.len <= 0) return s;
    for(i = 0; i < s.len; i++) s.str[i] = str.str[start + i];
    return s;
}

Int STR_next_match(const String str, const String pat, Int start) {
    Int i, j;
    if(str.len == 0) return -1;
    if(pat.len == 0) return -1;
    j = 0;
    for(i = start; i < str.len; i++) {
        if(str.str[i] == pat.str[j]) j++;
        else {
            i -= j;
            j = 0;
        }
        if(j == pat.len) return i - pat.len + 1;
    }
    return -1;
}

String STR_replace(String str, String pattern, String value) {
    String s;
    Int i, j;
    s = STR_empty_string();
    if(str.len == 0) return s;
    if(pattern.len == 0) return str;
    i = STR_next_match(str, pattern, 0);
    if(i < 0) return str;
    for(j = 0; j < i; j++) {
        if(s.len == STR_MAX_STRING_LENGTH) {
            printf("(STR_replace) Possible error: string is too long after replace\n");
            return s;
        }
        s.str[s.len] = str.str[j];
        s.len++;
    }
    for(j = 0; j < value.len; j++) {
        if(s.len == STR_MAX_STRING_LENGTH) {
            printf("(STR_replace) Possible error: string is too long after replace\n");
            return s;
        }
        s.str[s.len] = value.str[j];
        s.len++;
    }
    for(j = i + pattern.len; j < str.len; j++) {
        if(s.len == STR_MAX_STRING_LENGTH) {
            printf("(STR_replace) Possible error: string is too long after replace\n");
            return s;
        }
        s.str[s.len] = str.str[j];
        s.len++;
    }
    return s;
}

String STR_replace_all(const String str, const String pattern, const String value) {
    String s;
    Bool exit_after_copy;
    Int i, next_start, search_start;
    s = STR_empty_string();
    if(str.len == 0) return s;
    if(pattern.len == 0) return str;
    search_start = 0;
    while(true) {
        next_start = STR_next_match(str, pattern, search_start);
        if(next_start < 0) {
            exit_after_copy = true;
            next_start = str.len;
        }
        else exit_after_copy = false;
        for(i = search_start; i < next_start; i++) {
            if(s.len == STR_MAX_STRING_LENGTH) {
                printf("(STR_replace) Possible error: string is too long after replace\n");
                return s;
            }
            s.str[s.len] = str.str[i];
            s.len++;
        }
        if(exit_after_copy) break;
        for(i = 0; i < value.len; i++) {
            if(s.len == STR_MAX_STRING_LENGTH) {
                printf("(STR_replace) Possible error: string is too long after replace\n");
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
    Int n_slice = 0, *slice_index = NULL, next_slice = -1, i_slice, i;
    slice_index = (Int*)malloc(sizeof(Int) * str.len);
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
        else (*out)[i_slice].len = str.len - slice_index[i_slice];
        for(i = 0; i < (*out)[i_slice].len; i++) (*out)[i_slice].str[i] = str.str[slice_index[i_slice] + i];
    }
    free(slice_index);
    return n_slice;
}


Int STR_write(String str, FILE* fp);

String STR_read(FILE* fp);
