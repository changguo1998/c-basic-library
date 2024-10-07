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

/**
 * @brief convert time length in seconds to same period with TimePrecision count
 * @param s in seconds
 * @return count in TimePrecision
 */
TimePrecision DT_second2precision(Float s);

/**
 * @brief convert time length in TimePrecision count to seconds
 * @param tp time in TimePrecision
 * @return time length in seconds in Float type
 */
Float DT_precision2second(TimePrecision tp);

/**
 * @brief Date: year; month; day;
 * @param year Year
 * @param month Month range: 1 - 12
 * @param day Day
 */
typedef struct _DT_date_t {
    Year  year; /**< year */
    Month month; /**< month */
    Day   day; /**< day */
} Date;

/**
 * @brief get current date
 * @param tz 0-GMT,1-local time
 * @return Date
 */
Date DT_today(Int tz);

/**
 * @brief test if is leap year
 * @param year
 * @return true if year is leap
 */
Bool DT_is_leap_year(Year year);

/**
 * @brief test if date1 < date2
 * @param d1 date1
 * @param d2 date2
 * @return Bool: d1 < d2
 */
Bool DT_date_isless(Date d1, Date d2);

/**
 * @brief test if date1 == date2
 * @param d1 date1
 * @param d2 date2
 * @return true if d1 == d2
 */
Bool DT_date_isequal(Date d1, Date d2);

/**
 * @brief day of year. January 1st is 1
 * @param date
 * @return Day
 */
Day DT_day_of_year(Date date);

/**
 * @brief modified julian date: date from 1858-11-16
 * @param date
 * @return Day
 */
Day DT_modified_julian_date(Date date);

/**
 * @brief get date struct from modified julian date
 * @param julian_day_number
 * @return Date
 */
Date DT_date_from_mjd(Day julian_day_number);

/**
 * @brief recalculate date to make each component in normal form, such as month range in
 * @param date input date
 * @return
 */
Date DT_regularize_date(Date date);

/**
 * @brief format date type to string, stored in `string`
 * @param date Date input
 * @param string string buffer to save string format date
 */
void DT_date_string(Date date, Char* string);

/**
 * @brief date difference from d1 and d2. return d1-d2
 * @param d1
 * @param d2
 * @return Day
 */
Day DT_date_diff(Date d1, Date d2);


/**
 * @brief shift day according to date
 * @param d Date
 * @param day Day
 * @return shifted date
 */
Date DT_date_plus_day(Date d, Day day);


/**
 * @brief Time struct
 * @param hour Hour
 * @param minute Minute
 * @param second Second
 * @param millisecond Millisecond (possible not exit depending on time precision)
 * @param macrosecond Macrosecond (possible not exit depending on time precision)
 * @param Nanosecond Nanosecond (possible not exit depending on time precision)
 */
typedef struct _DT_time_t {
    Hour   hour;
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


/**
 * @brief initialize Time struct with all zero
 * @return
 */
Time DT_zero_time();


/**
 * @brief  regularize time struct to make the time satisfy normal range \n
 * 0 <= minute < 60 \n
 * 0 <= second < 60 \n
 * 0 <= millisecond < 1000 \n
 * 0 <= macrosecond < 1000 \n
 * 0 <= nanosecond  < 1000 \n
 * @param t
 * @return
 */
Time DT_regularize_time(Time t);


/**
 * @brief convert time struct to string and save in string
 * @param t
 * @param string char*
 */
void DT_time_string(Time t, Char* string);

/**
 * @brief calculate time difference between two time struct
 * @param t1
 * @param t2
 * @return time difference in time precision
 */
TimePrecision DT_time_diff(Time t1, Time t2);

/**
 * @brief shift time struct by time precision
 * @param t
 * @param s
 * @return
 */
Time DT_time_plus_precision(Time t, TimePrecision s);

/**
 * @brief DateTime struct
 * @param date Date
 * @param time Time
 */
typedef struct _DT_datetime_t {
    Date date;
    Time time;
} DateTime;

/** @brief get current date and time. Precision to Second
  * @param tz 0:GMT, 1:LocalTime
  * @return DateTime
  */
DateTime DT_now(Int tz);

/**
 * @brief regularize DateTime struct to normal range
 * @param datetime
 * @return
 */
DateTime DT_regularize_datetime(DateTime datetime);

/**
 * @brief calculate datetime difference in time precision
 * @param dt1
 * @param dt2
 * @return
 */
TimePrecision DT_datetime_diff(DateTime dt1, DateTime dt2);

/**
 * @brief shift date time by precision
 * @param dt
 * @param s
 * @return
 */
DateTime DT_datetime_plus_precision(DateTime dt, TimePrecision s);

/**
 * @brief calculate julian date number from datetime
 * @param dt
 * @return
 */
Float DT_datetime2julian(DateTime dt);

/**
 * @brief convert julian date number to DateTime struct
 * @param julian_date_time
 * @return
 */
DateTime DT_julian2datetime(Float julian_date_time);

/**
 * @brief convert DateTime to string
 * @param dt
 * @param string
 */
void DT_datetime_string(DateTime dt, Char* string);

#endif // _CBL_DATETIME_H_
