

#include <stdio.h>
#include <string.h>
#include <errno.h>

#include <pthread.h>
#include <wiringPi.h>
#include <wiringSerial.h>

#include "gps.h"
#include "star_tracker.h"
#include "pointer.h"

int main (int argc, char **argv)
{
	if (VIPS_INIT (argv[0])) {
    	vips_error_exit( NULL ); 
	}

	pthread_t gps_reciever_listener;
	pthread_t magnetometer_listener;
	pthread_t pointer_gps_listener;
	pthread_t star_tracker_listener;

	int error_num;

	// Boot up the FSW tasks
	if (!(error_num = pthread_create(&gps_reciever_listener, NULL, create_gps_listener, NULL)))
	{
		fprintf (stderr, "Unable to start gps: %s\n", strerror (errno)) ;
		return 1 ;
	}
	if (!(error_num = pthread_create(&magnetometer_listener, NULL, create_magnetometer_listener, NULL)))
	{
		fprintf (stderr, "Unable to start magnetometer: %s\n", strerror (errno)) ;
		return 1 ;
	}
	if (!(error_num = pthread_create(&star_tracker_listener, NULL, create_star_tracker, NULL)))
	{
		fprintf (stderr, "Unable to start star tracker: %s\n", strerror (errno)) ;
		return 1 ;
	}
	if (!(error_num = pthread_create(&pointer_gps_listener, NULL, listen_gps_updates, NULL)))
	{
		fprintf (stderr, "Unable to start pointer gps: %s\n", strerror (errno)) ;
		return 1 ;
	}

	// Close out the threads as they shut down
	if (!(error_num = pthread_join(gps_reciever_listener, NULL)))
	{
		fprintf (stderr, "Unable to start gps: %s\n", strerror (errno)) ;
		return 1 ;
	}
	if (!(error_num = pthread_join(magnetometer_listener, NULL)))
	{
		fprintf (stderr, "Unable to start magnetometer: %s\n", strerror (errno)) ;
		return 1 ;
	}
	if (!(error_num = pthread_join(star_tracker_listener, NULL)))
	{
		fprintf (stderr, "Unable to start star tracker: %s\n", strerror (errno)) ;
		return 1 ;
	}
	if (!(error_num = pthread_join(pointer_gps_listener, NULL)))
	{
		fprintf (stderr, "Unable to start pointer gps: %s\n", strerror (errno)) ;
		return 1 ;
	}
	return 0;
}