
#include <assert.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include <math.h>
#include <pthread.h>
#include <zmq.h>

#include "../util/zhelpers.h"
#include "../util/models.h"
#include "../util/registry.h"
#include "acs.h"

const int conflate = 1;

void* zmq_ctx;
pthread_mutex_t gps_mutex;
pthread_mutex_t magnet_mutex;

struct GPSPointSolution gps;
struct MagnetometerMeasurement magnetometer_data;

int has_magnet = 0;
int has_gps = 0;

void * listen_magnet_updates ()
{

    /* Initialize socket */
    printf("Initilizing magnetometer subscription socket.\n");
    void* pull = zmq_socket(zmq_ctx, ZMQ_SUB);
    int rc = zmq_connect (pull, MAGNET_SUBSCRIBE_URL);
	assert(rc == 0);
    rc = zmq_setsockopt (pull, ZMQ_SUBSCRIBE, EMPTY_TOPIC, EMPTY_TOPIC_LENGTH);
    int yes = 1;
    rc = zmq_setsockopt (pull, ZMQ_CONFLATE, &yes, sizeof(yes));
    //rc = zmq_setsockopt (pull, ZMQ_CONFLATE, &conflate, sizeof(conflate));
	assert(rc == 0);

    //printf("Pointer arm waiting for GPS updates.\n");

    while(1){
	  
        /* Block until a message is available to be received from socket */
        char *string = s_recv(pull);

        pthread_mutex_lock(&magnet_mutex);
        magnetometer_data = parse_magnetomer_data(string);
        has_magnet = 1;
        pthread_mutex_unlock(&magnet_mutex);

        fprintf(stdout,"%s\n",string);
        fflush(stdout);
    }

}

void * listen_gps_updates ()
{

    /* Initialize socket */
    printf("Initilizing gps subscription socket.\n");
    void* pull = zmq_socket(zmq_ctx, ZMQ_SUB);
    int rc = zmq_connect (pull, GPS_SUBSCRIBE_URL);
	assert(rc == 0);
    rc = zmq_setsockopt (pull, ZMQ_SUBSCRIBE, EMPTY_TOPIC, EMPTY_TOPIC_LENGTH);
	assert(rc == 0);

    while(1){
	  
        /* Block until a message is available to be received from socket */
        char *string = s_recv(pull);
        pthread_mutex_lock(&gps_mutex);
        gps = parse_gps(string);
        has_gps = 1;
        pthread_mutex_unlock(&gps_mutex);

        fprintf(stdout,"%s",string);
        fflush(stdout);
    }

}

void * publish_attitude ()
{

    /* Initialize socket */
    // printf("Initilizing attitude producer.\n");
    // void* pull = zmq_socket(zmq_ctx, ZMQ_PUB);
    // int rc = zmq_connect (pull, ATTITUDE_PUBLISH_URL);
	// assert(rc == 0);

    int local_has_gps = 0;
    int local_has_magnet = 0;

    while(1)
    {

        sleep(2);

        if (!(local_has_gps && local_has_magnet))
        {
            pthread_mutex_lock(&gps_mutex);
            local_has_gps = has_gps;
            pthread_mutex_unlock(&gps_mutex);

            // Wait for magnetometer mutex lock
            pthread_mutex_lock(&magnet_mutex);
            local_has_magnet = has_magnet;
            pthread_mutex_unlock(&magnet_mutex);
        }

        if (local_has_gps && local_has_magnet)
        {

            // Wait for gps mutex lock (how much delay can there between the gps and magnet data?  Are we introducing a latency?)
            pthread_mutex_lock(&gps_mutex);
            struct GPSPointSolution latest_gps = gps;
            pthread_mutex_unlock(&gps_mutex);

            // Wait for magnetometer mutex lock
            pthread_mutex_lock(&magnet_mutex);
            struct MagnetometerMeasurement latest_mag = magnetometer_data;
            pthread_mutex_unlock(&magnet_mutex);

            double declination = 0.18482;
            printf("1:%lf,%lf\n",magnetometer_data.x,magnetometer_data.y);
            double heading = atan2(latest_mag.y, latest_mag.x) - declination;
            printf("2:%lf\n",heading);
        
            // //Due to declination check for >360 degree
            // if(heading > 2*M_PI){
            //     heading = heading - 2*M_PI;
            // }

            // //check for sign
            // if(heading < 0){
            //     heading = heading + 2*M_PI;
            // }

            //convert into angle
            double heading_angle = heading * 180/M_PI;
            printf("%lf\n",heading_angle);
            fflush(stdout);

            // triad method to determine orientation in topocentric frame

            // utilize gps data to rotate to ECI coordinates
        }
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
	if (error_num = pthread_create(&magnetometer_listener, NULL, listen_magnet_updates, NULL))
	{
		fprintf (stderr, "Unable to start magnetometer listener: %s\n", strerror (error_num)) ;
		return 1 ;
	}
	if (error_num = pthread_create(&attitude_publisher, NULL, publish_attitude, NULL))
	{
		fprintf (stderr, "Unable to start attitude publisher: %s\n", strerror (error_num)) ;
		return 1 ;
	}

	// Close out the threads as they shut down
	fprintf(stdout, "Awaiting closure of threads.\n");
	pthread_join(gps_reciever_listener, NULL);
	pthread_join(magnetometer_listener, NULL);
	pthread_join(attitude_publisher, NULL);
    zmq_ctx_destroy(zmq_ctx);
    pthread_mutex_destroy(&gps_mutex);
    pthread_mutex_destroy(&magnet_mutex);
	return 0;
}
