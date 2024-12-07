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
                                                         std::optional<FunctionDefinition> fEqualityConstrains,
                                                         std::optional<FunctionDefinition> fInequalityConstaints) const
{

    auto number_of_variables = x0.size();
    auto opt = get_optimizer(number_of_variables);
    FunctionDefinition *fData = &fFitness;

    auto fDataEqConstaint = fEqualityConstrains.has_value() ? &fEqualityConstrains : nullptr;
    auto fDataInEqConstaint = fInequalityConstaints.has_value() ? &fInequalityConstaints : nullptr;

    opt->set_min_objective(objective_function, (void *)fData);

    if (fDataInEqConstaint != nullptr)
    {

        opt->add_inequality_constraint(objective_function, (void *)fDataInEqConstaint);
    }
    if (fDataEqConstaint != nullptr)
    {
        opt->add_equality_constraint(objective_function, (void *)fDataInEqConstaint, 1e-6);
    }

    // Set optimization parameters
    opt->set_xtol_rel(1e-4);
    opt->set_maxeval(100);

    // Initial guess
    std::vector<double> x = x0;

    // Perform the optimization
    double minf;
    nlopt::result result = opt->optimize(x, minf);
    return x;
}
} // namespace hft::optimizer
