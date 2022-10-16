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

const int stepsPerRevolution = 2048;  // change this to fit the number of steps per revolution
// for your motor

// initialize the Stepper library on pins 8 through 11:
Stepper my_stepper;
Stepper my_stepper2;

void setup() {

    my_stepper = init_stepper(stepsPerRevolution, 21,22,23,24);
    // set the speed at 60 rpm:
    set_speed(&my_stepper, 14);
    // initialize the serial port:
    //Serial.begin(9600);
    my_stepper2 = init_stepper(stepsPerRevolution, 5,6,10,11);
    set_speed(&my_stepper2, 14);
}

void loop() {
  // step one revolution in one direction:
  fprintf(stdout,"%d\n", my_stepper.total_step_number);
  fprintf(stdout,"clockwise\n");
  fflush(stdout);
  //step(&my_stepper, 1024);
  step(&my_stepper2, 1024);
  fprintf(stdout,"%d\n", my_stepper.total_step_number);
  delay(1000);
  //step(&my_stepper, 1024);
  step(&my_stepper2, 1024);
  fprintf(stdout,"%d\n", my_stepper.total_step_number);
  delay(1000);

  // step one revolution in the other direction:
  fprintf(stdout,"counter clockwise\n");
  free_stepper(&my_stepper);
  free_stepper(&my_stepper2);
  fprintf(stdout,"%d\n", my_stepper.total_step_number);
  delay(1000);
}


int main (int argc, char **argv)
{
  setup();
  loop();
}

