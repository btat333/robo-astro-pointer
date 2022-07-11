#include <stdio.h>
#include <assert.h>

#include "models.h"

/* Parses a GPSPointSolution data from string */
struct GPSPointSolution parse_gps(char *msg) 
{
    
    struct GPSPointSolution gps;
    float time;
    char north[1];
    char west[1];
    int type;
    char *rest;
    int f = sscanf( msg, "%f,%f,%1s,%f,%1s,%d,%d,%f,%f,%s", &time, &gps.latitude, north, 
                    &gps.longitude, west, &type, &gps.sat_num, &gps.hdop, &gps.altitude, rest);

    return gps;
}

/* Serializes magnetometer measurement to string */
void * serialize_magnetometer_data(struct MagnetometerMeasurement meas, char * out_string) 
{
    
    int f = sprintf( out_string, "%lf,%lf,%lf", meas.x, meas.y, meas.z);
    assert(f >= 0);
}

/* Serializes magnetometer measurement to string */
struct MagnetometerMeasurement parse_magnetomer_data(char * mm_string) 
{
    struct MagnetometerMeasurement meas;
    double x = 0;
    double y = 0;
    double z = 0;
    int f = sscanf( mm_string, "%f,%f,%f", &x, &y, &z);
    assert(f >= 0);
    meas.x = x;
    meas.y = y;
    meas.z = z;
    return meas;
}