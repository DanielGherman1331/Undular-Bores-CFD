#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
//Laplaceian_corect
// Functie creare matrice
double*** create_matrix(int dim1, int dim2, int dim3) {
    // Alocare pentru matricea de dimensiune dim1
    double*** matrix = (double***)malloc(dim1 * sizeof(double**));
    if (matrix == NULL) {
        printf("Eroare la alocarea memoriei pentru matrice!\n");
        exit(1);
    }

    // Alocare pentru fiecare plan (dim1)
    for (int i = 0; i < dim1; i++) {
        matrix[i] = (double**)malloc(dim2 * sizeof(double*));
        if (matrix[i] == NULL) {
            printf("Eroare la alocarea memoriei pentru matrice!\n");
            exit(1);
        }

        // Alocare pentru fiecare linie (dim2) din fiecare plan
        for (int j = 0; j < dim2; j++) {
            matrix[i][j] = (double*)malloc(dim3 * sizeof(double));
            if (matrix[i][j] == NULL) {
                printf("Eroare la alocarea memoriei pentru matrice!\n");
                exit(1);
            }
        }
    }

    return matrix;
}
double** create_2d_matrix(int rows, int cols) {
    double** matrix = (double**)malloc(rows * sizeof(double*));
    if (matrix == NULL) {
        printf("Eroare la alocarea memoriei pentru matrice!\n");
        exit(1);
    }

    for (int i = 0; i < rows; i++) {
        matrix[i] = (double*)malloc(cols * sizeof(double));
        if (matrix[i] == NULL) {
            printf("Eroare la alocarea memoriei pentru matrice!\n");
            exit(1);
        }
    }

    return matrix;
}
double**** create_4d_matrix(int dim1, int dim2, int dim3, int dim4) {
    double**** matrix = (double****)malloc(dim1 * sizeof(double***));
    if (matrix == NULL) {
        printf("Eroare la alocarea memoriei pentru matrice!\n");
        exit(1);
    }

    for (int i = 0; i < dim1; i++) {
        matrix[i] = (double***)malloc(dim2 * sizeof(double**));
        if (matrix[i] == NULL) {
            printf("Eroare la alocarea memoriei pentru matrice!\n");
            exit(1);
        }

        for (int j = 0; j < dim2; j++) {
            matrix[i][j] = (double**)malloc(dim3 * sizeof(double*));
            if (matrix[i][j] == NULL) {
                printf("Eroare la alocarea memoriei pentru matrice!\n");
                exit(1);
            }

            for (int k = 0; k < dim3; k++) {
                matrix[i][j][k] = (double*)malloc(dim4 * sizeof(double));
                if (matrix[i][j][k] == NULL) {
                    printf("Eroare la alocarea memoriei pentru matrice!\n");
                    exit(1);
                }
            }
        }
    }

    return matrix;
}

double h_punct(double*** Psi, double** h, double dx, double dz, int i, int t, int N) {
    // Verificări pentru zero
    if (dz == 0.0 || h[i][t] == 0.0 || dx == 0.0) {
        printf("Eroare: dz, dx sau h[%d][%d] este zero.\n", i, t);
        return NAN;
    }


    // Calculul principal
    double a = (1.0 + (h[i + 1][t] - h[i - 1][t]) * (h[i + 1][t] - h[i - 1][t]) / (4.0 * dx * dx)) *
        (Psi[i][N][t] - Psi[i][N - 1][t]) / dz / h[i][t] -
        (h[i + 1][t] - h[i - 1][t]) / (2.0 * dx) * (Psi[i + 1][N][t] - Psi[i - 1][N][t]) / (2.0 * dx);
    return a;
}

