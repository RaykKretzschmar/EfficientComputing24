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

void measure_and_print_duration(ofstream &outfile, function<void()> func, const string &description, int n, string p, int num_runs = 3)
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
        outfile << description << "," << "1" << "," << n << "," << p << "," << max<long long int>(1, avg_duration.count()) << endl;
    }
    catch (const std::exception &e)
    {
        outfile << description << ",ERROR: " << e.what() << endl;
    }
}

double pnorm_serial(double *x, int n, double p)
{
    double result = 0;
    if (p == 1)
    {
        for (int i = 0; i < n; i++)
        {
            result += abs(x[i]);
        }
    }
    else if (p == 2)
    {
        for (int i = 0; i < n; i++)
        {
            result += x[i] * x[i];
        }
        result = sqrt(result);
    }
    else if (p == INFINITY)
    {
        // max value of x
        double max = 0;

        // find max value of x
        for (int i = 0; i < n; i++)
        {
            if (x[i] > max)
            {
                max = abs(x[i]);
            }
        }
        result = max;
    }
    else
    {
        // throw exception
        throw invalid_argument("p must be 1, 2 or INFINITY");
    }
    return result;
}

double pnorm_parallel(double *x, int n, double p, int num_threads)
{

    omp_set_num_threads(num_threads);
    double result = 0.0;
    // when number of threads = 1
    if (p == 1)
    {
#pragma omp parallel for reduction(+ : result)
        for (int i = 0; i < n; i++)
        {
            result += abs(x[i]);
        }
    }
    else if (p == 2)
    {
#pragma omp parallel for reduction(+ : result)
        for (int i = 0; i < n; i++)
        {
            result += x[i] * x[i];
        }
        result = sqrt(result);
    }
    else if (p == INFINITY)
    {
        // max value of x
        double max = 0.0;

// find max value of x
#pragma omp parallel for
        for (int i = 0; i < n; i++)
        {
            if (x[i] > max)
            {
                max = abs(x[i]);
            }
        }
        result = max;
    }
    else
    {
        // throw exception
        throw invalid_argument("p must be 1, 2 or INFINITY");
    }
    return result;
}

int main(int argc, char *argv[])
{

    // array for n with different values
    int n_values[6] = {100, 1000, 10000, 100000, 1000000, 10000000};

    // Measure and print the duration of the pnorm function
    ofstream outfile("pnorm.csv");
    if (!outfile.is_open())
    {
        cerr << "Error: Unable to open pnorm.csv" << endl;
        return 1;
    }

    for (int n : n_values)
    {
        // Initialize vector x with random values
        double *x = new double[n];
        initialize_vector(x, n);

        measure_and_print_duration(outfile, [&]()
                                   { pnorm_serial(x, n, 1); }, "Serial", n, "1");

        measure_and_print_duration(outfile, [&]()
                                   { pnorm_serial(x, n, 2); }, "Serial", n, "2");

        measure_and_print_duration(outfile, [&]()
                                   { pnorm_serial(x, n, INFINITY); }, "Serial", n, "INFINITY");

        for (int num_threads = 2; num_threads <= 8; num_threads++)
        {

            double starttime = omp_get_wtime();
            pnorm_parallel(x, n, 1, num_threads);
            double endtime = omp_get_wtime();
            outfile << "Parallel," << num_threads << "," << n << "," << "1" << "," << (endtime - starttime) * 1e6 << endl;

            starttime = omp_get_wtime();
            pnorm_parallel(x, n, 2, num_threads);
            endtime = omp_get_wtime();
            outfile << "Parallel," << num_threads << "," << n << "," << "2" << "," << (endtime - starttime) * 1e6 << endl;

            starttime = omp_get_wtime();
            pnorm_parallel(x, n, INFINITY, num_threads);
            endtime = omp_get_wtime();
            outfile << "Parallel," << num_threads << "," << n << "," << "INFINITY" << "," << (endtime - starttime) * 1e6 << endl;
        }
        delete[] x;
    }
    outfile.close();

    return 0;
}
