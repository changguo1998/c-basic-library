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
#include "CBL_DateTime.h"

int main() {
    struct DateTime dt;
    struct Date     d;
    struct Time     t;
    struct String   msg;
    Float           jd;

    DateTime_new_(&dt);
    Date_new_(&d);
    Time_new_(&t);
    String_new_(&msg);
    printf("[test_DateTime.c] begin\n");
    dt.methods->now_(&dt, 1);
    d.methods->today_(&d, 1);

    printf("[test_DateTime.c] current date: %04d-%02d-%02d\n",
        d.year, d.month, d.day);
    printf("[test_DateTime.c] is leap year? %s\n",
        _DATETIME_is_leap_year(d.year) ? "True" : "False");
    printf("[test_DateTime.c] Day of year: %d\n",
        d.methods->day_of_year(&d));
    printf("[test_DateTime.c] Modified Julian date: %d\n",
        d.methods->julian(&d));
    // d.year = 1858;
    // d.month = 11;
    // d.day = 16;
    d.methods->add_(&d, 20);
    printf("[test_DateTime.c] new date: %04d-%02d-%02d\n",
        d.year, d.month, d.day);
    printf("[test_DateTime.c] Day of year: %d\n",
        d.methods->day_of_year(&d));
    printf("[test_DateTime.c] Modified Julian date: %d\n",
        d.methods->julian(&d));
    printf("[test_DateTime.c] date isequal: %s\n",
        dt.date.methods->isequal(&(dt.date), d) ? "True" : "False");
    printf("[test_DateTime.c] date isless: %s\n",
        dt.date.methods->lessthan(&(dt.date), d) ? "True" : "False");
    printf("[test_DateTime.c] date diff: %d\n", d.methods->diff(&d, dt.date));

    msg = dt.methods->string(&dt);
    printf("[test_DateTime.c] current time: %s\n", msg.str);
    printf("[test_DateTime.c] modified julian date: %d\n",
        dt.date.methods->julian(&(dt.date)));
    jd = dt.methods->julian(&dt);
    printf("[test_DateTime.c] julian date: %f\n", jd);
    dt.methods->set_julian_(&dt, jd);
    msg = dt.methods->string(&dt);
    printf("[test_DateTime.c] back to date: %s\n", msg.str);

    t = dt.time;
    msg = t.methods->string(&t);
    printf("[test_DateTime.c] time: %s\n", msg.str);
    t.methods->add_second_(&t, 300);
    msg = t.methods->string(&t);
    printf("[test_DateTime.c] time+500s: %s\n", msg.str);
    dt.methods->add_second_(&dt, 300.0);
    msg = dt.methods->string(&dt);
    printf("[test_DateTime.c] current time: %s\n", msg.str);

    return 0;
}
