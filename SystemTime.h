#ifndef SYSTEMTIME_H_
#define SYSTEMTIME_H_

#include <string>
#include <chrono>

class SystemTime
{
public:
  /********* classes for operation *********/
  struct Year     { Year    ():value(1970){}; Year    (const int64_t &value):value(value){}; const int64_t &operator()() const { return value; }; int64_t value; };
  struct Month    { Month   ():value(1)   {}; Month   (const int64_t &value):value(value){}; const int64_t &operator()() const { return value; }; int64_t value; };
  struct Day      { Day     ():value(1)   {}; Day     (const int64_t &value):value(value){}; const int64_t &operator()() const { return value; }; int64_t value; };
  struct Hour     { Hour    ():value(0)   {}; Hour    (const int64_t &value):value(value){}; const int64_t &operator()() const { return value; }; int64_t value; };
  struct Min      { Min     ():value(0)   {}; Min     (const int64_t &value):value(value){}; const int64_t &operator()() const { return value; }; int64_t value; };
  struct Sec      { Sec     ():value(0)   {}; Sec     (const int64_t &value):value(value){}; const int64_t &operator()() const { return value; }; int64_t value; };
  struct Millisec { Millisec():value(0)   {}; Millisec(const int64_t &value):value(value){}; const int64_t &operator()() const { return value; }; int64_t value; };
  struct Microsec { Microsec():value(0)   {}; Microsec(const int64_t &value):value(value){}; const int64_t &operator()() const { return value; }; int64_t value; };
  struct Nanosec  { Nanosec ():value(0)   {}; Nanosec (const int64_t &value):value(value){}; const int64_t &operator()() const { return value; }; int64_t value; };

  static SystemTime now() { return SystemTime().set_current(); }

  /********* constructor *********/
  SystemTime() {}
  SystemTime(const time_t           &value) { *this = value; } // nanosec is zero
  SystemTime(const std::tm          &value) { *this = value; } // nanosec is zero
  SystemTime(const struct timespec  &value) { *this = value; }
  SystemTime(const struct timeval   &value) { *this = value; }
  SystemTime(const std::chrono::system_clock::time_point &value) : is_null_(false), clock_(value) {}

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
  SystemTime &set_current();
  SystemTime &set_date    (const int64_t &year, const int64_t &month, const int64_t &day);
  SystemTime &set_time    (const int64_t &hour, const int64_t &min,   const int64_t &sec, const Millisec &millisec);
  SystemTime &set_time    (const int64_t &hour, const int64_t &min,   const int64_t &sec, const Microsec &microsec);
  SystemTime &set_time    (const int64_t &hour, const int64_t &min,   const int64_t &sec, const Nanosec  &nanosec = Nanosec(0));
  SystemTime &set_datetime(const int64_t &year, const int64_t &month, const int64_t &day,
                           const int64_t &hour, const int64_t &min,   const int64_t &sec, const Millisec &millisec);
  SystemTime &set_datetime(const int64_t &year, const int64_t &month, const int64_t &day,
                           const int64_t &hour, const int64_t &min,   const int64_t &sec, const Microsec &microsec);
  SystemTime &set_datetime(const int64_t &year, const int64_t &month, const int64_t &day,
                           const int64_t &hour, const int64_t &min,   const int64_t &sec, const Nanosec  &nanosec = Nanosec(0));

  SystemTime &set_year    (const int64_t &year);
  SystemTime &set_month   (const int64_t &month);
  SystemTime &set_day     (const int64_t &day);
  SystemTime &set_hour    (const int64_t &hour);
  SystemTime &set_min     (const int64_t &min);
  SystemTime &set_sec     (const int64_t &sec);
  SystemTime &set_millisec(const int64_t &millisec);
  SystemTime &set_microsec(const int64_t &microsec);
  SystemTime &set_nanosec (const int64_t &nanosec);

  template<typename T> SystemTime &set(const T &value){ return operator= (value); }
  template<typename T> SystemTime &add(const T &value){ return operator+=(value); }

  SystemTime  first_time_of_day   () const;
  SystemTime  first_day_of_month  () const;
  SystemTime  first_time_of_month () const;

  SystemTime  last_time_of_day    () const;
  SystemTime  last_day_of_month   () const;
  SystemTime  last_time_of_month  () const;

  /********* operator *********/
  SystemTime &operator= (const Year     &value) { return set_year     (value());}
  SystemTime &operator= (const Month    &value) { return set_month    (value());}
  SystemTime &operator= (const Day      &value) { return set_day      (value());}
  SystemTime &operator= (const Hour     &value) { return set_hour     (value());}
  SystemTime &operator= (const Min      &value) { return set_min      (value());}
  SystemTime &operator= (const Sec      &value) { return set_sec      (value());}
  SystemTime &operator= (const Millisec &value) { return set_millisec (value());}
  SystemTime &operator= (const Microsec &value) { return set_microsec (value());}
  SystemTime &operator= (const Nanosec  &value) { return set_nanosec  (value());}
  SystemTime &operator= (const time_t   &value) { clock_ = time_t_to_time_point(value); is_null_ = false; return *this; }
  SystemTime &operator= (std::tm         value) { clock_ = time_t_to_time_point(std::mktime(&value)); is_null_ = false; return *this; }
  SystemTime &operator= (const struct timespec &value) { clock_ = nano_time_t_to_time_point (value.tv_sec, value.tv_nsec); is_null_ = false; return *this; }
  SystemTime &operator= (const struct timeval  &value) { clock_ = micro_time_t_to_time_point(value.tv_sec, value.tv_usec); is_null_ = false; return *this; }

