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

#include <stepper-driver.h>
#include <wiringPi.h>

const int stepsPerRevolution = 200;  // change this to fit the number of steps per revolution
// for your motor

// initialize the Stepper library on pins 8 through 11:
Stepper my_stepper;

void setup() {

    my_stepper = init_stepper(stepsPerRevolution, 8, 9, 10, 11);
    // set the speed at 60 rpm:
    set_speed(&my_stepper, 60);
    // initialize the serial port:
    Serial.begin(9600);
}

void loop() {
  // step one revolution in one direction:
  fprintf(stdout,"clockwise");
  step(&my_stepper, stepsPerRevolution);
  delay(500);

  // step one revolution in the other direction:
  fprintf(stdout,"counter clockwise");
  step(&my_stepper, -stepsPerRevolution);
  delay(500);
}