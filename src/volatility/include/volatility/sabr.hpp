#ifndef SABR_HPP
#define SABR_HPP
#include "data.hpp"
#include <optional>

namespace volatility
{

class SABR
{
  public:
    static SABR CreateModel(SABRData surface_data);
    SABR(const SABR &) = default;
    SABR(SABR &&) = default;
    SABR &operator=(const SABR &) = default;
    SABR &operator=(SABR &&) = default;

    SABR(double alpha, double beta, double rho, double nu);

    double operator()(double F, double K, double T) const;

  private:
    std::optional<double> alpha_;
    std::optional<double> beta_;
    std::optional<double> rho_;
    std::optional<double> nu_;
};

} // namespace volatility

#endif // SABR_HPP