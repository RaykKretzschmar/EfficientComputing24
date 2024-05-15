#include <iostream>
#include <vector>

using namespace std;

// Function to initialize a vector with random values
void initialize_vector(double *vector, int n)
{
    for (int i = 0; i < n; i++)
    {
        vector[i] = (double)rand() / RAND_MAX; // Random value between 0 and 1
    }
}

void calculateY(double alpha, double *x, double *y, int n)
{
    // Calculate y = αx + y using a simple loop
    for (int i = 0; i < n; i++)
    {
        y[i] = alpha * x[i] + y[i];
    }
}

int main()
{
    // Example usage
    double alpha = 10;
    int n = 10;

    double *x = (double *)malloc(n * sizeof(double));
    double *y = (double *)malloc(n * sizeof(double));

    initialize_vector(x, n);
    initialize_vector(y, n);

    cout << "Original x: ";
    for (int i = 0; i < n; i++)
        cout << x[i] << " ";
    cout << endl;

    cout << "Original y: ";
    for (int i = 0; i < n; i++)
        cout << y[i] << " ";
    cout << endl;

    calculateY(alpha, x, y, n);

    cout << "Calculated y: ";
    for (int i = 0; i < n; i++)
        cout << y[i] << " ";
    cout << endl;

    free(x);
    free(y);

    return 0;
}
