import numpy as np
import time
import sys


def scalar_gemm(X, Y, Z):
    for i in range(n):
        for j in range(n):
            for k in range(n):
                Z[i, j] = Z[i, j] + X[i, k] * Y[k, j]


# n from arguments
n = int(sys.argv[1])

print("n = ", n)

X = np.random.rand(n, n)
Y = np.random.rand(n, n)
Z = np.random.rand(n, n)

# measure start time
start_time = time.time()

scalar_gemm(X, Y, Z)

# measure end time
end_time = time.time()

print("Elapsed time: ", end_time - start_time, "s")
