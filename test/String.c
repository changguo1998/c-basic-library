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
    printf("%s: ", vname);
    if(s.len < STRING_FIXED_BUFFER_LENGTH) {
        printf("\"%s\"\n", s.str);
        return;
    }
    memcpy(buf, s.str, STRING_FIXED_BUFFER_LENGTH * sizeof(Char));
    printf("\"%s", buf);
    if(s.more) printf("^%s\"", s.more);
    printf("\n");
}

int main() {
    FILE *fp;
    Int  i, nslice;
    char c,      buffer[10000] = {'\0'}, *vbuf = NULL;

    CBL_DECLARE_VARS(String, 3, s, t, u);
    struct String v[3], *strslices = NULL;
    for(i = 0; i < 3; i++) String_new_(&v[i]);

    // ! -----------------------------------------------------------------------
    printsection("global");
    printf("STRING_FIXED_BUFFER_LENGTH: %d\n", STRING_FIXED_BUFFER_LENGTH);

    // ! -----------------------------------------------------------------------
    printsection("set");
    CBL_CALL(s, set_, "tes");
    printstring("s", s);
    strncpy(buffer, s.str, STRING_FIXED_BUFFER_LENGTH);
    printf("s: {len: %d, str: \"%s\", more: \"%s\"}\n", s.len, buffer, s.more);
    CBL_CALL(s, set_, "testtesttest");
    printstring("s", s);
    strncpy(buffer, s.str, STRING_FIXED_BUFFER_LENGTH);
    printf("s: {len: %d, str: \"%s\", more: \"%s\"}\n", s.len, buffer, s.more);

    // ! -----------------------------------------------------------------------
    printsection("cstr");
    CBL_CALL(s, set_, "test1234"); printstring("s", s);
    CBL_CALL(s, cstr_, &vbuf); printf("vbuf: \"%s\"\n", vbuf);
    free(vbuf); vbuf = NULL;

    // ! -----------------------------------------------------------------------
    printsection("isequal");
    CBL_CALL(s, set_, "testtesttest");
    printstring("s", s);
    CBL_CALL(t, set_, "testtesttest");
    printstring("t", t);
    printf("isequal(s, t): %d\n", CBL_CALL(s, isequal, t));
    CBL_CALL(s, set_, "testtesttest");
    printstring("s", s);
    CBL_CALL(t, set_, "testtesttesb");
    printstring("t", t);
    printf("isequal(s, t): %d\n", CBL_CALL(s, isequal, t));

    // ! -----------------------------------------------------------------------
    printsection("append");
    CBL_CALL(s, set_, "123456789");
    printstring("s", s);
    CBL_CALL(t, set_, "abcd");
    printstring("t", t);
    CBL_CALL(s, append_, t);
    printstring("s", s);

    // ! -----------------------------------------------------------------------
    printsection("join");
    CBL_CALL(s, set_, "v[-1]");
    printstring("s", s);
    CBL_CALL(t, set_, ", ");
    printstring("t", t);
    for(i = 0; i < 3; i++) {
        sprintf(buffer, "%d%04d", i + 1, i + 1);
        CBL_CALL(v[i], set_, buffer);
        sprintf(buffer, "v[%d]", i);
        printstring(buffer, v[i]);
    }
    CBL_CALL(s, join_, v, 3, t);
    printstring("s", s);

    // ! -----------------------------------------------------------------------
    printsection("nextmatch");
    CBL_CALL(s, set_, "abcdefghijkl");
    printstring("s", s);
    CBL_CALL(t, set_, "def");
    printstring("t", t);
    printf("nextmatch(s, t, 0): %d\n", CBL_CALL(s, nextmatch, t, 0));
    printf("nextmatch(s, t, 4): %d\n", CBL_CALL(s, nextmatch, t, 4));

    // ! -----------------------------------------------------------------------
    printsection("startswith");
    CBL_CALL(s, set_, "abcdefghijkl");
    printstring("s", s);
    CBL_CALL(t, set_, "abc");
    printstring("t", t);
    printf("startswith(s, t, 0): %d\n", CBL_CALL(s, startswith, t));
    CBL_CALL(t, set_, "bcd");
    printstring("t", t);
    printf("startswith(s, t, 4): %d\n", CBL_CALL(s, startswith, t));

    // ! -----------------------------------------------------------------------
    printsection("endswith");
    CBL_CALL(s, set_, "abcdefghijkl");
    printstring("s", s);
    CBL_CALL(t, set_, "jkl");
    printstring("t", t);
    printf("endswith(s, t, 0): %d\n", CBL_CALL(s, endswith, t));
    CBL_CALL(t, set_, "bcd");
    printstring("t", t);
    printf("endswith(s, t, 4): %d\n", CBL_CALL(s, endswith, t));

    // ! -----------------------------------------------------------------------
    printsection("contains");
    CBL_CALL(s, set_, "abcdefghijkl");
    printstring("s", s);
    CBL_CALL(t, set_, "def");
    printstring("t", t);
    printf("contains(s, t, 0): %d\n", CBL_CALL(s, contains, t));
    CBL_CALL(t, set_, "dcb");
    printstring("t", t);
    printf("contains(s, t, 4): %d\n", CBL_CALL(s, contains, t));

    // ! -----------------------------------------------------------------------
    printsection("substring");
    CBL_CALL(s, set_, "abcdefghijkl");
    printstring("s", s);
    CBL_CALL(s, substring_, 3, 5);
    printstring("s", s);
    CBL_CALL(s, set_, "abcdefghijkl");
    printstring("s", s);
    CBL_CALL(s, substring_, 5, 3);
    printstring("s", s);

    // ! -----------------------------------------------------------------------
    printsection("strip");
    CBL_CALL(s, set_, "  abcdefghijkl  ");
    printstring("s", s);
    CBL_CALL(s, strip_);
    printstring("s", s);

    // ! -----------------------------------------------------------------------
    printsection("split");
    CBL_CALL(s, set_, ",1,23,456,7890,");
    printstring("s", s);
    CBL_CALL(t, set_, ",");
    printstring("t", t);
    CBL_CALL(s, split, t, &strslices, &nslice);
    printf("nslice: %d\n", nslice);
    for(i = 0; i < nslice; i++) {
        sprintf(buffer, "strslice[%d]", i);
        printstring(buffer, strslices[i]);
    }

    // ! -----------------------------------------------------------------------
    printsection("replace");
    CBL_CALL(s, set_, "abcdefghijkl"); printstring("s", s);
    CBL_CALL(t, set_, "ghij"); printstring("t", t);
    CBL_CALL(u, set_, "1234"); printstring("u", u);
    CBL_CALL(s, replace_, t, u); printstring("s", s);

    // ! -----------------------------------------------------------------------
    printsection("replaceall");
    CBL_CALL(s, set_, "abcabdabeabf"); printstring("s", s);
    CBL_CALL(t, set_, "ab"); printstring("t", t);
    CBL_CALL(u, set_, "1234"); printstring("u", u);
    CBL_CALL(s, replaceall_, t, u); printstring("s", s);

    // ! -----------------------------------------------------------------------
    printsection("reverse");
    CBL_CALL(s, set_, "0123456789");
    printstring("s", s);
    CBL_CALL(s, reverse_);
    printstring("s", s);

    // ! -----------------------------------------------------------------------
    printsection("print");
    CBL_CALL(s, set_, "AAAAAAAAAAA_"); printstring("s", s);
    fp = fopen("test_string.txt", "w");
    CBL_CALL(s, print, fp);

    // ! -----------------------------------------------------------------------
    printsection("println");
    CBL_CALL(s, println, fp);
    CBL_CALL(s, print, fp);
    fclose(fp);

    // ! -----------------------------------------------------------------------
    printsection("readuntil/readline");
    fp = fopen("test_string.txt", "r");
    CBL_CALL(t, readline_, fp); printstring("t", t);
    fclose(fp);

    // ! -----------------------------------------------------------------------
    printsection("readfile");
    fp = fopen("test_string.txt", "r");
    CBL_CALL(t, readfile_, fp); printstring("t", t);
    fclose(fp);

    // ! -----------------------------------------------------------------------
    printsection("write");
    printstring("s", s);
    fp = fopen("test_string.bin", "w");
    CBL_CALL(s, write, fp);
    fclose(fp);

    // ! -----------------------------------------------------------------------
    printsection("read");
    CBL_CALL(s, free_); printstring("s", s);
    fp = fopen("test_string.bin", "r");
    CBL_CALL(s, read_, fp); printstring("s", s);
    fclose(fp);

    // ! -----------------------------------------------------------------------
    printsection("free");
    CBL_FREE_VARS(String, 3, s, t, u);
    return 0;
}
