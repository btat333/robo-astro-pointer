#include <math.h>

#include "attitude.h"
#include "matrix.h"

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