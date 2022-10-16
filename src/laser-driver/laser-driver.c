#include <wiringPi.h>

#include "laser-driver.h"

const int laser_pin = 3;

/*
* Sets up laser
*/
void setup_laser() {
    wiringPiSetup();
    pinMode(laser_pin,OUTPUT);
}

/*
 * Turns on the laser
 */
void turn_on_laser() {
    digitalWrite(laser_pin, HIGH);
};

/*
 * Turns off the laser
 */
void turn_off_laser() {
    digitalWrite(laser_pin, LOW);
};