double Psi_punct(double*** Psi, double** h, double dx, double dz, int t, int i, int N) {

    double Psi_z_i = (Psi[i][N][t] - Psi[i][N - 1][t]) / dz;
    double Psi_x_i = (Psi[i + 1][N][t] - Psi[i - 1][N][t]) / 2.0 / dx;
    double h_d = (h[i + 1][t] - h[i - 1][t]) / 2.0 / dx;


    double a = 1 - h[i][t] - 0.5 * Psi_x_i * Psi_x_i + h_d / h[i][t] * Psi_x_i * Psi_z_i - 0.5 * 1 / h[i][t] / h[i][t] * (1 + h_d * h_d) * Psi_z_i * Psi_z_i + h_punct(Psi, h, dx, dz, i, t, N) / h[i][t] * Psi_z_i;
    return a;
}
void Ini_Psi(double*** Psi, int M, int N, double Valoare, double dx) {
    for (int i = 0; i <= M + 1; i++) {
        for (int j = 1; j <= N; j++) {
            Psi[i][j][0] = Valoare;
        }
    }
}
double h_derivat(double** h, int i, int t, double dx) {
    double a = 0.0;
    a = (h[i + 1][t] - h[i - 1][t]) / 2.0 / dx;
    return a;
}
double h_derivat_derivat(double** h, int i, int t, double dx) {
    double a = 0.0;
    a = (h[i + 1][t] - 2.0 * h[i][t] + h[i - 1][t]) / dx / dx;
    return a;
}
double termen(double** h, int i, int j, int t, double dx, double dz, int N) {
    double a = 0.0;
    a = 2.0 * (h[i][t] * h[i][t] / dx / dx + (1 + h_derivat(h, i, t, dx) * h_derivat(h, i, t, dx) * (j - 1) * (j - 1) * dz * dz) / dz / dz);
    return a;
}




