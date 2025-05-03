#ifndef VOL_DATA_HPP
#define VOL_DATA_HPP

#include "time/date.hpp"
#include <chrono>
#include <vector>
namespace hft::volatility
{

struct SABRDataRow
{
    hft::time::Date maturity_date;
    double strike;
    double implied_volatility;
    double forward;
};

struct SABRData
{
    std::vector<SABRDataRow> rows;
    std::chrono::year_month_day cob_date;
};
} // namespace hft::volatility

#endif // VOL_DATA_HPP