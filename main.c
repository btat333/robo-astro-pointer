

#include <stdio.h>
#include <string.h>
#include <errno.h>

#include <zmq.h>
#include <pthread.h>
#include <vips/vips.h>
#include <wiringPi.h>
#include <wiringSerial.h>

#include "gps.h"
#include "./star_tracker/star_tracker.h"
#include "pointer.h"


pthread_t gps_reciever_listener;
pthread_t magnetometer_listener;
pthread_t pointer_gps_listener;
pthread_t star_tracker_listener;

void *release_app_memory() {
	end_gps_loop();
	end_magnetometer_loop();
	pthread_join(gps_reciever_listener, NULL);
	pthread_join(magnetometer_listener, NULL);
	pthread_join(pointer_gps_listener, NULL);
	pthread_join(star_tracker_listener, NULL);
}

int main (int argc, char **argv)
{

	//fprintf (stdout, "Initializing VIPS.\n");

	if (VIPS_INIT (argv[0])) {
    	vips_error_exit( NULL ); 
	}

	//fprintf (stdout, "Initializing zeromq context.\n");

	void* zmq_ctx = zmq_ctx_new();
	int error_num;
	//fprintf (stdout, "Initilizing gps.\n");

	if (error_num = pthread_create(&gps_reciever_listener, NULL, create_gps_listener, zmq_ctx))
	{
		fprintf (stderr, "Unable to start gps: %s\n", strerror (error_num)) ;
		release_app_memory();
		return 1 ;
	}
	sleep(2);
	//fprintf (stdout, "Initilizing magnetometer.\n");
	if (error_num = pthread_create(&magnetometer_listener, NULL, create_magnetometer_listener, zmq_ctx))
	{
		fprintf (stderr, "Unable to start magnetometer: %s\n", strerror (error_num)) ;
		release_app_memory();
		return 1 ;
	}
	// if (error_num = pthread_create(&star_tracker_listener, NULL, create_star_tracker, zmq_ctx))
	// {
	// 	fprintf (stderr, "Unable to start star tracker: %s\n", strerror (error_num)) ;
	// 	release_app_memory();
	// 	return 1 ;
	// }
	//fprintf (stdout, "Initilizing pointer arm.\n");
	if (error_num = pthread_create(&pointer_gps_listener, NULL, listen_gps_updates, zmq_ctx))
	{
		fprintf (stderr, "Unable to start pointer gps: %s\n", strerror (error_num)) ;
		release_app_memory();
		return 1 ;
	}

	// Close out the threads as they shut down
	//fprintf(stdout, "Awaiting closure of threads.\n");
	if ((error_num = pthread_join(gps_reciever_listener, NULL)))
	{
		fprintf (stderr, "Unable to start gps: %s\n", strerror (errno)) ;
		return 1 ;
	}
	if ((error_num = pthread_join(magnetometer_listener, NULL)))
	{
		fprintf (stderr, "Unable to start magnetometer: %s\n", strerror (errno)) ;
		return 1 ;
	}
	// if ((error_num = pthread_join(star_tracker_listener, NULL)))
	// {
	// 	fprintf (stderr, "Unable to join star tracker: %s\n", strerror (error_num)) ;
	// 	return 1 ;
	// }
	if ((error_num = pthread_join(pointer_gps_listener, NULL)))
	{
		fprintf (stderr, "Unable to join pointing arm gps listener: %s\n", strerror (error_num)) ;
		return 1 ;
	}
	//fprintf (stdout, "All worker threads closed.\n");
	return 0;
}
