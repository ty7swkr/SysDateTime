# SysDateTime
A date-time class using c++11 std::chrono::system_clock

## output of example.cpp
<pre>
$ g++ example.cpp -std=c++11 -o example
$ ./example
strftime     2021-07-13 11:44:49
strftime_utc 2021-07-13 02:44:49
to_string    2021-07-13 11:44:49.810
strptime("2011-04-05 11:34:22", "%Y-%m-%d %H:%M:%S") 
2011-04-05 11:34:22

from_string("2011-04-05 11:34:22.123456789", "%Y-%m-%d %H:%M:%S.%N") 
2011-04-05 11:34:22.123456789

SysTime time = SysTime::now();     11:44:49.810481614
time  = SysTime::Hour(10);         10:44:49.810481614
time += SysTime::Hour(10);         20:44:49.810481614
time -= SysTime::Hour(10);         10:44:49.810481614
time  = SysTime::Min(67);          11:07:49.810481614
time += SysTime::Min(67);          12:14:49.810481614
time -= SysTime::Min(67);          11:07:49.810481614
time  = SysTime::Sec(15);          11:08:25.810481614
time += SysTime::Sec(15);          11:09:50.810481614
time -= SysTime::Sec(15);          11:08:25.810481614
time  = SysTime::Millisec(15);     11:08:25.015000000
time += SysTime::Millisec(15);     11:08:25.030000000
time -= SysTime::Millisec(15);     11:08:25.015000000
time  = SysTime::Microsec(15);     11:08:25.000015000
time += SysTime::Microsec(15);     11:08:25.000030000
time -= SysTime::Microsec(15);     11:08:25.000015000
time  = SysTime::Nanosec(15);      11:08:25.000000015
time += SysTime::Nanosec(15);      11:08:25.000000030
time -= SysTime::Nanosec(15);      11:08:25.000000015
time.set(SysTime::Hour(10));       10:08:25.000000015
time.add(SysTime::Hour(10));       20:08:25.000000015
time.add(SysTime::Hour(-10));      10:08:25.000000015
time.hour();     10
time.min();      8
time.sec();      25
time.millisec(); 0
time.microsec(); 0
time.nanosec();  15

SysDate date = SysDate::now();     2021-07-13
date  = SysDate::Year(2020);       2020-07-13
date += SysDate::Year(4);          2024-07-13
date -= SysDate::Year(4);          2020-07-13
date  = SysDate::Month(10);        2020-10-13
date += SysDate::Month(10);        2021-08-13
date -= SysDate::Month(10);        2020-10-13
date  = SysDate::Day(7);           2020-10-07
date += SysDate::Day(7);           2020-10-14
date -= SysDate::Day(7);           2020-10-07
date.set(SysTime::Month(10));      2020-10-07
date.add(SysTime::Month(10));      2021-08-07
date.add(SysTime::Month(-10));     2020-10-07
date.year();     2020
date.month();    10
date.day();      7

SysDateTime datetime = SysTime::now(); 2021-07-13 11:44:49.810943048
datetime = date;                   2020-10-07 11:44:49.810943048
datetime = time;                   2020-10-07 10:08:25.000000015
datetime  = SysTime::Hour(10);     2020-10-07 10:08:25.000000015
datetime += SysTime::Hour(10);     2020-10-07 20:08:25.000000015
datetime -= SysTime::Hour(10);     2020-10-07 10:08:25.000000015
datetime  = SysTime::Min(67);      2020-10-07 11:07:25.000000015
datetime += SysTime::Min(67);      2020-10-07 12:14:25.000000015
datetime -= SysTime::Min(67);      2020-10-07 11:07:25.000000015
datetime  = SysTime::Sec(15);      2020-10-07 12:25:25.000000015
datetime += SysTime::Sec(15);      2020-10-07 12:26:50.000000015
datetime -= SysTime::Sec(15);      2020-10-07 12:25:25.000000015
datetime  = SysTime::Millisec(15); 2020-10-07 12:25:25.015000000
datetime += SysTime::Millisec(15); 2020-10-07 12:25:25.030000000
datetime -= SysTime::Millisec(15); 2020-10-07 12:25:25.015000000
datetime  = SysDate::Year(2020);   2020-10-07 12:25:25.015000000
datetime += SysDate::Year(4);      2024-10-07 12:25:25.015000000
datetime -= SysDate::Year(4);      2020-10-07 12:25:25.015000000
datetime  = SysDate::Month(10);    2020-10-07 12:25:25.015000000
datetime += SysDate::Month(10);    2021-08-07 12:25:25.015000000
datetime -= SysDate::Month(10);    2020-10-07 12:25:25.015000000
datetime  = SysDate::Day(7);       2020-10-07 12:25:25.015000000
datetime += SysDate::Day(7);       2020-10-14 12:25:25.015000000
datetime -= SysDate::Day(7);       2020-10-07 12:25:25.015000000
datetime.set(SysTime::Month(10));  2020-10-07 12:25:25.015000000
datetime.add(SysTime::Month(10));  2021-08-07 12:25:25.015000000
datetime.add(SysTime::Month(-10)); 2020-10-07 12:25:25.015000000
datetime.year();     2020
datetime.month();    10
datetime.day();      7
datetime.hour();     12
datetime.min();      25
datetime.sec();      25
datetime.millisec(); 15
datetime.microsec(); 15000
datetime.nanosec();  15000000

</pre>
