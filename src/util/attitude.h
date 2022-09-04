
#ifndef __ATTITUDE_H_INCLUDED__
#define __ATTITUDE_H_INCLUDED__

#include "matrix.h"

// Euler 3rd axis rotation DCM
// angle - radians
Matrix get_euler_rot_3(double angle);

// 2 ROTATION MATRIX
Matrix get_euler_rot_2(double angle);

// 1 ROTATION MATRIX

#endif  //  __ATTITUDE_H_INCLUDED__