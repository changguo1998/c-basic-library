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

TimePrecision DT_second2precision(Float s) { return s * _DT_SECOND_PRECISION_RATIO; }

Float DT_precision2second(TimePrecision tp) { return ((Float)tp) / _DT_SECOND_PRECISION_RATIO; }

Date DT_today(Int tz) {
    DateTime buffer;
    buffer = DT_now(tz);
    return buffer.date;
}

bool DT_is_leap_year(Year year) {
    if(year % 100) {
        if(year % 4) return false;
        else return true;
    }
    else {
        if(year % 400) return false;
        else return true;
    }
}

Day _DT_day_diff_year_to_year(Year y1, Year y2) {
    Day dcount;
    Int nleap;
    Year y, ya, yb;
    if(y1 == y2) return (Day)0;
    if(y1 < y2) {
        ya = y1;
        yb = y2;
    }
    else {
        ya = y2;
        yb = y1;
    }
    nleap = 0;
    for(y = ya; y < yb; y += 1) if(DT_is_leap_year(y)) nleap += 1;
    y = 365 * (yb - ya) + nleap;
    if(y1 < y2) return (Day)(-y);
    else return (Day)y;
}

bool DT_date_isless(Date d1, Date d2) {
    if(d1.year < d2.year) return true;
    else if(d1.year > d2.year) return false;

    if(d1.month < d2.month) return true;
    else if(d1.month > d2.month) return false;

    if(d1.day < d2.day) return true;
    else return false;
}

bool DT_date_isequal(Date d1, Date d2) {
    if((d1.year == d2.year) && (d1.month == d2.month) && (d1.day == d2.day)) return true;
    else return false;
}

Day DT_day_of_year(Date date) {
    Day dcount = 0;
    Int imon;
    for(imon = 1; imon < date.month; imon += 1) dcount += _DT_DAYS_PER_MONTH[imon - 1];
    dcount += date.day;
    if(DT_is_leap_year(date.year) && (date.month > 2)) dcount += 1;
    return dcount;
}

Day DT_modified_julian_date(Date date) {
    Date td;
    td.year = 1858;
    td.month = 11;
    td.day = 16;
    return DT_date_diff(date, td);
}

Date DT_date_from_mjd(Day daynum) {
    Date tdate;
    Day tdaynum, dayres, isleapyear;
#ifdef _DATETIME_DEBUG_
    printf("(DT_date_from_mjd) \n");
    printf("(DT_date_from_mjd) daynum: %d\n", daynum);
#endif
    tdaynum = daynum + 319;
#ifdef _DATETIME_DEBUG_
    printf("(DT_date_from_mjd) tdaynum: %d\n", tdaynum);
#endif
    tdate.year = tdaynum / 366 + 1858;

    while(true) {
        dayres = tdaynum - _DT_day_diff_year_to_year(tdate.year, 1858);
#ifdef _DATETIME_DEBUG_
        printf("(DT_date_from_mjd) tdate.year: %d\n", tdate.year);
        printf("(DT_date_from_mjd) dayres: %d\n", dayres);
#endif
        if(dayres < 0) tdate.year -= 1;
        else if(dayres > (364 + DT_is_leap_year(tdate.year))) tdate.year += 1;
        else break;
    } // while
    tdate.month = 0;
    isleapyear = DT_is_leap_year(tdate.year);
    if(dayres < 31) { tdate.month = 0; }
    else if(dayres < (31 + 28 + isleapyear)) {
        tdate.month = 1;
        dayres -= 31;
    }
    else {
        tdate.month = 2;
        dayres -= (31 + 28 + isleapyear);
        while(dayres >= _DT_DAYS_PER_MONTH[tdate.month]) {
            dayres -= _DT_DAYS_PER_MONTH[tdate.month];
            tdate.month += 1;
        }
    }
#ifdef _DATETIME_DEBUG_
    printf("(DT_date_from_mjd) tdate.month: %d\n", tdate.month);
    printf("(DT_date_from_mjd) dayres: %d\n", dayres);
#endif
    tdate.month += 1;
    tdate.day = dayres + 1;
    return tdate;
}

Date DT_regularize_date(Date d) {
    Date td;
    Day tmjd;
    td.year = d.year;
    td.month = d.month;
    td.day = 1;
    tmjd = DT_modified_julian_date(td);
    tmjd += d.day - 1;
    return DT_date_from_mjd(tmjd);
}

