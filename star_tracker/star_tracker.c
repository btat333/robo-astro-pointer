// inclues

#include "star_tracker.h"

#include <czmq.h>

#include "camera.h"

void *create_star_tracker()
{

    /* Initialize socket */
    zsock_t *push = zsock_new_push ("inproc://attitude");

    // Set up camera

    // Take pictures and update attitude estimate
    while(1) {

        // Take picture
        const char* image_path = take_image();

        // Convert to FITS
        const char* fits_image_path = transform_to_fits(image_path);

        // Extract stars

        // First Iteration of Match

        // Addtl iterations

        // Determine Attitude

        // Publish Attitude

        sleep(50);
    }
}
