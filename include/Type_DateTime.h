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

/**
 * @brief Date: year; month; day;
 */
struct Date {
    Int year, month, day;

    struct DateMethods* methods;
};

/**
 * @brief Time struct
 * @param hour Hour
 * @param minute Minute
 * @param second Second
 * @param millisecond Millisecond (possible not exit depending on time precision)
 * @param macrosecond Macrosecond (possible not exit depending on time precision)
 * @param Nanosecond Nanosecond (possible not exit depending on time precision)
 */
struct Time {
    Int hour;
    Int minute;
    Int second;
#if TIME_PRECISION > 0
    Int millisecond;
#endif
#if TIME_PRECISION > 3
    Int macrosecond;
#endif
#if TIME_PRECISION > 6
    Int nanosecond;
#endif
    struct TimeMethods* methods;
};

struct DateTime {
    struct Date date;
    struct Time time;

    struct DateTimeMethods* methods;
};

struct DateMethods {
    // # set value
    /**
    * @brief get current date
    * @param this struct Date*
    * @param type 0-GMT,1-local time
    * @return Date
    */
    struct Date (*today_)(struct Date* this, Int type);

    /**
     * @brief set date and regularize
     * @param this struct Date*
     * @param year Int
     * @param month Int
     * @param day Int
     */
    struct Date (*set_)(struct Date* this, Int year, Int month, Int day);

    /**
     * @brief set date based on modified julian day
     */
    struct Date (*set_julian_)(struct Date* this, Int mjday);

    // # options
    /**
     * @brief test if this date is before another one
     * @param this struct Date*
     * @param another const struct Date*
     */
    Bool (*lessthan)(const struct Date* this, struct Date another);

    /**
     * @brief test if this date is equal to another date
     * @param this struct Date*
     * @param another const struct Date*
     */
    Bool (*isequal)(const struct Date* this, struct Date another);

    // # calculate
    /**
     * @brief day of year. January 1st is 1
     * @param this struct Date*
     */
    Int (*day_of_year)(const struct Date* this);

    /**
     * @brief calculate date difference with another date
     * @param this const struct Date*
     * @param date struct Date
     * @return Int
     */
    Int (*diff)(const struct Date* this, struct Date date);

    /**
     * @brief modified julian date: date from 1858-11-16
     * @param this struct Date*
     */
    Int (*julian)(const struct Date* this);

    /**
     * @brief add day number
     * @param this
     * @param day Int
     * @return new date
     */
    struct Date (*add_)(struct Date* this, Int day);

    // # other
    /**
     * @brief recalculate date to make each component in normal form, such as month range in
     * @param this const struct Date*
     */
    struct Date (*regularize_)(struct Date* this);

    /**
     * @brief format date type to string, stored in `string`
     * @param this const struct Date*
     * @return struct String
     */
    struct String (*string)(const struct Date* this);
};

struct Date   Date_today_(struct Date* this, Int type);
struct Date   Date_set_(struct Date* this, Int year, Int month, Int day);
struct Date   Date_set_julian_(struct Date* this, Int mjday);
Bool          Date_less_than(const struct Date* this, struct Date another);
Bool          Date_isequal(const struct Date* this, struct Date another);
Int           Date_day_of_year(const struct Date* this);
Int           Date_diff(const struct Date* this, struct Date date);
Int           Date_julian(const struct Date* this);
struct Date   Date_add_(struct Date* this, Int day);
struct Date   Date_regularize_(struct Date* this);
struct String Date_string(const struct Date* this);


struct TimeMethods {
    struct Time (*now_)(struct Time* this, Int type);

    struct Time (*set_)(struct Time* this,
                        Int          hour,
                        Int          minute,
                        Int          second
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
    );

    /**
     * @brief set all component to zero
     */
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

    /**
     * @brief convert time struct to string and save in string
     * @param this
     * @return struct String
     */
    struct String (*string)(const struct Time* this);

    /**
     * @brief calculate time difference between two time struct
     * @param this
     * @param time
     * @return time difference in time precision
     */
    Int (*diff)(const struct Time* this, struct Time time);

    Float (*diff_second)(const struct Time* this, struct Time time);

    /**
     * @brief shift time struct by time precision
     * @param this
     * @param precision
     * @return struct Time
     */
    struct Time (*add_)(struct Time* this, Int precision);

    struct Time (*add_second_)(struct Time* this, Float seconds);
};

struct Time Time_now_(struct Time* this, Int type);
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
                      Int macrosecond
#endif
#if TIME_PRECISION > 6
                             ,
                              Int nanosecond
#endif
);
struct Time   Time_zero_(struct Time* this);
struct Time   Time_regularize_(struct Time* this);
struct String Time_string(const struct Time* this);
Int           Time_diff(const struct Time* this, struct Time time);
Float         Time_diff_second(const struct Time* this, struct Time time);
struct Time   Time_add_(struct Time* this, Int precision);
struct Time   Time_add_second_(struct Time* this, Float seconds);

/**
 * @brief DateTime struct
 * @param date Date
 * @param time Time
 */
struct DateTimeMethods {
    // # set value
    /** @brief get current date and time. Precision to Second
      * @param this struct Date*
      * @param tz 0:GMT, 1:LocalTime
      * @return DateTime
      */
    struct DateTime (*now_)(struct DateTime* this, Int tz);

    struct DateTime (*set_)(struct DateTime* this,
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
    );


    struct DateTime (*set_julian_)(struct DateTime* this, Float mjdatetime);

    /**
     * @brief regularize DateTime struct to normal range
     * @param this struct DateTime*
     * @return struct DateTime
     */
    struct DateTime (*regularize_)(struct DateTime* this);

    /**
     * @brief calculate datetime difference in time precision
     * @param this
     * @param datetime
     */
    Int (*diff)(const struct DateTime* this, struct DateTime datetime);

    Float (*diff_second)(const struct DateTime* this, struct DateTime datetime);

    /**
     * @brief shift date time by precision
     * @param this
     * @param precision
     * @return
     */
    struct DateTime (*add_)(struct DateTime* this, Int precision);

    struct DateTime (*add_second_)(struct DateTime* this, Float seconds);

    Float (*julian)(const struct DateTime* this);

    struct String (*string)(const struct DateTime* this);
};

struct DateTime DateTime_now_(struct DateTime* this, Int tz);
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
);
struct DateTime DateTime_set_julian_(struct DateTime* this, Float mjdatetime);
struct DateTime DateTime_regularize_(struct DateTime* this);
Int             DateTime_diff(const struct DateTime* this, struct DateTime datetime);
Float           DateTime_diff_second(const struct DateTime* this,
                                     struct DateTime        datetime);
struct DateTime DateTime_add_(struct DateTime* this, Int precision);
struct DateTime DateTime_add_second_(struct DateTime* this, Float seconds);
Float           DateTime_julian(const struct DateTime* this);
struct String   DateTime_string(const struct DateTime* this);

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
    this->macrosecond = 0;
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
