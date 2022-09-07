#include <wiringPi.h>

#include "../util/matrix.h"
#include "../util/models.h"

#include "pointer_util.h"

// Point pointer at an RA DEC based direction and turn on laser
void* point_direction(Matrix latest_attitude, Direction dir) {

    // Determine unit vector in ECI

    // Convert unit vector to body frame

    // Convert body frame unit to angles

    // Convert angles to stepper motor values

    // Command pointer with stepper motor values

    // Turn on laser pointer
    turn_on_laser();
}

// Point pointer at an RA DEC based direction and turn on laser
void* point_home() {

    // Command pointer with stepper motor values

    // Turn on laser pointer
    turn_off_laser();
}

// Turn on the laser pointer
void* turn_on_laser() {

    digitalWrite(0, HIGH);
    return 0;
}

// Turn off the laser pointer
void* turn_off_laser() {
    digitalWrite(0,  LOW) ;  
}