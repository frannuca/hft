#include "optimization/NelderMead.h"
#include <memory.h>
#include <nlopt.hpp>

namespace hft::optimizer
{
std::unique_ptr<nlopt::opt> ConvexNelderMead::get_optimizer(int number_of_variables) const
{
    return std::make_unique<nlopt::opt>(nlopt::algorithm::LN_NELDERMEAD, number_of_variables);
}

ConvexNelderMead::~ConvexNelderMead() {}

std::string ConvexNelderMead::name() const { return "ConvexNelderMead"; }
} // namespace hft::optimizer