Day DT_date_diff(Date d1, Date d2) {
#ifdef _DATETIME_DEBUG_
    // printf("(DT_date_diff) d1: %d-%02d-%02d\n", d1.year, d1.month, d1.day);
    // printf("(DT_date_diff) day of year 1: %d\n", DT_day_of_year(d1));
    // printf("(DT_date_diff) d2: %d-%02d-%02d\n", d2.year, d2.month, d2.day);
    // printf("(DT_date_diff) day of year 2: %d\n", DT_day_of_year(d2));
    // printf("(DT_date_diff) _DT_day_diff_year_to_year: %d\n",
    //     _DT_day_diff_year_to_year(d1.year, d2.year));
#endif
    return (Day)(_DT_day_diff_year_to_year(d1.year, d2.year) + DT_day_of_year(d1) - DT_day_of_year(d2));
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
    t.hour = 0;
    t.minute = 0;
    t.second = 0;
#if _TIME_PRECISION > 0
    t.millisecond = 0;
#endif
#if _TIME_PRECISION > 3
    t.macrosecond =0;
#endif
#if _TIME_PRECISION > 6
    t.nanosecond  =0;
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
    t.macrosecond += t.millisecond*1000;
#endif
#if _TIME_PRECISION > 6
    t.nanosecond  += t.macrosecond*1000;
    t.macrosecond = t.nanosecond/1000;  t.nanosecond  %= 1000;
#endif
#if _TIME_PRECISION > 3
    t.millisecond = t.macrosecond/1000; t.macrosecond %= 1000;
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

TimePrecision DT_time_diff(Time t1, Time t2) {
    TimePrecision buf = 0;
    buf = t1.hour - t2.hour;
    buf = buf * 60 + t1.minute - t2.minute;
    buf = buf * 60 + t1.second - t2.second;
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
    DateTime buffer;
    struct tm* ptr = NULL;
    time_t rawtime;

    time(&rawtime);
#ifdef _DATETIME_DEBUG_
    // printf("(DT_now) ptr: %lX\n", ptr);
    // printf("(DT_now) rawtime: %ld\n", rawtime);
    // printf("(DT_now) tz: %d\n", tz);
#endif
    if(tz == 0) ptr = gmtime(&rawtime);
    else ptr = localtime(&rawtime);
#ifdef _DATETIME_DEBUG_
    // printf("(DT_now) ptr: %lX\n", ptr);
#endif
    buffer.date.year = ptr->tm_year + 1900;
    buffer.date.month = ptr->tm_mon + 1;
    buffer.date.day = ptr->tm_mday;
    buffer.time.hour = ptr->tm_hour;
    buffer.time.minute = ptr->tm_min;
    buffer.time.second = ptr->tm_sec;

#ifdef _DATETIME_DEBUG_
    // printf("(DT_now) year  : %d\n", buffer.date.year);
    // printf("(DT_now) month : %d\n", buffer.date.month);
    // printf("(DT_now) day   : %d\n", buffer.date.day);
    // printf("(DT_now) hour  : %d\n", buffer.time.hour);
    // printf("(DT_now) minute: %d\n", buffer.time.minute);
    // printf("(DT_now) second: %d\n", buffer.time.second);
#endif

#if _TIME_PRECISION > 0
    buffer.time.millisecond = 0;
#ifdef _DATETIME_DEBUG_
    printf("(DT_now) millisecond: %d\n", buffer.time.millisecond);
#endif
#endif


#if _TIME_PRECISION > 3
    buffer.time.macrosecond = 0;
#ifdef _DATETIME_DEBUG_
    printf("(DT_now) macrosecond: %d\n", buffer.time.macrosecond);
#endif
#endif

#if _TIME_PRECISION > 6
    buffer.time.nanosecond = 0;
#ifdef _DATETIME_DEBUG_
    printf("(DT_now) nanosecond: %d\n", buffer.time.nanosecond);
#endif
#endif
    // ! Do not need to free
    // free(ptr);

    return buffer;
}

DateTime DT_regularize_datetime(DateTime datetime) {
    DateTime buf;
    // memcpy(&buf, &datetime, sizeof(DateTime));
    buf = datetime;

    buf.time = DT_regularize_time(datetime.time);
    buf.date.day += buf.time.hour / 24;
    buf.time.hour %= 24;

    buf.time.hour += 24;
    buf.date.day -= 1;

    buf.time = DT_regularize_time(buf.time);
    buf.date.day += buf.time.hour / 24;
    buf.time.hour %= 24;

    buf.date = DT_regularize_date(buf.date);
    return buf;
}

TimePrecision DT_datetime_diff(DateTime dt1, DateTime dt2) {
    Day daydiff;
    TimePrecision timediff;
    daydiff = DT_date_diff(dt1.date, dt2.date);
    timediff = DT_time_diff(dt1.time, dt2.time);
    return ((TimePrecision)(86400 * _DT_SECOND_PRECISION_RATIO)) * daydiff + timediff;
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
    Float prec;
    Time tt;
    tt.hour = 0;
    tt.minute = 0;
    tt.second = 0;
#if _TIME_PRECISION > 0
    tt.millisecond = 0;
#endif
#if _TIME_PRECISION > 3
    tt.macrosecond = 0;
#endif
#if _TIME_PRECISION > 6
    tt.nanosecond = 0;
#endif
    prec = DT_precision2second(DT_time_diff(dt.time, tt)) / (24.0 * 60.0 * 60.0);
    return (Float)DT_modified_julian_date(dt.date) + 2400000 - 0.5 + prec;
}

DateTime DT_julian2datetime(Float jn) {
    Day rdays;
    TimePrecision dt;
    Float tj;
    DateTime buf;
    tj = jn + 0.5 - 2400000;
    rdays = (Day)tj;
    dt = DT_second2precision((tj - (Float)rdays) * 24 * 60 * 60);
    buf.date = DT_date_from_mjd(rdays);
    buf.time.hour = 0;
    buf.time.minute = 0;
    buf.time.second = 0;
#if _TIME_PRECISION > 0
    buf.time.millisecond = 0;
#endif
#if _TIME_PRECISION > 3
    buf.time.macrosecond = 0;
#endif
#if _TIME_PRECISION > 6
    buf.time.nanosecond = 0;
#endif
    return DT_datetime_plus_precision(buf, dt);
}
