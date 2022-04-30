
#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>

#include <czmq.h>
#include <pthread.h>

#include "../util/zhelpers.h"
#include "../util/models.h"
#include "../util/registry.h"
#include "acs.h"

void* zmq_ctx;
pthread_mutex_t gps_mutex;
pthread_mutex_t magnet_mutex;
struct GPSPointSolution gps;
int has_gps = 0;


void * listen_gps_updates ()
{

    /* Initialize socket */
    printf("Initilizing gps subscription socket.\n");
    void* pull = zmq_socket(zmq_ctx, ZMQ_SUB);
    int rc = zmq_connect (pull, "tcp://localhost:5555");
    rc = zmq_setsockopt (pull, ZMQ_SUBSCRIBE, GPS_TOPIC, GPS_TOPIC_LENGTH);
	assert(rc == 0);

    //printf("Pointer arm waiting for GPS updates.\n");

    while(1){
	  
        printf("Receiving message...\n");
        fflush(stdout);
        /* Block until a message is available to be received from socket */
        //printf("Looping and waiting on a gps message...\n");
        char *string = s_recv(pull);
        printf("Parsing message...\n");
        pthread_mutex_lock(&gps_mutex);
        struct GPSPointSolution gps = parse_gps(string);
        has_gps = 1;
        pthread_mutex_unlock(&gps_mutex);

        fprintf(stdout,"%f\n",gps.longitude);
    }

}

int main (int argc, char **argv)
{

	fprintf (stdout, "Initializing zeromq context.\n");

    pthread_t gps_reciever_listener;
    pthread_t magnetometer_listener;
    pthread_t attitude_publisher;

	zmq_ctx = zmq_ctx_new();
    pthread_mutex_init(&gps_mutex,NULL);
    pthread_mutex_init(&magnet_mutex,NULL);
	int error_num;
	fprintf (stdout, "Initilizing gps listener.\n");

	if (error_num = pthread_create(&gps_reciever_listener, NULL, listen_gps_updates, NULL))
	{
		fprintf (stderr, "Unable to start gps listener: %s\n", strerror (error_num)) ;
		return 1 ;
	}
	// fprintf (stdout, "Initilizing magnetometer listener.\n");
	// if (error_num = pthread_create(&magnetometer_listener, NULL, create_magnetometer_listener, zmq_ctx))
	// {
	// 	fprintf (stderr, "Unable to start magnetometer listener: %s\n", strerror (error_num)) ;
	// 	release_app_memory();
	// 	return 1 ;
	// }
	// if (error_num = pthread_create(&pointer_gps_listener, NULL, listen_gps_updates, zmq_ctx))
	// {
	// 	fprintf (stderr, "Unable to start pointer gps: %s\n", strerror (error_num)) ;
	// 	release_app_memory();
	// 	return 1 ;
	// }

	// Close out the threads as they shut down
	fprintf(stdout, "Awaiting closure of threads.\n");
	pthread_join(gps_reciever_listener, NULL);
    zmq_ctx_destroy(zmq_ctx);
    pthread_mutex_destroy(&gps_mutex);
    pthread_mutex_destroy(&magnet_mutex);
	return 0;
}
