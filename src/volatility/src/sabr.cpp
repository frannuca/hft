#include "volatility/sabr.hpp"

using namespace volatility;

SABR::SABR(double alpha, double beta, double rho, double nu) : alpha_(alpha), beta_(beta), rho_(rho), nu_(nu){};

double SABR::operator()(double F, double K, double T) const
{

    if (!alpha_ || !beta_ || !rho_ || !nu_)
    {
        throw std::runtime_error("SABR parameters are not set.");
    }

    if (F <= 0.0 || K <= 0.0 || *alpha_ <= 0.0)
    {
        throw std::invalid_argument("Invalid input: F, K, and alpha must be positive.");
    }

    const double epsilon = 1e-8; // small value to avoid division by zero
    double logFK = std::log(F / K);
    double FK_beta = std::pow(F * K, (1 - *beta_) / 2.0);

    double z = (*nu_ / *alpha_) * FK_beta * logFK;
    double x_z;

    if (std::fabs(z) < epsilon)
    {
        x_z = 1.0; // Avoid division by zero for small z
    }
    else
    {
        x_z = std::log((std::sqrt(1 - 2 * *rho_ * z + z * z) + z - *rho_) / (1 - *rho_));
    }

    double factor1 = *alpha_ / FK_beta;
    double factor2 = z / x_z;

    double impliedVol = factor1 * factor2;

    // Add higher order terms for precision
    double betaTerm = std::pow((1 - *beta_), 2) / 24.0;
    double logTerm = std::pow(logFK, 2);
    double nuTerm = (std::pow(*nu_, 2) / 24.0) * logTerm;
    impliedVol *= (1 + betaTerm * logTerm + nuTerm);

    return impliedVol;
};

SABR SABR::CreateModel(SABRData surface_data)
{
    // Implement the SABR calibration here
    return SABR(0.0, 0.0, 0.0, 0.0);
}
