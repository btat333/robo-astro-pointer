#include <math.h>
#include <time.h>

#include "attitude.h"
#include "matrix.h"
#include "time_util.h"

#include "frame.h"

// Earth rotation angle representing rotation from ECI/MJ2000 to ITRF about z-axis due to earth spin (no nutation/precession)
// ut1l_julian_date - ut1 julian date
double get_earth_rotation_angle(double ut1_julian_date) {

    double two_pi = 2*M_PI;
    double theta = fmod(two_pi*(0.7790572732640 + 1.00273781191135448*(ut1_julian_date - 2451545.0)),two_pi);
    return theta;
}

// Returns DCM representing rotation from ECI to ITRF at the specified julian date time
// time_t unix_time -> unix seconds representing desired epoch
Matrix get_eci_itrf_dcm(time_t unix_time) {

    // julian date
    double ut1_jd = get_julian_date(unix_time);

    // earth rotation angle
    double theta = get_earth_rotation_angle(ut1_jd);

    // 3 rotation DCM about Z axis
    Matrix C = get_euler_rot_3(theta);

    return C;
}

// Returns DCM representing rotation from ITRF to topocentric (SEZ) frame
// latitude and longitude - radians
Matrix get_itrf_topo_dcm(double latitude, double longitude) {

    double kUnit[3][1] = {{0.0},{0.0},{1.0}};
    double third_rot_angle = 90*M_PI/180;

    // Build euler axis rotation matrices
    Matrix C1 = get_euler_rot_3(longitude);
    Matrix C2 = get_euler_rot_2(-latitude);
    Matrix C3 = get_euler_rot_2(third_rot_angle);


   Matrix Cp = matrix_multiply(C2, C1);
   Matrix C = matrix_multiply(C3, Cp);
   return C;
}