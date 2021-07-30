/*
 * SysTime.h
 *
 *  Created on: 2021. 7. 10.
 *      Author: tys
 */

#ifndef SYSTIME_H_
#define SYSTIME_H_

#include <string>
#include <chrono>
#include <iomanip>

#include <string.h>

class SysTime
{
public:
  SysTime() {}
  SysTime(const int64_t &hour, const int64_t &min, const int64_t &sec, const int64_t &nanosec) { set(hour, min, sec, nanosec); }
  SysTime(const time_t  &value) { *this = value; }
  SysTime(const std::string &time_string, const std::string &format) { this->strptime(time_string, format); }

  /********* classes for operation *********/
  struct Hour     { Hour    ():value(0) {} Hour    (const int64_t &value):value(value){} const int64_t &operator()() const { return value; } int64_t value; };
  struct Min      { Min     ():value(0) {} Min     (const int64_t &value):value(value){} const int64_t &operator()() const { return value; } int64_t value; };
  struct Sec      { Sec     ():value(0) {} Sec     (const int64_t &value):value(value){} const int64_t &operator()() const { return value; } int64_t value; };
  struct Millisec { Millisec():value(0) {} Millisec(const int64_t &value):value(value){} const int64_t &operator()() const { return value; } int64_t value; };
  struct Microsec { Microsec():value(0) {} Microsec(const int64_t &value):value(value){} const int64_t &operator()() const { return value; } int64_t value; };
  struct Nanosec  { Nanosec ():value(0) {} Nanosec (const int64_t &value):value(value){} const int64_t &operator()() const { return value; } int64_t value; };

  static SysTime now();

  int64_t hour    () const { return hour_;  }
  int64_t min     () const { return min_;   }
  int64_t sec     () const { return sec_;   }
  int64_t millisec() const { return nano_/1000000LL; }
  int64_t microsec() const { return nano_/1000LL; }
  int64_t nanosec () const { return nano_;  }

  SysTime &set          (const int64_t  &hour, const int64_t &min, const int64_t &sec, const int64_t &nano = 0);
  SysTime &set_hour     (const int64_t  &value) { return set(value, min_,  sec_,  nano_); }
  SysTime &set_min      (const int64_t  &value) { return set(hour_, value, sec_,  nano_); }
  SysTime &set_sec      (const int64_t  &value) { return set(hour_, min_,  value, nano_); }
  SysTime &set_millisec (const int64_t  &value) { return set(hour_, min_,  sec_ , value * 1000000LL); }
  SysTime &set_microsec (const int64_t  &value) { return set(hour_, min_,  sec_,  value * 1000LL); }
  SysTime &set_nanosec  (const int64_t  &value) { return set(hour_, min_,  sec_,  value); }

  template<typename T> SysTime &set(const T &value){ return operator= (value); }
  template<typename T> SysTime &add(const T &value){ return operator+=(value); }

  SysTime &operator=  (const Hour     &rhs) { return set_hour     (rhs());}
  SysTime &operator=  (const Min      &rhs) { return set_min      (rhs());}
  SysTime &operator=  (const Sec      &rhs) { return set_sec      (rhs());}
  SysTime &operator=  (const Millisec &rhs) { return set_millisec (rhs());}
  SysTime &operator=  (const Microsec &rhs) { return set_microsec (rhs());}
  SysTime &operator=  (const Nanosec  &rhs) { return set_nanosec  (rhs());}
  SysTime &operator=  (const time_t   &rhs);

  SysTime &operator+= (const Hour     &rhs) { set_hour    (hour_  + rhs()); return *this; }
  SysTime &operator+= (const Min      &rhs) { set_min     (min_   + rhs()); return *this; }
  SysTime &operator+= (const Sec      &rhs) { set_sec     (sec_   + rhs()); return *this; }
  SysTime &operator+= (const Millisec &rhs) { set_nanosec (nano_  + rhs() * 1000000LL); return *this; }
  SysTime &operator+= (const Microsec &rhs) { set_nanosec (nano_  + rhs() * 1000LL); return *this; }
  SysTime &operator+= (const Nanosec  &rhs) { set_nanosec (nano_  + rhs()); return *this; }

