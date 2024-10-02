// @copyright

#ifndef _CBL_DATETIME_H_
#define _CBL_DATETIME_H_

#include "CBL_Basic.h"

// #define _DATETIME_DEBUG_

typedef Int Year;
typedef Int Month;
typedef Int Day;
typedef Int Hour;
typedef Int Minute;
typedef Int Second;

#if _TIME_PRECISION > 0
typedef Int Millisecond;
#endif

#if _TIME_PRECISION > 3
typedef Int Macrosecond;
#endif

#if _TIME_PRECISION > 6
typedef Int Nanosecond;
#endif

#if _TIME_PRECISION > 6
typedef Nanosecond TimePrecision;
#elif _TIME_PRECISION > 3
typedef Macrosecond TimePrecision;
#elif _TIME_PRECISION > 0
typedef Millisecond TimePrecision;
#else
typedef Second TimePrecision;
#endif

TimePrecision DT_second2precision(Float s);

Float DT_precision2second(TimePrecision tp);

typedef struct _DT_date_t {
    Year year;
    Month month;
    Day day;
} Date;

/// @brief get current date
/// @param tz 0-GMT,1-local time
/// @return Date
Date DT_today(Int tz);

/// @brief test if is leap year
/// @param y
/// @return bool
Bool DT_is_leap_year(Year y);

/// @brief test if date1 < date2
/// @param d1 date1
/// @param d2 date2
/// @return bool: d1 < d2
Bool DT_date_isless(Date d1, Date d2);

/// @brief test if date1 == date2
/// @param d1 date1
/// @param d2 date2
/// @return bool: d1 == d2
Bool DT_date_isequal(Date d1, Date d2);

/// @brief day of year. January 1st is 1
/// @param date
/// @return Day
Day DT_day_of_year(Date date);

/// @brief modified julian date: date from 1858-11-16
/// @param date
/// @return Day
Day DT_modified_julian_date(Date date);

/// @brief date struct from modified julian date
/// @param daynum
/// @return Date
Date DT_date_from_mjd(Day daynum);

Date DT_regularize_date(Date d);

/// @brief date difference from d1 and d2. return d1-d2
/// @param d1
/// @param d2
/// @return Day
Day DT_date_diff(Date d1, Date d2);

Date DT_date_plus_day(Date d, Day day);

typedef struct _DT_time_t {
    Hour hour;
    Minute minute;
    Second second;
#if _TIME_PRECISION > 0
    Millisecond millisecond;
#endif
#if _TIME_PRECISION > 3
    Macrosecond macrosecond;
#endif
#if _TIME_PRECISION > 6
    Nanosecond nanosecond;
#endif
} Time;

Time DT_zero_time();

Time DT_regularize_time(Time t);

TimePrecision DT_time_diff(Time t1, Time t2);

Time DT_time_plus_precision(Time t, TimePrecision s);

typedef struct _DT_datetime_t {
    Date date;
    Time time;
} DateTime;

/// @brief get current date and time. Precision to Second
/// @param tz 0:GMT, 1:LocalTime
/// @return DateTime
DateTime DT_now(Int tz);

DateTime DT_regularize_datetime(DateTime datetime);

TimePrecision DT_datetime_diff(DateTime dt1, DateTime dt2);

DateTime DT_datetime_plus_precision(DateTime dt, TimePrecision s);

Float DT_datetime2julian(DateTime dt);

DateTime DT_julian2datetime(Float jn);

#endif // _CBL_DATETIME_H_
