#ifndef HFT_TIME_DAYCOUNT_HPP
#define HFT_TIME_DAYCOUNT_HPP
#include "date.hpp"
#include <memory>
namespace hft::time
{

enum class DayCountConvention
{
    ACT_360,
    ACT_365,
    ACT_365F,
    ACT_ACT,
    THIRTY_360,
    THIRTY_365,
    THIRTY_365F
};

class DayCountConventionBase
{
  public:
    virtual ~DayCountConventionBase() = default;
    virtual double operator()(const Date &start, const Date &end) const = 0;
    double year_fraction(const Date &start, const Date &end) const;
    int monhts_fraction(const Date &start, const Date &end) const;
};

std::unique_ptr<DayCountConventionBase> create_daycount_convention(DayCountConvention convention);

}; // namespace hft::time

#endif // HFT_TIME_DAYCOUNT_HPP