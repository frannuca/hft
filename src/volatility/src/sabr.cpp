#include "volatility/sabr.hpp"
#include "optimization/NelderMead.h"
#include <chrono>
#include <utility>
#include <cmath>

using namespace hft::volatility;

SABR::SABR(double alpha, double beta, double rho, double nu, std::chrono::year_month_day cob_date,
           hft::time::DayCountConvention dc)
    : alpha_(alpha), beta_(beta), rho_(rho), nu_(nu), cob_date_(cob_date)
{
    day_count_convention_ = hft::time::create_daycount_convention(dc);
};

double SABR::operator()(double F, double K, hft::time::Date T) const
{

    auto year_fraction = day_count_convention_->year_fraction(cob_date_, T);
    return (*this)(F, K, year_fraction);
}

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

    if (T <= 0.0)
    {
        throw std::invalid_argument("Invalid input: T must be positive.");
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

SABR SABR::CreateModel(SABRData surface_data, std::chrono::year_month_day cob_date, hft::time::DayCountConvention dc)
{
    // Extract market data from surface_data
    // Initial guess for SABR parameters
    double alpha = 0.2;
    double beta = 0.5;
    double rho = 0.0;
    double nu = 0.2;
    auto day_count_convention = hft::time::create_daycount_convention(dc);
    // Define the objective function for optimization
    auto objectiveFunction = [&](const std::vector<double> &params)
    {
        double alpha = params[0];
        double beta = params[1];
        double rho = params[2];
        double nu = params[3];

        double error = 0.0;
        SABR sabrModel(alpha, beta, rho, nu, cob_date, dc);

        for (const SABRDataRow &point : surface_data.rows)
        {
            double F = point.forward;
            double K = point.strike;
            double T = day_count_convention->year_fraction(cob_date, point.maturity_date);
            double marketVol = point.implied_volatility;

            double modelVol = sabrModel(F, K, T);

            error += std::pow(modelVol - marketVol, 2);
        }

        return error;
    };

    hft::optimizer::FunctionDefinition function_support{.fFunc = objectiveFunction, .fGrad = std::nullopt};

    hft::optimizer::ConvexNelderMead convex;
    auto result = convex.optimize(
        {alpha, beta, rho, nu}, function_support,
        {std::make_pair(0.01, 2.0), std::make_pair(0.0, 1.0), std::make_pair(-0.99, 0.99), std::make_pair(0.01, 2.0)});

    // Create and return the calibrated SABR model
    return SABR(result[0], result[1], result[2], result[3], cob_date, dc);
}
