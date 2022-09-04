#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "attitude.h"
#include "matrix.h"
#include "test_functions.h"

void* test_get_euler_rot_3() {

    double angle = 37.9*M_PI/180;

    Matrix func_result = get_euler_rot_3(angle);

    double result_data[3][3] =  {
        { 0.78908408 ,-0.6142852,   0},
        { 0.6142852,   0.78908408,  0},
        { 0,           0,           1}};

    Matrix expected = init_mat(3,3,result_data);

    compare_matrix(func_result, expected);
}

void* test_get_euler_rot_2() {

    double angle = 47.364*M_PI/180;

    Matrix func_result = get_euler_rot_3(angle);

    double result_data[3][3] =   {
        { 0.67733834,  0,          0.73567165},
        { 0,           1,          0},
        {-0.73567165,  0,          0.67733834}};

    Matrix expected = init_mat(3,3,result_data);

    compare_matrix(func_result, expected);
}

int main (int argc, char **argv)
{

	fprintf (stdout, "Testing attitude util.\n");
    switch(argv[1][0]) {

        case '1'  :
            test_get_euler_rot_3();
            break; 
            
        case '2' :
            test_get_euler_rot_2();
            break; 
        
        /* you can have any number of case statements */
        default : /* Optional */
            printf("Not recognized test enum.");
            exit(1);
    }
}