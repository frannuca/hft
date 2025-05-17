#include "optimization/lasso.h"
#include <cmath>
namespace hft::optimizer{
std::tuple<double, double> Lasso::compute(double input, std::function<double(std::vector<double>,double)> fitness) const
{
    // Initialize variables
    const int max_iter = 1000;
    const double tol = 1e-6;
    const double lambda = input; // regularization parameter

    // Example: assume 2D problem for simplicity
    std::vector<double> w = {0.0, 0.0};
    std::vector<double> w_old = w;

    for (int iter = 0; iter < max_iter; ++iter) {
        w_old = w;
        for (size_t j = 0; j < w.size(); ++j) {
            // Compute partial residual
            double r = 0.0;
            for (size_t k = 0; k < w.size(); ++k) {
                if (k != j) r += w[k];
            }
            // Soft-thresholding update
            double zj = fitness(w, j) + r;
            if (zj > lambda)
                w[j] = zj - lambda;
            else if (zj < -lambda)
                w[j] = zj + lambda;
            else
                w[j] = 0.0;
        }
        // Check for convergence
        double diff = 0.0;
        for (size_t j = 0; j < w.size(); ++j)
            diff += std::abs(w[j] - w_old[j]);
        if (diff < tol) break;
    }
    return {w[0], w[1]};
}
}
