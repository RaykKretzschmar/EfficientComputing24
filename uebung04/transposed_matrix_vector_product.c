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

// Function to allocate memory for a vector
double *allocate_vector(int n)
{
    return (double *)malloc(n * sizeof(double));
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

// Function to initialize a vector with random values
void initialize_vector(double *vector, int n)
{
    for (int i = 0; i < n; i++)
    {
        vector[i] = (double)rand() / RAND_MAX; // Random value between 0 and 1
    }
}

// Function to compute matrix-vector product: y = Ax
void matrix_vector_product(double **A, double *x, double *y, int n)
{
    for (int i = 0; i < n; i++)
    {
        y[i] = 0.0;
        for (int j = 0; j < n; j++)
        {
            y[i] += A[i][j] * x[j];
        }
    }
}

// Function to compute the transpose matrix vector product y = A^T x
void transpose_matrix_vector_product(double **A, double *x, double *y, int n)
{
    for (int i = 0; i < n; i++)
    {
        y[i] = 0.0;
        for (int j = 0; j < n; j++)
        {
            y[i] += A[j][i] * x[j];
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
    int n = 1024 * i;

    srand(time(NULL)); // Seed random number generator

    // Allocate memory for matrix A, vector x, and result vector y
    double **A = allocate_matrix(n);
    double *x = allocate_vector(n);
    double *y = allocate_vector(n);

    // Initialize matrix A and vector x with random values
    initialize_matrix(A, n);
    initialize_vector(x, n);

    // Measure execution time
    clock_t start_time = clock();

    // Transpose matrix A
    transpose_matrix_vector_product(A, x, y, n);

    clock_t end_time = clock();
    double execution_time = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;

    printf("Matrix size (n): %d x %d\n", n, n);
    printf("mit Transponierter Matrix: \n");
    printf("Execution time: %.6f seconds\n", execution_time);

    clock_t start_time2 = clock();

    matrix_vector_product(A, x, y, n);

    clock_t end_time2 = clock();
    double execution_time2 = ((double)(end_time2 - start_time2)) / CLOCKS_PER_SEC;

    printf("ohne Transponierte Matrix: \n");
    printf("Execution time: %.6f seconds\n", execution_time2);

    // Free allocated memory
    for (int i = 0; i < n; i++)
    {
        free(A[i]);
    }
    free(A);
    free(x);
    free(y);

    return 0;
}
