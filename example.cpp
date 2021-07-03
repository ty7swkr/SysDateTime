#include "SystemTime.h"

#include <iostream>
#include <unistd.h>
#include <sys/time.h>

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

  system_time.strftime();
  cout << "strftime \n" << system_time.strftime() << endl << endl;
  cout << "to_string \n" << system_time.to_string() << endl << endl;

  // ********* parsing *********
  {
    system_time.strptime("2011-04-05 11:34:22", "%Y-%m-%d %H:%M:%S");
    cout << "strptime(\"2011-04-05 11:34:22\", \"%Y-%m-%d %H:%M:%S\") \n" << system_time.strftime() << endl << endl;

    system_time.from_string("2011-04-05 11:34:22.123456789", "%Y-%m-%d %H:%M:%S.%N");
    cout << "from_string(\"2011-04-05 11:34:22.123456789\", \"%Y-%m-%d %H:%M:%S.%N\") \n"
         << system_time.to_string("%Y-%m-%d %H:%M:%S.%N") << endl << endl;
  }

  // ********* set time *********
  {
    system_time.set_current();
    cout << "set_current \n" << system_time.to_string() << endl << endl;

    system_time.set_date(2011, 4, 3);
    cout << "set_date(2011, 4, 3) \n" << system_time.to_string() << endl << endl;

    system_time.set_time(11, 44, 21);
    cout << "set_time(11, 44, 21) \n" << system_time.to_string() << endl << endl;

    system_time.set_time(11, 44, 21, SystemTime::Millisec(123));
    cout << "set_time(11, 44, 21, SystemTime::Millisec(123)) \n"
         << system_time.to_string() << endl << endl;

    system_time.set_time(11, 44, 21, SystemTime::Microsec(3456));
    cout << "set_time(11, 44, 21, SystemTime::Microsec(3456)) \n"
         << system_time.to_string("%Y-%m-%d %H:%M:%S.%K") << endl << endl;

    system_time.set_time(11, 44, 21, SystemTime::Nanosec (3456789));
    cout << "set_time(11, 44, 21, SystemTime::Nanosec(3456789)) \n"
         << system_time.to_string("%Y-%m-%d %H:%M:%S.%N") << endl << endl;

    system_time.set_datetime(2021, 3, 1, 11, 44, 21);
    cout << "set_datetime(2021, 3, 1, 11, 44, 21) \n"
         << system_time.to_string("%Y-%m-%d %H:%M:%S") << endl << endl;

    system_time.set_datetime(2021, 3, 1, 11, 44, 21, SystemTime::Millisec(123));
    cout << "set_datetime(2021, 3, 1, 11, 44, 21, SystemTime::Millisec(123)) \n"
         << system_time.to_string("%Y-%m-%d %H:%M:%S.%L") << endl << endl;

    system_time.set_datetime(2021, 3, 1, 11, 44, 21, SystemTime::Microsec(3456));
    cout << "set_datetime(2021, 3, 1, 11, 44, 21, SystemTime::Microsec(3456)) \n"
         << system_time.to_string("%Y-%m-%d %H:%M:%S.%K") << endl << endl;

    system_time.set_datetime(2021, 3, 1, 11, 44, 21, SystemTime::Nanosec (3456789));
    cout << "set_datetime(2021, 3, 1, 11, 44, 21, SystemTime::Microsec(3456789)) \n"
         << system_time.to_string("%Y-%m-%d %H:%M:%S.%N") << endl << endl;

    system_time = SystemTime().set_current().first_time_of_day();
    cout << "first_time_of_day \n"
         << system_time.to_string() << endl << endl;

    system_time = SystemTime().set_current().first_day_of_month();
    cout << "first_day_of_month \n"
         << system_time.to_string() << endl << endl;

    system_time = SystemTime().set_current().first_time_of_month();
    cout << "first_time_of_month \n"
         << system_time.to_string() << endl << endl;

    system_time = SystemTime().set_current().last_time_of_day();
    cout << "last_time_of_day \n"
         << system_time.to_string() << endl << endl;

    system_time = SystemTime().set_current().last_day_of_month();
    cout << "last_day_of_month \n"
         << system_time.to_string() << endl << endl;

    system_time = SystemTime().set_current().last_time_of_month();
    cout << "last_time_of_month \n"
         << system_time.to_string() << endl << endl;
  }

  // ********* operation *********
  {
    // Year, Month, Day, Hour, Min, Sec, Millisec, Microsec, Nanosec, time_t, tm, timespec, timeval
    system_time = SystemTime::now();
    system_time.set(SystemTime::Month(5));
    cout << "set(SystemTime::Month(5)) \n"
         << system_time.to_string() << endl << endl;

    system_time = SystemTime::now();
    system_time = SystemTime::Month(5);
    cout << "system_time = SystemTime::Month(5) \n"
         << system_time.to_string() << endl << endl;

    system_time = SystemTime::now();
    system_time.add(SystemTime::Sec(88400));
    cout << "add(SystemTime::Sec(88400)) \n"
         << system_time.to_string() << endl << endl;

    system_time = system_time.set_current() + SystemTime::Month(15);
    cout << "system_time = system_time.set_current() + SystemTime::Month(15) \n"
         << system_time.to_string() << endl << endl;

    system_time = system_time.set_current() - SystemTime::Day(300);
    cout << "system_time = system_time.set_current() - SystemTime::Day(300) \n"
         << system_time.to_string() << endl << endl;

    system_time = SystemTime::now();
    system_time += SystemTime::Month(5);
    cout << "system_time += SystemTime::Month(5) \n"
         << system_time.to_string() << endl << endl;

    system_time = SystemTime::now();
    system_time -= SystemTime::Day(360);
    cout << "system_time -= SystemTime::Day(360) \n"
         << system_time.to_string() << endl << endl;

  }

  system_time = SystemTime::now();
  cout << system_time.to_string() << endl;
  cout << "year     " << system_time.year()      << endl;
  cout << "month    " << system_time.month()     << endl;
  cout << "day      " << system_time.day()       << endl;
  cout << "hour     " << system_time.hour()      << endl;
  cout << "min      " << system_time.min()       << endl;
  cout << "sec      " << system_time.sec()       << endl;
  cout << "millisec " << system_time.millisec()  << endl;
  cout << "microsec " << system_time.microsec()  << endl;
  cout << "nanosec  " << system_time.nanosec()   << endl;

  return 0;
}
