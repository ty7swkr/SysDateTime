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

  SysDate &operator= (const Year    &value) { return set_year  (value());}
  SysDate &operator= (const Month   &value) { return set_month (value());}
  SysDate &operator= (const Day     &value) { return set_day   (value());}

  SysDate &operator+=(const Year    &value) { set_year  (year_  + value()); return *this; }
  SysDate &operator+=(const Month   &value) { set_month (month_ + value()); return *this; }
  SysDate &operator+=(const Day     &value) { set_day   (day_   + value()); return *this; }

  SysDate &operator-=(const Year    &value) { set_year  (year_  - value()); return *this; }
  SysDate &operator-=(const Month   &value) { set_month (month_ - value()); return *this; }
  SysDate &operator-=(const Day     &value) { set_day   (day_   - value()); return *this; }

  SysDate  operator+ (const Year    &value) const { SysDate sd = *this; return sd.set_year (sd.year_  + value()); }
  SysDate  operator+ (const Month   &value) const { SysDate sd = *this; return sd.set_month(sd.month_ + value()); }
  SysDate  operator+ (const Day     &value) const { SysDate sd = *this; return sd.set_day  (sd.day_   + value()); }

  SysDate  operator- (const Year    &value) const { SysDate sd = *this; return sd.set_year (sd.year_  - value()); }
  SysDate  operator- (const Month   &value) const { SysDate sd = *this; return sd.set_month(sd.month_ - value()); }
  SysDate  operator- (const Day     &value) const { SysDate sd = *this; return sd.set_day  (sd.day_   - value()); }

  bool     operator==(const SysDate &rhs) const;
  bool     operator<=(const SysDate &rhs) const;
  bool     operator>=(const SysDate &rhs) const;
  bool     operator< (const SysDate &rhs) const;
  bool     operator> (const SysDate &rhs) const;

  SysDate first_day_of_month() const { SysDate sd = *this; sd.day_ = 1; return sd; }
  SysDate last_day_of_month () const;

  std::string to_string() const
  {
    return to_stringf(year_, "%04lld-") + to_stringf(month_, "%02lld-") + to_stringf(day_, "%02lld");
  }

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
