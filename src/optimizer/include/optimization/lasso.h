#ifndef OPTIMIZATION_LASSO_H
#define OPTIMIZATION_LASSO_H
#include <functional>
#include <tuple>
#include <vector>

namespace hft::optimizer
{
class Lasso
{
  public:
    Lasso();
    ~Lasso() = default;

        void set_lambda(double lambda) { m_lambda = lambda; }
        double get_lambda() const { return m_lambda; }

    void set_max_iter(int max_iter) { m_max_iter = max_iter; }
    int get_max_iter() const { return m_max_iter; }
    

    std::tuple<double, double> compute(double input, std::function<double(std::vector<double>,double)> fitness) const;
  private:
    double m_lambda{0.0};
    int m_max_iter{1000};
};

} // namespace hft::optimizer
#endif // OPTIMIZATION_LASSO_H