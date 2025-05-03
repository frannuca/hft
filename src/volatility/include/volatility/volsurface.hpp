#ifndef VOLATILITY_VOLSURFACE_HPP
#define VOLATILITY_VOLSURFACE_HPP
#include "data.hpp"
#include "sabr.hpp"
#include "time/date.hpp"
#include "time/daycount.hpp"
#include <map>
#include <memory>

// Your code here
namespace hft::volatility
{
class VolSurface
{
  protected:
    std::map<int, SABR> sabr_models_; // map from maturity in days to SABR model.
    std::shared_ptr<hft::time::DayCountConventionBase> day_count_convention_;
    hft::time::Date cob_date_;

  public:
    VolSurface(const SABRData &surface_data, hft::time::Date cob_date, time::DayCountConvention dc);
    virtual ~VolSurface() = default;
    virtual double operator()(double maturity, double strike) const;
};
} // namespace hft::volatility

#endif // VOLATILITY_VOLSURFACE_HPP