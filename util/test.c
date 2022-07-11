
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

void* zmq_ctx;

struct GPSPointSolution gps;
struct MagnetometerMeasurement magnetometer_data;

void * listen_magnet_updates ()
{

    /* Initialize socket */
    printf("Initilizing test of telemetry socket.\n");
    int conflate = 1;
    void* pull = create_subscription(zmq_ctx, "tcp://localhost:5558", conflate); 

    while(1){
	  
        /* Block until a message is available to be received from socket */
        char *s = s_recv(pull);

        printf("%s\n",s);
		fflush(stdout);
    }

}

int main (int argc, char **argv)
{

	fprintf (stdout, "Initializing zeromq context.\n");

    pthread_t gps_reciever_listener;
    pthread_t magnetometer_listener;

	zmq_ctx = zmq_ctx_new();
	listen_magnet_updates();
    zmq_ctx_destroy(zmq_ctx);
	return 0;
}
