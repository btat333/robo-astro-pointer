
#ifndef __FRAME_H_INCLUDED__
#define __FRAME_H_INCLUDED__

#include <time.h>

#include "matrix.h"

// Earth rotation angle representing rotation from ECI/MJ2000 to ITRF about z-axis due to earth spin (no nutation/precession)
// ut1l_julian_date - ut1 julian date
double get_earth_rotation_angle(double ut1_julian_date);

// Frame Rotate
// Returns DCM representing rotation from ECI to ITRF at the specified julian date time
// time_t unix_time - unix seconds representing desired epoch
Matrix get_eci_itrf_dcm(time_t unix_time);

// Returns DCM representing rotation from ITRF to topocentric (SEZ) frame
// latitude and longitude - radians
Matrix get_itrf_topo_dcm(double latitude, double longitude);

#endif  //  __MATRIX_H_INCLUDED__