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
#include <stdarg.h>
#include <time.h>
#include <math.h>
#include "Type_String.h"
#include "Type_Part_math_basic.h"
#include "Type_DateTime.h"


struct DateMethods _CBL_DATE_METHODS = {
    &Date_today_,
    &Date_set_,
    &Date_set_julian_,
    &Date_less_than,
    &Date_isequal,
    &Date_day_of_year,
    &Date_diff,
    &Date_julian,
    &Date_add_,
    &Date_regularize_,
    &Date_string
};

struct TimeMethods _CBL_TIME_METHODS = {
    &Time_now_,
    &Time_set_,
    &Time_zero_,
    &Time_regularize_,
    &Time_string,
    &Time_diff,
    &Time_diff_second,
    &Time_add_,
    &Time_add_second_
};

struct DateTimeMethods _CBL_DATETIME_METHODS = {
    &DateTime_now_,
    &DateTime_set_,
    &DateTime_set_julian_,
    &DateTime_regularize_,
    &DateTime_diff,
    &DateTime_diff_second,
    &DateTime_add_,
    &DateTime_add_second_,
    &DateTime_julian,
    &DateTime_string
};

#if TIME_PRECISION == 0
const long double _DT_SECOND_PRECISION_RATIO = 1.0;
#elif TIME_PRECISION == 3
const long double _DT_SECOND_PRECISION_RATIO = 1e3;
#elif TIME_PRECISION == 6
const long double _DT_SECOND_PRECISION_RATIO = 1e6;
#elif TIME_PRECISION == 9
const long double _DT_SECOND_PRECISION_RATIO = 1e9;
#endif

const Int _DT_DAYS_PER_MONTH[12] = {
    31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31
};

Int DateTime_second2precision(Float s) { return (Int)(s * _DT_SECOND_PRECISION_RATIO); }

Float DateTime_precision2second(Int tp) {
    return (Float)(tp / _DT_SECOND_PRECISION_RATIO);
}

// # ========================================================================
// # Methods for Date

struct Date Date_today_(struct Date* this, Int type) {
    struct DateTime buffer;
    DateTime_new_(&buffer);
    DateTime_now_(&buffer, type);
    *this = buffer.date;
    return *this;
}

struct Date Date_set_(struct Date* this, Int n, ...) {
    va_list ap;
    va_start(ap, n);
    this->year  = (n > 0) ? va_arg(ap, long) : 0;
    this->month = (n > 1) ? va_arg(ap, long) : 0;
    this->day   = (n > 2) ? va_arg(ap, long) : 0;
    va_end(ap);
    return *this;
}

Bool _DATETIME_is_leap_year(Int year) {
    if(year % 100) {
        if(year % 4) return false;
        return true;
    }
    if(year % 400) return false;
    return true;
}

Int _DATETIME_day_diff_year_to_year(Int y1, Int y2) {
    Int number_of_leap_year, y, ya, yb;
    if(y1 == y2) return 0;
    if(y1 < y2) {
        ya = y1;
        yb = y2;
    }
    else {
        ya = y2;
        yb = y1;
    }
    number_of_leap_year = 0;
    for(y = ya; y < yb; y += 1)
        if(_DATETIME_is_leap_year(y))
            number_of_leap_year += 1;
    y = 365 * (yb - ya) + number_of_leap_year;
    if(y1 < y2) return -y;
    return y;
}

struct Date Date_set_julian_(struct Date* this, Int mjday) {
    Int buffer_julian_day, residual_day_number, is_leap_year;

    buffer_julian_day = mjday + 319;
    this->year = buffer_julian_day / 366 + 1858;

    while(true) {
        residual_day_number = buffer_julian_day -
            _DATETIME_day_diff_year_to_year(this->year, 1858);
        if(residual_day_number < 0) this->year -= 1;
        else if(residual_day_number > (364 +
            _DATETIME_is_leap_year(this->year)))
            this->year += 1;
        else break;
    } // while
    this->month = 0;
    is_leap_year = (Int)_DATETIME_is_leap_year(this->year);
    if(residual_day_number < 31)
        this->month = 0;
    else if(residual_day_number < (31 + 28 + is_leap_year)) {
        this->month = 1;
        residual_day_number -= 31;
    }
    else {
        this->month = 2;
        residual_day_number -= (31 + 28 + is_leap_year);
        while(residual_day_number >= _DT_DAYS_PER_MONTH[this->month]) {
            residual_day_number -= _DT_DAYS_PER_MONTH[this->month];
            this->month += 1;
        }
    }
    this->month += 1;
    this->day = residual_day_number + 1;
    return *this;
}

Bool Date_less_than(const struct Date* this, struct Date another) {
    if(this->year < another.year) return true;
    if(this->year > another.year) return false;
    if(this->month < another.month) return true;
    if(this->month > another.month) return false;
    if(this->day < another.day) return true;
    return false;
}

