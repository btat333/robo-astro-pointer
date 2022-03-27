
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
    VipsImage *scrgb_image;
    VipsImage *bw_image;
    const char* fits_file = OUTFILE;
    int err_num;

    // open the image
    if(err_num = vips_jpegload(jpeg, &in)) {
        vips_error_exit(NULL);
    }

    // Convert to scrgb
    fprintf(stdout,"Converting to greyscale.");
    if(err_num = vips_colourspace(in, &bw_image, VIPS_INTERPRETATION_GREY16, NULL)) {
        vips_error_exit(NULL);
    }

    // Save FITS file
    if(err_num = vips_fitssave(in, fits_file)) {
        vips_error_exit(NULL);
    }

    return fits_file;
}