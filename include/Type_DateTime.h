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

#ifndef _CBL_DATETIME_H_
#define _CBL_DATETIME_H_

#include "Module_Basic.h"
#include "Type_String.h"


extern struct DateMethods     _CBL_DATE_METHODS;
extern struct TimeMethods     _CBL_TIME_METHODS;
extern struct DateTimeMethods _CBL_DATETIME_METHODS;

Bool _DATETIME_is_leap_year(Int year);

Int DateTime_second2precision(Float s);

Float DateTime_precision2second(Int tp);

struct DateMethods {
    // # io

    void (*read_)(struct Date* this, FILE* fp);
    void (*write_)(struct Date* this, FILE* fp);

    // # set value

    // 0-GMT,1-local time
    struct Date (*today_)(struct Date* this, Int type);
    struct Date (*set_)(struct Date* this, Int n, ...);
    struct Date (*set_julian_)(struct Date* this, Int mjday);

    // # options
    Bool (*lessthan)(const struct Date* this, struct Date another);
    Bool (*isequal)(const struct Date* this, struct Date another);

    // # calculate

    // day of year. January 1st is 1
    Int (*day_of_year)(const struct Date* this);
    Int (*diff)(const struct Date* this, struct Date date);

    // modified julian date: date from 1858-11-16
    Int (*        julian)(const struct Date* this);
    struct Date (*add_)(struct Date* this, Int day);

    // # other
    struct Date (*regularize_)(struct Date* this);
    void (*       string)(const struct Date* this, struct String* str);
};

void        Date_read_(struct Date* this, FILE* fp);
void        Date_write_(struct Date* this, FILE* fp);
struct Date Date_today_(struct Date* this, Int type);
struct Date Date_set_(struct Date* this, Int n, ...);
struct Date Date_set_julian_(struct Date* this, Int mjday);
Bool        Date_lessthan(const struct Date* this, struct Date another);
Bool        Date_isequal(const struct Date* this, struct Date another);
Int         Date_day_of_year(const struct Date* this);
Int         Date_diff(const struct Date* this, struct Date date);
Int         Date_julian(const struct Date* this);
struct Date Date_add_(struct Date* this, Int day);
struct Date Date_regularize_(struct Date* this);
void        Date_string(const struct Date* this, struct String* str);


struct TimeMethods {
    void (*read_)(struct Time* this, FILE* fp);
    void (*write_)(struct Time* this, FILE* fp);
    struct Time (*now_)(struct Time* this, Int type);
    struct Time (*set_)(struct Time* this, Int n, ...);
    struct Time (*zero_)(struct Time* this);

    /**
     * @brief  regularize time struct to make the time satisfy normal range \n
     * 0 <= minute < 60 \n
     * 0 <= second < 60 \n
     * 0 <= millisecond < 1000 \n
     * 0 <= macrosecond < 1000 \n
     * 0 <= nanosecond  < 1000 \n
     * @param this
     * @return struct Time
     */
    struct Time (*regularize_)(struct Time* this);
    void (*       string)(const struct Time* this, struct String* str);
    Int (*        diff)(const struct Time* this, struct Time time);
    Float (*      diff_second)(const struct Time* this, struct Time time);
    Bool (*       lessthan)(const struct Time* this, struct Time another);
    Bool (*       isequal)(const struct Time* this, struct Time another);
    struct Time (*add_)(struct Time* this, Int precision);
    struct Time (*add_second_)(struct Time* this, Float seconds);
};

void        Time_read_(struct Time* this, FILE* fp);
void        Time_write_(struct Time* this, FILE* fp);
struct Time Time_now_(struct Time* this, Int type);
struct Time Time_set_(struct Time* this, Int n, ...);
struct Time Time_zero_(struct Time* this);
struct Time Time_regularize_(struct Time* this);
void        Time_string(const struct Time* this, struct String* str);
Int         Time_diff(const struct Time* this, struct Time time);
Float       Time_diff_second(const struct Time* this, struct Time time);
Bool        Time_lessthan(const struct Time* this, struct Time another);
Bool        Time_isequal(const struct Time* this, struct Time another);
struct Time Time_add_(struct Time* this, Int precision);
struct Time Time_add_second_(struct Time* this, Float seconds);

/**
 * @brief DateTime struct
 * @param date Date
 * @param time Time
 */
struct DateTimeMethods {
    // # io

    void (*read_)(struct DateTime* this, FILE* fp);
    void (*write_)(struct DateTime* this, FILE* fp);

    // # set value
    //* 0:GMT, 1:LocalTime
    struct DateTime (*now_)(struct DateTime* this, Int tz);
    struct DateTime (*set_)(struct DateTime* this, Int n, ...);
    struct DateTime (*set_julian_)(struct DateTime* this, Float mjdatetime);
    struct DateTime (*regularize_)(struct DateTime* this);
    Int (*            diff)(const struct DateTime* this, struct DateTime datetime);
    Float (*          diff_second)(const struct DateTime* this, struct DateTime datetime);
    Bool (*           lessthan)(const struct DateTime* this, struct DateTime another);
    Bool (*           isequal)(const struct DateTime* this, struct DateTime another);
    struct DateTime (*add_)(struct DateTime* this, Int precision);
    struct DateTime (*add_second_)(struct DateTime* this, Float seconds);
    Float (*          julian)(const struct DateTime* this);
    void (*           string)(const struct DateTime* this, struct String* str);
};

void        DateTime_read_(struct DateTime* this, FILE* fp);
void        DateTime_write_(struct DateTime* this, FILE* fp);
struct DateTime DateTime_now_(struct DateTime* this, Int tz);
struct DateTime DateTime_set_(struct DateTime* this, Int n, ...);
struct DateTime DateTime_set_julian_(struct DateTime* this, Float mjdatetime);
struct DateTime DateTime_regularize_(struct DateTime* this);
Int             DateTime_diff(const struct DateTime* this, struct DateTime datetime);
Float           DateTime_diff_second(const struct DateTime* this,
                           struct DateTime                  datetime);
Bool            DateTime_lessthan(const struct DateTime* this, struct DateTime another);
Bool            DateTime_isequal(const struct DateTime* this, struct DateTime another);
struct DateTime DateTime_add_(struct DateTime* this, Int precision);
struct DateTime DateTime_add_second_(struct DateTime* this, Float seconds);
Float           DateTime_julian(const struct DateTime* this);
void            DateTime_string(const struct DateTime* this, struct String* str);

static inline void Date_new_(struct Date* this) {
    this->year = this->month = this->day = 0;
    this->methods = &_CBL_DATE_METHODS;
}

static inline void Time_new_(struct Time* this) {
    this->hour = this->minute = this->second = 0;
#if TIME_PRECISION > 0
    this->millisecond = 0;
#endif
#if TIME_PRECISION > 3
    this->microsecond = 0;
#endif
#if TIME_PRECISION > 6
    this->nanosecond = 0;
#endif
    this->methods = &_CBL_TIME_METHODS;
}

static inline void DateTime_new_(struct DateTime* this) {
    Date_new_(&this->date);
    Time_new_(&this->time);
    this->methods = &_CBL_DATETIME_METHODS;
}

#endif // _CBL_DATETIME_H_
