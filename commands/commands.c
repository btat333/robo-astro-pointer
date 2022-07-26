
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
#include "commands.h"

const int conflate = 1;

void* zmq_ctx;

void * broker_republish ()
{

    /* Initialize socket */
    printf("Initilizing broker socket.\n");
    int conflate = 0;
    int bind = 1;
    void* pull = create_subscription(zmq_ctx, COMMAND_SUBSCRIBE_URL, conflate, bind); 
    //void* push = create_publisher(zmq_ctx, TELEMETRY_REPUBLISH_URL, bind);

    while(1){
	  
        /* Block until a message is available to be received from socket */
        char *string_received = s_recv(pull);
        printf("Cmd received: %s",string_received);
        //s_send(push, string_received);
    }

}

int main (int argc, char **argv)
{

	fprintf (stdout, "Initializing zeromq context.\n");

    pthread_t broker;

	zmq_ctx = zmq_ctx_new();
	int error_num;
	fprintf (stdout, "Initilizing command broker.\n");
    if (error_num = pthread_create(&broker, NULL, broker_republish, NULL))
	{
		fprintf (stderr, "Unable to start broker: %s\n", strerror (error_num)) ;
		return 1 ;
	}

	// Close out the threads as they shut down
	fprintf(stdout, "Awaiting closure of threads.\n");
	pthread_join(broker, NULL);
    zmq_ctx_destroy(zmq_ctx);
	return 0;
}
