
#ifndef __MODELS_H_INCLUDED__
#define __MODELS_H_INCLUDED__

#include "matrix.h"

// Represents an instantaneous measurment returned from the GPS reciever
struct GPSPointSolution {
  double latitude; // Assumes north for now [dd][mm.mmmm]
  double longitude; // Assumes west for now [ddd][mm.mmmm]
  double altitude; // meters above sea level
  float hdop; // Accuracy of measurement horizontally - <1 is amazing, 1-5 is great/good
  int sat_num; // number of visible gps satellites.  less than 4 is bad.
};

// Represents an instantaneous measurement from the magnetometer
struct MagnetometerMeasurement {
  double x; // X axis magnetometer reading
  double y; // Y axis magnetometer reading
  double z; // Z axis magnetometer reading
};

// Functions
struct GPSPointSolution parse_gps (char *msg);

void * serialize_magnetometer_data(struct MagnetometerMeasurement meas, char * out_string);

struct MagnetometerMeasurement parse_magnetomer_data(char * mm_string);

void * serialize_attitude_data(Matrix C, char * out_string);

Matrix parse_attitude_data(char * C_string);

#endif  //  __MODELS_H_INCLUDED__