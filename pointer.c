
#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>

#include <czmq.h>

#include "pointer.h"

void * listen_gps_updates (void* zmq_ctx)
{

    /* Initialize socket */
    //printf("Initilizing gps subscription socket.\n");
    void *ctx = zmq_ctx_new();
    void* pull = zmq_socket(ctx, ZMQ_SUB);
    int rc = zmq_setsockopt (pull, ZMQ_SUBSCRIBE, "", 0);
    rc = zmq_connect (pull, "tcp://localhost:5555");
	assert(rc == 0);

    //printf("Pointer arm waiting for GPS updates.\n");

    while(1){
	  
        /* Create an empty 0MQ message */
        //printf("Looping and waiting on a gps message...\n");
        /* Create an empty ØMQ message */
        zmq_msg_t msg;
        int rc = zmq_msg_init (&msg);
        printf("GGA2: %s","Hello");
        fflush(stdout);
        /* Block until a message is available to be received from socket */
        //printf("Looping and waiting on a gps message...\n");
        rc = zmq_msg_recv (&msg, pull, 0);
        printf("GGA2: %s","World");
        fflush(stdout);
        //printf("Looping and waiting on a gps message...\n");
        zmq_msg_close (&msg);
        printf("GGA2: %s","Hi");
    }

}