#ifndef __OPTIMIZATION_NELDERMEAD_H__
#define __OPTIMIZATION_NELDERMEAD_H__

#include "convexbase.h"

#include <memory.h>
#include <memory>
#include <string>

namespace hft::optimizer
{

class ConvexNelderMead : public ConvexBase
{
  public:
    ~ConvexNelderMead() override;
    std::string name() const override;

  protected:
    std::unique_ptr<nlopt::opt> get_optimizer(int number_of_variables) const override;
};
} // namespace hft::optimizer

#endif