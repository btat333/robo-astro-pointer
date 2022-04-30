#include <stdio.h>

#include "models.h"

/* Updates stepper motor upon receipt of new GPS data */
struct GPSPointSolution parse_gps(char *msg) 
{
    
    struct GPSPointSolution gps;
    float time;
    char north[1];
    char west[1];
    int type;
    char *rest;
    printf(msg);
    int f = sscanf( msg, "GPS: %f,%f,%1s,%f,%1s,%d,%d,%f,%s", &time, &gps.latitude, north, 
                    &gps.longitude, west, &type, &gps.sat_num, &gps.hdop, rest);

    return gps;
}