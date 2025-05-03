#ifndef SABR_HPP
#define SABR_HPP
#include "data.hpp"
#include "time/date.hpp"
#include "time/daycount.hpp"
#include <chrono>
#include <optional>

namespace hft::volatility
{

class SABR
{
  public:
    static SABR CreateModel(SABRData surface_data, std::chrono::year_month_day cob_date,
                            hft::time::DayCountConvention dc = hft::time::DayCountConvention::ACT_365);

    static SABR CreateModel(double alpha, double beta, double rho, double nu, std::chrono::year_month_day cob_date,
                            hft::time::DayCountConvention dc = hft::time::DayCountConvention::ACT_365)
    {
        return SABR(alpha, beta, rho, nu, cob_date, dc);
    };

  public:
    std::chrono::year_month_day GetCobDate() const { return cob_date_; }

    double operator()(double F, double K, hft::time::Date T) const;
    double operator()(double F, double K, double T) const;

  private:
    SABR() = default;
    SABR(std::chrono::year_month_day cob_date,
         hft::time::DayCountConvention dc = hft::time::DayCountConvention::ACT_365)
        : cob_date_(cob_date), day_count_convention_(hft::time::create_daycount_convention(dc)){};

    SABR(const SABR &) = default;
    SABR(SABR &&) = default;
    SABR &operator=(const SABR &) = default;
    SABR &operator=(SABR &&) = default;

    SABR(double alpha, double beta, double rho, double nu, std::chrono::year_month_day cob_date,
         hft::time::DayCountConvention dc);

  private:
    std::optional<double> alpha_;
    std::optional<double> beta_;
    std::optional<double> rho_;
    std::optional<double> nu_;
    std::shared_ptr<hft::time::DayCountConventionBase> day_count_convention_;
    std::chrono::year_month_day cob_date_;
};

} // namespace hft::volatility

#endif // SABR_HPP