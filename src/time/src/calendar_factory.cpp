#include "time/calendar_factory.hpp"
#include "time/calendarsenum.hpp"

using namespace hft::time;

std::shared_ptr<CalendarBase> create_calendar(FinancialCalendar calendar){
    switch(calendar){
        case FinancialCalendar::NYSE:
            throw std::runtime_error("Not implemented");
        case FinancialCalendar::LSE:
            throw std::runtime_error("Not implemented");
        case FinancialCalendar::TSE:
            throw std::runtime_error("Not implemented");
        case FinancialCalendar::HKEX:
            throw std::runtime_error("Not implemented");
        case FinancialCalendar::SSE:
            throw std::runtime_error("Not implemented");
        case FinancialCalendar::Euronext:
            throw std::runtime_error("Not implemented");
        case FinancialCalendar::ASX:
            throw std::runtime_error("Not implemented");
        case FinancialCalendar::TSX:
            throw std::runtime_error("Not implemented");
        case FinancialCalendar::BSE:
            throw std::runtime_error("Not implemented");
        case FinancialCalendar::NSE:
            throw std::runtime_error("Not implemented");
    }
    return nullptr;
}

std::string name(FinancialCalendar calendar){
    switch(calendar){
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