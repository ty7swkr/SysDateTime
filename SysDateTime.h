#ifndef SYSDATETIME_H_
#define SYSDATETIME_H_

#include <SysDate.h>
#include <SysTime.h>

class SysDateTime
{
public:
  static SysDateTime now() { return SysDateTime().set_current(); }

  /********* constructor *********/
  SysDateTime() {}
  SysDateTime(const time_t           &value) { *this = value; } // nanosec is zero
  SysDateTime(const std::tm          &value) { *this = value; } // nanosec is zero
  SysDateTime(const struct timespec  &value) { *this = value; }
  SysDateTime(const struct timeval   &value) { *this = value; }
  SysDateTime(const std::chrono::system_clock::time_point &value) : clock_(value), is_null_(false) {}
  SysDateTime(const SysDate          &value) { set_date(value); } // nanosec is zero

  /********* returns the time value. *********/
  int64_t year()     const;
  int64_t month()    const;
  int64_t day()      const;
  int64_t hour()     const;
  int64_t min()      const;
  int64_t sec()      const;
  int64_t millisec() const;
  int64_t microsec() const;
  int64_t nanosec()  const;
  const std::chrono::system_clock::time_point &
          time_point() const { return clock_; }

  SysTime time() const;
  SysDate date() const;

  // SysDate::Day of week. [0-6]
  // 0sun 1mon 2tue 3wen 4thu 5fri 6sat
  int64_t day_of_week() const;

  /********* conversion *********/
  time_t          to_time_t   () const;
  std::tm         to_tm       () const;
  struct timespec to_timespec () const;
  struct timeval  to_timeval  () const;
  // strftime format + %L(msec) %K(usec) %N(nano sec)
  std::string     strftime    (std::string format = "%Y-%m-%d %H:%M:%S") const;
  std::string     to_string   (std::string format = "%Y-%m-%d %H:%M:%S.%L") const { return strftime(format); }

  /********* parsing *********/
  bool strptime   (const std::string &time_string,
                   const std::string &format = "%Y-%m-%d %H:%M:%S");
  // unstable function. only %Y %m %d %H %M %S %L(msec) %K(usec) %N(nano sec)
  bool from_string(const std::string &time_string,
                   const std::string &format = "%Y-%m-%d %H:%M:%S.%L");

  bool is_null    () const { return is_null_; }

  /********* set time *********/
  SysDateTime &set_current();
  SysDateTime &set_date    (const int64_t &year, const int64_t &month, const int64_t &day);
  SysDateTime &set_date    (const SysDate &date) { return set_date(date.year(), date.month(), date.day()); }

  SysDateTime &set_time    (const int64_t &hour, const int64_t &min,   const int64_t &sec, const SysTime::Millisec &millisec);
  SysDateTime &set_time    (const int64_t &hour, const int64_t &min,   const int64_t &sec, const SysTime::Microsec &microsec);
  SysDateTime &set_time    (const int64_t &hour, const int64_t &min,   const int64_t &sec, const SysTime::Nanosec  &nanosec = SysTime::Nanosec(0));
  SysDateTime &set_time    (const SysTime &time) { return set_time(time.hour(), time.min(), time.sec(), SysTime::Nanosec(time.nanosec())); }

  SysDateTime &set_datetime(const int64_t &year, const int64_t &month, const int64_t &day,
                            const int64_t &hour, const int64_t &min,   const int64_t &sec, const SysTime::Millisec &millisec);
  SysDateTime &set_datetime(const int64_t &year, const int64_t &month, const int64_t &day,
                            const int64_t &hour, const int64_t &min,   const int64_t &sec, const SysTime::Microsec &microsec);
  SysDateTime &set_datetime(const int64_t &year, const int64_t &month, const int64_t &day,
                            const int64_t &hour, const int64_t &min,   const int64_t &sec, const SysTime::Nanosec  &nanosec = SysTime::Nanosec(0));

  SysDateTime &set_year    (const int64_t &year);
  SysDateTime &set_month   (const int64_t &month);
  SysDateTime &set_day     (const int64_t &day);
  SysDateTime &set_hour    (const int64_t &hour);
  SysDateTime &set_min     (const int64_t &min);
  SysDateTime &set_sec     (const int64_t &sec);
  SysDateTime &set_millisec(const int64_t &millisec);
  SysDateTime &set_microsec(const int64_t &microsec);
  SysDateTime &set_nanosec (const int64_t &nanosec);

  template<typename T> SysDateTime &set(const T &value){ return operator= (value); }
  template<typename T> SysDateTime &add(const T &value){ return operator+=(value); }

  SysDateTime  first_time_of_day   () const;
  SysDateTime  first_day_of_month  () const;
  SysDateTime  first_time_of_month () const;

  SysDateTime  last_time_of_day    () const;
  SysDateTime  last_day_of_month   () const;
  SysDateTime  last_time_of_month  () const;

