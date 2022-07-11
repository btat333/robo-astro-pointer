
#ifndef __NETWORK_H_INCLUDED__
#define __NETWORK_H_INCLUDED__

void* create_subscription(void* zmq_ctx, char* url, int conflate_bool); 
void* create_publisher(void* zmq_ctx, char* url); 

#endif  //  __NETWORK_H_INCLUDED__