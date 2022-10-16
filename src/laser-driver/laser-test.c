/*
 Stepper Motor Control - one revolution
 This program drives a unipolar or bipolar stepper motor.
 The motor is attached to digital pins 8 - 11 of the Arduino.
 The motor should revolve one revolution in one direction, then
 one revolution in the other direction.
 Created 11 Mar. 2007
 Modified 30 Nov. 2009
 by Tom Igoe
 */

#include <stdio.h>

#include <wiringPi.h>

#include "laser-driver.h"

void setup() {
    setup_laser();
}

void loop() {
  
  fprintf(stdout,"turning on laser\n");
  turn_on_laser();
  delay(20000);
  fprintf(stdout,"turning off laser\n");
  turn_off_laser();
  fprintf(stdout,"done\n");
}


int main (int argc, char **argv)
{
  setup();
  loop();
}

