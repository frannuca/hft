#include <vector>
#include <chrono>

namespace volatility{

    struct SABRDataRow{
        double maturity_in_years;
        double strike;
        double implied_volatility;
        double forward;
    };

    struct SABRData{
        std::vector<SABRDataRow> rows;       
        std::chrono::year_month_day cob_date;
    };
}