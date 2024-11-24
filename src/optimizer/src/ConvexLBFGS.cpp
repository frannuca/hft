#include "optimization/ConvexLBFGS.h"
#include <nlopt.hpp>

namespace hft::optimizer
{

std::unique_ptr<nlopt::opt> ConvexLBFGS::get_optimizer(int number_of_variables) const
{
    return std::make_unique<nlopt::opt>(nlopt::algorithm::LD_LBFGS, number_of_variables);
}

ConvexLBFGS::~ConvexLBFGS() {}

std::string ConvexLBFGS::name() const { return "ConvexLBFGS"; }

} // namespace hft::optimizer