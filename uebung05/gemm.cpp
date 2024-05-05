#include <chrono>
#include <cstdlib>
#include <fstream>
#include <functional>
#include <iostream>
#include <vector>

using namespace std;
using namespace std::chrono;

// Helper function to generate random matrices
void generate_random_matrix(vector<vector<float>>& matrix, int size) {
    matrix.clear();
    matrix.resize(size, vector<float>(size));
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            matrix[i][j] = static_cast<float>(rand()) / RAND_MAX;
        }
    }
}

// Row-oriented Scalar algorithm
void gemm_scalar(vector<vector<float>>& Z, const vector<vector<float>>& X, const vector<vector<float>>& Y) {
    int n = X.size();
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            for (int k = 0; k < n; ++k) {
                Z[i][j] += X[i][k] * Y[k][j];
            }
        }
    }
}

// Column-oriented scalar algorithm
void gemm_col_scalar(vector<vector<float>>& Z, const vector<vector<float>>& X, const vector<vector<float>>& Y) {
    int n = X.size();
    for (int j = 0; j < n; ++j) {
        for (int k = 0; k < n; ++k) {
            for (int i = 0; i < n; ++i) {
                Z[i][j] += X[i][k] * Y[k][j];
            }
        }
    }
}

// Blocked algorithm
void gemm_blocked(vector<vector<float>>& Z, const vector<vector<float>>& X, const vector<vector<float>>& Y, int blockSize) {
    int n = X.size();
    for (int i0 = 0; i0 < n; i0 += blockSize) {
        for (int j0 = 0; j0 < n; j0 += blockSize) {
            for (int k0 = 0; k0 < n; k0 += blockSize) {
                for (int i = i0; i < min(i0 + blockSize, n); ++i) {
                    for (int j = j0; j < min(j0 + blockSize, n); ++j) {
                        for (int k = k0; k < min(k0 + blockSize, n); ++k) {
                            Z[i][j] += X[i][k] * Y[k][j];
                        }
                    }
                }
            }
        }
    }
}

void measure_and_print_duration(ofstream& outfile, function<void()> func, const string& description) {
    auto start = high_resolution_clock::now();
    func();
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    outfile << description << "," << duration.count() << endl;
}

int main() {
    srand(time(NULL));
    int n = 1000;  // Size of the matrix

    vector<vector<float>> X, Y, Z;
    generate_random_matrix(X, n);
    generate_random_matrix(Y, n);

    ofstream outfile("output.csv");
    if (!outfile.is_open()) {
        cerr << "Error: Unable to open output.csv" << endl;
        return 1;
    }

    // Row-oriented multiplication (using scalar as row-oriented is similar in this case)
    generate_random_matrix(Z, n);  // Reset Z
    measure_and_print_duration(
        outfile, [&]() { gemm_scalar(Z, X, Y); }, "c++, row-oriented scalar multiplication");

    // Column-oriented multiplication
    generate_random_matrix(Z, n);  // Reset Z
    measure_and_print_duration(
        outfile, [&]() { gemm_col_scalar(Z, X, Y); }, "c++, column-oriented scalar multiplication");

    // Blocked multiplication
    int blockSize = 50;  // initial block size
    while (blockSize <= n) {
        generate_random_matrix(Z, n);  // Reset Z
        measure_and_print_duration(
            outfile, [&]() { gemm_blocked(Z, X, Y, blockSize); }, "c++, blocked multiplication with block size " + to_string(blockSize));
        // Increase block size
        blockSize += 50;
    }
    outfile.close();
    return 0;
}
