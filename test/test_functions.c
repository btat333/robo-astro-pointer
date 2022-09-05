#include <assert.h>
#include <stdio.h>

#include "matrix.h"

#define DOUBLE_TOL 0.0000001;

void * compare_double(double actual, double expected) {
    double diff = actual - expected;
    double tol = DOUBLE_TOL
    assert(diff < tol && diff > -1*tol);
}

void * compare_matrix(Matrix actual, Matrix expected) {
    
    for (int i = 0; i < actual.rows*actual.columns; i++) {
        double diff = actual.mat[i] - expected.mat[i];
        double tol = DOUBLE_TOL

        if (diff >= tol || diff <= -1*tol) {
            fprintf(stdout,"Expected:\n");
            display_mat(expected);
            fprintf(stdout,"Actual:\n");
            display_mat(actual);
        }
        assert(diff < tol && diff > -1*tol);
    }
}

void * compare_matrix_tol(Matrix actual, Matrix expected, double tol) {
    
    for (int i = 0; i < actual.rows*actual.columns; i++) {
        double diff = actual.mat[i] - expected.mat[i];

        if (diff >= tol || diff <= -1*tol) {
            fprintf(stdout,"Expected:\n");
            display_mat(expected);
            fprintf(stdout,"Actual:\n");
            display_mat(actual);
        }
        assert(diff < tol && diff > -1*tol);
    }
}