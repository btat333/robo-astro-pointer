#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "matrix.h"
#include "models.h"

/* Parses a GPSPointSolution data from string */
struct GPSPointSolution parse_gps(char *msg) 
{
    
    struct GPSPointSolution gps;
    double time;
    char north[1];
    char west[1];
    int type;
    char remainder [200];

    char* bad_data_flag = strstr( msg, "00,99.99");

    if (bad_data_flag){

        gps.hdop = 99.99;
        gps.altitude = 0;
        gps.latitude = 0;
        gps.longitude = 0;
        gps.sat_num = 0;
        return gps;
    }

    int f = sscanf( msg, "%lf,%lf,%1s,%lf,%1s,%d,%d,%f,%lf,%s", &time, &gps.latitude, north, 
                    &gps.longitude, west, &type, &gps.sat_num, &gps.hdop, &gps.altitude, remainder);

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
    char remainder [200];

    sscanf( mm_string, "%lf,%lf,%lf%s", &x, &y, &z, remainder);

    meas.x = x;
    meas.y = y;
    meas.z = z;
    return meas;
}

void * serialize_attitude_data(Matrix C, char* out_string) {

    char tmp[10] = "";
    sprintf(tmp,"%10f",C.mat[0]);
    strcat(out_string,tmp);
    for(int i = 1; i < C.rows*C.columns; i++){
        sprintf(tmp,"%10f",C.mat[i]);
        strcat(out_string,",");
        strcat(out_string,tmp);
    }
}

/*  Parses attitude in form of DCM from string */
Matrix parse_attitude_data(char * att_string) 
{
    Matrix att;
    double att_data[9];

    int i = 0;
    char* pch = strtok (att_string,",");
    while (pch != NULL)
    {
        att_data[i] = atof(pch);
        pch = strtok (NULL, " ,.-");
        i++;
    }

    att = init_mat(3,3,att_data);
    return att;
}

/*  Parses command in form of DCM from string */
Command parse_command(char * command_string) {

    Command comm;
    char* command_type;
    char* data;

    sscanf( command_string, "%[A-Z] *", command_type, data);

    comm.command_type = command_type;
    comm.data = data;
    return comm;
}

RADec parse_direction(char * dir_string) {

    RADec direction;
    double RA;
    double dec;

    sscanf( dir_string, "%lf,%lf", &RA, &dec);

    direction.RA = RA;
    direction.dec = dec;
    return direction;
}