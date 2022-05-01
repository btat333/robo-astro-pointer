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
    printf(msg);
    int f = sscanf( msg, "%f,%f,%1s,%f,%1s,%d,%d,%f,%s", &time, &gps.latitude, north, 
                    &gps.longitude, west, &type, &gps.sat_num, &gps.hdop, rest);

    return gps;
}

/* Serializes magnetometer measurement to string */
void * serialize_magnetometer_data(struct MagnetometerMeasurement meas, char * out_string) 
{
    
    int f = sprintf( out_string, "%lf,%lf,%lf", meas.x, meas.y, meas.z);
    assert(f >= 0);
}

/* Serializes magnetometer measurement to string */
void * parse_magnetomer_data(char * mm_string, struct MagnetometerMeasurement * meas) 
{
    double x;
    double y;
    double z;
    int f = sscanf( mm_string, "%lf,%lf,%lf", x, y, z);
    meas->x = x;
    meas->x = y;
    meas->x = z;
    assert(f >= 0);
}