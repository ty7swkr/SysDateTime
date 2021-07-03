#include <iomanip>
#include <sstream>
#include <string.h>
#include <time.h>

inline
std::tm localtime_r__(const std::time_t &t)
{
  std::tm r;
  localtime_r(&t, &r);
  return r;
}

inline std::tm
SystemTime::to_tm() const
{
  return localtime_r__(to_time_t());
}

inline struct timespec
SystemTime::to_timespec() const
{
  return { to_time_t(), nanosec() };
}

inline struct timeval
SystemTime::to_timeval() const
{
  return { to_time_t(), microsec() };
}

inline SystemTime
SystemTime::first_day_of_month() const
{
  SystemTime st = *this;
  return st.set_day(1);
}

inline SystemTime
SystemTime::last_day_of_month() const
{
  #define SystemTime_LEAPYEAR(year) (!((year) % 4) && (((year) % 100) || !((year) % 400)))

  static const int64_t ytab[2][12] =
  {
   { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 },
   { 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 }
  };

  SystemTime st = *this;

  std::time_t time_t_v  = st.to_time_t();
  std::tm     tm_value  = st.to_tm();

  time_t_v += (ytab[SystemTime_LEAPYEAR(tm_value.tm_year)][tm_value.tm_mon] - tm_value.tm_mday) * 86400;

  st.clock_ = nano_time_t_to_time_point(time_t_v, nanosec());

  return st;
}

inline SystemTime
SystemTime::first_time_of_day() const
{
  SystemTime st = *this;
  return st.set_time(0, 0, 0, Nanosec(0));
}

inline SystemTime
SystemTime::first_time_of_month() const
{
  SystemTime st = *this;
  st.set_day(1);
  return st.set_time(0, 0, 0, Nanosec(0));
}

inline SystemTime
SystemTime::last_time_of_day() const
{
  SystemTime st = *this;
  return st.set_time(23, 59, 59, Nanosec(NANOSEC-1));
}

inline SystemTime
SystemTime::last_time_of_month() const
{
  return last_day_of_month().last_time_of_day();
}

inline time_t
SystemTime::to_time_t() const
{
  return std::chrono::system_clock::to_time_t(clock_);
}

inline std::string
SystemTime::strftime(std::string format) const
{
  if (format.find("%L") != std::string::npos)
    format.replace(format.find("%L"), 2, to_stringf(millisec(), "%03lld"));

  if (format.find("%K") != std::string::npos)
    format.replace(format.find("%K"), 2, to_stringf(microsec(), "%06lld"));

  if (format.find("%N") != std::string::npos)
    format.replace(format.find("%N"), 2, to_stringf(nanosec(),  "%09lld"));

  std::tm tm = localtime_r__(to_time_t());

  std::ostringstream str_time;
  str_time << std::put_time(&tm, format.c_str());
  return str_time.str();
}

inline bool
SystemTime::strptime(const std::string &time_string,
                        const std::string &format)
{
  std::tm tm;
  memset(&tm, 0x00, sizeof(tm));

  std::istringstream ss(time_string);

  ss >> std::get_time(&tm, format.c_str());

  if (ss.fail() == true)
    return false;

  clock_ = time_t_to_time_point(std::mktime(&tm));
  return true;
}

