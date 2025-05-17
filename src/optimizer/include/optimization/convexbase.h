#ifndef HFT_OPTIMIZER_CONVEXBASE_H
#define HFT_OPTIMIZER_CONVEXBASE_H
#include <optional>
#include <functional>
#include <string>
#include <memory>

namespace nlopt
{
class opt;
}
namespace hft::optimizer
{

struct FunctionDefinition
{
    std::function<double(std::vector<double>)> fFunc;
    std::optional<std::function<std::vector<double>(std::vector<double>)>> fGrad;
};

class ConvexBase
{
  public:
    virtual ~ConvexBase() = default;
    virtual std::string name() const = 0;
    std::vector<double> optimize(std::vector<double> x0, FunctionDefinition fFitness,
                                 std::vector<std::pair<double, double>> boundaries) const;

  protected:
    virtual std::unique_ptr<nlopt::opt> get_optimizer(int number_of_variables) const = 0;
};
} // namespace hft::optimizer
// namespace hft::optimizer

#endif