#include <stdio.h>
#include <math.h>
#include "DateTime.h"

int main(){
    DateTime dt;
    Date d;
    Time t;
    Float jd;
    printf("[test.c] begin\n");
    dt = DT_now(1);
    d = DT_today(1);

    printf("[test.c] current date: %04d-%02d-%02d\n", d.year, d.month, d.day);
    printf("[test.c] is leap year? %s\n", DT_is_leap_year(d.year) ? "True" : "False");
    printf("[test.c] Day of year: %d\n", DT_dayofyear(d));
    printf("[test.c] Modified Julian date: %d\n", DT_modified_julian_date(d));
    // d.year = 1858;
    // d.month = 11;
    // d.day = 16;
    d = DT_date_plus_day(d, 20);
    printf("[test.c] new date: %04d-%02d-%02d\n", d.year, d.month, d.day);
    printf("[test.c] Day of year: %d\n", DT_dayofyear(d));
    printf("[test.c] Modified Julian date: %d\n", DT_modified_julian_date(d));
    printf("[test.c] date isequal: %s\n", DT_date_isequal(dt.date, d) ? "True" : "False");
    printf("[test.c] date isless: %s\n", DT_date_isless(dt.date, d) ? "True" : "False");
    printf("[test.c] date diff: %d\n", DT_date_diff(d, dt.date));

    printf("[test.c] current time: %04d-%02d-%02d %02d:%02d:%02d.%03d\n",
        dt.date.year, dt.date.month, dt.date.day,
        dt.time.hour, dt.time.minute, dt.time.second, dt.time.millisecond);
    printf("[test.c] modified julian date: %d\n", DT_modified_julian_date(dt.date));
    jd = DT_datetime2julian(dt);
    printf("[test.c] julian date: %f\n", jd);
    dt = DT_julian2datetime(jd);
    printf("[test.c] back to date: %04d-%02d-%02d %02d:%02d:%02d.%03d\n",
        dt.date.year, dt.date.month, dt.date.day,
        dt.time.hour, dt.time.minute, dt.time.second, dt.time.millisecond);

    t = dt.time;
    printf("[test.c] time: %02d:%02d:%02d.%03d\n", t.hour, t.minute, t.second, t.millisecond);
    t = DT_time_plus_precision(t, DT_second2precision(300.0));
    printf("[test.c] time+500s: %02d:%02d:%02d.%03d\n", t.hour, t.minute, t.second, t.millisecond);
    dt = DT_datetime_plus_precision(dt, DT_second2precision(300.0));
    printf("[test.c] current time: %04d-%02d-%02d %02d:%02d:%02d.%03d\n",
        dt.date.year, dt.date.month, dt.date.day,
        dt.time.hour, dt.time.minute, dt.time.second, dt.time.millisecond);

    return 0;
}
