#include "volatility/volsurface.hpp"
#include "time/daycount.hpp"
#include <algorithm>
#include <chrono>



using namespace hft::volatility;

// namespace
VolSurface::VolSurface(const SABRData &surface_data, hft::time::Date cob_date, time::DayCountConvention dc)
{
    day_count_convention_ = hft::time::create_daycount_convention(dc);
    cob_date_ = cob_date;

    auto rows = surface_data.rows;
    std::sort(rows.begin(), rows.end(),
              [](const SABRDataRow &a, const SABRDataRow &b)
              { return std::chrono::sys_days(a.maturity_date) < std::chrono::sys_days(b.maturity_date); });
}
/**
 * @brief   std::map<int, std::vector<SABRDataRow>> maturity_data;
    for (const SABRDataRow &row : surface_data.rows)
    {
        int maturity = (int)(day_count_convention_->year_fraction(cob_date_, row.maturity_date));
    }

    // Calibrate surfaces:
    std::vector<std::future<SABR>> futures;
    for (auto data : maturity_data)
    {
        auto task = std::async(std::launch::async,
                               [&, maturity]()
                               {
                                   SABRData data;
                                   data.rows = maturity_data[maturity];
                                   data.cob_date = maturity;
                                   return SABR::CreateModel(data);
                               });
    }
 *
 */