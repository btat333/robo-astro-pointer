#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "frame.h"
#include "matrix.h"
#include "test_functions.h"

void* test_get_earth_rotation_angle() {

    double theta = get_earth_rotation_angle(2459819.7025694);
    fprintf(stdout,"%9.12lf\n\n",theta);
    fflush(stdout);
    compare_double(theta, 0.855807102419);
}

void* test_get_eci_itrf_dcm() {

    Matrix eci_2_itrf = get_eci_itrf_dcm(1661662330.996078);
    double data[3][3] = {{0.6556071440378199, 0.7551007719191979, -0.0014480792809151374}, {-0.7550990217533119, 0.6556087426923047, 0.0016259928062552767}, {0.0021771618598179733, 2.743074850519668E-5, 0.9999976296040851}};
    Matrix expected = init_mat(3,3,data);

    compare_matrix_tol(eci_2_itrf, expected, 0.01);
}

void* test_get_itrf_topo_dcm() {

    double latitude = 25.0*M_PI/180;
    double longitude = 45.0*M_PI/180;
    Matrix itrf_2_topo = get_itrf_topo_dcm(latitude,longitude);
    double data[3][3] = {{0.2988362387301202, 0.2988362387301198, -0.9063077870366499}, {-0.7071067811865475, 0.7071067811865477, -1.6653345369377348E-16}, {0.6408563820557885, 0.6408563820557884, 0.4226182617406997}};
    Matrix expected = init_mat(3,3,data);

    compare_matrix(itrf_2_topo, expected);
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