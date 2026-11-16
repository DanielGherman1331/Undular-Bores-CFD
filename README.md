# Undular-Bores-CFD
Numerical simulation of undular bores using finite-difference methods, explicit time integration, and a Gauss–Seidel solver with SOR acceleration, implemented in C.

## Overview

This project implements a numerical solver for a Computational Fluid Dynamics (CFD) problem using the C programming language.

The project was developed in 2024 as part of an Erasmus academic experience. It focuses on the numerical solution of a discretized partial differential equation using iterative methods and finite-difference approximations.

The implementation combines spatial discretization, explicit time integration, and an iterative Gauss–Seidel solver with Successive Over-Relaxation (SOR).

## Numerical Methods

The numerical solver incorporates the following techniques:

- **Finite Difference Method (FDM):** Spatial derivatives are approximated using finite-difference schemes.
- **Explicit Time Integration:** The temporal evolution of the free-surface-related variable is calculated using an explicit time-stepping scheme.
- **Gauss–Seidel Method:** An iterative method is used to solve the discretized elliptic equation.
- **Successive Over-Relaxation (SOR):** The Gauss–Seidel iterations are accelerated using an over-relaxation parameter.
- **Convergence Criterion:** Iterations continue until the sum of absolute differences between successive solutions falls below a prescribed tolerance.

## Numerical Configuration

The original simulation uses the following parameters:

| Parameter | Value | Description |
|---|---:|---|
| M | 300 | Number of spatial grid points |
| N | 30 | Number of vertical grid points |
| dx | 60/(M-1) | Horizontal grid spacing |
| dz | 1/(N-1) | Vertical grid spacing |
| dt | 0.010 | Time step |
| ω | 1.8 | SOR relaxation parameter |
| Tolerance | 10⁻⁸ | Iterative convergence tolerance |
| Time steps | 14,999 | Maximum number of temporal steps |

## Boundary Conditions

The implementation uses mixed boundary conditions:

- **Neumann boundary conditions:** Zero-gradient approximations are applied at the lateral boundaries and at the lower boundary.
- **Dirichlet boundary condition:** The upper boundary value is prescribed through the time-dependent solution.

## Implementation

The solver is written in C and uses standard libraries:

- `stdio.h` – input/output operations.
- `stdlib.h` – dynamic memory allocation.
- `math.h` – mathematical functions.

The computational workflow consists of:

1. Initialization of the spatial grid and simulation parameters.
2. Initialization of the solution fields.
3. Explicit temporal advancement of the evolving variable.
4. Iterative solution of the discretized spatial equation using Gauss–Seidel with SOR.
5. Evaluation of the convergence criterion.
6. Storage of the numerical results.

## Compilation

The project can be compiled using GCC:

```bash
gcc src/cfd_solver.c -o cfd_solver -lm -O2
```

## Execution

Run the compiled executable:

```bash
src/Merging and colliding bores Simulation.cpp
```

The simulation generates a numerical output file containing the temporal evolution of the computed field.

## Results

Simulation data and visualizations will be added to the `results/` directory.

## Development Context

This project was developed in 2024 during an Erasmus academic mobility program.

It provided practical experience in numerical methods, computational fluid dynamics, scientific programming, and the implementation of iterative algorithms for solving discretized differential equations.

## License

See the `LICENSE` file for licensing information.
