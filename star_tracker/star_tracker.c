// inclues

#include "star_tracker.h"

#include <czmq.h>

#include "camera.h"

void *create_star_tracker(void* context)
{

    /* Initialize socket */
	fprintf (stdout, "Initilizing attitude endpoint.\n");
    void* push = zmq_socket (context, ZMQ_PUB); 
    int rc = zmq_bind (push, "inproc://attitude");

    // Set up camera

    // Take pictures and update attitude estimate
    while(1) {

        // Take picture
	    fprintf (stdout, "Taking image.\n");
        const char* image_path = take_image();

        // Convert to FITS
	    fprintf (stdout, "Converting to FITS.\n");
        const char* fits_image_path = transform_to_fits(image_path);

        // Extract stars

        // First Iteration of Match

        // Addtl iterations

        // Determine Attitude

        // Publish Attitude

	    fprintf (stdout, "Sleeping.\n");
        sleep(50);
    }
}
