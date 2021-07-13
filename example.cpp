#include <SysDateTime.h>
#include <iostream>
#include <unistd.h>
#include <sys/time.h>

using namespace std;

int main(void)
{
  // ********* initialization *********
  {
    SysDateTime system_time1 = SysDateTime::now();
    SysDateTime system_time2 = std::chrono::system_clock::now();
    SysDateTime system_time3 = time(NULL);

    struct timespec ts;
    clock_gettime(CLOCK_REALTIME, &ts);
    SysDateTime system_time4 = ts;

    struct timeval tv;
    gettimeofday(&tv, NULL);
    SysDateTime system_time5 = tv;
  }

  // ********* conversion *********
  {
    SysDateTime system_time  = SysDateTime::now();
    time_t          time_t_v  = system_time.to_time_t();
    std::tm         tm_value  = system_time.to_tm();
    struct timespec ts        = system_time.to_timespec();
    struct timeval  tv        = system_time.to_timeval();
    std::chrono::system_clock::time_point time_pont = system_time.time_point();
  }

  // ********* to string *********
  {
    SysDateTime system_time  = SysDateTime::now();
    cout << "strftime     " << system_time.strftime()     << endl;
    cout << "strftime_utc " << system_time.strftime_utc() << endl;
    cout << "to_string    " << system_time.to_string()    << endl;
  }

  // ********* parsing *********
  {
    SysDateTime system_time;
    system_time.strptime("2011-04-05 11:34:22", "%Y-%m-%d %H:%M:%S");
    cout << "strptime(\"2011-04-05 11:34:22\", \"%Y-%m-%d %H:%M:%S\") \n" << system_time.strftime() << endl << endl;

    system_time.from_string("2011-04-05 11:34:22.123456789", "%Y-%m-%d %H:%M:%S.%N");
    cout << "from_string(\"2011-04-05 11:34:22.123456789\", \"%Y-%m-%d %H:%M:%S.%N\") \n"
         << system_time.to_string("%Y-%m-%d %H:%M:%S.%N") << endl << endl;
  }

  // ********* operation ********
  SysTime time = SysTime::now();      cout << "SysTime time = SysTime::now();     " << time.to_string() << endl;
  time  = SysTime::Hour(10);          cout << "time  = SysTime::Hour(10);         " << time.to_string() << endl;
  time += SysTime::Hour(10);          cout << "time += SysTime::Hour(10);         " << time.to_string() << endl;
  time -= SysTime::Hour(10);          cout << "time -= SysTime::Hour(10);         " << time.to_string() << endl;

  time  = SysTime::Min(67);           cout << "time  = SysTime::Min(67);          " << time.to_string() << endl;
  time += SysTime::Min(67);           cout << "time += SysTime::Min(67);          " << time.to_string() << endl;
  time -= SysTime::Min(67);           cout << "time -= SysTime::Min(67);          " << time.to_string() << endl;

  time  = SysTime::Sec(85);           cout << "time  = SysTime::Sec(15);          " << time.to_string() << endl;
  time += SysTime::Sec(85);           cout << "time += SysTime::Sec(15);          " << time.to_string() << endl;
  time -= SysTime::Sec(85);           cout << "time -= SysTime::Sec(15);          " << time.to_string() << endl;

  time  = SysTime::Millisec(15);      cout << "time  = SysTime::Millisec(15);     " << time.to_string() << endl;
  time += SysTime::Millisec(15);      cout << "time += SysTime::Millisec(15);     " << time.to_string() << endl;
  time -= SysTime::Millisec(15);      cout << "time -= SysTime::Millisec(15);     " << time.to_string() << endl;

  time  = SysTime::Microsec(15);      cout << "time  = SysTime::Microsec(15);     " << time.to_string() << endl;
  time += SysTime::Microsec(15);      cout << "time += SysTime::Microsec(15);     " << time.to_string() << endl;
  time -= SysTime::Microsec(15);      cout << "time -= SysTime::Microsec(15);     " << time.to_string() << endl;

  time  = SysTime::Nanosec(15);       cout << "time  = SysTime::Nanosec(15);      " << time.to_string() << endl;
  time += SysTime::Nanosec(15);       cout << "time += SysTime::Nanosec(15);      " << time.to_string() << endl;
  time -= SysTime::Nanosec(15);       cout << "time -= SysTime::Nanosec(15);      " << time.to_string() << endl;

  // template function
  time.set(SysTime::Hour(10));        cout << "time.set(SysTime::Hour(10));       " << time.to_string() << endl;
  time.add(SysTime::Hour(10));        cout << "time.add(SysTime::Hour(10));       " << time.to_string() << endl;
  time.add(SysTime::Hour(-10));       cout << "time.add(SysTime::Hour(-10));      " << time.to_string() << endl;

  cout << "time.hour();     " << time.hour() << endl;
  cout << "time.min();      " << time.min() << endl;
  cout << "time.sec();      " << time.sec() << endl;
  cout << "time.millisec(); " << time.millisec() << endl;
  cout << "time.microsec(); " << time.microsec() << endl;
  cout << "time.nanosec();  " << time.nanosec() << endl << endl;

  SysDate date = SysDate::now();      cout << "SysDate date = SysDate::now();     " << date.to_string() << endl;
  date  = SysDate::Year(2020);        cout << "date  = SysDate::Year(2020);       " << date.to_string() << endl;
  date += SysDate::Year(4);           cout << "date += SysDate::Year(4);          " << date.to_string() << endl;
  date -= SysDate::Year(4);           cout << "date -= SysDate::Year(4);          " << date.to_string() << endl;

  date  = SysDate::Month(10);         cout << "date  = SysDate::Month(10);        " << date.to_string() << endl;
  date += SysDate::Month(10);         cout << "date += SysDate::Month(10);        " << date.to_string() << endl;
  date -= SysDate::Month(10);         cout << "date -= SysDate::Month(10);        " << date.to_string() << endl;

  date  = SysDate::Day(7);            cout << "date  = SysDate::Day(7);           " << date.to_string() << endl;
  date += SysDate::Day(7);            cout << "date += SysDate::Day(7);           " << date.to_string() << endl;
  date -= SysDate::Day(7);            cout << "date -= SysDate::Day(7);           " << date.to_string() << endl;

  // template function
  date.set(SysDate::Month(10));       cout << "date.set(SysTime::Month(10));      " << date.to_string() << endl;
  date.add(SysDate::Month(10));       cout << "date.add(SysTime::Month(10));      " << date.to_string() << endl;
  date.add(SysDate::Month(-10));      cout << "date.add(SysTime::Month(-10));     " << date.to_string() << endl;

  cout << "date.year();     " << date.year() << endl;
  cout << "date.month();    " << date.month() << endl;
  cout << "date.day();      " << date.day() << endl << endl;

  SysDateTime datetime = SysDateTime::now(); cout << "SysDateTime datetime = SysTime::now(); " << datetime.to_string() << endl;
  datetime = date;                    cout << "datetime = date;                   " << datetime.to_string() << endl;
  datetime = time;                    cout << "datetime = date;                   " << datetime.to_string() << endl;

  datetime  = SysTime::Hour(10);      cout << "datetime  = SysTime::Hour(10);     " << datetime.to_string() << endl;
  datetime += SysTime::Hour(10);      cout << "datetime += SysTime::Hour(10);     " << datetime.to_string() << endl;
  datetime -= SysTime::Hour(10);      cout << "datetime -= SysTime::Hour(10);     " << datetime.to_string() << endl;

  datetime  = SysTime::Min(67);       cout << "datetime  = SysTime::Min(67);      " << datetime.to_string() << endl;
  datetime += SysTime::Min(67);       cout << "datetime += SysTime::Min(67);      " << datetime.to_string() << endl;
  datetime -= SysTime::Min(67);       cout << "datetime -= SysTime::Min(67);      " << datetime.to_string() << endl;

  datetime  = SysTime::Sec(85);       cout << "datetime  = SysTime::Sec(15);      " << datetime.to_string() << endl;
  datetime += SysTime::Sec(85);       cout << "datetime += SysTime::Sec(15);      " << datetime.to_string() << endl;
  datetime -= SysTime::Sec(85);       cout << "datetime -= SysTime::Sec(15);      " << datetime.to_string() << endl;

  datetime  = SysTime::Millisec(15);  cout << "datetime  = SysTime::Millisec(15); " << datetime.to_string() << endl;
  datetime += SysTime::Millisec(15);  cout << "datetime += SysTime::Millisec(15); " << datetime.to_string() << endl;
  datetime -= SysTime::Millisec(15);  cout << "datetime -= SysTime::Millisec(15); " << datetime.to_string() << endl;

  datetime  = SysDate::Year(2020);    cout << "datetime  = SysDate::Year(2020);   " << datetime.to_string() << endl;
  datetime += SysDate::Year(4);       cout << "datetime += SysDate::Year(4);      " << datetime.to_string() << endl;
  datetime -= SysDate::Year(4);       cout << "datetime -= SysDate::Year(4);      " << datetime.to_string() << endl;

  datetime  = SysDate::Month(10);     cout << "datetime  = SysDate::Month(10);    " << datetime.to_string() << endl;
  datetime += SysDate::Month(10);     cout << "datetime += SysDate::Month(10);    " << datetime.to_string() << endl;
  datetime -= SysDate::Month(10);     cout << "datetime -= SysDate::Month(10);    " << datetime.to_string() << endl;

  datetime  = SysDate::Day(7);        cout << "datetime  = SysDate::Day(7);       " << datetime.to_string() << endl;
  datetime += SysDate::Day(7);        cout << "datetime += SysDate::Day(7);       " << datetime.to_string() << endl;
  datetime -= SysDate::Day(7);        cout << "datetime -= SysDate::Day(7);       " << datetime.to_string() << endl;

  // template function
  datetime.set(SysDate::Month(10));   cout << "datetime.set(SysTime::Month(10));  " << datetime.to_string() << endl;
  datetime.add(SysDate::Month(10));   cout << "datetime.add(SysTime::Month(10));  " << datetime.to_string() << endl;
  datetime.add(SysDate::Month(-10));  cout << "datetime.add(SysTime::Month(-10)); " << datetime.to_string() << endl;

  cout << "datetime.year();     " << datetime.year() << endl;
  cout << "datetime.month();    " << datetime.month() << endl;
  cout << "datetime.day();      " << datetime.day() << endl;
  cout << "datetime.hour();     " << datetime.hour() << endl;
  cout << "datetime.min();      " << datetime.min() << endl;
  cout << "datetime.sec();      " << datetime.sec() << endl;
  cout << "datetime.millisec(); " << datetime.millisec() << endl;
  cout << "datetime.microsec(); " << datetime.microsec() << endl;
  cout << "datetime.nanosec();  " << datetime.nanosec() << endl << endl;

  return 0;
}

