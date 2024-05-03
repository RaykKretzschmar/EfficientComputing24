#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Function to allocate memory for a matrix
double **allocate_matrix(int n)
{
    double **matrix = (double **)malloc(n * sizeof(double *));
    for (int i = 0; i < n; i++)
    {
        matrix[i] = (double *)malloc(n * sizeof(double));
    }
    return matrix;
}

// Function to initialize a matrix with random values
void initialize_matrix(double **matrix, int n)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            matrix[i][j] = (double)rand() / RAND_MAX; // Random value between 0 and 1
        }
    }
}

// Function to compute row oriented gemm operation Z = Z + X * Y
void row_oriented_gemm(double **X, double **Y, double **Z, int n)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            for (int k = 0; k < n; k++)
            {
                Z[i][j] = Z[i][j] + X[i][k] * Y[k][j];
            }
        }
    }
}

// Function to compute column oriented gemm operation Z = Z + X * Y
void column_oriented_gemm(double **X, double **Y, double **Z, int n)
{
    for (int j = 0; j < n; j++)
    {
        for (int i = 0; i < n; i++)
        {
            for (int k = 0; k < n; k++)
            {
                Z[i][j] = Z[i][j] + X[i][k] * Y[k][j];
            }
        }
    }
}

// Function to compute blocked gemm operation Z = Z + X * Y
void blocked_gemm(double **X, double **Y, double **Z, int n, int s)
{
    for (int i0 = 0; i0 < n; i0 += s)
    {
        for (int j0 = 0; j0 < n; j0 += s)
        {
            for (int k0 = 0; k0 < n; k0 += s)
            {
                for (int i = i0; i < i0 + s; i++)
                {
                    for (int j = j0; j < j0 + s; j++)
                    {
                        for (int k = k0; k < k0 + s; k++)
                        {
                            Z[i][j] = Z[i][j] + X[i][k] * Y[k][j];
                        }
                    }
                }
            }
        }
    }
}

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./matrix_vector_product <i>\n");
        return 1;
    }

    int i = atoi(argv[1]);
    int n = i;
    int s = 32;

    srand(time(NULL)); // Seed random number generator

    // Allocate memory for matrix A, vector x, and result vector y
    double **X = allocate_matrix(n);
    double **Y = allocate_matrix(n);
    double **Z = allocate_matrix(n);

    // Initialize matrix A and vector x with random values
    initialize_matrix(X, n);
    initialize_matrix(Y, n);
    initialize_matrix(Z, n);

    // Measure execution time
    clock_t start_time = clock();

    // gemm operation
    row_oriented_gemm(X, Y, Z, n);

    clock_t end_time = clock();
    double execution_time = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;

    printf("Matrix size (n): %d x %d\n", n, n);
    printf("row_oriented_gemm: \n");
    printf("Execution time: %.6f seconds\n", execution_time);

    // Measure execution time
    start_time = clock();

    // gemm operation
    column_oriented_gemm(X, Y, Z, n);

    end_time = clock();
    execution_time = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;

    printf("column_oriented_gemm: \n");
    printf("Execution time: %.6f seconds\n", execution_time);

    // Measure execution time
    start_time = clock();

    // gemm operation
    blocked_gemm(X, Y, Z, n, s);

    end_time = clock();
    execution_time = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;

    printf("blocked_gemm: \n");
    printf("Execution time: %.6f seconds\n", execution_time);

    // Free allocated memory
    for (int i = 0; i < n; i++)
    {
        free(X[i]);
        free(Y[i]);
        free(Z[i]);
    }
    free(X);
    free(Y);
    free(Z);

    return 0;
}