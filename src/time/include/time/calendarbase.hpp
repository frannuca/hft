#ifndef CALENDARBASE_HPP
#define CALENDARBASE_HPP

#include "date.hpp"

namespace hft::time{

class CalendarBase{
    public:
    virtual ~CalendarBase() = default;    
    virtual bool is_holiday(const Date& date) const = 0;
    virtual Date next_business_day(const Date& date) const = 0;
    virtual Date prev_business_day(const Date& date) const = 0;
    virtual int day_in_between(const Date& start, const Date& end) const = 0;
};
}
#endif