Bool Date_isequal(const struct Date* this, struct Date another) {
    if((this->year == another.year) &&
        (this->month == another.month) &&
        (this->day == another.day))
        return true;
    return false;
}

Int Date_day_of_year(const struct Date* this) {
    Int day_count = 0;
    Int i_month;
    for(i_month = 1; i_month < this->month; i_month += 1)
        day_count += _DT_DAYS_PER_MONTH[i_month - 1];
    day_count += this->day;
    if(_DATETIME_is_leap_year(this->year) && (this->month > 2)) day_count += 1;
    return day_count;
}

Int Date_diff(const struct Date* this, struct Date date) {
    return _DATETIME_day_diff_year_to_year(this->year, date.year) +
        Date_day_of_year(this) - Date_day_of_year(&date);
}

Int Date_julian(const struct Date* this) {
    struct Date td;
    Date_new_(&td);
    Date_set_(&td, 3, 1858L, 11L, 16L);
    return Date_diff(this, td);
}

struct Date Date_add_(struct Date* this, Int day) {
    Int julian_day;
    julian_day = Date_julian(this);
    Date_set_julian_(this, julian_day + day);
    return *this;
}

struct Date Date_regularize_(struct Date* this) {
    struct Date buffer_date;
    Int         modified_julian_day;
    Date_new_(&buffer_date);
    buffer_date = *this;
    buffer_date.day = 1;
    modified_julian_day = Date_julian(&buffer_date);
    modified_julian_day += this->day - 1;
    Date_set_julian_(this, modified_julian_day);
    return *this;
}

struct String Date_string(const struct Date* this) {
    struct String buffer;
    String_new_(&buffer);
    sprintf(buffer.str, "%04d-%02d-%02d",
        this->year, this->month, this->day);
    buffer.len = (Int)strlen(buffer.str);
    return buffer;
}

// # ========================================================================
// # Methods for Time
struct Time Time_now_(struct Time* this, Int type) {
    struct DateTime buffer;
    DateTime_new_(&buffer);
    DateTime_now_(&buffer, type);
    *this = buffer.time;
    return *this;
}

struct Time Time_set_(struct Time* this, Int n, ...) {
    va_list args;
    va_start(args, n);
    this->hour   = (n > 0) ? va_arg(args, int) : 0;
    this->minute = (n > 1) ? va_arg(args, int) : 0;
    this->second = (n > 2) ? va_arg(args, int) : 0;
#if TIME_PRECISION > 0
    this->millisecond = (n > 3) ? va_arg(args, int) : 0;
#endif
#if TIME_PRECISION > 3
    this->macrosecond = (n > 4) ? va_arg(args, int) : 0;
#endif
#if TIME_PRECISION > 6
    this->nanosecond = (n > 5) ? va_arg(args, int) : 0;
#endif
    va_end(args);
    return *this;
}

struct Time Time_zero_(struct Time* this) {
    this->hour = 0;
    this->minute = 0;
    this->second = 0;
#if TIME_PRECISION > 0
    this->millisecond = 0;
#endif
#if TIME_PRECISION > 3
    this->macrosecond = 0;
#endif
#if TIME_PRECISION > 6
    this->nanosecond = 0;
#endif
    return *this;
}

static inline void _time_round_same_sign(long long *large, long long *small, long long base) {
    *large = *small / base;
    *small -= *large * base;
    while(*small >= base) {
        *small -= base;
        *large += 1;
    }
    while(*small < 0) {
        *small += base;
        *large -= 1;
    }
    if(*large < 0 && *small > 0) {
        *small -= base;
        *large += 1;
    }
}

struct Time Time_regularize_(struct Time* this) {
    long long t1, t2 = 0;
    t1 = this->hour;             // t1: hour
    // printf("hour: %d, t1: %lld\n", this->hour, t1);
    t1 = this->minute + t1 * 60; // t1: minute
    // printf("minute: %d, t1: %lld\n", this->minute, t1);
    t1 = this->second + t1 * 60; // t1: second
    // printf("second: %d, t1: %lld\n", this->second, t1);
#if TIME_PRECISION > 0
    t1 = this->millisecond + t1 * 1000; // t1: millisecond
    // printf("millisecond: %d, t1: %lld\n", this->millisecond, t1);
#endif
#if TIME_PRECISION > 3
    t1 = this->macrosecond + t1 * 1000; // t1: macrosecond
    // printf("macrosecond: %d, t1: %lld\n", this->macrosecond, t1);
#endif
#if TIME_PRECISION > 6
    t1 = this->nanosecond + t1 * 1000; // t1: nanosecond

