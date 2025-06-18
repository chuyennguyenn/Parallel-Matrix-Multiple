# Parallel-Matrix-Multiple

Contains 2 version of Matrix Multiplication: sequential and parallel

# Sequential Matrix Multiplication
Using Strassen algorithm: https://en.wikipedia.org/wiki/Strassen_algorithm

# Parallel Matrix Multiplication
Using OpenMP and nested-loop matrix multiplication. The file contains the following methods: 
1. Parallel 2D Matrix Multiplication
2. Parallel 1D Matrix Multiplication
3. Convert 2D to 1D Matrix

# Notes:
1. The both matrices in both files are randomly generated using the same seed: srand(3) for Matrix A and srand(4) for Matrix B
2. For the program to return meeaningful runtime, the matrix's size should be 200 or more. 
