#ifndef __STEPPER_H_INCLUDED__
#define __STEPPER_H_INCLUDED__

typedef struct t_stepper {
    int direction;            // Direction of rotation
    unsigned long step_delay; // delay between steps, in us, based on speed
    int number_of_steps;      // total number of steps this motor can take
    int pin_count;            // how many pins are in use.
    int step_number;          // which step the motor is on
    int total_step_number;          // which total step the motor is on since initialization

    // motor pin numbers:
    int motor_pin_1;
    int motor_pin_2;
    int motor_pin_3;
    int motor_pin_4;

    unsigned long last_step_time; // timestamp in us of when the last step was taken
} Stepper;

/*
 *   constructor for four-pin version
 *   Sets which wires should control the motor.
 */
Stepper init_stepper(int number_of_steps, int motor_pin_1, int motor_pin_2,
                                      int motor_pin_3, int motor_pin_4);

/*
 * Sets the speed in revs per minute
 */
void set_speed(Stepper *stepper, long whatSpeed);

/*
 * Moves the motor steps_to_move steps.  If the number is negative,
 * the motor moves in the reverse direction.
 */
void step(Stepper *stepper, int steps_to_move);

/*
 * Moves the motor forward or backwards.
 */
void step_motor(Stepper *stepper, int thisStep);

/*
 * Steps motor to the specified angle from the '0' step position in radians
 */
void step_motor_to_angle(Stepper *stepper, double angle);

/*
 * Steps motor back to zero steps.
 */
void home(Stepper *stepper);

/*
 * Steps motor back to zero steps and turns all pins to low.
 */
void free_stepper(Stepper *stepper);

#endif  //  __STEPPER_H_INCLUDED__