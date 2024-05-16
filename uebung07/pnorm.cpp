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
}
