
#include <stdio.h>
#include <stdlib.h>

#include <wiringPi.h>

#include "../util/time_util.h"

#include "stepper-driver.h"

/*
 *   constructor for four-pin version
 *   Sets which wires should control the motor.
 */
Stepper init_stepper(int number_of_steps, int motor_pin_1, int motor_pin_2,
                                      int motor_pin_3, int motor_pin_4)
{
    Stepper stepper;
    stepper.step_number = 0;    // which step the motor is on
    stepper.direction = 0;      // motor direction
    stepper.last_step_time = 0; // timestamp in us of the last step taken
    stepper.number_of_steps = number_of_steps; // total number of steps for this motor

    // Arduino pins for the motor control connection:
    stepper.motor_pin_1 = motor_pin_1;
    stepper.motor_pin_2 = motor_pin_2;
    stepper.motor_pin_3 = motor_pin_3;
    stepper.motor_pin_4 = motor_pin_4;
    

    // setup the pins on the microcontroller:
    pinMode(stepper.motor_pin_1, OUTPUT);
    pinMode(stepper.motor_pin_2, OUTPUT);
    pinMode(stepper.motor_pin_3, OUTPUT);
    pinMode(stepper.motor_pin_4, OUTPUT);
    digitalWrite(stepper.motor_pin_1, LOW);
    digitalWrite(stepper.motor_pin_3, LOW);
    digitalWrite(stepper.motor_pin_4, LOW);
    digitalWrite(stepper.motor_pin_2, LOW);

    // pin_count is used by the stepMotor() method:
    stepper.pin_count = 4;

    return stepper;
}

/*
 * Sets the speed in revs per minute
 */
void set_speed(Stepper *stepper, long whatSpeed)
{
  stepper->step_delay = 60L * 1000L * 1000L / stepper->number_of_steps / whatSpeed;
}

/*
 * Moves the motor steps_to_move steps.  If the number is negative,
 * the motor moves in the reverse direction.
 */
void step(Stepper *stepper, int steps_to_move)
{
  int steps_left = abs(steps_to_move);  // how many steps to take

  // determine direction based on whether steps_to_mode is + or -:
  if (steps_to_move > 0) { stepper->direction = 1; }
  if (steps_to_move < 0
  ) { stepper->direction = 0; }

  // decrement the number of steps, moving one step each time:
  while (steps_left > 0)
  {
    unsigned long now = micros();
    // move only if the appropriate delay has passed:
    if (now - stepper->last_step_time >= stepper->step_delay)
    {
      // get the timeStamp of when you stepped:
      stepper->last_step_time = now;
      // increment or decrement the step number,
      // depending on direction:
      if (stepper->direction == 1)
      {
        stepper->step_number++;
        if (stepper->step_number == stepper->number_of_steps) {
          stepper->step_number = 0;
        }
      }
      else
      {
        if (stepper->step_number == 0) {
          stepper->step_number = stepper->number_of_steps;
        }
        stepper->step_number--;
      }
      // decrement the steps left:
      steps_left--;
      // step the motor to step number 0, 1, ..., {3 or 10}
      if (stepper->pin_count == 5)
        step_motor(stepper, stepper->step_number % 10);
      else
        step_motor(stepper, stepper->step_number % 4);
    }
  }
}

/*
 * Moves the motor forward or backwards.
 */
void step_motor(Stepper *stepper, int thisStep)
{
  switch (thisStep) {
    case 0:  // 1010
      digitalWrite(stepper->motor_pin_1, HIGH);
      digitalWrite(stepper->motor_pin_2, HIGH);
      digitalWrite(stepper->motor_pin_3, LOW);
      digitalWrite(stepper->motor_pin_4, LOW);
    break;
    case 1:  // 0110
      digitalWrite(stepper->motor_pin_1, LOW);
      digitalWrite(stepper->motor_pin_2, HIGH);
      digitalWrite(stepper->motor_pin_3, HIGH);
      digitalWrite(stepper->motor_pin_4, LOW);
    break;
    case 2:  //0101
      digitalWrite(stepper->motor_pin_1, LOW);
      digitalWrite(stepper->motor_pin_2, LOW);
      digitalWrite(stepper->motor_pin_3, HIGH);
      digitalWrite(stepper->motor_pin_4, HIGH);
    break;
    case 3:  //1001
      digitalWrite(stepper->motor_pin_1, HIGH);
      digitalWrite(stepper->motor_pin_2, LOW);
      digitalWrite(stepper->motor_pin_3, LOW);
      digitalWrite(stepper->motor_pin_4, HIGH);
    break;
  }
}