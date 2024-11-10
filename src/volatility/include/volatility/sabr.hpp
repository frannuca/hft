#ifndef SABR_HPP
#define SABR_HPP
#include <optional>
#include "data.hpp"

namespace volatility {

    class SABR{
        public:
          SABR(const SABR &) = default;
          SABR(SABR &&) = default;
          SABR &operator=(const SABR &) = default;
          SABR &operator=(SABR &&) = default;

          SABR(double alpha, double beta, double rho, double nu);          
          SABR(SABRData data);

          double operator()(double F, double K, double T) const;

        private:
        std::optional<double> alpha_;
        std::optional<double> beta_;
        std::optional<double> rho_;
        std::optional<double> nu_;
    };



} // namespace volatility

#endif // SABR_HPP