int main() {
    FILE* file = fopen("date_simulare2.txt", "w"); // Deschide fișierul pentru scriere
    if (file == NULL) {
        perror("Unable to open file");
        return 1;
    }
    //Parametri de precizie si de experiment
    int M = 300;
    int N = 30;
    double dx = 60.0 / (M - 1);
    double dz = 1.0 / (N - 1);
    double dt = 0.010;
    int Pasi_t = 15000;
    double h_0 = 1.2;
    double delta = dz / dx;
    double omega = 1.8;

    double*** Psi = create_matrix(M + 2, N + 1, Pasi_t);
    double*** Psi_test = create_matrix(M + 2, N + 1, Pasi_t);
    double** h = create_2d_matrix(M + 2, Pasi_t);

    for (int i = 0; i <= M + 1; i++) {
        h[i][0] = tanh(-3.0 * (i * dx - 10.0)) * 0.2 + 0.2 + 1.0;
    }



    Ini_Psi(Psi_test, M, N, 0.0, dx);
    Ini_Psi(Psi, M, N, 0.0, dx);




    for (int t = 0;t <= 14998;t++) {
        fprintf(file, "%lf ", (t + 1) * dt);
        for (int i = 1; i <= M;i++) {
            Psi[i][N][t + 1] = Psi[i][N][t] + dt * Psi_punct(Psi, h, dx, dz, t, i, N);
            Psi_test[i][N][0] = Psi[i][N][t + 1];
            h[i][t + 1] = h[i][t] + dt * h_punct(Psi, h, dx, dz, i, t, N);
            fprintf(file, "%lf ", h[i][t + 1]);
        }
        fprintf(file, "\n");
        h[0][t + 1] = h[2][t + 1];
        h[M + 1][t + 1] = h[M - 1][t + 1];
        int n = 0;
        int conditie = 0;
        while (conditie == 0) {
            for (int i = 1;i <= M;i++) {
                Psi_test[i][N][n + 1] = Psi_test[i][N][n];
            }
            for (int j = 1;j <= N;j++) {
                Psi_test[0][j][n + 1] = Psi_test[2][j][n];
                Psi_test[M + 1][j][n + 1] = Psi_test[M - 1][j][n];
            }

            for (int i = 1;i <= M;i++) {
                for (int j = 2; j <= N - 1;j++) {
                    if (j > 2) {
                        Psi_test[i][j][n + 1] = (h[i][t + 1] * h[i][t + 1] / dx / dx * (Psi_test[i + 1][j][n] + Psi_test[i - 1][j][n + 1]) +
                            (1 + h_derivat(h, i, t + 1, dx) * h_derivat(h, i, t + 1, dx) * (j - 1) * (j - 1) * dz * dz) * (Psi_test[i][j + 1][n] + Psi_test[i][j - 1][n + 1]) / dz / dz -
                            2 * (j - 1) * dz * h[i][t + 1] * h_derivat(h, i, t + 1, dx) * (Psi_test[i + 1][j + 1][n] - Psi_test[i + 1][j - 1][n] - Psi_test[i - 1][j + 1][n + 1] + Psi_test[i - 1][j - 1][n + 1]) / 4 / dx / dz +
                            (2 * (j - 1) * dz * h_derivat(h, i, t + 1, dx) * h_derivat(h, i, t + 1, dx) - (j - 1) * dz * h[i][t + 1] * h_derivat_derivat(h, i, t + 1, dx)) * (Psi_test[i][j + 1][n] - Psi_test[i][j - 1][n + 1]) / 2 / dz) / termen(h, i, j, t + 1, dx, dz, N);
                        Psi_test[i][j][n + 1] = (1 - omega) * Psi_test[i][j][n] + omega * Psi_test[i][j][n + 1];
                    }
                    else {
                        Psi_test[i][j][n + 1] = (h[i][t + 1] * h[i][t + 1] / dx / dx * (Psi_test[i + 1][j][n] + Psi_test[i - 1][j][n + 1]) +
                            (1 + h_derivat(h, i, t + 1, dx) * h_derivat(h, i, t + 1, dx) * (j - 1) * (j - 1) * dz * dz) * (Psi_test[i][j + 1][n] + Psi_test[i][j - 1][n]) / dz / dz -
                            2 * (j - 1) * dz * h[i][t + 1] * h_derivat(h, i, t + 1, dx) * (Psi_test[i + 1][j + 1][n] - Psi_test[i + 1][j - 1][n] - Psi_test[i - 1][j + 1][n + 1] + Psi_test[i - 1][j - 1][n]) / 4 / dx / dz +
                            (2 * (j - 1) * dz * h_derivat(h, i, t + 1, dx) * h_derivat(h, i, t + 1, dx) - (j - 1) * dz * h[i][t + 1] * h_derivat_derivat(h, i, t + 1, dx)) * (Psi_test[i][j + 1][n] - Psi_test[i][j - 1][n]) / 2 / dz) / termen(h, i, j, t + 1, dx, dz, N);
                        Psi_test[i][j][n + 1] = (1 - omega) * Psi_test[i][j][n] + omega * Psi_test[i][j][n + 1];
                    }
                }
            }

            for (int j = 1;j <= N;j++) {
                Psi_test[0][j][n + 1] = Psi_test[2][j][n + 1];
                Psi_test[M + 1][j][n + 1] = Psi_test[M - 1][j][n + 1];
            }
            for (int i = 1;i <= M;i++) {
                Psi_test[i][1][n + 1] = Psi_test[i][2][n + 1];
            }
            double Suma_control = 0.0;
            for (int i = 1;i <= M;i++) {
                for (int j = 1; j <= N;j++) {
                    //fprintf(file, "%lf  ", Psi_test[i][j][n + 1]);
                    Suma_control = Suma_control + fabsf(Psi_test[i][j][n + 1] - Psi_test[i][j][n]);
                }
                //fprintf(file, "\n");
            }
            printf("%0.10lf %d\n ", Suma_control, t);
            if (Suma_control < 0.00000001) {
                //printf("Conditia s-a indeplinit\n");
                conditie = 1;
                for (int i = 0;i <= M + 1;i++) {
                    for (int j = 1; j <= N;j++) {
                        Psi[i][j][t + 1] = Psi_test[i][j][n + 1];

                    }
                }
                printf("%d\n", (t + 1));
            }
            else {
                //printf("Conditie nu s-a indeplinit, suma este = %lf\n", Suma_control);
                for (int i = 0;i <= M + 1;i++) {
                    for (int j = 1; j <= N;j++) {
                        Psi_test[i][j][n] = Psi_test[i][j][n + 1];

                    }
                }
            }

        }
    }


    return 0;
}