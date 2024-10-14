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
#include <time.h>
#include "Type_String.h"
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
const Float _DT_SECOND_PRECISION_RATIO = 1.0;
#elif TIME_PRECISION == 3
const Float _DT_SECOND_PRECISION_RATIO = 1e3;
#elif TIME_PRECISION == 6
const Float _DT_SECOND_PRECISION_RATIO = 1e6;
#elif TIME_PRECISION == 9
const Float _DT_SECOND_PRECISION_RATIO = 1e9;
#endif

const Int _DT_DAYS_PER_MONTH[12] = {
    31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31
};

Int _second2precision(Float s) { return (Int)(s * _DT_SECOND_PRECISION_RATIO); }

Float _precision2second(Int tp) {
    return (Float)tp / _DT_SECOND_PRECISION_RATIO;
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

struct Date Date_set_(struct Date* this, Int year, Int month, Int day) {
    this->year = year;
    this->month = month;
    this->day = day;
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
    td.methods->set_(&td, 1858, 11, 16);
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

struct Time Time_set_(struct Time* this,
                      Int          hour,
                      Int          minute,
                      Int          second
#if TIME_PRECISION > 0
                     ,
                      Int millisecond
#endif
#if TIME_PRECISION > 3
                     ,
                      Int microsecond
#endif
#if TIME_PRECISION > 6
                     ,
                      Int nanosecond
#endif
) {
    this->hour = hour;
    this->minute = minute;
    this->second = second;
#if TIME_PRECISION > 0
    this->millisecond = millisecond;
#endif
#if TIME_PRECISION > 3
    this->macrosecond = microsecond;
#endif
#if TIME_PRECISION > 6
    this->nanosecond = nanosecond;
#endif
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

struct Time Time_regularize_(struct Time* this) {
    this->minute += this->hour * 60;
    this->second += this->minute * 60;
#if TIME_PRECISION > 0
    this->millisecond += this->second * 1000;
#endif
#if TIME_PRECISION > 3
    this->macrosecond += this->millisecond * 1000;
#endif
#if TIME_PRECISION > 6
    this->nanosecond += this->macrosecond * 1000;
    this->macrosecond = this->nanosecond / 1000;
    this->nanosecond %= 1000;
#endif
#if TIME_PRECISION > 3
    this->millisecond = this->macrosecond / 1000;
    this->macrosecond %= 1000;
#endif
#if TIME_PRECISION > 0
    this->second = this->millisecond / 1000;
    this->millisecond %= 1000;
#endif
    this->minute = this->second / 60;
    this->second %= 60;
    this->hour = this->minute / 60;
    this->minute %= 60;
    return *this;
}

struct String Time_string(const struct Time* this) {
    struct String buffer;
    String_new_(&buffer);
#if TIME_PRECISION == 0
    sprintf(buffer.str, "%02d:%02d:%02d", this->hour, this->minute,
        this->second);
#elif TIME_PRECISION == 3
    sprintf(buffer.str, "%02d:%02d:%02d.%03d", this->hour, this->minute,
        this->second, this->millisecond);
#elif TIME_PRECISION == 6
    sprintf(buffer.str, "%02d:%02d:%02d.%03d%03d",
        this->hour, this->minute, this->second, this->millisecond,
        this->macrosecond);
#elif TIME_PRECISION == 9
    sprintf(buffer.str, "%02d:%02d:%02d.%03d%03d%03d",
        this->hour, this->minute, this->second, this->millisecond,
        this->macrosecond, this->nanosecond);
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
    return Time_add_(this, _second2precision(seconds));
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

    return *this;
}

struct DateTime DateTime_set_(struct DateTime* this,
                              Int              year,
                              Int              month,
                              Int              day,
                              Int              hour,
                              Int              minute,
                              Int              second
#if TIME_PRECISION > 0
                             ,
                              Int millisecond
#endif
#if TIME_PRECISION > 3
                             ,
                              Int macrosecond
#endif
#if TIME_PRECISION > 6
                             ,
                              Int nanosecond
#endif
) {
    this->date.year = year;
    this->date.month = month;
    this->date.day = day;
    this->time.hour = hour;
    this->time.minute = minute;
    this->time.second = second;
#if TIME_PRECISION > 0
    this->time.millisecond = millisecond;
#endif
#if TIME_PRECISION > 3
    this->time.macrosecond = macrosecond;
#endif
#if TIME_PRECISION > 6
    this->time.nanosecond = nanosecond;
#endif
    return *this;
}

struct DateTime DateTime_set_julian_(struct DateTime* this, Float mjdatetime) {
    Int   julian_day_number;
    Int   time_residual;
    Float temporary_julian_date_time;

    temporary_julian_date_time = mjdatetime + 0.5 - 2400000;
    julian_day_number = (Int)temporary_julian_date_time;
    time_residual = _second2precision(
        (temporary_julian_date_time - (Float)julian_day_number) * 24 * 60 * 60);
    Date_set_julian_(&(this->date), julian_day_number);
    this->time.hour = 0;
    this->time.minute = 0;
    this->time.second = 0;
#if TIME_PRECISION > 0
    this->time.millisecond = 0;
#endif
#if TIME_PRECISION > 3
    this->time.macrosecond = 0;
#endif
#if TIME_PRECISION > 6
    this->time.nanosecond = 0;
#endif
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
    return _second2precision(86400) * day_diff + time_diff;
}

Float DateTime_diff_second(const struct DateTime* this,
                           struct DateTime        datetime) {
    Int day_diff, time_diff;
    day_diff = Date_diff(&(this->date), datetime.date);
    time_diff = Time_diff(&(this->time), datetime.time);
    return 86400.0 * day_diff + _precision2second(time_diff);
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
    return DateTime_add_(this, _second2precision(seconds));
}

Float DateTime_julian(const struct DateTime* this) {
    Float       second_residual;
    struct Time tt;
    Time_new_(&tt);
    Time_zero_(&tt);
    second_residual = _precision2second(Time_diff(&(this->time), tt)) /
        (24.0 * 60.0 * 60.0);
    return (Float)Date_julian(&(this->date)) + 2400000 - 0.5 + second_residual;
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
