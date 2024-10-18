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
#include <math.h>
#include "Type_DateTime.h"

int main() {
    CBL_DECLARE_VARS(DateTime, 1, dt);
    CBL_DECLARE_VARS(Date, 1, d);
    CBL_DECLARE_VARS(Time, 1, t);
    CBL_DECLARE_VARS(String, 1, msg);

    Float jd;
    Int   mjd;

    printf("[test_DateTime.c] begin\n");
    CBL_CALL(dt, now_, 1);
    CBL_CALL(d, today_, 1);

    printf("[test_DateTime.c] current date: %04d-%02d-%02d\n",
        d.year, d.month, d.day);
    printf("[test_DateTime.c] is leap year? %s\n",
        _DATETIME_is_leap_year(d.year) ? "True" : "False");
    printf("[test_DateTime.c] Day of year: %d\n",
        d.methods->day_of_year(&d));
    printf("[test_DateTime.c] Modified Julian date: %d\n", CBL_CALL(d, julian));
    mjd = CBL_CALL(d, julian);
    CBL_CALL(d, set_julian_, mjd);
    msg = CBL_CALL(d, string);
    printf("[test_DateTime.c] Modified Julian to Date: %s\n\n", msg.str);
    // d.year = 1858;
    // d.month = 11;
    // d.day = 16;
    CBL_CALL(d, add_, 20);
    printf("[test_DateTime.c] new date: %04d-%02d-%02d\n",
        d.year, d.month, d.day);
    printf("[test_DateTime.c] Day of year: %d\n", CBL_CALL(d, day_of_year));
    printf("[test_DateTime.c] Modified Julian date: %d\n", CBL_CALL(d, julian));
    printf("[test_DateTime.c] date isequal: %s\n",
        CBL_CALL(dt.date, isequal, d) ? "True" : "False");
    printf("[test_DateTime.c] date isless: %s\n", CBL_CALL(dt.date, lessthan, d) ? "True" : "False");
    printf("[test_DateTime.c] date diff: %d\n\n", CBL_CALL(d, diff, dt.date));

    msg = CBL_CALL(dt, string);
    printf("[test_DateTime.c] current time: %s\n", msg.str);
    printf("[test_DateTime.c] modified julian date: %f\n", CBL_CALL(dt, julian));
    jd = CBL_CALL(dt, julian);
    printf("[test_DateTime.c] julian date: %f\n", jd);
    CBL_CALL(dt, set_julian_, jd);
    msg = CBL_CALL(dt, string);
    printf("[test_DateTime.c] back to date: %s\n", msg.str);

    t = dt.time;
    msg = CBL_CALL(t, string);
    printf("[test_DateTime.c] time: %s\n", msg.str);
    CBL_CALL(t, add_second_, 300);
    msg = CBL_CALL(t, string);
    printf("[test_DateTime.c] time+300s: %s\n", msg.str);
    CBL_CALL(dt, add_second_, 300);
    msg = CBL_CALL(dt, string);
    printf("[test_DateTime.c] current time: %s\n\n", msg.str);

    printf("[test_DateTime.c] test regularize\n");
    CBL_CALL(d, set_, 3, 2024L, 10L, -5L);
    msg = CBL_CALL(d, string);
    printf("[test_DateTime.c] before regularize: %s\n", msg.str);
    CBL_CALL(d, regularize_);
    msg = CBL_CALL(d, string);
    printf("[test_DateTime.c] after regularize: %s\n", msg.str);

    CBL_CALL(t, set_, 1, 1L);
    CBL_CALL(t, add_, -1);
    t.hour = -2;
    msg = CBL_CALL(t, string);
    printf("[test_DateTime.c] before regularize: %s\n", msg.str);
    CBL_CALL(t, regularize_);
    msg = CBL_CALL(t, string);
    printf("[test_DateTime.c] after regularize: %s\n", msg.str);

    CBL_CALL(dt, set_, 6, 2024l, 10l, -5l, 1l, -15l, -5l);
    msg = CBL_CALL(dt, string);
    printf("[test_DateTime.c] before regularize: %s\n", msg.str);
    CBL_CALL(dt, regularize_);
    msg = CBL_CALL(dt, string);
    printf("[test_DateTime.c] after regularize: %s\n", msg.str);
    return 0;
}
