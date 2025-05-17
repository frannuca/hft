#include "time/daycount.hpp"
#include <chrono>
#include <cmath>

using namespace hft::time;
using namespace std::chrono;


class DayCountConventionACT_360 : public DayCountConventionBase
{
  public:
    double operator()(const Date &start, const Date &end) const override;
};

class DayCountConventionACT_365F : public DayCountConventionBase
{
  public:
    double operator()(const Date &start, const Date &end) const override;
};

class DayCountConventionACT_ACT : public DayCountConventionBase
{
  public:
    double operator()(const Date &start, const Date &end) const override;
};

class DayCountConventionTHIRTY_360 : public DayCountConventionBase
{
  public:
    double operator()(const Date &start, const Date &end) const override;
};

class DayCountConventionTHIRTY_365 : public DayCountConventionBase
{
  public:
    double operator()(const Date &start, const Date &end) const override;
};

class DayCountConventionTHIRTY_ACT : public DayCountConventionBase
{
  public:
    double operator()(const Date &start, const Date &end) const override;
};

double DayCountConventionACT_360::operator()(const Date &start, const Date &end) const
{
    return (std::chrono::sys_days(end) - std::chrono::sys_days(start)).count() / 360.0;
}

double DayCountConventionACT_365F::operator()(const Date &start, const Date &end) const
{
    return (std::chrono::sys_days(end) - std::chrono::sys_days(start)).count() / 365.0;
}

double DayCountConventionACT_ACT::operator()(const Date &start, const Date &end) const
{
    using namespace std::chrono;

    // Convert year_month_day to sys_days for arithmetic
    sys_days start_days = sys_days(start);
    sys_days end_days = sys_days(end);

    // Ensure start date is before end date
    if (start_days > end_days)
    {
        std::swap(start_days, end_days);
    }

    // Initialize total year fraction
    double year_fraction = 0.0;

    auto current_date = start_days;

    while (current_date < end_days)
    {
        auto current_year = year_month_day{current_date}.year(); // Start of next year
        auto next_year = current_year + years{1};
        auto year_end = sys_days{year{next_year} / month{1} / day{1}}; // Start of next year

        auto next_date = std::min(year_end, end_days); // Take the earlier of year-end or end_date
        auto days_in_period = duration_cast<days>(next_date - current_date).count();

        // Use 365 or 366 depending on whether the current year is a leap year
        double days_in_year = current_year.is_leap() ? 366.0 : 365.0;
        year_fraction += days_in_period / days_in_year;

        current_date = next_date; // Move to the next period
    }

    return year_fraction;
}

double DayCountConventionTHIRTY_360::operator()(const Date &start, const Date &end) const
{
    using namespace std::chrono;

    // Extract year, month, and day for both dates
    int start_year = (int)start.year();
    int start_month = (int)unsigned{start.month()};
    int start_day = std::min((int)unsigned{start.day()}, 30); // Adjust day to 30 if > 30

    int end_year = (int)end.year();
    int end_month = (int)unsigned{end.month()};
    int end_day = std::min((int)unsigned{end.day()}, 30); // Adjust day to 30 if > 30

    // Calculate the difference in days under Thirty/360
    int day_count = (end_year - start_year) * 360 + (end_month - start_month) * 30 + (end_day - start_day);

    // Compute the year fraction
    return static_cast<double>(day_count) / 360.0;
}

double DayCountConventionTHIRTY_365::operator()(const Date &start, const Date &end) const
{
    using namespace std::chrono;

    // Extract year, month, and day for both dates
    int start_year = (int)start.year();
    int start_month = (int)unsigned{start.month()};
    int start_day = std::min((int)unsigned{start.day()}, 30); // Adjust day to 30 if > 30

    int end_year = (int)end.year();
    int end_month = (int)unsigned{end.month()};
    int end_day = std::min((int)unsigned{end.day()}, 30); // Adjust day to 30 if > 30

    // Calculate the difference in days under Thirty/360
    int day_count = (end_year - start_year) * 360 + (end_month - start_month) * 30 + (end_day - start_day);

    // Compute the year fraction
    return static_cast<double>(day_count) / 365.0;
}

double DayCountConventionTHIRTY_ACT::operator()(const Date &start, const Date &end) const
{
    using namespace std::chrono;

    // Convert year_month_day to sys_days for arithmetic
    sys_days start_days = sys_days(start);
    sys_days end_days = sys_days(end);

    // Ensure start date is before end date
    if (start_days > end_days)
    {
        std::swap(start_days, end_days);
    }

    // Initialize total year fraction
    double year_fraction = 0.0;

    auto current_days = start_days;

    DayCountConventionTHIRTY_365 thirty_365;

    while (current_days < end_days)
    {
        auto current_year = year_month_day{current_days}.year(); // Start of next year
        auto next_year = current_year + years{1};
        auto year_end = sys_days{year{next_year} / month{1} / day{1}}; // Start of next year

        auto next_date = std::min(year_end, end_days); // Take the earlier of year-end or end_date

        // Use 365 or 366 depending on whether the current year is a leap year
        year_fraction += current_year.is_leap() ? thirty_365(next_date, current_days) * 366 / 365
                                                : thirty_365(next_date, current_days);

        current_days = next_date; // Move to the next period
    }

    return year_fraction;
}

double DayCountConventionBase::year_fraction(const Date &start, const Date &end) const { return (*this)(start, end); }

int DayCountConventionBase::monhts_fraction(const Date &start, const Date &end) const
{
    return static_cast<int>(std::round(this->year_fraction(start, end) * 12.0));
}

std::unique_ptr<DayCountConventionBase> hft::time::create_daycount_convention(DayCountConvention convention)
{
    switch (convention)
    {
    case DayCountConvention::ACT_360:
        return std::make_unique<DayCountConventionACT_360>();
    case DayCountConvention::ACT_365F:
    case DayCountConvention::ACT_365:
        return std::make_unique<DayCountConventionACT_365F>();
    case DayCountConvention::ACT_ACT:
        return std::make_unique<DayCountConventionACT_ACT>();
    case DayCountConvention::THIRTY_360:
        return std::make_unique<DayCountConventionTHIRTY_360>();
    case DayCountConvention::THIRTY_365:
        return std::make_unique<DayCountConventionTHIRTY_365>();
    case DayCountConvention::THIRTY_365F:
        return std::make_unique<DayCountConventionTHIRTY_ACT>();
    default:
        throw std::invalid_argument("Unknown DayCountConvention value");
    }
}