  SysTime &operator-= (const Hour     &rhs) { set_hour    (hour_  - rhs()); return *this; }
  SysTime &operator-= (const Min      &rhs) { set_min     (min_   - rhs()); return *this; }
  SysTime &operator-= (const Sec      &rhs) { set_sec     (sec_   - rhs()); return *this; }
  SysTime &operator-= (const Millisec &rhs) { set_nanosec (nano_  - rhs() * 1000000LL); return *this; }
  SysTime &operator-= (const Microsec &rhs) { set_nanosec (nano_  - rhs() * 1000LL); return *this; }
  SysTime &operator-= (const Nanosec  &rhs) { set_nanosec (nano_  - rhs()); return *this; }

  SysTime  operator+  (const Hour     &rhs) const { SysTime sd = *this; return sd.set_hour    (sd.hour_ + rhs()); }
  SysTime  operator+  (const Min      &rhs) const { SysTime sd = *this; return sd.set_min     (sd.min_  + rhs()); }
  SysTime  operator+  (const Sec      &rhs) const { SysTime sd = *this; return sd.set_sec     (sd.sec_  + rhs()); }
  SysTime  operator+  (const Millisec &rhs) const { SysTime sd = *this; return sd.set_nanosec (sd.nano_ + rhs() * 1000000LL); }
  SysTime  operator+  (const Microsec &rhs) const { SysTime sd = *this; return sd.set_nanosec (sd.nano_ + rhs() * 1000LL); }
  SysTime  operator+  (const Nanosec  &rhs) const { SysTime sd = *this; return sd.set_nanosec (sd.nano_ + rhs()); }

  SysTime  operator-  (const Hour     &rhs) const { SysTime sd = *this; return sd.set_hour    (sd.hour_ - rhs()); }
  SysTime  operator-  (const Min      &rhs) const { SysTime sd = *this; return sd.set_min     (sd.min_  - rhs()); }
  SysTime  operator-  (const Sec      &rhs) const { SysTime sd = *this; return sd.set_sec     (sd.sec_  - rhs()); }
  SysTime  operator-  (const Millisec &rhs) const { SysTime sd = *this; return sd.set_nanosec (sd.nano_ - rhs() * 1000000LL); }
  SysTime  operator-  (const Microsec &rhs) const { SysTime sd = *this; return sd.set_nanosec (sd.nano_ - rhs() * 1000LL); }
  SysTime  operator-  (const Nanosec  &rhs) const { SysTime sd = *this; return sd.set_nanosec (sd.nano_ - rhs()); }

  bool     operator== (const SysTime  &rhs) const;
  bool     operator<= (const SysTime  &rhs) const;
  bool     operator>= (const SysTime  &rhs) const;
  bool     operator<  (const SysTime  &rhs) const;
  bool     operator>  (const SysTime  &rhs) const;

  std::string strftime (std::string        format = "%H:%M:%S") const;
  std::string to_string(const std::string &format = "%H:%M:%S") const { return strftime(format); }
  bool        strptime (const std::string &time_string,
                        const std::string &format = "%H:%M:%S");

  static std::tm localtime(const std::time_t &t)
  {
    std::tm r;
    localtime_r(&t, &r);
    return r;
  }

