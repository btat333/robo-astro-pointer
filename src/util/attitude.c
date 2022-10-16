#include <math.h>

#include "attitude.h"
#include "matrix.h"
#include "models.h"

// Euler 3rd axis rotation DCM
// angle - radians
Matrix get_euler_rot_3(double angle) {

	double c = cos(angle);
	double s = sin(angle);
    double c_data[3][3] = {  
        {c, s, 0.0},   /*  initializers for row indexed by 0 */
        {-s, c, 0.0},   /*  initializers for row indexed by 1 */
        {0.0, 0.0, 1.0}   /*  initializers for row indexed by 2 */
    };

    Matrix C = init_mat(3, 3, c_data);

    return C;
}

// Euler 2nd axis rotation DCM
// angle - radians
Matrix get_euler_rot_2(double angle) {

	double c = cos(angle);
	double s = sin(angle);
    double c_data[3][3] = {  
        {c, 0.0, -s},   /*  initializers for row indexed by 0 */
        {0.0, 1.0, 0.0},   /*  initializers for row indexed by 1 */
        {s, 0.0, c}   /*  initializers for row indexed by 2 */
    };

    Matrix C = init_mat(3, 3, c_data);

    return C;
}

// Converts an RA and DEC in radians to a unit vector
Matrix radec_2_unitvec(RADec radec) {

	double x = cos(radec.RA);
	double y = sin(radec.RA);
	double z = sin(radec.dec);
    double c_data[3][1] = {  
        {x},   /*  initializers for row indexed by 0 */
        {y},   /*  initializers for row indexed by 1 */
        {z}   /*  initializers for row indexed by 2 */
    };

    Matrix C = init_mat(3, 1, c_data);

    return C;
}

// Euler 2nd axis rotation DCM
// angle - radians
RADec unitvec_2_radec(Matrix unitvec) {

    double x = unitvec.mat[1,1];
    double y = unitvec.mat[2,1];
    double z = unitvec.mat[3,1];

    double xy = sqrt(pow(x,2)+pow(y,2));
    double dec = asin(z/xy);
    double ra = atan2(y,x);

	RADec radec;
    radec.RA = ra;
    radec.dec = dec;

    return radec;
}