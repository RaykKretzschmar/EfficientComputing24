#!/bin/bash

g++ -o gemm gemm.cpp
./gemm

# Execute Python script
python3 gemm.py
