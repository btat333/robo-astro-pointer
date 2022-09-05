#include <stdio.h>
#include <stdlib.h>

#include "matrix.h"

Matrix init_mat(const int    height,
                const int    width,
                double values[])
{
    Matrix matrix;
    int i,j = 0;

    if ((matrix.mat = malloc((1 + width * height) * sizeof(double))) == NULL) {
        exit(84);
    }
    matrix.rows = height;
    matrix.columns = width;
    if (values != NULL) {
        for (i = 0; i < height; i++) {
            for (j = 0; j < width; j++) {
                matrix.mat[i*width+j] = values[i*width+j];
            }
        }
    }
    return (matrix);
}

void delete_mat(Matrix mat) {

    free(mat.mat);
    return;
}

Matrix zeros(int rows, int columns) {
    Matrix new = init_mat(rows, columns, NULL);
    int i;

    for (i = 0; i < rows*columns; i++) {
        new.mat[i] = 0;
    }
    return (new);
}

Matrix matrix_multiply(Matrix left, Matrix right) {

    if(left.mat == NULL || right.mat == NULL) {
        fprintf(stderr, "Attempting to multiply invalid matrix with zero entries, exiting...\n");
        exit(EXIT_FAILURE);
    }

    if(left.columns != right.rows) {        
        fprintf(stderr, "Attempting to multiply matrices of incorrect sizes for multiplication, exiting...\n");
        exit(EXIT_FAILURE);
    }

    Matrix out = init_mat(left.rows, right.columns, NULL);

    for (int i = 0; i < left.rows; i++){
        for(int j = 0; j < right.columns; j++) {

            int l = i * right.columns + j;
            out.mat[l] = 0;

            for(int k = 0; k < left.columns; k++) {

                // Degenerate indices from multi -> single array
                int m = i * left.columns + k;
                int n = k * right.columns + j;
                out.mat[l] += left.mat[m]*right.mat[n];
            }
        }
    }

    return out;
}

Matrix transpose_matrix(Matrix src) {

    if(sizeof(src) == 0) {
        fprintf(stderr, "Attempting to transpose invalid matrix with zero entries, exiting...\n");
        exit(EXIT_FAILURE);
    }

    int M = src.rows;
    int N = src.columns;

    double mat_data[M][N];

    for(int n = 0; n<N*M; n++) {
        int i = n/N;
        int j = n%N;
        mat_data[i][j] = src.mat[M*j + i];
    }

    Matrix dst = init_mat(M, N, mat_data);
    return dst;
}

void display_mat(Matrix mat) {

    for (int i = 0; i < mat.rows; i++) {

        fprintf(stdout,"[");
        for (int j = 0; j < mat.columns; j++) {
            fprintf(stdout,"%18.10f",mat.mat[i*mat.columns+j]);

            if (j != mat.columns-1) {
                fprintf(stdout,", ");
            }
        }
        fprintf(stdout,"]\n");
    }
    fprintf(stdout,"\n");
    fflush(stdout);
}