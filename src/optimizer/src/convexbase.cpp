#include "optimization/convexbase.h"
#include <nlopt.hpp>
namespace hft::optimizer
{
std::string hft::optimizer::ConvexBase::name() const
{
    nlopt::opt opt(nlopt::LD_AUGLAG, 2);
    return "ConvexBase";
}
} // namespace hft::optimizer
