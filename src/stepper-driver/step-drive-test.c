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

#include "stepper-driver.h"

const int stepsPerRevolution = 4096;  // change this to fit the number of steps per revolution
// for your motor

// initialize the Stepper library on pins 8 through 11:
Stepper my_stepper;

void setup() {

    wiringPiSetup();
    my_stepper = init_stepper(stepsPerRevolution, 21,22,23,24);
    // set the speed at 60 rpm:
    set_speed(&my_stepper, 8);
    // initialize the serial port:
    //Serial.begin(9600);
}

void loop() {
  // step one revolution in one direction:
  fprintf(stdout,"clockwise\n");
  fflush(stdout);
  step(&my_stepper, 4096);
  delay(1000);

  // step one revolution in the other direction:
  fprintf(stdout,"counter clockwise\n");
  step(&my_stepper, -4096);
  delay(1000);
}


int main (int argc, char **argv)
{
  setup();
  while(1) {
    //loop();
  }
}

