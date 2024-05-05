import csv
import numpy as np
from time import time

# Row-oriented scalar algorithm
def gemm_row_scalar(Z, X, Y):
    n = len(X)
    for i in range(n):
        for j in range(n):
            for k in range(n):
                Z[i][j] += X[i][k] * Y[k][j]

def generate_random_matrix(size):
    return np.random.rand(size, size).tolist()

def main():
    n = 1000  # Size of the matrix
    X = generate_random_matrix(n)
    Y = generate_random_matrix(n)
    Z = [[0 for _ in range(n)] for _ in range(n)]  # Result matrix

    start = time()
    gemm_row_scalar(Z, X, Y)
    end = time()

    duration = (end - start) * 1e6  # in microseconds

    with open('output.csv', 'a', newline='') as csvfile:
        writer = csv.writer(csvfile)
        writer.writerow(['python, row-oriented scalar multiplication', duration])

if __name__ == "__main__":
    main()
