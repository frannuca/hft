#ifndef CALENDARBASE_HPP
#define CALENDARBASE_HPP

#include "date.hpp"

namespace hft::time
{

class CalendarBase
{
  public:
    virtual ~CalendarBase() = default;
    virtual bool is_holiday(const Date &date) const = 0;
    virtual Date next_business_day(const Date &date) const;
    virtual Date prev_business_day(const Date &date) const;
    virtual int day_in_between(const Date &start, const Date &end) const;
};

class CalendarNYSE : public CalendarBase
{
    virtual bool is_holiday(const Date &date) const override;
};

class CalendarLSE : public CalendarBase
{
    virtual bool is_holiday(const Date &date) const override;
};

class CalendarTSE : public CalendarBase
{
    virtual bool is_holiday(const Date &date) const override;
};

class CalendarHKEX : public CalendarBase
{
    virtual bool is_holiday(const Date &date) const override;
};

class CalendarSSE : public CalendarBase
{
    virtual bool is_holiday(const Date &date) const override;
};
class CalendarEuronext : public CalendarBase
{
    virtual bool is_holiday(const Date &date) const override;
};

class CalendarASX : public CalendarBase
{
    virtual bool is_holiday(const Date &date) const override;
};

class CalendarTSX : public CalendarBase
{
    virtual bool is_holiday(const Date &date) const override;
};

class CalendarNSE : public CalendarBase
{
    virtual bool is_holiday(const Date &date) const override;
};

class CalendarBSE : public CalendarBase
{
    virtual bool is_holiday(const Date &date) const override;
};

} // namespace hft::time
#endif