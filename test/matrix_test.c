#include <stdio.h>

#include "matrix.h"
#include "test_functions.h"

void* test_matrix_multiply() {

    double left_data[2][3] = {  
        {3, 2, 0.0},
        {1, -1, 5}
    };
    double right_data[3][2] = {  
        {3, 2},
        {1, -1},
        {3, -4}
    };
    double result_data[2][2] = {  
        {11, 4},
        {17, -17}
    };

    Matrix left = init_mat(2, 3, left_data);
    Matrix right = init_mat(3, 2, right_data);
    Matrix result = init_mat(2, 2, result_data);

    Matrix func_result = matrix_multiply(left, right);

    compare_matrix(func_result, result);
}

void* test_matrix_transpose() {

    double src_data[2][3] = {  
        {3, 2, 0.0},
        {1, -1, 5}
    };
    double result_data[3][2] = {  
        {3, 1},
        {2, -1},
        {0, 5}
    };

    Matrix src = init_mat(2, 3, src_data);
    Matrix result = init_mat(3, 2, result_data);

    Matrix func_result = transpose_matrix(src);

    compare_matrix(func_result, result);
}

int main (int argc, char **argv)
{

	fprintf (stdout, "Testing matrix util.\n");

    switch(argv[0][0]) {

        case 1  :
            test_matrix_multiply();
            break; 
            
        case 2  :
            test_matrix_transpose();
            break; 
        
        /* you can have any number of case statements */
        default : /* Optional */
            printf("Not recognized test enum.");
    }
}