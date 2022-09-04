#include <math.h>
#include <stdio.h>

#include "attitude.h"
#include "matrix.h"
#include "test_functions.h"

void* test_get_earth_rotation_angle() {
}

void* test_get_eci_itrf_dcm() {
}

void* test_get_itrf_topo_dcm() {
}

int main (int argc, char **argv)
{

	fprintf (stdout, "Testing attitude util.\n");
    switch(argv[0][0]) {

        case 1  :
            test_get_earth_rotation_angle();
            break; 
            
        case 2  :
            test_get_eci_itrf_dcm();
            break; 

        case 3  :
            test_get_itrf_topo_dcm();
            break; 
        
        /* you can have any number of case statements */
        default : /* Optional */
            printf("Not recognized test enum.");
    }
}