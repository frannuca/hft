#include "optimization/convexbase.h"
#include <cstdlib>
#include <memory>
#include <nlopt.hpp>
#include <ranges>
namespace hft::optimizer
{
std::string hft::optimizer::ConvexBase::name() const { return "ConvexBase"; }

std::vector<double> compute_gradient(std::function<double(std::vector<double>)> fFitness, std::vector<double> x)
{
    std::vector<double> grad;
    int n = x.size();
    for (int i : std::ranges::iota_view(0, n))
    {
        std::vector<double> x_m = x;
        std::vector<double> x_p = x;
        x_m[i] -= 1e-8;
        x_p[i] += 1e-8;
        grad.push_back((fFitness(x_p) - fFitness(x_m)) / 2e-8);
    }
    return grad;
}

double objective_function(const std::vector<double> &x, std::vector<double> &grad, void *data)
{
    auto *fData = static_cast<FunctionDefinition *>(data);
    if (!grad.empty())
    {
        if (fData->fGrad)
        {
            grad = fData->fGrad.value()(x);
        }
        else
        {
            grad = compute_gradient(fData->fFunc, x);
        }
    }
    return fData->fFunc(x);
}

std::vector<double> hft::optimizer::ConvexBase::optimize(std::vector<double> x0, FunctionDefinition fFitness,
                                                         std::vector<std::pair<double, double>> boundaries) const
{

    auto number_of_variables = x0.size();
    auto opt = get_optimizer(number_of_variables);
    FunctionDefinition *fData = &fFitness;

    std::vector<double> lb;
    std::vector<double> ub;
    if (!boundaries.empty())
    {
        if (boundaries.size() != number_of_variables)
        {
            throw std::invalid_argument("Dimension mismatch between boundaries and number of variables");
        }

        for (auto [l, u] : boundaries)
        {
            lb.push_back(l);
            ub.push_back(u);
        }
        opt->set_lower_bounds(lb);
        opt->set_upper_bounds(ub);
    }

    opt->set_min_objective(objective_function, (void *)fData);

    // Set optimization parameters
    opt->set_xtol_rel(1e-6);
    opt->set_maxeval(10000);
    opt->set_ftol_rel(1e-6);

    // Initial guess
    std::vector<double> x = x0;

    // Perform the optimization
    double minf;
    nlopt::result result = opt->optimize(x, minf);
    return x;
}
} // namespace hft::optimizer
