#include "convexbase.h"
#include <memory.h>
#include <memory>
#include <string>

namespace hft::optimizer
{

class ConvexLBFGS : public ConvexBase
{
  public:
    ~ConvexLBFGS() override;
    std::string name() const override;

  protected:
    std::unique_ptr<nlopt::opt> get_optimizer(int number_of_variables) const override;
};
} // namespace hft::optimizer