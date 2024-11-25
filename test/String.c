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

#include <stdio.h>
#include <stdlib.h>
#include "Module_Basic.h"
#include "Type_String.h"

#define TVI(n) i_tmpvar_##n
#define _NEW_VECS(type, varnm, n)\
    for(int TVI(varnm) = 0; TVI(varnm) < n; TVI(varnm)++) type##_new_(&varnm[TVI(varnm)]);

#define _VECTOR_DEFINE(varnm, n) varnm[n]
#define _VECTOR_DEFINE_1(varnm, n, ...) _VECTOR_DEFINE(varnm, n)
#define _VECTOR_DEFINE_2(varnm, n, ...) _VECTOR_DEFINE(varnm, n), _VECTOR_DEFINE_1(__VA_ARGS__)
#define _VECTOR_DEFINE_3(varnm, n, ...) _VECTOR_DEFINE(varnm, n), _VECTOR_DEFINE_2(__VA_ARGS__)

void printsection(const char* s) { printf("\n----------------------------------------\n * %s\n\n", s); }

void printstring(const char* vname, struct String s) {
    Char buf[(STRING_FIXED_BUFFER_LENGTH) + 1] = {'\0'};
    if(s.len >= STRING_FIXED_BUFFER_LENGTH) {
        memcpy(buf, s.str, STRING_FIXED_BUFFER_LENGTH * sizeof(Char));
        printf("%s: %s%s", vname, buf, s.more);
    }
    else
        printf("%s: %s", vname, s.str);
    printf("\n");
}

int main() {
    Int  nslice, i;
    char c,      buffer[100] = {'\0'};

    CBL_DECLARE_VARS(String, 1, s);

    printsection("global");
    printf("STRING_FIXED_BUFFER_LENGTH: %d\n", STRING_FIXED_BUFFER_LENGTH);
    printsection("set");
    CBL_CALL(s, set_, "tes");
    printstring("s", s);
    strncpy(buffer, s.str, STRING_FIXED_BUFFER_LENGTH);
    printf("s: {len: %d, str: \"%s\", more: \"%s\"}\n", s.len, buffer, s.more);
    CBL_CALL(s, set_, "testtesttest"); printstring("s", s);
    strncpy(buffer, s.str, STRING_FIXED_BUFFER_LENGTH);
    printf("s: {len: %d, str: \"%s\", more: \"%s\"}\n", s.len, buffer, s.more);

    printsection("free");
    CBL_FREE_VARS(String, 1, s);
    return 0;
}

/*
    for(i = 0; i < 5; i++) String_new_(&(r[i]));
    for(i = 0; i < 3; i++) {
        String_new_(&(s[i]));
        String_new_(&(t[i]));
    }

    for(c = 'a'; c <= 'e'; c++) {
        sprintf(buffer, "ab%c", c);
        printf("%s\n", buffer);
        String_set_(&(r[(Int)(c - 'a')]), buffer);
    }

    s[0].methods->join_(&s[0], r, 5, String_set(""));
    s[1] = s[0];
    printf("s0: %s\ns1: %s\n", s[0].str, s[1].str);
    printf("s0 == s1 : %d\n", s[0].methods->isequal(&s[0], s[1]));
    s[1].methods->reverse_(&s[1]);
    printf("s0: %s\ns1: %s\n", s[0].str, s[1].str);
    printf("s0 == s1 : %d\n", s[0].methods->isequal(&s[0], s[1]));
    s[2] = s[0];
    s[2].methods->substring_(&s[2], 0, 1);
    printf("s2: %s\n", s[2].str);
    printf("s0 startswith s2: %d\n", s[0].methods->starts_with(&s[0], s[2]));
    printf("s0 endswith s2: %d\n", s[0].methods->ends_with(&s[0], s[2]));
    printf("s0 contains s2: %d\n", s[0].methods->contains(&s[0], s[2]));
    printf("s0 == s2 : %d\n", s[0].methods->isequal(&s[0], s[2]));
    t[0].methods->join_(&t[0], r, 5, Sbuffer.methods->set_(&Sbuffer, "_"));
    printf("join of r[0-4]: %s\n", t[0].str);
    t[0].methods->set_(&t[0], "ab");
    printf("t[0]: %s\n", t[0].str);
    t[1].methods->set_(&t[1], "xy");
    printf("t[1]: %s\n", t[1].str);
    t[2] = s[0];
    printf("t[2]: %s\n", t[2].str);
    t[2].methods->replace_(&t[2], t[0], t[1]);
    printf("replace %s with %s in %s, get: %s\n", t[0].str, t[1].str, s[0].str,
        t[2].str);
    t[2] = s[0];
    t[2].methods->replace_all_(&t[2], t[0], t[1]);
    printf("replace all %s with %s in %s, get: %s\n", t[0].str, t[1].str,
        s[0].str, t[2].str);

    t[2].methods->append_(&t[2], t[1]);

    printf("t[1]: %s\n", t[1].str);
    printf("t[2]: %s\n", t[2].str);
    t[2].methods->split(&t[2], t[1], &sp, &nslice);
    printf("n slice: %d\n", nslice);
    for(c = 0; c < nslice; c++) printf("slice[%d]: %s\n", c, sp[c].str);
    free(sp);
*/
