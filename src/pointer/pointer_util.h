
#ifndef __POINTER_UTIL_H_INCLUDED__
#define __POINTER_UTIL_H_INCLUDED__

#include "../util/matrix.h"
#include "../util/models.h"

// Point pointer at an RA DEC based direction and turn on laser
void* point_direction(Matrix latest_attitude, Direction dir);

// Point at a planet using planetary ephemerides
void* point_planet(Matrix latest_attitude, char* planet);

// Point at a planet using planetary ephemerides
void* point_satellite(Matrix latest_attitude, int norad_id);

// Reset the stepper motors to their zero position and turn off laser
void* point_home();

// Command the stepper motors to a specific position
void* command_motors();

// Turn on the laser pointer
void* turn_on_laser();

// Turn off the laser pointer
void* turn_off_laser();

#endif  //  __POINTER_UTIL_H_INCLUDED__