  static std::tm gmtime(const std::time_t &t)
  {
    std::tm r;
    gmtime_r(&t, &r);
    return r;
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

  int64_t hour_ = 0;
  int64_t min_  = 0;
  int64_t sec_  = 0;
  int64_t nano_ = 0;
};

inline bool
SysTime::strptime(const std::string &time_string,
                  const std::string &format)
{
  std::tm tm;
  memset(&tm, 0x00, sizeof(tm));

  std::istringstream ss(time_string);
  ss >> std::get_time(&tm, format.c_str());

  if (ss.fail() == true)
    return false;

  hour_ = tm.tm_hour;
  min_  = tm.tm_min;
  sec_  = tm.tm_sec;
  nano_ = 0;

  return true;
}

inline std::string
SysTime::strftime(std::string format) const
{
  if (format.find("%L") != std::string::npos)
    format.replace(format.find("%L"), 2, to_stringf(millisec(), "%03lld"));

  if (format.find("%K") != std::string::npos)
    format.replace(format.find("%K"), 2, to_stringf(microsec(), "%06lld"));

  if (format.find("%N") != std::string::npos)
    format.replace(format.find("%N"), 2, to_stringf(nanosec(), "%09lld"));

  std::tm tm;
  memset(&tm, 0x00, sizeof(std::tm));

  tm.tm_hour = hour_;
  tm.tm_min  = min_;
  tm.tm_sec  = sec_;

  std::ostringstream str_time;
  str_time << std::put_time(&tm, format.c_str());
  return str_time.str();
}

inline SysTime
SysTime::now()
{
  std::chrono::system_clock::time_point clock = std::chrono::system_clock::now();

  time_t time_t_v = std::chrono::system_clock::to_time_t(clock);

  std::tm to = localtime(time_t_v);

  int64_t nano =
      std::chrono::duration_cast<std::chrono::nanoseconds>(
          clock.time_since_epoch()
          ).count() - (int64_t)time_t_v * 1000000000LL;

  return SysTime(to.tm_hour, to.tm_min, to.tm_sec, nano);
}

inline SysTime &
SysTime::set(const int64_t &hour, const int64_t &min, const int64_t &sec, const int64_t &nano)
{
  std::tm from;
  memset(&from, 0x00, sizeof(std::tm));

  from.tm_hour = hour;
  from.tm_min  = min;
  from.tm_sec  = sec;

  time_t from_time_t = std::mktime(&from);

  if (nano >= 1000000000LL)
  {
    from_time_t += (nano / 1000000000LL);
    nano_        = nano % 1000000000LL;
  }
  else if (nano < 0)
  {
    int64_t share = (-nano / 1000000000LL);
    if ((-nano % 1000000000LL) > 0)
      ++share;

    from_time_t  -= share;
    nano_         = (share * 1000000000LL) - -nano;
  }
  else
  {
    nano_ = nano;
  }

  std::tm to = localtime(from_time_t);

  hour_ = to.tm_hour;
  min_  = to.tm_min;
  sec_  = to.tm_sec;

  return *this;
}

inline SysTime &
SysTime::operator=(const time_t &rhs)
{
  std::tm to = localtime(rhs);
  hour_ = to.tm_hour;
  min_  = to.tm_min;
  sec_  = to.tm_sec;
  nano_ = 0;

  return *this;
}

inline bool
SysTime::operator==(const SysTime &rhs) const
{
  return hour_ == rhs.hour_ && min_ == rhs.min_ && sec_ == rhs.sec_ && nano_ == rhs.nano_;
}

inline bool
SysTime::operator<=(const SysTime &rhs) const
{
  if (hour_ == rhs.hour_ && min_ == rhs.min_ && sec_ == rhs.sec_) return nano_ <= rhs.nano_;
  if (hour_ == rhs.hour_ && min_ == rhs.min_) return sec_ <= rhs.sec_;
  if (hour_ == rhs.hour_) return min_ <= rhs.min_;
  return hour_ <= rhs.hour_;
}

inline bool
SysTime::operator>=(const SysTime &rhs) const
{
  if (hour_ == rhs.hour_ && min_ == rhs.min_ && sec_ == rhs.sec_) return nano_ >= rhs.nano_;
  if (hour_ == rhs.hour_ && min_ == rhs.min_) return sec_ >= rhs.sec_;
  if (hour_ == rhs.hour_) return min_ >= rhs.min_;
  return hour_ >= rhs.hour_;
}

inline bool
SysTime::operator< (const SysTime &rhs) const
{
  if (hour_ == rhs.hour_ && min_ == rhs.min_ && sec_ == rhs.sec_) return nano_ < rhs.nano_;
  if (hour_ == rhs.hour_ && min_ == rhs.min_) return sec_ < rhs.sec_;
  if (hour_ == rhs.hour_) return min_ < rhs.min_;
  return hour_ < rhs.hour_;
}

inline bool
SysTime::operator> (const SysTime &rhs) const
{
  if (hour_ == rhs.hour_ && min_ == rhs.min_ && sec_ == rhs.sec_) return nano_ > rhs.nano_;
  if (hour_ == rhs.hour_ && min_ == rhs.min_) return sec_ > rhs.sec_;
  if (hour_ == rhs.hour_) return min_ > rhs.min_;
  return hour_ > rhs.hour_;
}


#endif /* SYSTEM_SYSDATE_H_ */
