
#include <stdio.h>
#include <string.h>
#include <errno.h>

#include <czmq.h>

#include "pointer.h"

void * listen_gps_updates (void* zmq_ctx)
{

    /* Initialize socket */
    void* pull = zmq_socket(zmq_ctx, ZMQ_SUB);
    int rc = zmq_connect (pull, "inproc://gps");

    while(1){
	  
        /* Create an empty 0MQ message */
        zmq_msg_t msg;
        int rc = zmq_msg_init (&msg);
        /* Block until a message is available to be received from socket */
        rc = zmq_msg_recv (&msg, pull, 0);

        /* Release message */
        zmq_msg_close (&msg);
        printf("GGA2: %s","Hi");
    }

}