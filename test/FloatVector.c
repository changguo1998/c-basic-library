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
#include <time.h>

#include "Module_Basic.h"
#include "Type_IntVector.h"
#include "Type_FloatVector.h"
#include "Type_FloatMatrix.h"
#include "Type_Part_math_basic.h"

#define initzeros(x, n) CBL_CALL(x, alloc_, n);\
    CBL_CALL(x, fill_, 0.0)

#define initrand(x, n, a, b) CBL_CALL(x, alloc_, n);\
CBL_CALL(x, rand_, a, b)

#define initrandv(x, n) initrand(x, n, 0, 20)

#define randf(x) initrand(x, 5, 0, 20)

void print_section(const char* section) {
    printf("\n==============================\n");
    printf(" * %s\n\n", section);
}

void print_ivec(struct IntVector v) {
    printf("[");
    for(Int i = 0; i < v.len; i++) printf("%d, ", v.data[i]);
    printf("]\n");
}

void print_fvec(struct FloatVector v) {
    printf("[");
    for(Int i = 0; i < v.len; i++) printf("%.2f, ", v.data[i]);
    printf("]\n");
}

void printivecn(const char* vname, struct IntVector v) {
    printf("%s:", vname);
    print_ivec(v);
}

void printfvecn(const char* vname, struct FloatVector v) {
    printf("%s:", vname);
    print_fvec(v);
}

void printfmatn(const char* vname, struct FloatMatrix m) {
    Int i, j;
    printf("%s: [\n", vname);
    for(i = 0; i < m.nrow; i++) {
        printf("  ");
        for(j = 0; j < m.ncol; j++) printf("%.2f, ", CBL_CALL(m, get, i, j));
        printf("\n");
    }
    printf("]\n");
}

Float mapff_core(Float x, Float y) { return x / y; }

