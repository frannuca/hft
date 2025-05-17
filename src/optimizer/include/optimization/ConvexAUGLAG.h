#ifndef HFT_OPTIMIZER_CONVEXAUGLAG_H
#define HFT_OPTIMIZER_CONVEXAUGLAG_H

#include "convexbase.h"


namespace hft::optimizer
{

class ConvexAUGLAG : public ConvexBase
{
  public:
    ~ConvexAUGLAG() override;
    std::string name() const override;

  protected:
    std::unique_ptr<nlopt::opt> get_optimizer(int number_of_variables) const override;
};
} // namespace hft::optimizer

#endif