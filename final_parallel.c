#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>
#include <math.h>

#define N 256

void generateRandomMatrix(int matrix[N][N]) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            matrix[i][j] = rand() % 10;
        }
    }
}

void zeroMatrix(int matrix[N][N]){
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            matrix[i][j] = 0;
        }
    }
}

void printMatrix(int matrix[N][N]) {
    printf("The matrix is \n");
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

void printOneDimMatrix(int matrix[N*N]){
    printf("The 1D matrix is \n");
    for (int i = 0; i < N*N; i++){
        printf("%d ", matrix[i]);
    }
    printf("\n");
}

int multiplyMatrices(int matrix1[N][N], int matrix2[N][N], int result[N][N]) {      //parallel matrix multiply with 2d array
    int i,j,k;
    #pragma omp parallel shared(matrix1,matrix2,result) private(i,j,k)
        #pragma omp for schedule(static)
        for (i = 0; i < N; i++) {
            for ( j = 0; j < N; j++) {
                int temp =0;
                for ( k = 0; k < N; k++) {
                    temp+= matrix1[i][k] * matrix2[k][j];
                }
                result[i][j] = temp;
            //printf("%d\t", result[i][j]);
        }
        //printf("\n");
        }
    return 0;
}

int multiply1DimensionMatrices(int matrix1[N*N], int matrix2[N*N], int result[N][N]){   //parallel matrix multiply with 1d array
    int i,j,k;
    #pragma omp parallel shared(matrix1,matrix2,result) private(i,j,k)
        #pragma omp for schedule(static)
        for (i = 0; i < N; i++){
            for (j = 0; j < N; j++){
                int temp = 0;
                for (k = 0; k < N; k++){
                    temp += matrix1[i*N +k] * matrix2[j*N + k];
                }
                result[i][j] = temp;
            }
        }
    return 0;
}

int twoDimToOneDim(int A[N][N], int B[N][N], int dimension, int A1[N*N], int B1[N*N]){      //turn 2d array into 1d
    for (int i = 0; i < dimension; i++){
        for (int j = 0; j < dimension; j++){
            A1[i*dimension+j] = A[i][j];
        }
    }

    for (int i = 0; i < dimension; i++){
        for (int j = 0; j < dimension; j++){
            B1[j*dimension+i] = B[i][j];
        }
    }
    return 0;
}

int main(){
    int A[N][N];
    int B[N][N];
    int C[N][N];
    int A1[N*N];
    int B1[N*N];
    zeroMatrix(C);
    srand(3);
    generateRandomMatrix(A);
    //printMatrix(A);
    srand(4);
    generateRandomMatrix(B);
    //printMatrix(B);
    twoDimToOneDim(A, B, N, A1, B1);
    //printOneDimMatrix(A1);
    //printOneDimMatrix(B1);
    clock_t tic = clock();
    //multiply1DimensionMatrices(A1, B1, C);
    //multiplyMatrices(A, B, C);
    clock_t toc = clock();
    printMatrix(C);
    printf("Elapsed: %f seconds\n", (double)(toc - tic) / CLOCKS_PER_SEC);
}