
#ifndef __ATTITUDE_H_INCLUDED__
#define __ATTITUDE_H_INCLUDED__

#include "matrix.h"

// Euler 3rd axis rotation DCM
// angle - radians
Matrix get_euler_rot_3(double angle);

// 2 ROTATION MATRIX
Matrix get_euler_rot_2(double angle);

// 1 ROTATION MATRIX

// Converts an RA and DEC in radians to a unit vector
Matrix radec_2_unitvec(RADec radec);

// Euler 2nd axis rotation DCM
// angle - radians
RADec unitvec_2_radec(Matrix unitvec);

#endif  //  __ATTITUDE_H_INCLUDED__