Übung 05

Contributors:
Rayk Kretzschmar
Bohdan Babii

Compile the gemm.cpp and run the executable. The program will write the time measurements in output.csv.
Then run 'python gemm.py'. This will add the time measurement for the python code to the output.csv.

Ratios:
Python (Scalar) vs. Fastest C++ (Row-Oriented) :
100654880 microseconds / 5957627 microseconds ≈ 16.9

C++ (Row-Oriented) vs. C++ (Column-Oriented) :
5957627 microseconds / 6471164 microseconds ≈ 0.92

C++ (Row-oriented) vs. C++ (Fastest Blocked):
5957627 microseconds / 8715700 microseconds ≈ 0.68

C++ (Column-oriented) vs. C++ (Fastest Blocked):
6471164 microseconds / 8715700 microseconds ≈ 0.74

As predicted by the ideal cache model, the row-oriented implementation has a slight advantage over the column-oriented implementation.
However, the blocked implementation should outperform both column-oriented and row-oriented implementation. This is not represented by our measurements.
