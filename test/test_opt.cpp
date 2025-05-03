#include "optimization/ConvexAUGLAG.h"
#include "optimization/ConvexLBFGS.h"
#include <Eigen/Dense>
#include <gtest/gtest.h>
#include <memory.h>
// Test the PCA fit and transform
TEST(OPT, Convex)
{

    hft::optimizer::FunctionDefinition data{.fFunc = [](std::vector<double> x)
                                            { return (x[0] - 3) * (x[0] - 3) + (x[1] - 2) * (x[1] - 2); },
                                            .fGrad =
                                                [](std::vector<double> x) {
                                                    return std::vector<double>{2 * (x[0] - 3), 2 * (x[1] - 2)};
                                                }};

    hft::optimizer::ConvexLBFGS convex;
    std::vector<std::pair<double, double>> boundaries;
    auto result = convex.optimize({0, 0}, data, boundaries);

    ASSERT_EQ(result.size(), 2);
    ASSERT_NEAR(result[0], 3, 1e-8);
    ASSERT_NEAR(result[1], 2, 1e-8);
}

TEST(OPT, Convex_Constraints)
{

    hft::optimizer::FunctionDefinition data{.fFunc = [](std::vector<double> x)
                                            { return (x[0] - 3) * (x[0] - 3) + (x[1] - 2) * (x[1] - 2); },
                                            .fGrad =
                                                [](std::vector<double> x) {
                                                    return std::vector<double>{2 * (x[0] - 3), 2 * (x[1] - 2)};
                                                }};

    hft::optimizer::FunctionDefinition dataInEq{.fFunc = [](std::vector<double> x) { return x[0] - 2.5; },
                                                .fGrad =
                                                    [](std::vector<double> x) {
                                                        return std::vector<double>{1, 0};
                                                    }};
    hft::optimizer::ConvexAUGLAG convex;
    auto result = convex.optimize({0, 0}, data, {std::make_pair(0, 5), std::make_pair(0, 5)});

    ASSERT_EQ(result.size(), 2);
    ASSERT_NEAR(result[0], 2.5, 1e-8);
    ASSERT_NEAR(result[1], 2, 1e-8);
}