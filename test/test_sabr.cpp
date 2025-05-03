#include "time/date.hpp"
#include "time/daycount.hpp"
#include "volatility/sabr.hpp"
#include <gtest/gtest.h>

using namespace std::chrono;
using namespace hft::volatility;

TEST(SABRTest, CalculateImpliedVolatility)
{
    // Given
    double alpha = 0.2;
    double beta = 0.5;
    double rho = 0.0;
    double nu = 0.2;
    double F = 100.0;
    double K = 100.0;
    double T = 1.0;
    hft::time::Date cobdate(std::chrono::year{2021}, std::chrono::month{1}, std::chrono::day{1});

    auto sabrModel =
        hft::volatility::SABR::CreateModel(alpha, beta, rho, nu, cobdate, hft::time::DayCountConvention::ACT_365);

    // When
    double impliedVol = sabrModel(F, K, T);

    // Then
    double expectedVol = 0.2; // Expected implied volatility
    EXPECT_NEAR(impliedVol, expectedVol, 1e-6);
}

TEST(SABRTest, CalibrateModelToMarketData)
{
    hft::time::Date cobdate(year{2021}, month{1}, day{1});
    // Given
    SABRData sabrData;
    sabrData.cob_date = cobdate;
    sabrData.rows = {
        {.maturity_date = year{2021} / month{10} / day{1},
         .strike = 90.0,
         .implied_volatility = 0.15,
         .forward = 100.0},
        {.maturity_date = year{2021} / month{10} / day{1},
         .strike = 95.0,
         .implied_volatility = 0.17,
         .forward = 100.0},
        {.maturity_date = year{2021} / month{10} / day{1},
         .strike = 100.0,
         .implied_volatility = 0.2,
         .forward = 100.0},
        {.maturity_date = year{2021} / month{10} / day{1},
         .strike = 105.0,
         .implied_volatility = 0.225,
         .forward = 100.0},
        {.maturity_date = year{2021} / month{10} / day{1},
         .strike = 110.0,
         .implied_volatility = 0.276,
         .forward = 100.0},
    };
    // When
    SABR calibratedModel = SABR::CreateModel(sabrData, cobdate, hft::time::DayCountConvention::ACT_365);

    // Then
    for (const auto &dataPoint : sabrData.rows)
    {
        double modelVol = calibratedModel(dataPoint.forward, dataPoint.strike, dataPoint.maturity_date);
        EXPECT_NEAR(modelVol, dataPoint.implied_volatility, 0.1);
    }
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);

    // Set the test filter to choose which tests to run
    ::testing::GTEST_FLAG(filter) = "SABRTest.CalibrateModelToMarketData";

    return RUN_ALL_TESTS();
}