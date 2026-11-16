# Governing Equations

## Physical problem

This repository contains a numerical simulation associated with **undular bores**. The implementation evolves two fields:

- `h(x,t)`, represented by the array `h[i][t]`;
- `Psi(x,z,t)`, represented by the array `Psi[i][j][t]`.

The code evaluates the time derivatives through the functions `h_punct()` and `Psi_punct()`.

## Model equations

The exact continuous governing equations should be written here from the mathematical model or the original Erasmus project notes.

They should **not** be inferred solely from variable names or reconstructed by guessing from the discretized implementation. In particular, the precise physical meaning, nondimensionalization, and assumptions behind `h` and `Psi` need to be confirmed against the original model.

Suggested format once the original equations are available:

\[
\frac{\partial h}{\partial t} = \mathcal{F}(h,\Psi),
\]

\[
\frac{\partial \Psi}{\partial t} = \mathcal{G}(h,\Psi).
\]

Here, `F` and `G` must be replaced by the actual model expressions.

## Implementation correspondence

In the current C implementation:

- `h_punct()` computes the right-hand side used to advance `h`;
- `Psi_punct()` computes the right-hand side used to advance the upper-boundary value of `Psi`;
- `h_derivat()` and `h_derivat_derivat()` approximate first and second derivatives of `h` in the horizontal direction;
- `termen()` evaluates a coefficient used in the iterative discretized equation for `Psi`.

The equations and notation in this document should be completed and checked against the original mathematical formulation before being treated as a definitive description of the physical model.