    _time_round_same_sign(&t2, &t1, 1000);
    this->nanosecond = (Int)t1;
    t1 = t2; // macrosecond
#endif
#if TIME_PRECISION > 3
    _time_round_same_sign(&t2, &t1, 1000);
    this->macrosecond = (Int)t1;
    t1 = t2; // millisecond
    // printf("macrosecond: %d, t1: %lld\n", this->macrosecond, t1);
#endif
#if TIME_PRECISION > 0
    _time_round_same_sign(&t2, &t1, 1000);
    this->millisecond = (Int)t1;
    t1 = t2; // second
    // printf("millisecond: %d, t1: %lld\n", this->millisecond, t1);
#endif
    _time_round_same_sign(&t2, &t1, 60);
    this->second = (Int)t1;
    t1 = t2; // minute
    // printf("second: %d, t1: %lld\n", this->second, t1);
    _time_round_same_sign(&t2, &t1, 60);
    this->minute = (Int)t1;
    this->hour = (Int)t2;
    // printf("minute: %d, t1: %lld\n", this->minute, t1);
    // printf("hour: %d, t2: %lld\n", this->hour, t2);
    return *this;
}

struct String Time_string(const struct Time* this) {
    struct String buffer;
    Int h, m, s, ms, us, ns;
    Char sign = ' ';
    String_new_(&buffer);
    h = _bm_abs_int(this->hour);
    if(this->hour < 0) sign = '-';
    m = _bm_abs_int(this->minute);
    if(this->minute < 0) sign = '-';
    s = _bm_abs_int(this->second);
    if(this->second < 0) sign = '-';

#if TIME_PRECISION > 0
    ms = _bm_abs_int(this->millisecond);
    if(this->millisecond < 0) sign = '-';
#endif
#if TIME_PRECISION > 3
    us = _bm_abs_int(this->macrosecond);
    if(this->macrosecond < 0) sign = '-';
#endif
#if TIME_PRECISION > 6
    ns = _bm_abs_int(this->nanosecond);
    if(this->nanosecond < 0) sign = '-';
#endif


#if TIME_PRECISION == 0
    sprintf(buffer.str, "%c%02d:%02d:%02d", sign, h, m, s);
#elif TIME_PRECISION == 3
    sprintf(buffer.str, "%c%02d:%02d:%02d.%03d", sign, h, m, s, ms);
#elif TIME_PRECISION == 6
    sprintf(buffer.str, "%c%02d:%02d:%02d.%03d%03d", sign, h, m, s, ms, us);
#elif TIME_PRECISION == 9
    sprintf(buffer.str, "%c%02d:%02d:%02d.%03d%03d%03d", sign, h, m, s, ms, us, ns);
#endif
    buffer.len = (Int)strlen(buffer.str);
    return buffer;
}

Int Time_diff(const struct Time* this, struct Time time) {
    Int buf = 0;
    buf = this->hour - time.hour;
    buf = buf * 60 + this->minute - time.minute;
    buf = buf * 60 + this->second - time.second;
#if TIME_PRECISION > 0
    buf = buf * 1000 + this->millisecond - time.millisecond;
#endif
#if TIME_PRECISION > 3
    buf = buf * 1000 + this->macrosecond - time.macrosecond;
#endif
#if TIME_PRECISION > 6
    buf = buf * 1000 + this->nanosecond - time.nanosecond;
#endif
    return buf;
}

Float Time_diff_second(const struct Time* this, struct Time time) {
    Float buf;
    buf = (Float)this->hour - time.hour;
    buf = buf * 60.0 + this->minute - time.minute;
    buf = buf * 60.0 + this->second - time.second;
#if TIME_PRECISION > 0
    buf = buf + (this->millisecond - time.millisecond) * 1.0e-3;
#endif
#if TIME_PRECISION > 3
    buf = buf + (this->macrosecond - time.macrosecond) * 1.0e-6;
#endif
#if TIME_PRECISION > 6
    buf = buf + (this->nanosecond - time.nanosecond) * 1.0e-9;
#endif
    return buf;
}

struct Time Time_add_(struct Time* this, Int precision) {
#if TIME_PRECISION > 6
    this->nanosecond += precision;
#elif TIME_PRECISION > 3
    this->macrosecond += precision;
#elif TIME_PRECISION > 0
    this->millisecond += precision;
#else
    this->second += precision;
#endif
    Time_regularize_(this);
    return *this;
}

struct Time Time_add_second_(struct Time* this, Float seconds) {
    return Time_add_(this, DateTime_second2precision(seconds));
}

// # ========================================================================
// # Methods for DateTime

struct DateTime DateTime_now_(struct DateTime* this, Int tz) {
    struct tm* system_time_pointer;
    time_t     raw_time;

    time(&raw_time);

    if(tz == 0) system_time_pointer = gmtime(&raw_time);
    else system_time_pointer = localtime(&raw_time);

