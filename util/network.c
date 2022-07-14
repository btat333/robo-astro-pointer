#include <assert.h>
#include <zmq.h>
#include <errno.h>
#include <string.h>

#include "../util/registry.h"

void* create_subscription(void* zmq_ctx, char* url, int conflate_bool, int bind_bool) 
{
    /* Initialize socket */
    printf("Initilizing subscription socket for %s.\n",url);
    void* pull = zmq_socket(zmq_ctx, ZMQ_SUB);
    int rc = 0;
    printf("%d\n",bind_bool);
    printf("%s\n",url);
    if (bind_bool == 1) {
	    rc = zmq_bind(pull, url);
    } else {
	    rc = zmq_connect(pull, url);
    }
    if(rc != 0) {

        printf("Error: %s\n", strerror(errno));
	    assert(rc == 0);
    }
    rc = zmq_setsockopt (pull, ZMQ_SUBSCRIBE, EMPTY_TOPIC, EMPTY_TOPIC_LENGTH);
    
    if (conflate_bool == 1) {
        rc = zmq_setsockopt (pull, ZMQ_CONFLATE, &conflate_bool, sizeof(conflate_bool));
        assert(rc == 0);
    }
	
    return pull;
}


/* Initialize socket */
void* create_publisher(void* zmq_ctx, char* url, int bind_bool)
{
  	void *push = zmq_socket (zmq_ctx, ZMQ_PUB); 
	/* Bind/Connect it to a in-process transport with the address */
    int rc = 0;
    printf("%s\n",url);
    if (bind_bool == 1) {
	    rc = zmq_bind(push, url);
    } else {
	    rc = zmq_connect(push, url);
    }
	assert(rc == 0);

    return push;
}
