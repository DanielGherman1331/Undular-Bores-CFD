# Numerical Method

## Overview

The solver is implemented in C and combines finite-difference approximations, explicit time advancement, and an iterative method for the discretized field equation.

## Spatial discretization

The computational grid uses:

- `M = 300` horizontal grid intervals/indices as defined by the implementation;
- `N = 30` vertical grid indices;
- horizontal spacing `dx = 60.0 / (M - 1)`;
- vertical spacing `dz = 1.0 / (N - 1)`.

The code uses centered finite differences for the first and second horizontal derivatives of `h`:

\[
h_x \approx \frac{h_{i+1}-h_{i-1}}{2\Delta x},
\]

\[
h_{xx} \approx \frac{h_{i+1}-2h_i+h_{i-1}}{\Delta x^2}.
\]

## Time advancement

The evolving field `h` is advanced explicitly:

\[
h_i^{n+1}=h_i^n+\Delta t\,F_i^n,
\]

where `F_i^n` is evaluated by `h_punct()` and `dt = 0.010`.

The upper-boundary value of `Psi` is also advanced explicitly using `Psi_punct()`.

## Iterative solution: Gauss–Seidel with SOR

At each time step, the code iteratively updates the interior values of `Psi_test`. The update uses previously available values from the current and preceding iteration levels, following a Gauss–Seidel-type ordering.

Successive Over-Relaxation is applied in the form

\[
\Psi^{(k+1)} \leftarrow (1-\omega)\Psi^{(k)}
+\omega\Psi_{\mathrm{GS}}^{(k+1)},
\]

with `omega = 1.8`.

## Convergence criterion

After each iteration, the code computes

\[
S^{(k)} =
\sum_{i=1}^{M}\sum_{j=1}^{N}
\left|\Psi_{i,j}^{(k+1)}-\Psi_{i,j}^{(k)}\right|.
\]

The iteration is accepted when

\[
S^{(k)} < 10^{-8}.
\]

**Implementation note:** the current source code does not impose a maximum number of iterations in this `while` loop. Adding a maximum iteration count would make the solver more robust against non-convergence.

## Parameters in the current source

| Parameter | Value |
|---|---:|
| `M` | 300 |
| `N` | 30 |
| `dt` | 0.010 |
| `omega` | 1.8 |
| Convergence tolerance | `1e-8` |
| Time-loop upper index | 14998 |

The exact physical interpretation of the fields and the full governing equations should be documented from the original model formulation.
