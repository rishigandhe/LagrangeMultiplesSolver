#include <functional>
#include <iostream>
#include <vector>

namespace optimization {

const auto objective = [](const std::vector<double>& v)
  {
  return v[0] * v[0] + v[1] * v[1] + v[2] * v[2]; // x^2 + y^2 + z^2
  };

const auto constraint = [](const std::vector<double>& v)
  {
  return v[0] + v[1] * v[1] + v[2] - 9.0; // x + y^2 + z = 9
  };

// Computes numerical gradient using central finite differences
std::vector<double> ComputeGradient(
    std::function<double(const std::vector<double>&)> f, const std::vector<double>& v)
  {
  std::vector<double> gradient(v.size());
  const double step_size = 1e-7;

  for (auto i = 0; i < v.size(); i++)
    {
    std::vector<double> v_plus = v;
    std::vector<double> v_minus = v;

    v_plus[i] += step_size;
    v_minus[i] -= step_size;

    gradient[i] = (f(v_plus) - f(v_minus)) / (2.0 * step_size);
    }
  return gradient;
  }

void PrintVector(const std::vector<double>& v)
  {
  for (auto i = 0; i < v.size(); i++)
    {
    std::cout << v[i];
    if (i < v.size() - 1) std::cout << ", ";
    }
  std::cout << std::endl;
  }

double DotProduct(const std::vector<double>& v1, const std::vector<double>& v2)
  {
  double total = 0.0;
  for (auto i = 0; i < v1.size(); i++)
    {
    total += v1[i] * v2[i];
    }
  return total;
  }

// Solves constrained optimization using Lagrange multipliers
void Solve(std::function<double(const std::vector<double>&)> objective, std::function<double(const std::vector<double>&)> constraint, std::vector<double>& x)
  {
  const double alpha = 0.01;
  const double penalty = 1.0;
  double lambda = 0.0;

  for (auto iter = 0; iter < 1000; iter++)
    {
    auto grad_f = ComputeGradient(objective, x);
    auto grad_g = ComputeGradient(constraint, x);
    double dot_fg = DotProduct(grad_f, grad_g);
    double dot_gg = DotProduct(grad_g, grad_g);

    if (dot_gg > 1e-10) {
      lambda = dot_fg / dot_gg;
    }

    double constraint_value = constraint(x);

    for (auto j = 0; j < x.size(); j++)
      {
      double grad_residual = grad_f[j] - lambda * grad_g[j];
      x[j] -= alpha * grad_residual;
      x[j] -= alpha * penalty * constraint_value * grad_g[j];
      }
    }
  }

}  // namespace optimization

int main()
{
  std::vector<double> initial_guess = {3.0, 2.0, 1.0};

  std::cout << "Initial objective: " << optimization::objective(initial_guess) << std::endl;
  std::cout << "Initial constraint: " << optimization::constraint(initial_guess) << std::endl;

  optimization::Solve(optimization::objective, optimization::constraint, initial_guess);

  std::cout << "Final solution: ";
  optimization::PrintVector(initial_guess);

  return 0;
}