  SystemTime  operator+ (const Year     &value) { SystemTime st = *this; return st.set_year  (st.year()  + value()); }
  SystemTime  operator+ (const Month    &value) { SystemTime st = *this; return st.set_month (st.month() + value()); }
  SystemTime  operator+ (const Day      &value) { SystemTime st = *this; st.clock_ += std::chrono::hours       (value()*24); st.is_null_ = false; return st; }
  SystemTime  operator+ (const Hour     &value) { SystemTime st = *this; st.clock_ += std::chrono::hours       (value());    st.is_null_ = false; return st; }
  SystemTime  operator+ (const Min      &value) { SystemTime st = *this; st.clock_ += std::chrono::minutes     (value());    st.is_null_ = false; return st; }
  SystemTime  operator+ (const Sec      &value) { SystemTime st = *this; st.clock_ += std::chrono::seconds     (value());    st.is_null_ = false; return st; }
  SystemTime  operator+ (const Millisec &value) { SystemTime st = *this; st.clock_ += std::chrono::milliseconds(value());    st.is_null_ = false; return st; }
  SystemTime  operator+ (const Microsec &value) { SystemTime st = *this; st.clock_ += std::chrono::microseconds(value());    st.is_null_ = false; return st; }
  SystemTime  operator+ (const Nanosec  &value) { SystemTime st = *this; st.clock_ += std::chrono::nanoseconds (value());    st.is_null_ = false; return st; }

  SystemTime  operator- (const Year     &value) { SystemTime st = *this; return st.set_year  (st.year()  - value()); }
  SystemTime  operator- (const Month    &value) { SystemTime st = *this; return st.set_month (st.month() - value()); }
  SystemTime  operator- (const Day      &value) { SystemTime st = *this; st.clock_ -= std::chrono::hours       (value()*24); st.is_null_ = false; return st; }
  SystemTime  operator- (const Hour     &value) { SystemTime st = *this; st.clock_ -= std::chrono::hours       (value());    st.is_null_ = false; return st; }
  SystemTime  operator- (const Min      &value) { SystemTime st = *this; st.clock_ -= std::chrono::minutes     (value());    st.is_null_ = false; return st; }
  SystemTime  operator- (const Sec      &value) { SystemTime st = *this; st.clock_ -= std::chrono::seconds     (value());    st.is_null_ = false; return st; }
  SystemTime  operator- (const Millisec &value) { SystemTime st = *this; st.clock_ -= std::chrono::milliseconds(value());    st.is_null_ = false; return st; }
  SystemTime  operator- (const Microsec &value) { SystemTime st = *this; st.clock_ -= std::chrono::microseconds(value());    st.is_null_ = false; return st; }
  SystemTime  operator- (const Nanosec  &value) { SystemTime st = *this; st.clock_ -= std::chrono::nanoseconds (value());    st.is_null_ = false; return st; }

  SystemTime &operator+=(const Year     &value) { set_year  (year () + value()); return *this;  }
  SystemTime &operator+=(const Month    &value) { set_month (month() + value()); return *this;  }
  SystemTime &operator+=(const Day      &value) { clock_ += std::chrono::hours        (value()*24); is_null_ = false; return *this; }
  SystemTime &operator+=(const Hour     &value) { clock_ += std::chrono::hours        (value());    is_null_ = false; return *this; }
  SystemTime &operator+=(const Min      &value) { clock_ += std::chrono::minutes      (value());    is_null_ = false; return *this; }
  SystemTime &operator+=(const Sec      &value) { clock_ += std::chrono::seconds      (value());    is_null_ = false; return *this; }
  SystemTime &operator+=(const Millisec &value) { clock_ += std::chrono::milliseconds (value());    is_null_ = false; return *this; }
  SystemTime &operator+=(const Microsec &value) { clock_ += std::chrono::microseconds (value());    is_null_ = false; return *this; }
  SystemTime &operator+=(const Nanosec  &value) { clock_ += std::chrono::nanoseconds  (value());    is_null_ = false; return *this; }

  SystemTime &operator-=(const Year     &value) { set_year  (year () - value()); return *this; }
  SystemTime &operator-=(const Month    &value) { set_month (month() - value()); return *this; }
  SystemTime &operator-=(const Day      &value) { clock_ -= std::chrono::hours        (value()*24); is_null_ = false; return *this; }
  SystemTime &operator-=(const Hour     &value) { clock_ -= std::chrono::hours        (value());    is_null_ = false; return *this; }
  SystemTime &operator-=(const Min      &value) { clock_ -= std::chrono::minutes      (value());    is_null_ = false; return *this; }
  SystemTime &operator-=(const Sec      &value) { clock_ -= std::chrono::seconds      (value());    is_null_ = false; return *this; }
  SystemTime &operator-=(const Millisec &value) { clock_ -= std::chrono::milliseconds (value());    is_null_ = false; return *this; }
  SystemTime &operator-=(const Microsec &value) { clock_ -= std::chrono::microseconds (value());    is_null_ = false; return *this; }
  SystemTime &operator-=(const Nanosec  &value) { clock_ -= std::chrono::nanoseconds  (value());    is_null_ = false; return *this; }

  bool operator< (const SystemTime &rhs) const { return clock_ <  rhs.clock_; }
  bool operator> (const SystemTime &rhs) const { return clock_ >  rhs.clock_; }
  bool operator<=(const SystemTime &rhs) const { return clock_ <= rhs.clock_; }
  bool operator>=(const SystemTime &rhs) const { return clock_ >= rhs.clock_; }
  bool operator==(const SystemTime &rhs) const { return clock_ == rhs.clock_; }

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

#include "SystemTime.inl"

#endif /* SYSTEMTIME_H_ */
