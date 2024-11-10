#ifndef CALENDARS_ENUM_HPP
#define CALENDARS_ENUM_HPP

namespace hft::time {

enum class FinancialCalendar {
    NYSE,       // New York Stock Exchange
    LSE,        // London Stock Exchange
    TSE,        // Tokyo Stock Exchange
    HKEX,       // Hong Kong Stock Exchange
    SSE,        // Shanghai Stock Exchange
    Euronext,   // Euronext
    ASX,        // Australian Securities Exchange
    TSX,        // Toronto Stock Exchange
    BSE,        // Bombay Stock Exchange
    NSE         // National Stock Exchange of India
};

} // namespace hft::time

#endif // CALENDARS_ENUM_HPP