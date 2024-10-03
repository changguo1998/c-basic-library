#include <stdio.h>
#include <time.h>
#include "CBL_DateTime.h"


#if _TIME_PRECISION > 6
const Float _DT_SECOND_PRECISION_RATIO = 1e9;
#elif _TIME_PRECISION > 3
const Float _DT_SECOND_PRECISION_RATIO = 1e6;
#elif _TIME_PRECISION > 0
const Float _DT_SECOND_PRECISION_RATIO = 1e3;
#else
const Float _DT_SECOND_PRECISION_RATIO = 1.0;
#endif

const Int _DT_DAYS_PER_MONTH[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

TimePrecision DT_second2precision(Float s) { return (TimePrecision)(s * _DT_SECOND_PRECISION_RATIO); }

Float DT_precision2second(TimePrecision tp) { return (Float)tp / _DT_SECOND_PRECISION_RATIO; }

Date DT_today(Int tz) {
    DateTime buffer;
    buffer = DT_now(tz);
    return buffer.date;
}

Bool DT_is_leap_year(Year year) {
    if(year % 100) {
        if(year % 4) return false;
        return true;
    }
    else {
        if(year % 400) return false;
        return true;
    }
}

Day _DT_day_diff_year_to_year(Year y1, Year y2) {
    Int  number_of_leap_year;
    Year y, ya, yb;
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
    for(y = ya; y < yb; y += 1) if(DT_is_leap_year(y)) number_of_leap_year += 1;
    y = 365 * (yb - ya) + number_of_leap_year;
    if(y1 < y2) return -y;
    return y;
}

Bool DT_date_isless(Date d1, Date d2) {
    if(d1.year < d2.year) return true;
    if(d1.year > d2.year) return false;
    if(d1.month < d2.month) return true;
    if(d1.month > d2.month) return false;
    if(d1.day < d2.day) return true;
    return false;
}

Bool DT_date_isequal(Date d1, Date d2) {
    if((d1.year == d2.year) && (d1.month == d2.month) && (d1.day == d2.day)) return true;
    return false;
}

Day DT_day_of_year(Date date) {
    Day day_count = 0;
    Int i_month;
    for(i_month = 1; i_month < date.month; i_month += 1) day_count += _DT_DAYS_PER_MONTH[i_month - 1];
    day_count += date.day;
    if(DT_is_leap_year(date.year) && (date.month > 2)) day_count += 1;
    return day_count;
}

Day DT_modified_julian_date(Date date) {
    Date td;
    td.year  = 1858;
    td.month = 11;
    td.day   = 16;
    return DT_date_diff(date, td);
}

Date DT_date_from_mjd(Day julian_day_number) {
    Date buffer_date;
    Day  buffer_julian_day, residual_day_number;
    Bool is_leap_year;

    buffer_julian_day = julian_day_number + 319;
    buffer_date.year  = buffer_julian_day / 366 + 1858;

    while(true) {
        residual_day_number = buffer_julian_day - _DT_day_diff_year_to_year(buffer_date.year, 1858);
        if(residual_day_number < 0) buffer_date.year -= 1;
        else if(residual_day_number > (364 + DT_is_leap_year(buffer_date.year))) buffer_date.year += 1;
        else break;
    } // while
    buffer_date.month = 0;
    is_leap_year      = DT_is_leap_year(buffer_date.year);
    if(residual_day_number < 31) { buffer_date.month = 0; }
    else if(residual_day_number < (31 + 28 + (Day)is_leap_year)) {
        buffer_date.month = 1;
        residual_day_number -= 31;
    }
    else {
        buffer_date.month = 2;
        residual_day_number -= (31 + 28 + (Day)is_leap_year);
        while(residual_day_number >= _DT_DAYS_PER_MONTH[buffer_date.month]) {
            residual_day_number -= _DT_DAYS_PER_MONTH[buffer_date.month];
            buffer_date.month += 1;
        }
    }
    buffer_date.month += 1;
    buffer_date.day = residual_day_number + 1;
    return buffer_date;
}

Date DT_regularize_date(Date date) {
    Date buffer_date;
    Day  modified_julian_day;
    buffer_date.year    = date.year;
    buffer_date.month   = date.month;
    buffer_date.day     = 1;
    modified_julian_day = DT_modified_julian_date(buffer_date);
    modified_julian_day += date.day - 1;
    return DT_date_from_mjd(modified_julian_day);
}

void DT_date_string(Date date, char* string) { sprintf(string, "%04d-%02d-%02d", date.year, date.month, date.day); }

Day DT_date_diff(Date d1, Date d2) {
    return _DT_day_diff_year_to_year(d1.year, d2.year) + DT_day_of_year(d1) - DT_day_of_year(d2);
}

Date DT_date_plus_day(Date d, Day day) {
#ifdef _DATETIME_DEBUG_
    Day td;
    Date tdate;
    printf("(DT_date_plus_day) Date: %d-%02d-%02d\n", d.year, d.month, d.day);
    printf("(DT_date_plus_day) day: %d\n", day);
    td = DT_modified_julian_date(d);
    printf("(DT_date_plus_day) mjdate: %d\n", td);
    td += day;
    printf("(DT_date_plus_day) mjdate(d) + day: %d\n", td);
    tdate = DT_date_from_mjd(td);
    printf("(DT_date_plus_day) new date: %d-%02d-%-2d\n", tdate.year, tdate.month, tdate.day);
    td = DT_modified_julian_date(tdate);
    printf("(DT_date_plus_day) mjdate final: %d\n", td);
#endif
    return DT_date_from_mjd(DT_modified_julian_date(d) + day);
}

Time DT_zero_time() {
    Time t;
    t.hour   = 0;
    t.minute = 0;
    t.second = 0;
#if _TIME_PRECISION > 0
    t.millisecond = 0;
#endif
#if _TIME_PRECISION > 3
    t.macrosecond = 0;
#endif
#if _TIME_PRECISION > 6
    t.nanosecond = 0;
#endif
    return t;
}

Time DT_regularize_time(Time t) {
    t.minute += t.hour * 60;
    t.second += t.minute * 60;
#if _TIME_PRECISION > 0
    t.millisecond += t.second * 1000;
#endif
#if _TIME_PRECISION > 3
    t.macrosecond += t.millisecond * 1000;
#endif
#if _TIME_PRECISION > 6
    t.nanosecond += t.macrosecond * 1000;
    t.macrosecond = t.nanosecond / 1000;
    t.nanosecond %= 1000;
#endif
#if _TIME_PRECISION > 3
    t.millisecond = t.macrosecond / 1000;
    t.macrosecond %= 1000;
#endif
#if _TIME_PRECISION > 0
    t.second = t.millisecond / 1000;
    t.millisecond %= 1000;
#endif
    t.minute = t.second / 60;
    t.second %= 60;
    t.hour = t.minute / 60;
    t.minute %= 60;
    return t;
}

void DT_time_string(Time t, char* string) {
#if _TIME_PRECISION == 0
    sprintf(string, "%02d:%02d:%02d", t.hour, t.minute, t.second);
#elif _TIME_PRECISION == 3
    sprintf(string, "%02d:%02d:%02d.%03d", t.hour, t.minute, t.second, t.millisecond);
#elif _TIME_PRECISION == 6
    sprintf(string, "%02d:%02d:%02d.%03d%03d", t.hour, t.minute, t.second, t.millisecond, t.macrosecond);
#elif _TIME_PRECISION == 9
    sprintf(string, "%02d:%02d:%02d.%03d%03d%03d", t.hour, t.minute, t.second,
        t.millisecond, t.macrosecond, t.nanosecond);
#endif
}

TimePrecision DT_time_diff(Time t1, Time t2) {
    TimePrecision buf = 0;
    buf               = t1.hour - t2.hour;
    buf               = buf * 60 + t1.minute - t2.minute;
    buf               = buf * 60 + t1.second - t2.second;
#if _TIME_PRECISION > 0
    buf = buf * 1000 + t1.millisecond - t2.millisecond;
#endif
#if _TIME_PRECISION > 3
    buf = buf * 1000 + t1.macrosecond - t2.macrosecond;
#endif
#if _TIME_PRECISION > 6
    buf = buf * 1000 + t1.nanosecond - t2.nanosecond;
#endif
    return buf;
}

Time DT_time_plus_precision(Time t, TimePrecision s) {
#if _TIME_PRECISION > 6
    t.nanosecond += s;
#elif _TIME_PRECISION > 3
    t.macrosecond += s;
#elif _TIME_PRECISION > 0
    t.millisecond += s;
#else
    t.second += s;
#endif
    return DT_regularize_time(t);
}

DateTime DT_now(Int tz) {
    DateTime   buffer;
    struct tm* system_time_pointer;
    time_t     raw_time;

    time(&raw_time);

    if(tz == 0) system_time_pointer = gmtime(&raw_time);
    else system_time_pointer        = localtime(&raw_time);

    buffer.date.year   = system_time_pointer->tm_year + 1900;
    buffer.date.month  = system_time_pointer->tm_mon + 1;
    buffer.date.day    = system_time_pointer->tm_mday;
    buffer.time.hour   = system_time_pointer->tm_hour;
    buffer.time.minute = system_time_pointer->tm_min;
    buffer.time.second = system_time_pointer->tm_sec;
#if _TIME_PRECISION > 0
    buffer.time.millisecond = 0;
#endif
#if _TIME_PRECISION > 3
    buffer.time.macrosecond = 0;
#endif
#if _TIME_PRECISION > 6
    buffer.time.nanosecond = 0;
#endif
    // ! Do not need to free
    // free(ptr);

    return buffer;
}

DateTime DT_regularize_datetime(DateTime datetime) {
    DateTime buffer_datetime;
    buffer_datetime = datetime;

    buffer_datetime.time = DT_regularize_time(datetime.time);
    buffer_datetime.date.day += buffer_datetime.time.hour / 24;
    buffer_datetime.time.hour %= 24;

    buffer_datetime.time.hour += 24;
    buffer_datetime.date.day -= 1;

    buffer_datetime.time = DT_regularize_time(buffer_datetime.time);
    buffer_datetime.date.day += buffer_datetime.time.hour / 24;
    buffer_datetime.time.hour %= 24;

    buffer_datetime.date = DT_regularize_date(buffer_datetime.date);
    return buffer_datetime;
}

TimePrecision DT_datetime_diff(DateTime dt1, DateTime dt2) {
    Day           day_diff;
    TimePrecision time_diff;
    day_diff  = DT_date_diff(dt1.date, dt2.date);
    time_diff = DT_time_diff(dt1.time, dt2.time);
    return ((TimePrecision)(86400 * _DT_SECOND_PRECISION_RATIO)) * day_diff + time_diff;
}

DateTime DT_datetime_plus_precision(DateTime dt, TimePrecision s) {
#if _TIME_PRECISION > 6
    dt.time.nanosecond += s;
#elif _TIME_PRECISION > 3
    dt.time.macrosecond += s;
#elif _TIME_PRECISION > 0
    dt.time.millisecond += s;
#else
    dt.time.second += s;
#endif
    return DT_regularize_datetime(dt);
}

Float DT_datetime2julian(DateTime dt) {
    Float second_residual;
    Time  tt;
    tt              = DT_zero_time();
    second_residual = DT_precision2second(DT_time_diff(dt.time, tt)) / (24.0 * 60.0 * 60.0);
    return (Float)DT_modified_julian_date(dt.date) + 2400000 - 0.5 + second_residual;
}

DateTime DT_julian2datetime(Float julian_date_time) {
    Day julian_day_number;
    TimePrecision time_residual;
    Float temporary_julian_date_time;
    DateTime datetime;
    temporary_julian_date_time = julian_date_time + 0.5 - 2400000;
    julian_day_number = (Day)temporary_julian_date_time;
    time_residual = DT_second2precision((temporary_julian_date_time - (Float)julian_day_number) * 24 * 60 * 60);
    datetime.date = DT_date_from_mjd(julian_day_number);
    datetime.time.hour = 0;
    datetime.time.minute = 0;
    datetime.time.second = 0;
#if _TIME_PRECISION > 0
    datetime.time.millisecond = 0;
#endif
#if _TIME_PRECISION > 3
    datetime.time.macrosecond = 0;
#endif
#if _TIME_PRECISION > 6
    datetime.time.nanosecond = 0;
#endif
    return DT_datetime_plus_precision(datetime, time_residual);
}

void DT_datetime_string(DateTime dt, char* string) {
    Char date_str[32] = "", time_str[32] = "";
    DT_date_string(dt.date, date_str);
    DT_time_string(dt.time, time_str);
    sprintf(string, "%s %s", date_str, time_str);
}