  /********* operator *********/
  SysDateTime &operator= (const SysDate           &value) { return set_date     (value);}
  SysDateTime &operator= (const SysTime           &value) { return set_time     (value);}
  SysDateTime &operator= (const SysDate::Year     &value) { return set_year     (value());}
  SysDateTime &operator= (const SysDate::Month    &value) { return set_month    (value());}
  SysDateTime &operator= (const SysDate::Day      &value) { return set_day      (value());}
  SysDateTime &operator= (const SysTime::Hour     &value) { return set_hour     (value());}
  SysDateTime &operator= (const SysTime::Min      &value) { return set_min      (value());}
  SysDateTime &operator= (const SysTime::Sec      &value) { return set_sec      (value());}
  SysDateTime &operator= (const SysTime::Millisec &value) { return set_millisec (value());}
  SysDateTime &operator= (const SysTime::Microsec &value) { return set_microsec (value());}
  SysDateTime &operator= (const SysTime::Nanosec  &value) { return set_nanosec  (value());}
  SysDateTime &operator= (const time_t            &value) { clock_ = time_t_to_time_point(value); is_null_ = false; return *this; }
  SysDateTime &operator= (std::tm                  value) { clock_ = time_t_to_time_point(std::mktime(&value)); is_null_ = false; return *this; }
  SysDateTime &operator= (const struct timespec   &value) { clock_ = nano_time_t_to_time_point (value.tv_sec, value.tv_nsec); is_null_ = false; return *this; }
  SysDateTime &operator= (const struct timeval    &value) { clock_ = micro_time_t_to_time_point(value.tv_sec, value.tv_usec); is_null_ = false; return *this; }

  SysDateTime &operator+=(const SysDate::Year     &value) { set_year  (year () + value()); return *this;  }
  SysDateTime &operator+=(const SysDate::Month    &value) { set_month (month() + value()); return *this;  }
  SysDateTime &operator+=(const SysDate::Day      &value) { clock_ += std::chrono::hours        (value()*24); is_null_ = false; return *this; }
  SysDateTime &operator+=(const SysTime::Hour     &value) { clock_ += std::chrono::hours        (value());    is_null_ = false; return *this; }
  SysDateTime &operator+=(const SysTime::Min      &value) { clock_ += std::chrono::minutes      (value());    is_null_ = false; return *this; }
  SysDateTime &operator+=(const SysTime::Sec      &value) { clock_ += std::chrono::seconds      (value());    is_null_ = false; return *this; }
  SysDateTime &operator+=(const SysTime::Millisec &value) { clock_ += std::chrono::milliseconds (value());    is_null_ = false; return *this; }
  SysDateTime &operator+=(const SysTime::Microsec &value) { clock_ += std::chrono::microseconds (value());    is_null_ = false; return *this; }
  SysDateTime &operator+=(const SysTime::Nanosec  &value) { clock_ += std::chrono::nanoseconds  (value());    is_null_ = false; return *this; }

  SysDateTime &operator-=(const SysDate::Year     &value) { set_year  (year () - value()); return *this; }
  SysDateTime &operator-=(const SysDate::Month    &value) { set_month (month() - value()); return *this; }
  SysDateTime &operator-=(const SysDate::Day      &value) { clock_ -= std::chrono::hours        (value()*24); is_null_ = false; return *this; }
  SysDateTime &operator-=(const SysTime::Hour     &value) { clock_ -= std::chrono::hours        (value());    is_null_ = false; return *this; }
  SysDateTime &operator-=(const SysTime::Min      &value) { clock_ -= std::chrono::minutes      (value());    is_null_ = false; return *this; }
  SysDateTime &operator-=(const SysTime::Sec      &value) { clock_ -= std::chrono::seconds      (value());    is_null_ = false; return *this; }
  SysDateTime &operator-=(const SysTime::Millisec &value) { clock_ -= std::chrono::milliseconds (value());    is_null_ = false; return *this; }
  SysDateTime &operator-=(const SysTime::Microsec &value) { clock_ -= std::chrono::microseconds (value());    is_null_ = false; return *this; }
  SysDateTime &operator-=(const SysTime::Nanosec  &value) { clock_ -= std::chrono::nanoseconds  (value());    is_null_ = false; return *this; }