inline bool
SystemTime::from_string(const std::string &datetime,
                        const std::string &format)
{
  int64_t year  = 1900;
  int64_t month = 1;
  int64_t day   = 1;
  int64_t hour  = 0;
  int64_t min   = 0;
  int64_t sec   = 0;
  int64_t nano  = 0;

  size_t index_datetime = 1;
  for (size_t index = 1; index < format.size(); ++index, ++index_datetime)
  {
    if (format.at(index-1) != '%')
      continue;

    if (index_datetime > datetime.length()-1)
      return false;

    switch (format.at(index))
    {
      case 'Y':
      {
        if ((datetime.length() - (index_datetime-1)) < 3)
          return false;

        year = std::atoll(datetime.substr(index_datetime-1, 4).c_str());
        index_datetime += 2;
        break;
      }
      case 'm':
      {
        if ((datetime.length() - (index_datetime-1)) < 2)
          return false;

        month = std::atoll(datetime.substr(index_datetime-1, 2).c_str());
        break;
      }
      case 'd':
      {
        if ((datetime.length() - (index_datetime-1)) < 2)
          return false;

        day = std::atoll(datetime.substr(index_datetime-1, 2).c_str());
        break;
      }
      case 'H':
      {
        if ((datetime.length() - (index_datetime-1)) < 2)
          return false;

        hour = std::atoll(datetime.substr(index_datetime-1, 2).c_str());
        break;
      }
      case 'M':
      {
        if ((datetime.length() - (index_datetime-1)) < 2)
          return false;

        min = std::atoll(datetime.substr(index_datetime-1, 2).c_str());
        break;
      }
      case 'S':
      {
        if ((datetime.length() - (index_datetime-1)) < 2)
          return false;

        sec = std::atoll(datetime.substr(index_datetime-1, 2).c_str());
        break;
      }
      case 'L':
      {
        if ((datetime.length() - (index_datetime-1)) < 2)
          return false;

        nano = std::atoll(datetime.substr(index_datetime-1, 3).c_str()) * MICROSEC;
        ++index_datetime;
        break;
      }
      case 'K':
      {
        if ((datetime.length() - (index_datetime-1)) < 6)
          return false;

        nano = std::atoll(datetime.substr(index_datetime-1, 6).c_str()) * MILLISEC;
        index_datetime += 4;
        break;
      }
      case 'N':
      {
        if ((datetime.length() - (index_datetime-1)) < 9)
          return false;

        nano = std::atoll(datetime.substr(index_datetime-1, 9).c_str());
        index_datetime += 7;
        break;
      }
      default:
      {
        return false;
      }
    }
  }

  set_datetime(year, month, day, hour, min, sec, Nanosec(nano));

  return true;
}

inline SystemTime &
SystemTime::set_current()
{
  clock_    = std::chrono::system_clock::now();

  return *this;
}

inline int64_t
SystemTime::year() const
{
  return to_tm().tm_year + 1900;
}

inline int64_t
SystemTime::month() const
{
  return to_tm().tm_mon + 1;
}

inline int64_t
SystemTime::day() const
{
  return to_tm().tm_mday;
}

inline int64_t
SystemTime::hour() const
{
  return to_tm().tm_hour;
}

inline int64_t
SystemTime::min() const
{
  return to_tm().tm_min;
}

inline int64_t
SystemTime::sec() const
{
  return to_tm().tm_sec;
}

inline int64_t
SystemTime::millisec() const
{
  return std::chrono::duration_cast<std::chrono::milliseconds>(clock_.time_since_epoch()).count() - (to_time_t() * MILLISEC);
}

inline int64_t
SystemTime::microsec() const
{
  return std::chrono::duration_cast<std::chrono::microseconds>(clock_.time_since_epoch()).count() - (to_time_t() * MICROSEC);
}

inline int64_t
SystemTime::nanosec() const
{
  return std::chrono::duration_cast<std::chrono::nanoseconds>(clock_.time_since_epoch()).count() - (to_time_t() * NANOSEC);
}

inline SystemTime &
SystemTime::set_date(const int64_t &year, const int64_t &month, const int64_t &day)
{
  std::tm value = to_tm();

  value.tm_year = year  - 1900;
  value.tm_mon  = month - 1;
  value.tm_mday = day;

  clock_ = nano_time_t_to_time_point(std::mktime(&value), nanosec());

  return *this;
}

inline SystemTime &
SystemTime::set_time(const int64_t &hour, const int64_t &min, const int64_t &sec, const Millisec &millisec)
{
  return set_time(hour, min, sec, Nanosec(millisec() * 1000000LL));
}