    this->date.year = system_time_pointer->tm_year + 1900;
    this->date.month = system_time_pointer->tm_mon + 1;
    this->date.day = system_time_pointer->tm_mday;
    this->time.hour = system_time_pointer->tm_hour;
    this->time.minute = system_time_pointer->tm_min;
    this->time.second = system_time_pointer->tm_sec;
#if TIME_PRECISION > 0
    this->time.millisecond = 0;
#endif
#if TIME_PRECISION > 3
    this->time.macrosecond = 0;
#endif
#if TIME_PRECISION > 6
    this->time.nanosecond = 0;
#endif
    DateTime_regularize_(this);
    return *this;
}

struct DateTime DateTime_set_(struct DateTime* this, Int n, ...) {
    va_list ap;
    va_start(ap, n);
    this->date.year   = (n > 0) ? va_arg(ap, long) : 0;
    this->date.month  = (n > 1) ? va_arg(ap, long) : 0;
    this->date.day    = (n > 2) ? va_arg(ap, long) : 0;
    this->time.hour   = (n > 3) ? va_arg(ap, long) : 0;
    this->time.minute = (n > 4) ? va_arg(ap, long) : 0;
    this->time.second = (n > 5) ? va_arg(ap, long) : 0;
#if TIME_PRECISION > 0
    this->time.millisecond = (n > 6) ? va_arg(ap, long) : 0;
#endif
#if TIME_PRECISION > 3
    this->time.macrosecond = (n > 7) ? va_arg(ap, long) : 0;
#endif
#if TIME_PRECISION > 6
    this->time.nanosecond = (n > 8) ? va_arg(ap, long) : 0;
#endif
    va_end(ap);
    return *this;
}

struct DateTime DateTime_set_julian_(struct DateTime* this, Float mjdatetime) {
    Int   julian_day_number;
    Int   time_residual;
    Float jdatetime_f, jtime_res_f, mjdate_f;

    jdatetime_f = mjdatetime + 0.5;
    jtime_res_f = modf(jdatetime_f, &mjdate_f);
    if(jtime_res_f < 0.0) {
        mjdate_f    -= 1.0;
        jtime_res_f += 1.0;
    }
    julian_day_number = (Int)mjdate_f;
    time_residual = DateTime_second2precision(jtime_res_f * 86400.0);
    Date_set_julian_(&(this->date), julian_day_number);
    Time_zero_(&(this->time));
    return DateTime_add_(this, time_residual);
}

struct DateTime DateTime_regularize_(struct DateTime* this) {
    Time_regularize_(&(this->time));
    this->date.day += this->time.hour / 24;
    this->time.hour %= 24;
    this->time.hour += 24;
    this->date.day -= 1;
    Time_regularize_(&(this->time));
    this->date.day += this->time.hour / 24;
    this->time.hour %= 24;
    Date_regularize_(&(this->date));
    return *this;
}

Int DateTime_diff(const struct DateTime* this, struct DateTime datetime) {
    Int day_diff, time_diff;
    day_diff = Date_diff(&(this->date), datetime.date);
    time_diff = Time_diff(&(this->time), datetime.time);
    return DateTime_second2precision(86400) * day_diff + time_diff;
}

Float DateTime_diff_second(const struct DateTime* this,
                           struct DateTime        datetime) {
    Int day_diff, time_diff;
    day_diff = Date_diff(&(this->date), datetime.date);
    time_diff = Time_diff(&(this->time), datetime.time);
    return 86400.0 * day_diff + DateTime_precision2second(time_diff);
}

struct DateTime DateTime_add_(struct DateTime* this, Int precision) {
#if TIME_PRECISION > 6
    this->time.nanosecond += precision;
#elif TIME_PRECISION > 3
    this->time.macrosecond += precision;
#elif TIME_PRECISION > 0
    this->time.millisecond += precision;
#else
    this->time.second += precision;
#endif
    return DateTime_regularize_(this);
}

struct DateTime DateTime_add_second_(struct DateTime* this, Float seconds) {
    return DateTime_add_(this, DateTime_second2precision(seconds));
}

Float DateTime_julian(const struct DateTime* this) {
    Float       second_residual;
    struct Time tt;
    Time_new_(&tt);
    Time_zero_(&tt);
    second_residual = DateTime_precision2second(Time_diff(&(this->time), tt)) /
        (24.0 * 60.0 * 60.0);
    return (Float)Date_julian(&(this->date)) - 0.5 + second_residual;
}

struct String DateTime_string(const struct DateTime* this) {
    struct String date_str, time_str, buffer_str;
    String_new_(&date_str);
    String_new_(&time_str);
    String_new_(&buffer_str);
    date_str = Date_string(&(this->date));
    time_str = Time_string(&(this->time));
    sprintf(buffer_str.str, "%s %s", date_str.str, time_str.str);
    buffer_str.len = (Int)strlen(buffer_str.str);
    return buffer_str;
}
