#include <abc/system/SysDateTime.h>
#include <iostream>
#include <unistd.h>
#include <sys/time.h>

//using namespace abc;
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

  SysDateTime system_time  = SysDateTime::now();

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

  SysTime time = SysTime::now(); cout << time.to_string() << " SysTime time = SysTime::now();" << endl;
  time  = SysTime::Hour(10); cout << time.to_string() << " time  = SysTime::Hour(10);" << endl;
  time += SysTime::Hour(10); cout << time.to_string() << " time += SysTime::Hour(10);" << endl;
  time -= SysTime::Hour(10); cout << time.to_string() << " time -= SysTime::Hour(10);" << endl;

  time  = SysTime::Min(67); cout << time.to_string() << " time  = SysTime::Min(67);" << endl;
  time += SysTime::Min(67); cout << time.to_string() << " time += SysTime::Min(67);" << endl;
  time -= SysTime::Min(67); cout << time.to_string() << " time -= SysTime::Min(67);" << endl;

  time  = SysTime::Sec(85); cout << time.to_string() << " time  = SysTime::Sec(15);" << endl;
  time += SysTime::Sec(85); cout << time.to_string() << " time += SysTime::Sec(15);" << endl;
  time -= SysTime::Sec(85); cout << time.to_string() << " time -= SysTime::Sec(15);" << endl;

  time  = SysTime::Millisec(15); cout << time.to_string() << " time  = SysTime::Millisec(15);" << endl;
  time += SysTime::Millisec(15); cout << time.to_string() << " time += SysTime::Millisec(15);" << endl;
  time -= SysTime::Millisec(15); cout << time.to_string() << " time -= SysTime::Millisec(15);" << endl;

  SysDate date = SysDate::now(); cout << date.to_string() << " SysDate date = SysDate::now();" << endl;
  date  = SysDate::Year(2020); cout << date.to_string() << " date  = SysDate::Year(2020);" << endl;
  date += SysDate::Year(4); cout << date.to_string() << " date += SysDate::Year(4);" << endl;
  date -= SysDate::Year(4); cout << date.to_string() << " date -= SysDate::Year(4);" << endl;

  date  = SysDate::Month(10); cout << date.to_string() << " date  = SysDate::Month(10);" << endl;
  date += SysDate::Month(10); cout << date.to_string() << " date += SysDate::Month(10);" << endl;
  date -= SysDate::Month(10); cout << date.to_string() << " date -= SysDate::Month(10);" << endl;

  date  = SysDate::Day(7); cout << date.to_string() << " date  = SysDate::Day(7)" << endl;
  date += SysDate::Day(7); cout << date.to_string() << " date += SysDate::Day(7)" << endl;
  date -= SysDate::Day(7); cout << date.to_string() << " date -= SysDate::Day(7)" << endl;

  SysDateTime datetime = SysDateTime::now(); cout << datetime.to_string() << " SysDateTime datetime = SysTime::now();" << endl;
  datetime = date; cout << datetime.to_string() << " datetime = date;" << endl;
  datetime = time; cout << datetime.to_string() << " datetime = date;" << endl;

  datetime  = SysTime::Hour(10); cout << datetime.to_string() << " datetime  = SysTime::Hour(10);" << endl;
  datetime += SysTime::Hour(10); cout << datetime.to_string() << " datetime += SysTime::Hour(10);" << endl;
  datetime -= SysTime::Hour(10); cout << datetime.to_string() << " datetime -= SysTime::Hour(10);" << endl;

  datetime  = SysTime::Min(67); cout << datetime.to_string() << " datetime  = SysTime::Min(67);" << endl;
  datetime += SysTime::Min(67); cout << datetime.to_string() << " datetime += SysTime::Min(67);" << endl;
  datetime -= SysTime::Min(67); cout << datetime.to_string() << " datetime -= SysTime::Min(67);" << endl;

  datetime  = SysTime::Sec(85); cout << datetime.to_string() << " datetime  = SysTime::Sec(15);" << endl;
  datetime += SysTime::Sec(85); cout << datetime.to_string() << " datetime += SysTime::Sec(15);" << endl;
  datetime -= SysTime::Sec(85); cout << datetime.to_string() << " datetime -= SysTime::Sec(15);" << endl;

  datetime  = SysTime::Millisec(15); cout << datetime.to_string() << " datetime  = SysTime::Millisec(15);" << endl;
  datetime += SysTime::Millisec(15); cout << datetime.to_string() << " datetime += SysTime::Millisec(15);" << endl;
  datetime -= SysTime::Millisec(15); cout << datetime.to_string() << " datetime -= SysTime::Millisec(15);" << endl;

  datetime  = SysDate::Year(2020); cout << datetime.to_string() << " datetime  = SysDate::Year(2020);" << endl;
  datetime += SysDate::Year(4); cout << datetime.to_string() << " datetime += SysDate::Year(4);" << endl;
  datetime -= SysDate::Year(4); cout << datetime.to_string() << " datetime -= SysDate::Year(4);" << endl;

  datetime  = SysDate::Month(10); cout << datetime.to_string() << " datetime  = SysDate::Month(10);" << endl;
  datetime += SysDate::Month(10); cout << datetime.to_string() << " datetime += SysDate::Month(10);" << endl;
  datetime -= SysDate::Month(10); cout << datetime.to_string() << " datetime -= SysDate::Month(10);" << endl;

  datetime  = SysDate::Day(7); cout << datetime.to_string() << " datetime  = SysDate::Day(7)" << endl;
  datetime += SysDate::Day(7); cout << datetime.to_string() << " datetime += SysDate::Day(7)" << endl;
  datetime -= SysDate::Day(7); cout << datetime.to_string() << " datetime -= SysDate::Day(7)" << endl;

  return 0;
}


