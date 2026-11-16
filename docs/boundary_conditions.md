# Boundary Conditions

This document describes the boundary assignments visible in the current C source code.

## Lateral boundaries in the horizontal direction

The code assigns the lateral ghost/edge values using interior values:

```c
Psi_test[0][j][n + 1]     = Psi_test[2][j][n];
Psi_test[M + 1][j][n + 1] = Psi_test[M - 1][j][n];
```

These assignments are consistent with a zero-normal-gradient (Neumann-type) treatment, subject to the grid-index convention used by the implementation.

The evolving field `h` receives analogous lateral assignments:

```c
h[0][t + 1]     = h[2][t + 1];
h[M + 1][t + 1] = h[M - 1][t + 1];
```

## Lower boundary in the vertical direction

The lower boundary of `Psi_test` is assigned from the adjacent interior row:

```c
Psi_test[i][1][n + 1] = Psi_test[i][2][n + 1];
```

This is a zero-gradient, Neumann-type assignment in the vertical direction.

## Upper boundary in the vertical direction

The upper row is initialized/updated from the time-dependent solution:

```c
Psi_test[i][N][0] = Psi[i][N][t + 1];
```

This corresponds to prescribing the upper-boundary value (Dirichlet-type treatment).

## Summary

| Boundary | Assignment in the source | Interpretation |
|---|---|---|
| Left | Copy from `i = 2` | Neumann-type, zero-gradient |
| Right | Copy from `i = M-1` | Neumann-type, zero-gradient |
| Bottom | Copy from `j = 2` | Neumann-type, zero-gradient |
| Top | Prescribed from `Psi` | Dirichlet-type |

These are **mixed Dirichlet–Neumann boundary conditions**, not periodic boundary conditions.

The exact discrete derivative represented by each assignment depends on the indexing and placement of physical and ghost nodes. Confirm the grid convention before presenting these as formal boundary equations.
