# LagrangeMultiplesSolver

A C++ implementation of constrained optimization using the Lagrange multiplier method with numerical gradient computation.

## Overview

This project solves constrained optimization problems of the form:
- **Minimize:** f(x)
- **Subject to:** g(x) = 0

The algorithm finds critical points where ∇f = λ∇g and the constraint g(x) = 0 is satisfied.

## Example Problem

The implementation demonstrates optimization on:
- **Objective:** f(x, y, z) = x² + y² + z²
- **Constraint:** g(x, y, z) = x + y² + z - 9 = 0

Starting from initial guess (3.0, 2.0, 1.0), the optimizer finds the constrained minimum.

## Features

- Numerical gradient computation using central finite differences
- Augmented Lagrangian approach for constraint satisfaction
- Clean, namespace-organized C++ code
- Single-file implementation for easy understanding

## Build & Run
```bash
# Compile
g++ -std=c++17 lagrange_optimizer.cpp -o optimizer

# Run
./optimizer
```

## Algorithm

The optimizer uses an iterative approach:
1. Compute gradients ∇f and ∇g numerically
2. Update x to minimize ||∇f - λ∇g|| (enforce gradient parallelism)
3. Apply penalty term to drive g(x) → 0 (satisfy constraint)
4. Update Lagrange multiplier λ based on gradient ratio

### Parameters
- Learning rate (α): 0.01
- Penalty weight: 1.0
- Max iterations: 1000
- Gradient step size: 1×10⁻⁷

## Code Structure
```
optimization/
├── ComputeGradient()  - Numerical differentiation
├── DotProduct()       - Vector operations
├── Solve()           - Main optimization loop
└── PrintVector()     - Utility output
```

## Mathematical Background

The Lagrange multiplier method finds points where:
- ∇f(x) = λ∇g(x) (gradients are parallel)
- g(x) = 0 (constraint is satisfied)

This implementation uses gradient descent with an augmented Lagrangian approach to iteratively approach these conditions.

## Future Improvements

- [ ] Add convergence criteria (early stopping)
- [ ] Support for inequality constraints
- [ ] Multiple constraint handling
- [ ] Configurable optimizer parameters
- [ ] Result struct with convergence metrics
