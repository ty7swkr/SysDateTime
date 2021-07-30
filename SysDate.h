/*
 * SysDate.h
 *
 *  Created on: 2021. 7. 10.
 *      Author: tys
 */

#ifndef SYSDATE_H_
#define SYSDATE_H_

#include <string>
#include <chrono>
#include <sstream>
#include <iomanip>

#include <string.h>

class SysDate
{
public:
  SysDate() {}
  SysDate(const int64_t &year, const int64_t &month, const int64_t &day) { set(year, month, day); }

  /********* classes for operation *********/
  struct Year { Year    ():value(1970){} Year    (const int64_t &value):value(value){} const int64_t &operator()() const { return value; } int64_t value; };
  struct Month{ Month   ():value(1)   {} Month   (const int64_t &value):value(value){} const int64_t &operator()() const { return value; } int64_t value; };
  struct Day  { Day     ():value(1)   {} Day     (const int64_t &value):value(value){} const int64_t &operator()() const { return value; } int64_t value; };

  static SysDate now();

  const int64_t &year () const { return year_;  }
  const int64_t &month() const { return month_; }
  const int64_t &day  () const { return day_;   }
  const int64_t &day_of_week() const { return day_of_week_; }

  SysDate &set       (const int64_t &year, const int64_t &month, const int64_t &day);
  SysDate &set_year  (const int64_t &value) { return set(value, month_, day_); }
  SysDate &set_month (const int64_t &value) { return set(year_, value,  day_); }
  SysDate &set_day   (const int64_t &value) { return set(year_, month_, value); }

  template<typename T> SysDate &set(const T &value){ return operator= (value); }
  template<typename T> SysDate &add(const T &value){ return operator+=(value); }

  SysDate &operator= (const Year    &rhs) { return set_year  (rhs());}
  SysDate &operator= (const Month   &rhs) { return set_month (rhs());}
  SysDate &operator= (const Day     &rhs) { return set_day   (rhs());}

  SysDate &operator+=(const Year    &rhs) { set_year  (year_  + rhs()); return *this; }
  SysDate &operator+=(const Month   &rhs) { set_month (month_ + rhs()); return *this; }
  SysDate &operator+=(const Day     &rhs) { set_day   (day_   + rhs()); return *this; }

  SysDate &operator-=(const Year    &rhs) { set_year  (year_  - rhs()); return *this; }
  SysDate &operator-=(const Month   &rhs) { set_month (month_ - rhs()); return *this; }
  SysDate &operator-=(const Day     &rhs) { set_day   (day_   - rhs()); return *this; }

  SysDate  operator+ (const Year    &rhs) const { SysDate sd = *this; return sd.set_year (sd.year_  + rhs()); }
  SysDate  operator+ (const Month   &rhs) const { SysDate sd = *this; return sd.set_month(sd.month_ + rhs()); }
  SysDate  operator+ (const Day     &rhs) const { SysDate sd = *this; return sd.set_day  (sd.day_   + rhs()); }

  SysDate  operator- (const Year    &rhs) const { SysDate sd = *this; return sd.set_year (sd.year_  - rhs()); }
  SysDate  operator- (const Month   &rhs) const { SysDate sd = *this; return sd.set_month(sd.month_ - rhs()); }
  SysDate  operator- (const Day     &rhs) const { SysDate sd = *this; return sd.set_day  (sd.day_   - rhs()); }

  bool     operator==(const SysDate &rhs) const;
  bool     operator<=(const SysDate &rhs) const;
  bool     operator>=(const SysDate &rhs) const;
  bool     operator< (const SysDate &rhs) const;
  bool     operator> (const SysDate &rhs) const;

  SysDate first_day_of_month() const { SysDate sd = *this; sd.day_ = 1; return sd; }
  SysDate last_day_of_month () const;

  std::string strftime (const std::string &format = "%Y-%m-%d") const;
  std::string to_string(const std::string &format = "%Y-%m-%d") const { return strftime(format); }

private:
  static std::string
  to_stringf(const int64_t &value, const std::string &format = "%03ll")
  {
    int size_f = std::snprintf(nullptr, 0, format.c_str(), value) + 1;
    if (size_f <= 0) return "";

    char buff[size_f] = { 0, };
    std::snprintf(buff, sizeof(buff), format.c_str(), value);
    return buff;
  }

  int64_t year_  = 1970;
  int64_t month_ = 1;
  int64_t day_   = 1;
  int64_t day_of_week_ = 0;
};

inline std::string
SysDate::strftime(const std::string &format) const
{
  std::tm tm;
  memset(&tm, 0x00, sizeof(std::tm));

  tm.tm_year = year_  - 1900;
  tm.tm_mon  = month_ - 1;
  tm.tm_mday = day_;

  std::ostringstream str_time;
  str_time << std::put_time(&tm, format.c_str());
  return str_time.str();
}

inline SysDate
SysDate::last_day_of_month() const
{
#define SysDate_LEAPYEAR(year) (!((year) % 4) && (((year) % 100) || !((year) % 400)))

  static const int64_t ytab[2][12] =
  {
   { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 },
   { 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 }
  };

  SysDate st = *this;

  st.day_ = ytab[SysDate_LEAPYEAR(year_-1900)][month_-1];

  return st;
}

inline SysDate
SysDate::now()
{
  time_t from_time_t = std::time(nullptr);

  std::tm to;
  localtime_r(&from_time_t, &to);

  return SysDate(to.tm_year + 1900,
                 to.tm_mon  + 1,
                 to.tm_mday);
}

inline SysDate &
SysDate::set(const int64_t &year, const int64_t &month, const int64_t &day)
{
  std::tm from;
  memset(&from, 0x00, sizeof(std::tm));

  from.tm_year = year  - 1900;
  from.tm_mon  = month - 1;
  from.tm_mday = day;

  time_t from_time_t = std::mktime(&from);

  std::tm to;
  localtime_r(&from_time_t, &to);

  year_  = to.tm_year + 1900;
  month_ = to.tm_mon  + 1;
  day_   = to.tm_mday;
  day_of_week_ = to.tm_wday;

  return *this;
}

inline bool
SysDate::operator==(const SysDate &rhs) const
{
  return year_ == rhs.year_ && month_ == rhs.month_ && day_ == rhs.day_;
}

inline bool
SysDate::operator<=(const SysDate &rhs) const
{
  if (year_ == rhs.year_ && month_ == rhs.month_) return day_ <= rhs.day_;
  if (year_ == rhs.year_) return month_ <= rhs.month_;
  return year_ <= rhs.year_;
}

inline bool
SysDate::operator>=(const SysDate &rhs) const
{
  if (year_ == rhs.year_ && month_ == rhs.month_) return day_ >= rhs.day_;
  if (year_ == rhs.year_) return month_ >= rhs.month_;
  return year_ >= rhs.year_;
}

inline bool
SysDate::operator< (const SysDate &rhs) const
{
  if (year_ == rhs.year_ && month_ == rhs.month_) return day_ < rhs.day_;
  if (year_ == rhs.year_) return month_ < rhs.month_;
  return year_ < rhs.year_;
}

inline bool
SysDate::operator> (const SysDate &rhs) const
{
  if (year_ == rhs.year_ && month_ == rhs.month_) return day_ > rhs.day_;
  if (year_ == rhs.year_) return month_ > rhs.month_;
  return year_ > rhs.year_;
}


#endif /* SYSTEM_SYSDATE_H_ */
