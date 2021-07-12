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
#include <string.h>

class SysTime
{
public:
  SysTime() {}
  SysTime(const int64_t &hour, const int64_t &min, const int64_t &sec, const int64_t &nanosec)
  { set(hour, min, sec, nanosec); }

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

  SysTime &operator=  (const Hour     &value) { return set_hour     (value());}
  SysTime &operator=  (const Min      &value) { return set_min      (value());}
  SysTime &operator=  (const Sec      &value) { return set_sec      (value());}
  SysTime &operator=  (const Millisec &value) { return set_millisec (value());}
  SysTime &operator=  (const Microsec &value) { return set_microsec (value());}
  SysTime &operator=  (const Nanosec  &value) { return set_nanosec  (value());}

  SysTime &operator+= (const Hour     &value) { set_hour    (hour_  + value()); return *this; }
  SysTime &operator+= (const Min      &value) { set_min     (min_   + value()); return *this; }
  SysTime &operator+= (const Sec      &value) { set_sec     (sec_   + value()); return *this; }
  SysTime &operator+= (const Millisec &value) { set_nanosec (nano_  + value() * 1000000LL); return *this; }
  SysTime &operator+= (const Microsec &value) { set_nanosec (nano_  + value() * 1000LL); return *this; }
  SysTime &operator+= (const Nanosec  &value) { set_nanosec (nano_  + value()); return *this; }

  SysTime &operator-= (const Hour     &value) { set_hour    (hour_  - value()); return *this; }
  SysTime &operator-= (const Min      &value) { set_min     (min_   - value()); return *this; }
  SysTime &operator-= (const Sec      &value) { set_sec     (sec_   - value()); return *this; }
  SysTime &operator-= (const Millisec &value) { set_nanosec (nano_  - value() * 1000000LL); return *this; }
  SysTime &operator-= (const Microsec &value) { set_nanosec (nano_  - value() * 1000LL); return *this; }
  SysTime &operator-= (const Nanosec  &value) { set_nanosec (nano_  - value()); return *this; }

  SysTime  operator+  (const Hour     &value) const { SysTime sd = *this; return sd.set_hour    (sd.hour_ + value()); }
  SysTime  operator+  (const Min      &value) const { SysTime sd = *this; return sd.set_min     (sd.min_  + value()); }
  SysTime  operator+  (const Sec      &value) const { SysTime sd = *this; return sd.set_sec     (sd.sec_  + value()); }
  SysTime  operator+  (const Millisec &value) const { SysTime sd = *this; return sd.set_nanosec (sd.nano_ + value() * 1000000LL); }
  SysTime  operator+  (const Microsec &value) const { SysTime sd = *this; return sd.set_nanosec (sd.nano_ + value() * 1000LL); }
  SysTime  operator+  (const Nanosec  &value) const { SysTime sd = *this; return sd.set_nanosec (sd.nano_ + value()); }

  SysTime  operator-  (const Hour     &value) const { SysTime sd = *this; return sd.set_hour    (sd.hour_ - value()); }
  SysTime  operator-  (const Min      &value) const { SysTime sd = *this; return sd.set_min     (sd.min_  - value()); }
  SysTime  operator-  (const Sec      &value) const { SysTime sd = *this; return sd.set_sec     (sd.sec_  - value()); }
  SysTime  operator-  (const Millisec &value) const { SysTime sd = *this; return sd.set_nanosec (sd.nano_ - value() * 1000000LL); }
  SysTime  operator-  (const Microsec &value) const { SysTime sd = *this; return sd.set_nanosec (sd.nano_ - value() * 1000LL); }
  SysTime  operator-  (const Nanosec  &value) const { SysTime sd = *this; return sd.set_nanosec (sd.nano_ - value()); }

  bool     operator== (const SysTime  &rhs) const;
  bool     operator<= (const SysTime  &rhs) const;
  bool     operator>= (const SysTime  &rhs) const;
  bool     operator<  (const SysTime  &rhs) const;
  bool     operator>  (const SysTime  &rhs) const;

  std::string to_string() const
  {
    return to_stringf(hour_, "%02lld:") + to_stringf(min_, "%02lld:") + to_stringf(sec_, "%02lld.") + to_stringf(nano_, "%09lld");
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

inline SysTime
SysTime::now()
{
  std::chrono::system_clock::time_point clock = std::chrono::system_clock::now();

  time_t time_t_v = std::chrono::system_clock::to_time_t(clock);

  std::tm to;
  localtime_r(&time_t_v, &to);

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

  std::tm to;
  localtime_r(&from_time_t, &to);

  hour_ = to.tm_hour;
  min_  = to.tm_min;
  sec_  = to.tm_sec;

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