  SysDateTime  operator+ (const SysDate::Year     &value) const { SysDateTime st = *this; return st.set_year  (st.year()  + value()); }
  SysDateTime  operator+ (const SysDate::Month    &value) const { SysDateTime st = *this; return st.set_month (st.month() + value()); }
  SysDateTime  operator+ (const SysDate::Day      &value) const { SysDateTime st = *this; st.clock_ += std::chrono::hours       (value()*24); st.is_null_ = false; return st; }
  SysDateTime  operator+ (const SysTime::Hour     &value) const { SysDateTime st = *this; st.clock_ += std::chrono::hours       (value());    st.is_null_ = false; return st; }
  SysDateTime  operator+ (const SysTime::Min      &value) const { SysDateTime st = *this; st.clock_ += std::chrono::minutes     (value());    st.is_null_ = false; return st; }
  SysDateTime  operator+ (const SysTime::Sec      &value) const { SysDateTime st = *this; st.clock_ += std::chrono::seconds     (value());    st.is_null_ = false; return st; }
  SysDateTime  operator+ (const SysTime::Millisec &value) const { SysDateTime st = *this; st.clock_ += std::chrono::milliseconds(value());    st.is_null_ = false; return st; }
  SysDateTime  operator+ (const SysTime::Microsec &value) const { SysDateTime st = *this; st.clock_ += std::chrono::microseconds(value());    st.is_null_ = false; return st; }
  SysDateTime  operator+ (const SysTime::Nanosec  &value) const { SysDateTime st = *this; st.clock_ += std::chrono::nanoseconds (value());    st.is_null_ = false; return st; }

  SysDateTime  operator- (const SysDate::Year     &value) const { SysDateTime st = *this; return st.set_year  (st.year()  - value()); }
  SysDateTime  operator- (const SysDate::Month    &value) const { SysDateTime st = *this; return st.set_month (st.month() - value()); }
  SysDateTime  operator- (const SysDate::Day      &value) const { SysDateTime st = *this; st.clock_ -= std::chrono::hours       (value()*24); st.is_null_ = false; return st; }
  SysDateTime  operator- (const SysTime::Hour     &value) const { SysDateTime st = *this; st.clock_ -= std::chrono::hours       (value());    st.is_null_ = false; return st; }
  SysDateTime  operator- (const SysTime::Min      &value) const { SysDateTime st = *this; st.clock_ -= std::chrono::minutes     (value());    st.is_null_ = false; return st; }
  SysDateTime  operator- (const SysTime::Sec      &value) const { SysDateTime st = *this; st.clock_ -= std::chrono::seconds     (value());    st.is_null_ = false; return st; }
  SysDateTime  operator- (const SysTime::Millisec &value) const { SysDateTime st = *this; st.clock_ -= std::chrono::milliseconds(value());    st.is_null_ = false; return st; }
  SysDateTime  operator- (const SysTime::Microsec &value) const { SysDateTime st = *this; st.clock_ -= std::chrono::microseconds(value());    st.is_null_ = false; return st; }
  SysDateTime  operator- (const SysTime::Nanosec  &value) const { SysDateTime st = *this; st.clock_ -= std::chrono::nanoseconds (value());    st.is_null_ = false; return st; }

  bool operator< (const SysDateTime &rhs) const { return clock_ <  rhs.clock_; }
  bool operator> (const SysDateTime &rhs) const { return clock_ >  rhs.clock_; }
  bool operator<=(const SysDateTime &rhs) const { return clock_ <= rhs.clock_; }
  bool operator>=(const SysDateTime &rhs) const { return clock_ >= rhs.clock_; }
  bool operator==(const SysDateTime &rhs) const { return clock_ == rhs.clock_; }

protected:
  enum
  {
    MILLISEC  = 1000LL,
    MICROSEC  = 1000000LL,
    NANOSEC   = 1000000000LL
  };

  static std::chrono::system_clock::time_point
  time_t_to_time_point(const int64_t &time_t)
  {
    return std::chrono::time_point<std::chrono::system_clock>(std::chrono::seconds(time_t));
  }

  static std::chrono::system_clock::time_point
  milli_time_t_to_time_point(const int64_t &time_t, const int64_t &millisec)
  {
    return std::chrono::time_point<std::chrono::system_clock>(std::chrono::milliseconds(time_t * MILLISEC + millisec));
  }

  static std::chrono::system_clock::time_point
  micro_time_t_to_time_point(const int64_t &time_t, const int64_t &microsec)
  {
    return std::chrono::time_point<std::chrono::system_clock>(std::chrono::microseconds(time_t * MICROSEC + microsec));
  }

  static std::chrono::system_clock::time_point
  nano_time_t_to_time_point(const int64_t &time_t, const int64_t &nanosec)
  {
    return std::chrono::time_point<std::chrono::system_clock>(std::chrono::nanoseconds(time_t * NANOSEC + nanosec));
  }

  static std::string
  to_stringf(const int64_t &value, const std::string &format = "%03ll")
  {
    int size_f = std::snprintf(nullptr, 0, format.c_str(), value) + 1;
    if (size_f <= 0) return "";

    char buff[size_f] = { 0, };
    std::snprintf(buff, sizeof(buff), format.c_str(), value);
    return buff;
  }

private:
  std::chrono::system_clock::time_point clock_;
  bool is_null_ = true;
};

#include "SysDateTime.inl"

#endif /* SYSDATETIME_H_ */
