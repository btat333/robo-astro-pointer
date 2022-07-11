#include <assert.h>
#include <zmq.h>
#include <errno.h>
#include <string.h>

#include "../util/registry.h"

void* create_subscription(void* zmq_ctx, char* url, int conflate_bool) 
{
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
	
    return pull;
}


/* Initialize socket */
void* create_publisher(void* zmq_ctx, char* url)
{
  	void *push = zmq_socket (zmq_ctx, ZMQ_PUB); 
	/* Bind it to a in-process transport with the address */
    printf("%s\n",url);
	int rc = zmq_connect(push, url);
    printf("Oh dear, something went wrong with read()! %s\n", strerror(errno));
	assert(rc == 0);

    return push;
}
