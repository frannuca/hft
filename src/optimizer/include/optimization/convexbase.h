#include <string>

namespace hft::optimizer
{
class ConvexBase
{
  public:
    virtual ~ConvexBase() = default;
    std::string name() const;
};
} // namespace hft::optimizer