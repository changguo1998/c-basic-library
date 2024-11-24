// MIT License
//
// Copyright (c) 2024 Chang Guo
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.
//

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "Module_Basic.h"
#include "Type_IntVector.h"

#define randinit(x, n) CBL_CALL(x, alloc_, n);\
    CBL_CALL(x, rand_, 0, 20)

void print_section(const char* section) {
    printf("\n==============================\n");
    printf(" * %s\n\n", section);
}

void print_ivec(const struct IntVector v) {
    printf("[");
    for(Int i = 0; i < v.len; i++) printf("%d,", v.data[i]);
    printf("]\n");
}

Int larger_than_10(Int x) {
    if(x > 10) return 1;
    else return 0;
}

int main() {
    Int i, j;

    CBL_DECLARE_VARS(IntVector, 3, iu, iv, iw);

    print_section("new");
    printf("after new:\n");
    printf("iv.len=%d\n", iu.len);
    printf("iv.data=%p\n", iu.data);
    printf("iv.methods=%p\n", iu.methods);

    print_section("alloc_");
    CBL_CALL(iu, alloc_, 5);
    print_ivec(iu);

    print_section("index_");
    randinit(iu, 5);
    CBL_CALL(iv, setas_, 3, 0, 2, 4);
    printf("before:\n");
    printf("  iu: ");
    print_ivec(iu);
    printf("  iv: ");
    print_ivec(iv);
    CBL_CALL(iu, index_, iv);
    printf("after:\n");
    printf("  iu: ");
    print_ivec(iu);
    printf("  iv: ");
    print_ivec(iv);

    print_section("slice_");
    randinit(iu, 5);
    printf("before:\n");
    printf("  iu: ");
    print_ivec(iu);
    CBL_CALL(iu, slice_, 1, 2, 3);
    printf("after:\n");
    printf("  iu: ");
    print_ivec(iu);

    print_section("count");
    CBL_CALL(iu, alloc_, 5);
    CBL_CALL(iu, rand_, 0, 2);
    printf("iu: ");
    print_ivec(iu);
    printf("count: %d\n", CBL_CALL(iu, count));

    print_section("index_flag_");
    randinit(iu, 5);
    CBL_CALL(iv, alloc_, 5);
    CBL_CALL(iv, rand_, 0, 1);
    while(!CBL_CALL(iv, count))
        CBL_CALL(iv, rand_, 0, 1);
    printf("before:\n");
    printf("  iu: ");
    print_ivec(iu);
    printf("  iv: ");
    print_ivec(iv);
    CBL_CALL(iu, index_flag_, iv);
    printf("after:\n");
    printf("  iu: ");
    print_ivec(iu);

    print_section("set_");
    randinit(iu, 5);
    printf("  iu: ");
    print_ivec(iu);
    CBL_CALL(iu, set_, 0, 30);
    printf("  iu: ");
    print_ivec(iu);

    print_section("setas_");
    randinit(iu, 5);
    printf("  iu: ");
    print_ivec(iu);
    CBL_CALL(iu, setas_, 3, 100, 200, 300);
    printf("  iu: ");
    print_ivec(iu);

    print_section("vcat_");
    randinit(iu, 5);
    randinit(iv, 3);
    randinit(iw, 2);
    printf("before:\n");
    printf("  iu: ");
    print_ivec(iu);
    printf("  iv: ");
    print_ivec(iv);
    printf("  iw: ");
    print_ivec(iw);
    CBL_CALL(iu, vcat_, 2, iv, iw);
    printf("after:\n");
    printf("  iu: ");
    print_ivec(iu);
    printf("  iv: ");
    print_ivec(iv);
    printf("  iw: ");
    print_ivec(iw);

    print_section("rand_");
    randinit(iu, 5);
    print_ivec(iu);

    print_section("get");
    randinit(iu, 5);
    print_ivec(iu);
    printf("get iu[2]=%d\n", CBL_CALL(iu, get, 2));


    print_section("rand_from_");
    randinit(iu, 5);
    randinit(iv, 3);
    printf("  iu: ");
    print_ivec(iu);
    printf("  iv: ");
    print_ivec(iv);
    CBL_CALL(iv, rand_from_, iu);
    printf("  iu: ");
    print_ivec(iu);
    printf("  iv: ");
    print_ivec(iv);


    print_section("fill_");
    randinit(iu, 5);
    printf("  iu: ");
    print_ivec(iu);
    CBL_CALL(iu, fill_, 32);
    printf("  iu: ");
    print_ivec(iu);

    print_section("range_");
    randinit(iu, 5);
    print_ivec(iu);
    CBL_CALL(iu, range_, 3, 2, 12);
    print_ivec(iu);
    CBL_CALL(iu, range_, 3, 2, 13);
    print_ivec(iu);

    print_section("copy_");
    printf("before:\n");
    printf("  iu: ");
    print_ivec(iu);
    printf("  iv: ");
    print_ivec(iv);
    CBL_CALL(iv, copy_, iu);
    printf("after:\n");
    printf("  iu: ");
    print_ivec(iu);
    printf("  iv: ");
    print_ivec(iv);

    print_section("find_trues_");
    CBL_CALL(iu, free_);
    CBL_CALL(iv, alloc_, 5);
    CBL_CALL(iv, rand_, 0, 1);
    while(!CBL_CALL(iv, count))
        CBL_CALL(iv, rand_, 0, 1);
    printf("  iv: ");
    print_ivec(iv);
    CBL_CALL(iu, find_trues_, iv);
    printf("  iu: ");
    print_ivec(iu);

    print_section("filter_");
    CBL_CALL(iu, alloc_, 5);
    CBL_CALL(iu, rand_, 0, 20);
    printf("  iu: ");
    print_ivec(iu);
    CBL_CALL(iu, filter_, larger_than_10);
    printf("after:\n");
    printf("  iu: ");
    print_ivec(iu);

    print_section("push_");
    CBL_CALL(iu, alloc_, 5);
    CBL_CALL(iu, rand_, 0, 20);
    printf("  iu: ");
    print_ivec(iu);
    CBL_CALL(iu, push_, 32);
    printf("  iu: ");
    print_ivec(iu);

    print_section("isequal");
    CBL_CALL(iu, alloc_, 5);
    CBL_CALL(iu, rand_, 0, 20);
    printf("  iu: ");
    print_ivec(iu);
    CBL_CALL(iv, alloc_, 5);
    CBL_CALL(iv, rand_, 0, 20);
    printf("  iv: ");
    print_ivec(iv);
    printf("iu == iv: %d\n", CBL_CALL(iu, isequal, iv));
    CBL_CALL(iv, copy_, iu);
    printf("  iu: ");
    print_ivec(iu);
    printf("  iv: ");
    print_ivec(iv);
    printf("iu == iv: %d\n", CBL_CALL(iu, isequal, iv));

    print_section("sum");
    CBL_CALL(iu, alloc_, 5);
    CBL_CALL(iu, rand_, 0, 5);
    printf("  iu: ");
    print_ivec(iu);
    printf(" sum(iu): %d", CBL_CALL(iu, sum));

    print_section("prod");
    CBL_CALL(iu, alloc_, 5);
    CBL_CALL(iu, rand_, 0, 5);
    printf("  iu: ");
    print_ivec(iu);
    printf(" sum(iu): %d", CBL_CALL(iu, prod));

    print_section("min/argmin");
    i = CBL_CALL(iu, min);
    j = CBL_CALL(iu, argmin);
    print_ivec(iu);
    printf("min iu: iu[%d]=%d\n", j, i);

    print_section("max/argmax");
    i = CBL_CALL(iu, max);
    j = CBL_CALL(iu, argmax);
    print_ivec(iu);
    printf("max iu: iu[%d]=%d\n", j, i);

    print_section("cumsum_");
    CBL_CALL(iu, alloc_, 3);
    CBL_CALL(iu, rand_, 0, 5);
    printf("  iu: ");
    print_ivec(iu);
    CBL_CALL(iu, cumsum_, 0);
    printf("  iu: ");
    print_ivec(iu);

    print_section("cumprod_");
    CBL_CALL(iu, alloc_, 3);
    CBL_CALL(iu, rand_, 1, 5);
    printf("  iu: ");
    print_ivec(iu);
    CBL_CALL(iu, cumprod_, 1);
    printf("  iu: ");
    print_ivec(iu);

    print_section("sort_");
    CBL_CALL(iu, alloc_, 5);
    CBL_CALL(iu, rand_, 0, 30);
    printf("  iu: ");
    print_ivec(iu);
    CBL_CALL(iu, sort_);
    printf("  iu: ");
    print_ivec(iu);

    print_section("sortperm_");
    CBL_CALL(iu, alloc_, 5);
    CBL_CALL(iu, rand_, 0, 30);
    CBL_CALL(iv, free_);
    printf("  iu: ");
    print_ivec(iu);
    printf("  iv: ");
    print_ivec(iv);
    CBL_CALL(iu, sortperm_, &iv);
    printf("  iu: ");
    print_ivec(iu);
    printf("  iv: ");
    print_ivec(iv);

    print_section("dot");
    randinit(iu, 3);
    randinit(iv, 3);
    CBL_CALL(iu, rand_, 1, 5);
    CBL_CALL(iv, rand_, 1, 5);
    printf("  iu: ");
    print_ivec(iu);
    printf("  iv: ");
    print_ivec(iv);
    printf("dot(iu, iv) = %d\n", CBL_CALL(iv, dot, iv));

    print_section("coord_linear");
    CBL_CALL(iv, setas_, 3, 2, 1, 1);
    CBL_CALL(iw, setas_, 3, 5, 4, 3);
    printf("iv: ");
    print_ivec(iv);
    printf("iw: ");
    print_ivec(iw);
    i = CBL_CALL(iv, coord_linear, iw);
    printf("linear index: %d\n", i);

    print_section("coord_cartesian_");
    CBL_CALL(iv, coord_cartesian_, iw, i);
    printf("reverse iv:");
    print_ivec(iv);

    print_section("free_");
    CBL_FREE_VARS(IntVector, 3, iu, iv, iw);
    return 0;
}
