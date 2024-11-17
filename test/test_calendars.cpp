#include "time/calendar_factory.hpp"
#include "time/calendarsenum.hpp"
#include <Eigen/Dense>
#include <chrono>
#include <gtest/gtest.h>

// Test the PCA fit and transform
TEST(CALENDARS, Holidays)
{
    using namespace hft::time;
    using namespace std::chrono;

    auto date = std::chrono::year_month_day{2022y / January / 1};
    auto calendarnye = create_calendar(FinancialCalendar::NYSE);
    ASSERT_EQ(calendarnye->is_holiday(date), true);
}
