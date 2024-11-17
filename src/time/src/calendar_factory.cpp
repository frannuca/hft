#include "time/calendar_factory.hpp"
#include "time/calendars.hpp"
#include "time/calendarsenum.hpp"
#include <memory>

using namespace hft::time;

std::shared_ptr<CalendarBase> hft::time::create_calendar(FinancialCalendar calendar)
{

    switch (calendar)
    {
    case FinancialCalendar::NYSE:
        return std::make_unique<CalendarNYSE>();
    case FinancialCalendar::LSE:
        return std::make_unique<CalendarLSE>();
    case FinancialCalendar::TSE:
        return std::make_unique<CalendarTSE>();
    case FinancialCalendar::HKEX:
        return std::make_unique<CalendarHKEX>();
    case FinancialCalendar::SSE:
        return std::make_unique<CalendarSSE>();
    case FinancialCalendar::Euronext:
        return std::make_unique<CalendarEuronext>();
    case FinancialCalendar::ASX:
        return std::make_unique<CalendarASX>();
    case FinancialCalendar::TSX:
        return std::make_unique<CalendarTSX>();
    case FinancialCalendar::BSE:
        return std::make_unique<CalendarBSE>();
    case FinancialCalendar::NSE:
        return std::make_unique<CalendarNSE>();
    default:
        throw std::invalid_argument("Unknown FinancialCalendar value");
    }
}

std::string hft::time::name(FinancialCalendar calendar)
{
    switch (calendar)
    {
    case FinancialCalendar::NYSE:
        return "New York Stock Exchange";
    case FinancialCalendar::LSE:
        return "London Stock Exchange";
    case FinancialCalendar::TSE:
        return "Tokyo Stock Exchange";
    case FinancialCalendar::HKEX:
        return "Hong Kong Stock Exchange";
    case FinancialCalendar::SSE:
        return "Shanghai Stock Exchange";
    case FinancialCalendar::Euronext:
        return "Euronext";
    case FinancialCalendar::ASX:
        return "Australian Securities Exchange";
    case FinancialCalendar::TSX:
        return "Toronto Stock Exchange";
    case FinancialCalendar::BSE:
        return "Bombay Stock Exchange";
    case FinancialCalendar::NSE:
        return "National Stock Exchange of India";
    }
    return "";
}