#include <iostream>
#include <vector>
#include <omp.h>
#include <chrono>
#include <cstdlib>
#include <fstream>
#include <functional>
#include <cmath>

using namespace std;

// Function to initialize a vector with random values
void initialize_vector(double *vector, int n)
{
    for (int i = 0; i < n; i++)
    {
        vector[i] = (double)rand() / RAND_MAX; // Random value between 0 and 1
    }
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

double *pnorm(double *x, int n, double p)
{
    double *result = new double;
    *result = 0;
    // when number of threads = 1
    if (omp_get_max_threads() == 1)
    {
#pragma omp parallel for
        for (int i = 0; i < n; i++)
        {
            *result += abs(x[i]);
        }
    }
    else if (omp_get_max_threads() == 2)
    {
#pragma omp parallel for
        for (int i = 0; i < omp_get_max_threads(); i++)
        {
            *result += x[i] * x[i];
        }
        *result = sqrt(*result);
    }
    else
    {
        // max value of x
        double max = 0;

// find max value of x
#pragma omp parallel for
        for (int i = 0; i < n; i++)
        {
            if (x[i] > max)
            {
                max = abs(x[i]);
            }
        }
    }
    return result;
}

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        cout << "Usage: " << argv[0] << " <n> <p>" << endl;
        return 1;
    }

    int n = 1000000;
    double p = atof(argv[1]);

    // Initialize vector x with random values
    double *x = new double[n];
    initialize_vector(x, n);

    // Measure and print the duration of the pnorm function
    ofstream outfile("pnorm.csv");
    measure_and_print_duration(outfile, [&]()
                               { pnorm(x, n, p); }, "pnorm", n);
    outfile.close();

    delete[] x;

    return 0;
}
