#ifndef TIME_CALENDAR_FACTORY_HPP
#define TIME_CALENDAR_FACTORY_HPP


#include "calendarbase.hpp"
#include "calendarsenum.hpp"
#include <memory>

namespace hft::time{
    std::shared_ptr<CalendarBase> create_calendar(FinancialCalendar calendar);
    std::string name(FinancialCalendar calendar);
}

#endif //TIME_CALENDAR_FACTORY_HPP