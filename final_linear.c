#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 256

void generateRandomMatrix(int matrix[N][N])
{
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            matrix[i][j] = rand() % 10;
        }
    }
}

void zeroMatrix(int matrix[N][N])
{
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            matrix[i][j] = 0;
        }
    }
}

void printMatrix(int matrix[N][N])
{
    printf("The matrix is \n");
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

void recursiveMultiplyMatrices(int A[N][N], int B[N][N], int C[N][N], int rowA, int colA, int rowB, int colB, int size)
{
    if (size == 1)
    {
        C[rowA][colB] += A[rowA][colA] * B[rowB][colB];
    }
    else
    {
        int newSize = size / 2;
        recursiveMultiplyMatrices(A, B, C, rowA, colA, rowB, colB, newSize);                                         // A11, B11, C11
        recursiveMultiplyMatrices(A, B, C, rowA, colA + newSize, rowB + newSize, colB, newSize);                     // A12, B21, C11
        recursiveMultiplyMatrices(A, B, C, rowA, colA, rowB, colB + newSize, newSize);                               // A11, B12, C12
        recursiveMultiplyMatrices(A, B, C, rowA, colA + newSize, rowB + newSize, colB + newSize, newSize);           // A12, B22, C12
        recursiveMultiplyMatrices(A, B, C, rowA + newSize, colA, rowB, colB, newSize);                               // A21, B11, C21
        recursiveMultiplyMatrices(A, B, C, rowA + newSize, colA + newSize, rowB + newSize, colB, newSize);           // A22, B21, C21
        recursiveMultiplyMatrices(A, B, C, rowA + newSize, colA, rowB, colB + newSize, newSize);                     // A21, B12, C22
        recursiveMultiplyMatrices(A, B, C, rowA + newSize, colA + newSize, rowB + newSize, colB + newSize, newSize); // A22, B22, C22
    }
}

void multiplyMatrices(int matrix1[N][N], int matrixN[N][N], int result[N][N])
{
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            result[i][j] = 0;
            for (int k = 0; k < N; k++)
            {
                result[i][j] += matrix1[i][k] * matrixN[k][j];
            }
        }
    }
}

int main()
{
    int A[N][N];
    int B[N][N];
    int C[N][N];
    zeroMatrix(C);
    srand(3);
    generateRandomMatrix(A);
    // printMatrix(A);
    srand(4);
    generateRandomMatrix(B);
    // printMatrix(B);
    clock_t tic = clock();
    multiplyMatrices(A, B, C);
    // recursiveMultiplyMatrices(A, B, C, 0, 0, 0, 0, N);
    clock_t toc = clock();
    printMatrix(C);
    printf("Elapsed: %f seconds\n", (double)(toc - tic) / CLOCKS_PER_SEC);
}