
#include <stdio.h>
#include <string.h>
#include <errno.h>

#include <czmq.h>

#include "pointer.h"

void * listen_gps_updates ()
{

    /* Initialize socket */
    zsock_t *pull = zsock_new_pull ("inproc://gps");

    while(1){
	  
        char *string = zstr_recv(pull);
        printf("GGA2: %s",string);
    }

}