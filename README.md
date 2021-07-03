# SystemTime
A date-time class using c++11 std::chrono::system_clock
* Compilers that support C++11

### example
<pre>
<code>
#include "SystemTime.h"
#include &#60;iostream&#62;

using namespace std;

int main(void)
{
  // ********* initialization *********
  {
    SystemTime system_time1 = SystemTime::now();
    SystemTime system_time2 = std::chrono::system_clock::now();
    SystemTime system_time3 = time(NULL);

    struct timespec ts;
    clock_gettime(CLOCK_REALTIME, &ts);
    SystemTime system_time4 = ts;

    struct timeval tv;
    gettimeofday(&tv, NULL);
    SystemTime system_time5 = tv;
    SystemTime system_time  = SystemTime::now();
  }

  SystemTime system_time  = SystemTime::now();

  // ********* conversion *********
  {
    time_t          time_t_v  = system_time.to_time_t();
    std::tm         tm_value  = system_time.to_tm();
    struct timespec ts        = system_time.to_timespec();
    struct timeval  tv        = system_time.to_timeval();
    std::chrono::system_clock::time_point time_pont = system_time.time_point();
  }

  std::cout << system_time.strftime() << std::endl;
  std::cout << system_time.to_string() << std::endl;

  // ********* parsing *********
  {
    system_time.strptime("2011-04-05 11:34:22", "%Y-%m-%d %H:%M:%S");
    system_time.from_string("2011-04-05 11:34:22.123456789", "%Y-%m-%d %H:%M:%S.%N");
  }

  // ********* set time *********
  {
    system_time.set_current();
    system_time.set_date(2011, 4, 3);
    system_time.set_time(11, 44, 21);
    system_time.set_time(11, 44, 21, SystemTime::Millisec(123));
    system_time.set_time(11, 44, 21, SystemTime::Microsec(123456));
    system_time.set_time(11, 44, 21, SystemTime::Nanosec (123456789));
    system_time.set_datetime(2021, 3, 1, 11, 44, 21);
    system_time.set_datetime(2021, 3, 1, 11, 44, 21, SystemTime::Millisec(123));
    system_time.set_datetime(2021, 3, 1, 11, 44, 21, SystemTime::Microsec(123456));
    system_time.set_datetime(2021, 3, 1, 11, 44, 21, SystemTime::Nanosec (123456789));

    system_time = system_time.first_time_of_day();
    system_time = system_time.first_day_of_month();
    system_time = system_time.first_time_of_month();

    system_time = system_time.last_time_of_day();
    system_time = system_time.last_day_of_month();
    system_time = system_time.last_time_of_month();
  }

  // ********* operation *********
  {
    // classes for operation : Year, Month, Day, Hour, Min, Sec, Millisec, Microsec, Nanosec
    system_time.set(SystemTime::Month(5));
    system_time.add(SystemTime::Sec(86400));

    system_time = SystemTime::Year(2014);
    system_time = system_time + SystemTime::Month(5);
    system_time = system_time - SystemTime::Day(360);

    system_time += SystemTime::Month(5);
    system_time -= SystemTime::Day(360);
  }

  cout << system_time.to_string() << endl;
  cout << system_time.year()      << endl;
  cout << system_time.month()     << endl;
  cout << system_time.day()       << endl;
  cout << system_time.hour()      << endl;
  cout << system_time.min()       << endl;
  cout << system_time.sec()       << endl;
  cout << system_time.millisec()  << endl;
  cout << system_time.microsec()  << endl;
  cout << system_time.nanosec()   << endl;

  return 0;
}
</code>
</pre>

## output of example.cpp
<pre>
$ g++ example.cpp -std=c++11 -o example
$ ./example
strftime 
2021-07-03 11:23:21

to_string 
2021-07-03 11:23:21.247

strptime("2011-04-05 11:34:22", "%Y-%m-%d %H:%M:%S") 
2011-04-05 11:34:22

from_string("2011-04-05 11:34:22.123456789", "%Y-%m-%d %H:%M:%S.%N") 
2011-04-05 11:34:22.123456789

set_current 
2021-07-03 11:23:21.247

set_date(2011, 4, 3) 
2011-04-03 11:23:21.247

set_time(11, 44, 21) 
2011-04-03 11:44:21.000

set_time(11, 44, 21, SystemTime::Millisec(123)) 
2011-04-03 11:44:21.123

set_time(11, 44, 21, SystemTime::Microsec(3456)) 
2011-04-03 11:44:21.003456

set_time(11, 44, 21, SystemTime::Nanosec(3456789)) 
2011-04-03 11:44:21.003456789

set_datetime(2021, 3, 1, 11, 44, 21) 
2021-03-01 11:44:21

set_datetime(2021, 3, 1, 11, 44, 21, SystemTime::Millisec(123)) 
2021-03-01 11:44:21.123

set_datetime(2021, 3, 1, 11, 44, 21, SystemTime::Microsec(3456)) 
2021-03-01 11:44:21.003456

set_datetime(2021, 3, 1, 11, 44, 21, SystemTime::Microsec(3456789)) 
2021-03-01 11:44:21.003456789

first_time_of_day 
2021-07-03 00:00:00.000

first_day_of_month 
2021-07-01 11:23:21.248

first_time_of_month 
2021-07-01 00:00:00.000

last_time_of_day 
2021-07-03 23:59:59.999

last_day_of_month 
2021-07-31 11:23:21.248

last_time_of_month 
2021-07-31 23:59:59.999

set(SystemTime::Month(5)) 
2021-05-03 11:23:21.248

system_time = SystemTime::Month(5) 
2021-05-03 11:23:21.248

add(SystemTime::Sec(88400)) 
2021-07-04 11:56:41.248

system_time = system_time.set_current() + SystemTime::Month(15) 
2022-10-03 11:23:21.248

system_time = system_time.set_current() - SystemTime::Day(300) 
2020-09-06 11:23:21.248

system_time += SystemTime::Month(5) 
2021-12-03 11:23:21.248

system_time -= SystemTime::Day(360) 
2020-07-08 11:23:21.248

2021-07-03 11:23:21.248
year     2021
month    7
day      3
hour     11
min      23
sec      21
millisec 248
microsec 248917
nanosec  248917743
</pre>
