#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "frame.h"
#include "test_functions.h"

void* test_get_earth_rotation_angle() {

    double theta = get_earth_rotation_angle(2459819.7025694);
    fprintf(stdout,"%9.12lf\n\n",theta);
    fflush(stdout);
    compare_double(theta, 0.855807102419);
}

void* test_get_eci_itrf_dcm() {
}

void* test_get_itrf_topo_dcm() {
}

int main (int argc, char **argv)
{

	fprintf (stdout, "Testing frame util.\n");
    switch(argv[1][0]) {

        case '1'  :
            test_get_earth_rotation_angle();
            break; 
            
        case '2'  :
            test_get_eci_itrf_dcm();
            break; 

        case '3'  :
            test_get_itrf_topo_dcm();
            break; 
        
        /* you can have any number of case statements */
        default : /* Optional */
            printf("Not recognized test enum.");
            exit(1);
    }
}