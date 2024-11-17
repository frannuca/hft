#include "time/calendars.hpp"
#include <chrono>
#include <set>
namespace
{
auto increment1Day = [](auto d, int days)
{ return std::chrono::year_month_day(std::chrono::sys_days(d) + std::chrono::days{days}); };

std::chrono::year_month_day adjust_observed(std::chrono::year_month_day date)
{
    auto wd = std::chrono::weekday(std::chrono::sys_days(date));
    if (wd == std::chrono::Saturday)
    {
        return std::chrono::sys_days(date) - std::chrono::days{1}; // Observed on Friday
    }
    else if (wd == std::chrono::Sunday)
    {
        return std::chrono::sys_days(date) + std::chrono::days{1}; // Observed on Monday
    }
    return date;
}
// Helper function to check if a date is a weekend (Saturday or Sunday)
bool is_weekend(std::chrono::year_month_day date)
{
    auto weekday = std::chrono::weekday(std::chrono::sys_days(date));
    return weekday == std::chrono::Saturday || weekday == std::chrono::Sunday;
}
} // namespace

namespace hft::time
{

Date CalendarBase::next_business_day(const Date &date) const
{

    Date next_day = increment1Day(date, 1);
    const int max_days = 10;
    int counter = 0;
    while (is_holiday(next_day) && counter++ <= max_days)
    {
        next_day = increment1Day(next_day, 1);
    }
    if (max_days == counter)
    {
        throw std::runtime_error("Cannot find next business day");
    }

    return next_day;
}

Date CalendarBase::prev_business_day(const Date &date) const
{
    Date prev_day = increment1Day(date, -1);
    const int max_days = 10;
    int counter = 0;
    while (is_holiday(prev_day) && counter++ <= max_days)
    {
        prev_day = increment1Day(prev_day, -1);
    }
    if (max_days == counter)
    {
        throw std::runtime_error("Cannot find next business day");
    }

    return prev_day;
}

int CalendarBase::day_in_between(const Date &start, const Date &end) const
{
    std::chrono::sys_days date = start;
    int days = 0;
    while (date <= end)
    {
        date = next_business_day(date);
        days++;
    }

    return days;
}

bool CalendarNYSE::is_holiday(const Date &date) const
{

    using namespace std::chrono;

    auto year = date.year();

    // Static NYSE holidays
    std::set<year_month_day> holidays = {
        adjust_observed(year / January / 1),  // New Year's Day
        adjust_observed(year / July / 4),     // Independence Day
        adjust_observed(year / December / 25) // Christmas Day
    };

    // Martin Luther King Jr. Day (Third Monday of January)
    auto mlk_day = year / January / 1;
    while (std::chrono::weekday(std::chrono::sys_days(mlk_day)) != std::chrono::Monday || mlk_day.day() > day(15))
        mlk_day = sys_days(mlk_day) + std::chrono::days{1};
    holidays.insert(mlk_day);

    // Presidents' Day (Third Monday of February)
    auto presidents_day = year / February / 1;
    while (std::chrono::weekday(std::chrono::sys_days(presidents_day)) != std::chrono::Monday ||
           presidents_day.day() > day(15))
        presidents_day = sys_days(presidents_day) + std::chrono::days{1};
    holidays.insert(presidents_day);

    // Thanksgiving Day (Fourth Thursday of November)
    auto thanksgiving_day = year / November / 1;
    while (std::chrono::weekday(std::chrono::sys_days(thanksgiving_day)) != std::chrono::Thursday ||
           thanksgiving_day.day() > day(20))
        thanksgiving_day = sys_days(thanksgiving_day) + std::chrono::days{1};
    holidays.insert(thanksgiving_day);

    return (holidays.find(date) != holidays.end()) || is_weekend(date);
}

bool CalendarLSE::is_holiday(const Date &date) const
{
    using namespace std::chrono;

    auto year = date.year();

    // Static LSE holidays
    std::set<year_month_day> holidays = {
        adjust_observed(year / January / 1),   // New Year's Day
        adjust_observed(year / December / 25), // Christmas Day
        adjust_observed(year / December / 26)  // Boxing Day
    };

    // Good Friday (Friday before Easter Sunday)
    auto easter_sunday = year / April / 1;
    while (std::chrono::weekday(std::chrono::sys_days(easter_sunday)) != std::chrono::Sunday)
        easter_sunday = sys_days(easter_sunday) + std::chrono::days{1};
    auto good_friday = sys_days(easter_sunday) - std::chrono::days{2};
    holidays.insert(good_friday);

    // Easter Monday (Monday after Easter Sunday)
    auto easter_monday = sys_days(easter_sunday) + std::chrono::days{1};
    holidays.insert(easter_monday);

    // Early May Bank Holiday (First Monday of May)
    auto early_may_bank_holiday = year / May / 1;
    while (std::chrono::weekday(std::chrono::sys_days(early_may_bank_holiday)) != std::chrono::Monday)
        early_may_bank_holiday = sys_days(early_may_bank_holiday) + std::chrono::days{1};
    holidays.insert(early_may_bank_holiday);

    // Spring Bank Holiday (Last Monday of May)
    auto spring_bank_holiday = year / May / 31;
    while (std::chrono::weekday(std::chrono::sys_days(spring_bank_holiday)) != std::chrono::Monday)
        spring_bank_holiday = sys_days(spring_bank_holiday) - std::chrono::days{1};
    holidays.insert(spring_bank_holiday);

    // Summer Bank Holiday (Last Monday of August)
    auto summer_bank_holiday = year / August / 31;
    while (std::chrono::weekday(std::chrono::sys_days(summer_bank_holiday)) != std::chrono::Monday)
        summer_bank_holiday = sys_days(summer_bank_holiday) - std::chrono::days{1};
    holidays.insert(summer_bank_holiday);

    return (holidays.find(date) != holidays.end()) || is_weekend(date);
}; // namespace hft::time

bool CalendarTSE::is_holiday(const Date &date) const
{
    using namespace std::chrono;

    auto year = date.year();

    // Static TSE holidays
    std::set<year_month_day> holidays = {
        adjust_observed(year / January / 1),   // New Year's Day
        adjust_observed(year / December / 23), // Emperor's Birthday
        adjust_observed(year / December / 25)  // Christmas Day
    };

    // Coming of Age Day (Second Monday of January)
    auto coming_of_age_day = year / January / 1;
    while (std::chrono::weekday(std::chrono::sys_days(coming_of_age_day)) != std::chrono::Monday ||
           coming_of_age_day.day() > day(8))
        coming_of_age_day = sys_days(coming_of_age_day) + std::chrono::days{1};
    holidays.insert(coming_of_age_day);

    // Vernal Equinox Day (Around March 20)
    holidays.insert(year / March / 20);

    // Showa Day (April 29)
    holidays.insert(year / April / 29);

    // Constitution Memorial Day (May 3)
    holidays.insert(year / May / 3);

    // Greenery Day (May 4)
    holidays.insert(year / May / 4);

    // Children's Day (May 5)
    holidays.insert(year / May / 5);

    // Marine Day (Third Monday of July)
    auto marine_day = year / July / 1;
    while (std::chrono::weekday(std::chrono::sys_days(marine_day)) != std::chrono::Monday || marine_day.day() > day(15))
        marine_day = sys_days(marine_day) + std::chrono::days{1};
    holidays.insert(marine_day);

    // Mountain Day (August 11)
    holidays.insert(year / August / 11);

    // Respect for the Aged Day (Third Monday of September)
    auto respect_for_aged_day = year / September / 1;
    while (std::chrono::weekday(std::chrono::sys_days(respect_for_aged_day)) != std::chrono::Monday ||
           respect_for_aged_day.day() > day(15))
        respect_for_aged_day = sys_days(respect_for_aged_day) + std::chrono::days{1};
    holidays.insert(respect_for_aged_day);

    // Autumnal Equinox Day (Around September 23)
    holidays.insert(year / September / 23);

    // Health and Sports Day (Second Monday of October)
    auto health_and_sports_day = year / October / 1;
    while (std::chrono::weekday(std::chrono::sys_days(health_and_sports_day)) != std::chrono::Monday ||
           health_and_sports_day.day() > day(8))
        health_and_sports_day = sys_days(health_and_sports_day) + std::chrono::days{1};
    holidays.insert(health_and_sports_day);

    // Culture Day (November 3)
    holidays.insert(year / November / 3);

    // Labor Thanksgiving Day (November 23)
    holidays.insert(year / November / 23);

    return (holidays.find(date) != holidays.end()) || is_weekend(date);
};

bool CalendarHKEX::is_holiday(const Date &date) const
{
    using namespace std::chrono;

    auto year = date.year();

    // Static HKEX holidays
    std::set<year_month_day> holidays = {
        adjust_observed(year / January / 1),  // New Year's Day
        adjust_observed(year / July / 1),     // HKSAR Establishment Day
        adjust_observed(year / October / 1),  // National Day
        adjust_observed(year / December / 25) // Christmas Day
    };

    // Lunar New Year (First three days of the Lunar New Year)
    // Note: This requires a conversion from Gregorian to Lunar calendar, which is complex and not shown here.
    // Placeholder dates for demonstration purposes:
    holidays.insert(year / February / 12);
    holidays.insert(year / February / 13);
    holidays.insert(year / February / 14);

    // Ching Ming Festival (April 4 or 5)
    holidays.insert(year / April / 4);

    // Good Friday (Friday before Easter Sunday)
    auto easter_sunday = year / April / 1;
    while (std::chrono::weekday(std::chrono::sys_days(easter_sunday)) != std::chrono::Sunday)
        easter_sunday = sys_days(easter_sunday) + std::chrono::days{1};
    auto good_friday = sys_days(easter_sunday) - std::chrono::days{2};
    holidays.insert(good_friday);

    // Easter Monday (Monday after Easter Sunday)
    auto easter_monday = sys_days(easter_sunday) + std::chrono::days{1};
    holidays.insert(easter_monday);

    // Labour Day (May 1)
    holidays.insert(year / May / 1);

    // Tuen Ng Festival (Dragon Boat Festival, fifth day of the fifth lunar month)
    // Placeholder date for demonstration purposes:
    holidays.insert(year / June / 14);

    // Mid-Autumn Festival (Day after the Mid-Autumn Festival)
    // Placeholder date for demonstration purposes:
    holidays.insert(year / September / 22);

    // Chung Yeung Festival (Ninth day of the ninth lunar month)
    // Placeholder date for demonstration purposes:
    holidays.insert(year / October / 14);

    return (holidays.find(date) != holidays.end()) || is_weekend(date);
};

bool CalendarSSE::is_holiday(const Date &date) const
{
    using namespace std::chrono;

    auto year = date.year();

    // Static SSE holidays
    std::set<year_month_day> holidays = {
        adjust_observed(year / January / 1), // New Year's Day
        adjust_observed(year / May / 1),     // Labour Day
        adjust_observed(year / October / 1), // National Day
        adjust_observed(year / October / 2), // National Day Holiday
        adjust_observed(year / October / 3)  // National Day Holiday
    };

    // Chinese New Year (First three days of the Lunar New Year)
    // Note: This requires a conversion from Gregorian to Lunar calendar, which is complex and not shown here.
    // Placeholder dates for demonstration purposes:
    holidays.insert(year / February / 12);
    holidays.insert(year / February / 13);
    holidays.insert(year / February / 14);

    // Qingming Festival (April 4 or 5)
    holidays.insert(year / April / 4);

    // Dragon Boat Festival (fifth day of the fifth lunar month)
    // Placeholder date for demonstration purposes:
    holidays.insert(year / June / 14);

    // Mid-Autumn Festival (Day after the Mid-Autumn Festival)
    // Placeholder date for demonstration purposes:
    holidays.insert(year / September / 22);

    return (holidays.find(date) != holidays.end()) || is_weekend(date);
};

bool CalendarEuronext::is_holiday(const Date &date) const
{
    using namespace std::chrono;

    auto year = date.year();

    // Static Euronext holidays
    std::set<year_month_day> holidays = {
        adjust_observed(year / January / 1),   // New Year's Day
        adjust_observed(year / December / 25), // Christmas Day
        adjust_observed(year / December / 26)  // Boxing Day
    };

    // Good Friday (Friday before Easter Sunday)
    auto easter_sunday = year / April / 1;
    while (std::chrono::weekday(std::chrono::sys_days(easter_sunday)) != std::chrono::Sunday)
        easter_sunday = sys_days(easter_sunday) + std::chrono::days{1};
    auto good_friday = sys_days(easter_sunday) - std::chrono::days{2};
    holidays.insert(good_friday);

    // Easter Monday (Monday after Easter Sunday)
    auto easter_monday = sys_days(easter_sunday) + std::chrono::days{1};
    holidays.insert(easter_monday);

    // Labour Day (May 1)
    holidays.insert(year / May / 1);

    // Ascension Day (39 days after Easter Sunday)
    auto ascension_day = sys_days(easter_sunday) + std::chrono::days{39};
    holidays.insert(ascension_day);

    // Whit Monday (50 days after Easter Sunday)
    auto whit_monday = sys_days(easter_sunday) + std::chrono::days{50};
    holidays.insert(whit_monday);

    // Bastille Day (July 14)
    holidays.insert(year / July / 14);

    // All Saints' Day (November 1)
    holidays.insert(year / November / 1);

    // Armistice Day (November 11)
    holidays.insert(year / November / 11);

    return (holidays.find(date) != holidays.end()) || is_weekend(date);
};

bool CalendarASX::is_holiday(const Date &date) const
{
    using namespace std::chrono;

    auto year = date.year();

    // Static ASX holidays
    std::set<year_month_day> holidays = {
        adjust_observed(year / January / 1),   // New Year's Day
        adjust_observed(year / January / 26),  // Australia Day
        adjust_observed(year / December / 25), // Christmas Day
        adjust_observed(year / December / 26)  // Boxing Day
    };

    // Good Friday (Friday before Easter Sunday)
    auto easter_sunday = year / April / 1;
    while (std::chrono::weekday(std::chrono::sys_days(easter_sunday)) != std::chrono::Sunday)
        easter_sunday = sys_days(easter_sunday) + std::chrono::days{1};
    auto good_friday = sys_days(easter_sunday) - std::chrono::days{2};
    holidays.insert(good_friday);

    // Easter Monday (Monday after Easter Sunday)
    auto easter_monday = sys_days(easter_sunday) + std::chrono::days{1};
    holidays.insert(easter_monday);

    // ANZAC Day (April 25)
    holidays.insert(year / April / 25);

    // Queen's Birthday (Second Monday in June)
    auto queens_birthday = year / June / 1;
    while (std::chrono::weekday(std::chrono::sys_days(queens_birthday)) != std::chrono::Monday ||
           queens_birthday.day() > day(8))
        queens_birthday = sys_days(queens_birthday) + std::chrono::days{1};
    holidays.insert(queens_birthday);

    // Labour Day (First Monday in October)
    auto labour_day = year / October / 1;
    while (std::chrono::weekday(std::chrono::sys_days(labour_day)) != std::chrono::Monday)
        labour_day = sys_days(labour_day) + std::chrono::days{1};
    holidays.insert(labour_day);

    return (holidays.find(date) != holidays.end()) || is_weekend(date);
};

bool CalendarTSX::is_holiday(const Date &date) const
{
    using namespace std::chrono;

    auto year = date.year();

    // Static TSX holidays
    std::set<year_month_day> holidays = {
        adjust_observed(year / January / 1),   // New Year's Day
        adjust_observed(year / July / 1),      // Canada Day
        adjust_observed(year / December / 25), // Christmas Day
        adjust_observed(year / December / 26)  // Boxing Day
    };

    // Family Day (Third Monday of February)
    auto family_day = year / February / 1;
    while (std::chrono::weekday(std::chrono::sys_days(family_day)) != std::chrono::Monday || family_day.day() > day(15))
        family_day = sys_days(family_day) + std::chrono::days{1};
    holidays.insert(family_day);

    // Good Friday (Friday before Easter Sunday)
    auto easter_sunday = year / April / 1;
    while (std::chrono::weekday(std::chrono::sys_days(easter_sunday)) != std::chrono::Sunday)
        easter_sunday = sys_days(easter_sunday) + std::chrono::days{1};
    auto good_friday = sys_days(easter_sunday) - std::chrono::days{2};
    holidays.insert(good_friday);

    // Easter Monday (Monday after Easter Sunday)
    auto easter_monday = sys_days(easter_sunday) + std::chrono::days{1};
    holidays.insert(easter_monday);

    // Victoria Day (Last Monday before May 25)
    auto victoria_day = year / May / 24;
    while (std::chrono::weekday(std::chrono::sys_days(victoria_day)) != std::chrono::Monday)
        victoria_day = sys_days(victoria_day) - std::chrono::days{1};
    holidays.insert(victoria_day);

    // Labour Day (First Monday of September)
    auto labour_day = year / September / 1;
    while (std::chrono::weekday(std::chrono::sys_days(labour_day)) != std::chrono::Monday)
        labour_day = sys_days(labour_day) + std::chrono::days{1};
    holidays.insert(labour_day);

    // Thanksgiving Day (Second Monday of October)
    auto thanksgiving_day = year / October / 1;
    while (std::chrono::weekday(std::chrono::sys_days(thanksgiving_day)) != std::chrono::Monday ||
           thanksgiving_day.day() > day(8))
        thanksgiving_day = sys_days(thanksgiving_day) + std::chrono::days{1};
    holidays.insert(thanksgiving_day);

    return (holidays.find(date) != holidays.end()) || is_weekend(date);
};

bool CalendarNSE::is_holiday(const Date &date) const
{
    using namespace std::chrono;

    auto year = date.year();

    // Static NSE holidays
    std::set<year_month_day> holidays = {
        adjust_observed(year / January / 26), // Republic Day
        adjust_observed(year / August / 15),  // Independence Day
        adjust_observed(year / October / 2),  // Gandhi Jayanti
        adjust_observed(year / December / 25) // Christmas Day
    };

    // Holi (March 10, placeholder date)
    holidays.insert(year / March / 10);

    // Mahavir Jayanti (April 6, placeholder date)
    holidays.insert(year / April / 6);

    // Good Friday (Friday before Easter Sunday)
    auto easter_sunday = year / April / 1;
    while (std::chrono::weekday(std::chrono::sys_days(easter_sunday)) != std::chrono::Sunday)
        easter_sunday = sys_days(easter_sunday) + std::chrono::days{1};
    auto good_friday = sys_days(easter_sunday) - std::chrono::days{2};
    holidays.insert(good_friday);

    // Eid-ul-Fitr (May 24, placeholder date)
    holidays.insert(year / May / 24);

    // Eid-ul-Adha (July 31, placeholder date)
    holidays.insert(year / July / 31);

    // Diwali (November 14, placeholder date)
    holidays.insert(year / November / 14);

    // Guru Nanak Jayanti (November 30, placeholder date)
    holidays.insert(year / November / 30);

    return (holidays.find(date) != holidays.end()) || is_weekend(date);
};

bool CalendarBSE::is_holiday(const Date &date) const
{
    using namespace std::chrono;

    auto year = date.year();

    // Static BSE holidays
    std::set<year_month_day> holidays = {
        adjust_observed(year / January / 26), // Republic Day
        adjust_observed(year / August / 15),  // Independence Day
        adjust_observed(year / October / 2),  // Gandhi Jayanti
        adjust_observed(year / December / 25) // Christmas Day
    };

    // Holi (March 10, placeholder date)
    holidays.insert(year / March / 10);

    // Mahavir Jayanti (April 6, placeholder date)
    holidays.insert(year / April / 6);

    // Good Friday (Friday before Easter Sunday)
    auto easter_sunday = year / April / 1;
    while (std::chrono::weekday(std::chrono::sys_days(easter_sunday)) != std::chrono::Sunday)
        easter_sunday = sys_days(easter_sunday) + std::chrono::days{1};
    auto good_friday = sys_days(easter_sunday) - std::chrono::days{2};
    holidays.insert(good_friday);

    // Eid-ul-Fitr (May 24, placeholder date)
    holidays.insert(year / May / 24);

    // Eid-ul-Adha (July 31, placeholder date)
    holidays.insert(year / July / 31);

    // Diwali (November 14, placeholder date)
    holidays.insert(year / November / 14);

    // Guru Nanak Jayanti (November 30, placeholder date)
    holidays.insert(year / November / 30);

    return (holidays.find(date) != holidays.end()) || is_weekend(date);
};

} // namespace hft::time
