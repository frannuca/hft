#include "optimization/ConvexAUGLAG.h"
#include <nlopt.hpp>

namespace hft::optimizer
{

std::unique_ptr<nlopt::opt> ConvexAUGLAG::get_optimizer(int number_of_variables) const
{
    return std::make_unique<nlopt::opt>(nlopt::algorithm::LD_AUGLAG, number_of_variables);
}

ConvexAUGLAG::~ConvexAUGLAG() {}

std::string ConvexAUGLAG::name() const { return "ConvexAUGLAG"; }

} // namespace hft::optimizer