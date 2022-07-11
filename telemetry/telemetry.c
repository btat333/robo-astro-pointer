
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
#include "../util/network.h"
#include "telemetry.h"
#include "telemetry_util.h"

const int conflate = 1;

void* zmq_ctx;

struct GPSPointSolution gps;
struct MagnetometerMeasurement magnetometer_data;

void * listen_magnet_updates ()
{

    /* Initialize socket */
    printf("Initilizing magnetometer subscription socket.\n");
    int conflate = 1;
    void* pull = create_subscription(zmq_ctx, MAGNET_SUBSCRIBE_URL, conflate); 
    void* push = create_publisher(zmq_ctx, TELEMETRY_PUBLISH_URL);

    while(1){
	  
        /* Block until a message is available to be received from socket */
        char *string = s_recv(pull);
        magnetometer_data = parse_magnetomer_data(string);
		printf("%s\n",string);
		fflush(stdout);

		publish_tlm_double(push, MAGNET_PACKET, X_MNEMONIC, magnetometer_data.x);
		publish_tlm_double(push, MAGNET_PACKET, Y_MNEMONIC, magnetometer_data.y);
		publish_tlm_double(push, MAGNET_PACKET, Z_MNEMONIC, magnetometer_data.z);
    }

}

void * listen_gps_updates ()
{

    /* Initialize socket */
    printf("Initilizing gps subscription socket.\n");
    int conflate = 1;
    void* pull = create_subscription(zmq_ctx, GPS_SUBSCRIBE_URL, conflate); 
    void* push = create_publisher(zmq_ctx, TELEMETRY_PUBLISH_URL);

    while(1){
	  
        /* Block until a message is available to be received from socket */
        char *string = s_recv(pull);
        gps = parse_gps(string);

		publish_tlm_double(push, GPS_PACKET, ALT_MNEMONIC, gps.altitude);
		publish_tlm_double(push, GPS_PACKET, LAT_MNEMONIC, gps.latitude);
		publish_tlm_double(push, GPS_PACKET, LONG_MNEMONIC, gps.longitude);
		publish_tlm_double(push, GPS_PACKET, SATNUM_MNEMONIC, gps.sat_num);
		publish_tlm_double(push, GPS_PACKET, HDOP_MNEMONIC, gps.hdop);
    }

}

  /* Initialize socket */
    printf("Initilizing subscription socket for %s.\n",url);
    void* pull = zmq_socket(zmq_ctx, ZMQ_SUB);
    int rc = zmq_connect (pull, url);
	assert(rc == 0);
    rc = zmq_setsockopt (pull, ZMQ_SUBSCRIBE, EMPTY_TOPIC, EMPTY_TOPIC_LENGTH);
    
    if (conflate_bool == 1) {
        rc = zmq_setsockopt (pull, ZMQ_CONFLATE, &conflate_bool, sizeof(conflate_bool));
        assert(rc == 0);
    }

int main (int argc, char **argv)
{

	fprintf (stdout, "Initializing zeromq context.\n");

    pthread_t gps_reciever_listener;
    pthread_t magnetometer_listener;

	zmq_ctx = zmq_ctx_new();
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

	// Close out the threads as they shut down
	fprintf(stdout, "Awaiting closure of threads.\n");
	pthread_join(gps_reciever_listener, NULL);
	pthread_join(magnetometer_listener, NULL);
    zmq_ctx_destroy(zmq_ctx);
	return 0;
}
