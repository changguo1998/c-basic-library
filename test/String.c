#include <stdio.h>
#include <stdlib.h>
#include "CBL_String.h"

int main() {
    String r[5], s[3], t[3];
    String* sp;
    Int nslice;
    char c, buffer[100];
    for(c = 'a'; c <= 'e'; c++) {
        sprintf(buffer, "ab%c", c);
        printf("%s\n", buffer);
        r[c - 'a'] = STR_String(buffer);
    }
    s[0] = STR_join(r, 5, STR_empty_string());
    s[1] = s[0];
    printf("s0: %s\ns1: %s\n", s[0].str, s[1].str);
    printf("s0 == s1 : %d\n", STR_isequal(s[0], s[1]));
    s[2] = STR_slice(s[0], 0, 1);
    printf("s2: %s\n", s[2].str);
    printf("s0 == s2 : %d\n", STR_isequal(s[0], s[2]));
    t[0] = STR_join(r, 5, STR_String("_"));
    printf("join of r[0-4]: %s\n", t[0].str);
    t[0] = STR_String("ab");
    t[1] = STR_String("xy");
    t[2] = STR_replace(s[0], t[0], t[1]);
    printf("replace %s with %s in %s, get: %s\n", t[0].str, t[1].str, s[0].str, t[2].str);
    t[2] = STR_replace_all(s[0], t[0], t[1]);
    printf("replace all %s with %s in %s, get: %s\n", t[0].str, t[1].str, s[0].str, t[2].str);
    nslice = STR_split(&sp, t[2], t[1]);
    printf("n slice: %d\n", nslice);
    for(c = 0; c < nslice; c++) { printf("slice[%d]: %s\n", c, sp[c].str); }
    return 0;
}