inline SystemTime &
SystemTime::set_time(const int64_t &hour, const int64_t &min, const int64_t &sec, const Microsec &microsec)
{
  return set_time(hour, min, sec, Nanosec(microsec() * 1000LL));
}

inline SystemTime &
SystemTime::set_time(const int64_t &hour, const int64_t &min, const int64_t &sec, const Nanosec &nanosec)
{
  std::tm value = localtime_r__(to_time_t());

  value.tm_hour = hour;
  value.tm_min  = min;
  value.tm_sec  = sec;

  clock_ = nano_time_t_to_time_point(std::mktime(&value), nanosec());

  return *this;
}

inline SystemTime &
SystemTime::set_datetime(const int64_t &year, const int64_t &month, const int64_t &day,
                         const int64_t &hour, const int64_t &min,   const int64_t &sec, const Millisec &millisec)
{
  return set_datetime(year, month, day, hour, min, sec, Nanosec(millisec() * 1000000LL));
}

inline SystemTime &
SystemTime::set_datetime(const int64_t &year, const int64_t &month, const int64_t &day,
                         const int64_t &hour, const int64_t &min,   const int64_t &sec, const Microsec &microsec)
{
  return set_datetime(year, month, day, hour, min, sec, Nanosec(microsec() * 1000LL));
}

inline SystemTime &
SystemTime::set_datetime(const int64_t &year, const int64_t &month, const int64_t &day,
                         const int64_t &hour, const int64_t &min,   const int64_t &sec, const Nanosec &nanosec)
{
  std::tm value = to_tm();

  value.tm_year = year  - 1900;
  value.tm_mon  = month - 1;
  value.tm_mday = day;
  value.tm_hour = hour;
  value.tm_min  = min;
  value.tm_sec  = sec;

  clock_ = nano_time_t_to_time_point(std::mktime(&value), nanosec());

  return *this;
}

inline SystemTime &
SystemTime::set_year(const int64_t &year)
{
  std::tm value = localtime_r__(to_time_t());

  value.tm_year = year - 1900;

  clock_ = nano_time_t_to_time_point(std::mktime(&value), nanosec());

  return *this;
}

inline SystemTime &
SystemTime::set_month(const int64_t &month)
{
  std::tm value = localtime_r__(to_time_t());

  value.tm_mon = month - 1;

  clock_ = nano_time_t_to_time_point(std::mktime(&value), nanosec());

  return *this;
}

inline SystemTime &
SystemTime::set_day(const int64_t &day)
{
  std::tm value = localtime_r__(to_time_t());

  value.tm_mday = day;

  clock_ = nano_time_t_to_time_point(std::mktime(&value), nanosec());

  return *this;
}

inline SystemTime &
SystemTime::set_hour(const int64_t &hour)
{
  std::tm value = localtime_r__(to_time_t());

  value.tm_hour = hour;

  clock_ = nano_time_t_to_time_point(std::mktime(&value), nanosec());

  return *this;
}

inline SystemTime &
SystemTime::set_min(const int64_t &min)
{
  std::tm value = localtime_r__(to_time_t());

  value.tm_min = min;

  clock_ = nano_time_t_to_time_point(std::mktime(&value), nanosec());

  return *this;
}

inline SystemTime &
SystemTime::set_sec(const int64_t &sec)
{
  std::tm value = localtime_r__(to_time_t());

  value.tm_sec = sec;

  clock_ = time_t_to_time_point(std::mktime(&value));

  return *this;
}

inline SystemTime &
SystemTime::set_millisec(const int64_t &millisec)
{
  clock_ = milli_time_t_to_time_point(to_time_t(), millisec);
  return *this;
}

inline SystemTime &
SystemTime::set_microsec(const int64_t &microsec)
{
  clock_ = micro_time_t_to_time_point(to_time_t(), microsec);
  return *this;
}

inline SystemTime &
SystemTime::set_nanosec(const int64_t &nanosec)
{
  clock_ = nano_time_t_to_time_point(to_time_t(), nanosec);
  return *this;
}