int main() {
    CBL_DECLARE_VARS(IntVector, 1, iu);
    CBL_DECLARE_VARS(FloatVector, 3, fu, fv, fw);
    CBL_DECLARE_VARS(FloatMatrix, 1, fmat);

    Int   i, j;
    Float x, y;

    // -----------------------------------------------------------------
    print_section("new");
    printf("after new:\n");
    printf("iv.len=%d\n", fv.len);
    printf("iv.data=%p\n", fv.data);
    printf("iv.methods=%p\n", fv.methods);

    // -----------------------------------------------------------------
    print_section("alloc");
    CBL_CALL(fv, alloc_, 5);
    print_fvec(fv);

    // -----------------------------------------------------------------
    print_section("get");
    randf(fu);
    print_fvec(fu);
    printf("fu[2]=%.3f\n", CBL_CALL(fu, get, 2));

    // -----------------------------------------------------------------
    print_section("index");
    randf(fu);
    CBL_CALL(iu, setas_, 2, 1, 3);
    printfvecn("fu", fu);
    printivecn("iu", iu);
    CBL_CALL(fu, index_, iu);
    printfvecn("fu", fu);

    // -----------------------------------------------------------------
    print_section("slice");
    randf(fu);
    printfvecn("fu", fu);
    CBL_CALL(fu, slice_, 1, 1, 3);
    printfvecn("fu", fu);

    // -----------------------------------------------------------------
    print_section("index_flag");
    initrandv(fu, 5);
    CBL_CALL(iu, alloc_, 5);
    do
        CBL_CALL(iu, rand_, 0, 1); while(CBL_CALL(iu, count) == 0);
    printfvecn("fu", fu);
    printivecn("iu", iu);
    CBL_CALL(fu, index_flag_, iu);
    printfvecn("fu", fu);

    // -----------------------------------------------------------------
    print_section("set");
    randf(fu);
    printfvecn("fu", fu);
    CBL_CALL(fu, set_, 2, 100);
    printfvecn("fu", fu);

    // -----------------------------------------------------------------
    print_section("setas");
    randf(fu);
    printfvecn("fu", fu);
    CBL_CALL(fu, setas_, 2, 100.0, 300.0);
    printfvecn("fu", fu);

    // -----------------------------------------------------------------
    print_section("vcat");
    initrandv(fu, 5);
    initrandv(fv, 3);
    printfvecn("fu", fu);
    printfvecn("fv", fv);
    CBL_CALL(fu, vcat_, 1, fv);
    printfvecn("fu", fu);
    printfvecn("fv", fv);

    // -----------------------------------------------------------------
    print_section("rand");
    CBL_CALL(fu, free_);
    printfvecn("fu", fu);
    CBL_CALL(fu, alloc_, 5);
    CBL_CALL(fu, rand_, 1, 10);
    printfvecn("fu", fu);

    // -----------------------------------------------------------------
    print_section("rand_from");
    initrandv(fu, 10);
    initrandv(fv, 3);
    CBL_CALL(fu, fill_, 0);
    printfvecn("fu", fu);
    printfvecn("fv", fv);
    CBL_CALL(fu, rand_from_, fv);
    printfvecn("fu", fu);

    // -----------------------------------------------------------------
    print_section("fill");
    randf(fu);
    printfvecn("fu", fu);
    CBL_CALL(fu, fill_, 100.0);
    printfvecn("fu", fu);

    // -----------------------------------------------------------------
    print_section("linrange");
    initzeros(fu, 5);
    printfvecn("fu", fu);
    CBL_CALL(fu, linrange_, 1.0, 3.0);
    printfvecn("fu", fu);

    // -----------------------------------------------------------------
    print_section("range");
    CBL_CALL(fu, free_);
    printfvecn("fu", fu);
    CBL_CALL(fu, range_, 1.0, 0.2, 2.0);
    printfvecn("fu", fu);

    // -----------------------------------------------------------------
    print_section("copy_");
    randf(fu);
    initrandv(fv, 3);
    printfvecn("fu", fu);
    printfvecn("fv", fv);
    CBL_CALL(fu, copy_, fv);
    printfvecn("fu", fu);
    printfvecn("fv", fv);

    // -----------------------------------------------------------------
    print_section("sum/mean/var/std/prod");
    CBL_CALL(fu, range_, 0.2, 0.2, 1.0);
    printfvecn("fu", fu);
    printf("sum(fu) = %.2f\n", CBL_CALL(fu, sum));
    printf("mean(fu) = %.2f\n", CBL_CALL(fu, mean));
    printf("var(fu) = %.2f\n", CBL_CALL(fu, var));
    printf("std(fu) = %g\n", CBL_CALL(fu, std));
    printf("prod(fu) = %g\n", CBL_CALL(fu, prod));

    // -----------------------------------------------------------------
    print_section("norm");
    CBL_CALL(fu, setas_, 2, 3.0, -4.0);
    printfvecn("fu", fu);
    printf("norm(fu, 0) = %g\n", CBL_CALL(fu, norm, 0));
    printf("norm(fu, 1) = %g\n", CBL_CALL(fu, norm, 1));
    printf("norm(fu, 2) = %g\n", CBL_CALL(fu, norm, 2));
    printf("norm(fu, 3) = %g\n", CBL_CALL(fu, norm, 3));
    printf("norm(fu, Inf) = %g\n", CBL_CALL(fu, norm, CBL_INT_MAX));

    // -----------------------------------------------------------------
    print_section("min/argmin/max/argmax");
    randf(fu);
    printfvecn("fu", fu);
    x = CBL_CALL(fu, min);
    i = CBL_CALL(fu, argmin);
    y = CBL_CALL(fu, max);
    j = CBL_CALL(fu, argmax);
    printf("min: fu[%d]=%.2f\n", i, x);
    printf("max: fu[%d]=%.2f\n", j, y);

    // -----------------------------------------------------------------
    print_section("cumsum");
    CBL_CALL(fu, setas_, 3, 1.0, 2.0, 3.0);
    printfvecn("fu", fu);
    CBL_CALL(fu, cumsum_, 0.0);
    printfvecn("fu", fu);

    // -----------------------------------------------------------------
    print_section("cumprod");
    CBL_CALL(fu, setas_, 3, 1.0, 2.0, 3.0);
    printfvecn("fu", fu);
    CBL_CALL(fu, cumprod_, 1.0);
    printfvecn("fu", fu);

    // -----------------------------------------------------------------
    print_section("sort");
    randf(fu);
    printfvecn("fu", fu);
    CBL_CALL(fu, sort_);
    printfvecn("fu", fu);

    // -----------------------------------------------------------------
    print_section("sortperm");
    randf(fu);
    printfvecn("fu", fu);
    CBL_CALL(fu, sortperm_, &iu);
    printfvecn("fu", fu);
    printivecn("iu", iu);

    // -----------------------------------------------------------------
    print_section("dot");
    randf(fu);
    randf(fv);
    printfvecn("fu", fu);
    printfvecn("fv", fv);
    printf("dot(fu, fv) = %g\n", CBL_CALL(fu, dot, fv));

    // -----------------------------------------------------------------
    print_section("cross");
    CBL_CALL(fu, setas_, 3, 1.0, 0.0, 0.0);
    CBL_CALL(fv, setas_, 3, 1.0, 1.0, 0.0);
    printfvecn("fu", fu);
    printfvecn("fv", fv);
    CBL_CALL(fw, cross_, fu, fv);
    printfvecn("fw", fw);

    // -----------------------------------------------------------------
    print_section("map_f_f_, sqrt");
    CBL_CALL(fu, setas_, 3, 1.0, 4.0, 9.0);
    printfvecn("fu", fu);
    CBL_CALL(fu, map_f_f_, _bm_sqrt);
    printfvecn("fu", fu);

    // -----------------------------------------------------------------
    print_section("map_f_ff_, div");
    CBL_CALL(fu, setas_, 3, 1.0, 2.0, 3.0);
    CBL_CALL(fv, setas_, 3, 1.0, 4.0, 5.0);
    printfvecn("fu", fu);
    printfvecn("fv", fv);
    CBL_CALL(fu, map_f_ff_, mapff_core, fv);
    printfvecn("fu", fu);

    // -----------------------------------------------------------------
    print_section("add_scalar/sub_scalar/mul_scalar/div_scalar");
    CBL_CALL(fu, setas_, 3, 1.0, 3.0, 5.0);
    printfvecn("fu", fu);
    CBL_CALL(fu, add_scalar_, 2.0);
    printf("add_scalar");
    printfvecn("fu", fu);
    CBL_CALL(fu, sub_scalar_, 1.0);
    printf("sub_scalar");
    printfvecn("fu", fu);
    CBL_CALL(fu, mul_scalar_, 3.0);
    printf("mul_scalar");
    printfvecn("fu", fu);
    CBL_CALL(fu, div_scalar_, 2.0);
    printf("div_scalar");
    printfvecn("fu", fu);

    // -----------------------------------------------------------------
    print_section("add");
    CBL_CALL(fu, setas_, 3, 1.0, 3.0, 5.0);
    CBL_CALL(fu, setas_, 3, 1.0, 2.0, 4.0);
    printfvecn("  fu", fu);
    printfvecn("  fv", fv);
    CBL_CALL(fu, add_, fv);
    printf("add_\n");
    printfvecn("  fu", fu);
    printfvecn("  fv", fv);

    // -----------------------------------------------------------------
    print_section("sub");
    CBL_CALL(fu, setas_, 3, 1.0, 3.0, 5.0);
    CBL_CALL(fu, setas_, 3, 1.0, 2.0, 4.0);
    printfvecn("  fu", fu);
    printfvecn("  fv", fv);
    CBL_CALL(fu, sub_, fv);
    printf("sub_\n");
    printfvecn("  fu", fu);
    printfvecn("  fv", fv);

    // -----------------------------------------------------------------
    print_section("mul");
    CBL_CALL(fu, setas_, 3, 1.0, 3.0, 5.0);
    CBL_CALL(fu, setas_, 3, 1.0, 2.0, 4.0);
    printfvecn("  fu", fu);
    printfvecn("  fv", fv);
    CBL_CALL(fu, mul_, fv);
    printf("mul_\n");
    printfvecn("  fu", fu);
    printfvecn("  fv", fv);

    // -----------------------------------------------------------------
    print_section("div");
    CBL_CALL(fu, setas_, 3, 1.0, 3.0, 5.0);
    CBL_CALL(fu, setas_, 3, 1.0, 2.0, 4.0);
    printfvecn("  fu", fu);
    printfvecn("  fv", fv);
    CBL_CALL(fu, div_, fv);
    printf("div_\n");
    printfvecn("  fu", fu);
    printfvecn("  fv", fv);

    // -----------------------------------------------------------------
    print_section("sqrt");
    CBL_CALL(fu, setas_, 3, 1.0, 4.0, 9.0);
    printfvecn("  fu", fu);
    CBL_CALL(fu, sqrt_);
    printf("sqrt_\n");
    printfvecn("  fu", fu);

    // -----------------------------------------------------------------
    print_section("root 3");
    CBL_CALL(fu, setas_, 3, 1.0, 8.0, 27.0);
    printfvecn("  fu", fu);
    CBL_CALL(fu, root_, 3);
    printf("root_\n");
    printfvecn("  fu", fu);

    // -----------------------------------------------------------------
    print_section("pow 3");
    CBL_CALL(fu, setas_, 3, 1.0, 2.0, 3.0);
    printfvecn("  fu", fu);
    CBL_CALL(fu, pow_, 3);
    printf("pow 3\n");
    printfvecn("  fu", fu);

    // -----------------------------------------------------------------
    print_section("normalize2");
    CBL_CALL(fu, setas_, 2, -3.0, 4.0);
    printfvecn("  fu", fu);
    CBL_CALL(fu, normalize2_);
    printfvecn("  fu", fu);

    // -----------------------------------------------------------------
    print_section("normalize2");
    CBL_CALL(fu, setas_, 2, -3.0, -4.0);
    printfvecn("  fu", fu);
    CBL_CALL(fu, normalize_, CBL_INT_MAX);
    printfvecn("  fu", fu);

    // -----------------------------------------------------------------
    print_section("polyval/polyint/polydiff");
    CBL_CALL(fu, setas_, 3, 1.0, 2.0, 3.0);
    printfvecn("  fu", fu);
    x = 2.0;
    printf("polyval: f(%g)=%g\n", x, CBL_CALL(fu, polyval, x));
    printf("Integral:\n");
    CBL_CALL(fu, polyint_, 1.0);
    printfvecn("  fu", fu);
    printf("Diff:\n");
    CBL_CALL(fu, polydiff_);
    printfvecn("  fu", fu);

    // -----------------------------------------------------------------
    print_section("get_col/get_row");
    CBL_CALL(fmat, alloc_, 4, 5);
    CBL_CALL(fmat, rand_, 0.0, 10.0);
    printfmatn("fmat", fmat);
    i = 1;
    j = 2;
    CBL_CALL(fu, get_row_, fmat, i);
    printf("fmat[%d, :]: ", i);
    print_fvec(fu);
    CBL_CALL(fv, get_column_, fmat, j);
    printf("fmat[:, %d]: ", j);
    print_fvec(fv);


    // -----------------------------------------------------------------
    print_section("free");
    CBL_FREE_VARS(IntVector, 1, iu);
    CBL_FREE_VARS(FloatVector, 2, fu, fv);
    return 0;
}

// ! ---------------------------------------------------------------
/*
CBL_CALL(fv, rand_, 0.0, 20.0);
printf("rand: ");
print_fvec(&fv);
x = CBL_CALL(fv, min);
i = CBL_CALL(fv, argmin);
printf("min: %.3f at %d\n", x, i);

y = CBL_CALL(fv, max);
j = CBL_CALL(fv, argmax);
printf("max: %.3f at %d\n", y, j);

CBL_CALL(fv, fill_range_, 1.0, 2.0);
printf("range: ");
print_fvec(&fv);

printf("sum: %.3f\n", CBL_CALL(fv, sum));
printf("prod: %.3f\n", CBL_CALL(fv, prod));

CBL_CALL(fv, rand_, 0.0, 10.0);
print_fvec(&fv);
CBL_CALL(fv, sortperm_, &iv);
printf("sort: ");
print_fvec(&fv);
printf("perm:");
print_ivec(&iv);

*/
