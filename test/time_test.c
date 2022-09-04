#include <assert.h>
#include <stdio.h>
#include <time.h>

#include "models.h"
#include "test_functions.h"
#include "time_util.h"

void* zmq_ctx;

struct GPSPointSolution gps;
struct MagnetometerMeasurement magnetometer_data;

void * test_get_julian_date ()
{
    double jd = get_julian_date(1661662302);
    printf("%lf",jd);
    compare_double(jd, 2459819.7025694);
}

int main (int argc, char **argv)
{

	fprintf (stdout, "Testing time util.\n");
    test_get_julian_date();
}
