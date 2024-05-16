#include <iostream>
#include <vector>
#include <omp.h>
#include <chrono>
#include <cstdlib>
#include <fstream>
#include <functional>

using namespace std;

// Function to initialize a vector with random values
void initialize_vector(double *vector, int n)
{
    for (int i = 0; i < n; i++)
    {
        vector[i] = (double)rand() / RAND_MAX; // Random value between 0 and 1
    }
}

// Serial function to calculate y = αx + y
void calculateY_serial(double alpha, double *x, double *y, int n)
{
    // Calculate y = αx + y using a simple loop
    for (int i = 0; i < n; i++)
    {
        y[i] = alpha * x[i] + y[i];
    }
}

// Parallel function to calculate y = αx + y
void calculateY_parallel(double alpha, double *x, double *y, int n)
{

    double *y_new = y;
// Calculate y = αx + y using OpenMP
#pragma omp parallel for
    for (int i = 0; i < n; i++)
    {
        y_new[i] = alpha * x[i] + y[i];
    }
    y = y_new;
}

void measure_and_print_duration(ofstream &outfile, function<void()> func, const string &description, int n, int num_runs = 3)
{
    try
    {
        auto total_duration = std::chrono::microseconds::zero();
        for (int i = 0; i < num_runs; ++i)
        {
            auto start = std::chrono::high_resolution_clock::now();
            func();
            auto stop = std::chrono::high_resolution_clock::now();
            total_duration += std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
        }

        auto avg_duration = total_duration / num_runs;
        outfile << description << "," << n << "," << 1 << "," << avg_duration.count() << endl;
    }
    catch (const std::exception &e)
    {
        outfile << description << ",ERROR: " << e.what() << endl;
    }
}

int main(int argc, char *argv[])
{
    ofstream outfile("output.csv");
    if (!outfile.is_open())
    {
        cerr << "Error: Unable to open output.csv" << endl;
        return 1;
    }

    // Example usage
    double alpha = 10;
    // array for n with different values
    int n_values[6] = {100, 1000, 10000, 100000, 1000000, 10000000};

    for (int n : n_values)
    {

        double *x = (double *)malloc(n * sizeof(double));
        double *y = (double *)malloc(n * sizeof(double));
        double *y_copy = (double *)malloc(n * sizeof(double));

        initialize_vector(x, n);
        initialize_vector(y, n);
        y_copy = y;

        calculateY_serial(alpha, x, y, n);
        measure_and_print_duration(outfile, [&]()
                                   { calculateY_serial(alpha, x, y, n); }, "Serial", n);

        for (int n_threads = 2; n_threads <= 8; n_threads++)
        {
            omp_set_num_threads(n_threads);
            double start_time = omp_get_wtime();

            calculateY_parallel(alpha, x, y_copy, n);

            double end_time = omp_get_wtime();
            outfile << "Parallel," << n << "," << n_threads << "," << (end_time - start_time) * 1e6 << endl;
        }
        free(x);
        free(y);
    }

    return 0;
}
