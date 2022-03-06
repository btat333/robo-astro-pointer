
#include <vips/vips.h>

#include "camera.h"

// Configure locations of catalogue data & images
#define IMAGE "./sample_images/26_07_-_20_52_00_image7_800.jpg"
#define OUTFILE "./fits/out.fits"

const char* take_image() {

    const char* image_path = IMAGE;
    return image_path;
}

const char* transform_to_fits(const char* jpeg) {

    VipsImage *in;
    VipsImage *bw_image;
    const char* fits_file = OUTFILE;
    int err_num;

    // open the image
    if( !(err_num = vips_jpegload(jpeg, &in)) ) {
        vips_error_exit(NULL);
    }

    // Convert to B/W
    if( !(err_num = vips_scRGB2BW(in, &bw_image)) ) {
        vips_error_exit(NULL);
    }

    // Save FITS file
    if( !(err_num = vips_fitssave(bw_image, fits_file)) ) {
        vips_error_exit(NULL);
    }

    return fits_file;
}