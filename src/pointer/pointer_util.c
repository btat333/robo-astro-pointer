#include <pthread.h>
#include <stdio.h> 
#include <string.h>
#include <wiringPi.h>

#include "attitude.h"
#include "matrix.h"
#include "models.h"
#include "../laser-driver/laser-driver.h"
#include "pointer_util.h"
#include "../stepper-driver/stepper-driver.h"

// initialize the two pi steppers:
Stepper stepper_az;
Stepper stepper_el;

pthread_t step_thread1;
pthread_t step_thread2;

// Setup pointer
void setup_pointer() {

    wiringPiSetup();
    stepper_az = init_stepper(2048, 21,22,23,24);
    set_speed(&stepper_az, 14);
    stepper_el = init_stepper(2048, 5,6,10,11);
    set_speed(&stepper_el, 14);
    setup_laser();
}

// Point pointer at an RA DEC based direction and turn on laser
void point_direction(Matrix eci_2_body_dcm, RADec dir) {

    // Determine unit vector in ECI
    Matrix unitvec_eci = radec_2_unitvec(dir);

    // Convert unit vector to body frame
    Matrix unitvec_body = matrix_multiply(eci_2_body_dcm, unitvec_eci);

    // Convert body frame unit to angles
    RADec radec = unitvec_2_radec(unitvec_body);

	pthread_create(&step_thread1, NULL, step_motor_to_angle(&stepper_az, radec.RA), NULL);
	pthread_create(&step_thread2, NULL, step_motor_to_angle(&stepper_el, radec.dec), NULL);

	// Close out the threads as they shut down
	pthread_join(step_thread1, NULL);
	pthread_join(step_thread2, NULL);

    // Turn on laser pointer
    turn_on_laser();
}

// Point pointer at an RA DEC based direction and turn on laser
void point_home() {

    home(&stepper_az);
    home(&stepper_el);

    // Turn on laser pointer
    turn_off_laser();
}

// Setup pointer
void shutdown_pointer() {

    free_stepper(&stepper_az);
    free_stepper(&stepper_el);
    turn_off_laser();
}