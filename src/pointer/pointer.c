
#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>

#include <czmq.h>

#include "../util/zhelpers.h"
#include "../util/models.h"
#include "../util/registry.h"
#include "pointer.h"


int main(int argc, char **argv)
{
    fprintf (stdout, "Initializing zeromq context.\n");

	void* zmq_ctx = zmq_ctx_new();
	int error_num;
	fprintf (stdout, "Initilizing pointer listener.\n");

	listen_gps_updates(zmq_ctx);

    zmq_ctx_destroy(zmq_ctx);

	return 0;
}

void * listen_gps_updates (void* zmq_ctx)
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
        struct GPSPointSolution gps = parse_gps(string);

        fprintf(stdout,"%f\n",gps.longitude);
    }

}