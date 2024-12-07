#include "volatility/sabr.hpp"
#include <gtest/gtest.h>

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

    volatility::SABR sabrModel(alpha, beta, rho, nu);

    // When
    double impliedVol = sabrModel(F, K, T);

    // Then
    double expectedVol = 0.2; // Expected implied volatility
    EXPECT_NEAR(impliedVol, expectedVol, 1e-6);
}

TEST(SABRTest, CalibrateModelToMarketData)
{
    // Given
    volatility::SABRData sabrData;
    sabrData.rows = {{100.0, 90.0, 1.0, 0.25}, {100.0, 100.0, 1.0, 0.2}, {100.0, 110.0, 1.0, 0.22}};

    // When
    volatility::SABR calibratedModel = volatility::SABR::CreateModel(sabrData);

    // Then
    for (const auto &dataPoint : sabrData.rows)
    {
        double modelVol = calibratedModel(dataPoint.forward, dataPoint.strike, dataPoint.maturity_in_years);
        EXPECT_NEAR(modelVol, dataPoint.implied_volatility, 0.05);
    }
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);

    // Set the test filter to choose which tests to run
    ::testing::GTEST_FLAG(filter) = "SABRTest.CalibrateModelToMarketData";

    return RUN_ALL_TESTS();
}