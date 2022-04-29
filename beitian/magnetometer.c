
#include <assert.h>
#include <errno.h>
#include <math.h>
#include <pthread.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <wiringPi.h>
#include <wiringSerial.h>
#include <wiringPiI2C.h>
#include <zmq.h>
#include "zhelpers.h"

int magnetometer_init(int fd){

	int err = 0;

	//write to Configuration Register A
	err = wiringPiI2CWriteReg8(fd, REGISTER_A, 0x70);

	if (err == -1){
		printf(strerror(errno));
		return err;
	}

	//Write to Configuration Register B for gain
	err = wiringPiI2CWriteReg8(fd, REGISTER_B, 0xa0);

	if (err == -1){
		return err;
	}

	//Write to mode Register for selecting mode
	err = wiringPiI2CWriteReg8(fd, REGISTER_MODE, 0);

	if (err == -1){
		return err;
	}

	return 0;
}

double read_raw_data(int fd, int addr){
    
	//Read raw 16-bit value
	int high = wiringPiI2CReadReg8(fd, addr);
	int low = wiringPiI2CReadReg8(fd, addr+1);

	//concatenate higher and lower value
	double value = ((high << 8) | low);

	//to get signed value from module
	if(value > 32768){
		value = value - 65536;
	}

	return value;
}

void *create_magnetometer_listener(void* zmq_ctx)
{
	double x = 0;
	double z;
	double y;
	double heading = 0;
	double declination;
	double heading_angle;
	char s[50];
	terminate_magnetometer = false;

	/* Initialize socket */
	//printf("Initilizing magnet data publish socket.\n");
  	push_magnet = zmq_socket (zmq_ctx, ZMQ_PUB); 
	/* Bind it to a in-process transport with the address 'magnet' */
	int rc = zmq_bind (push_magnet, "inproc://magnet");

	// Initialize wiring pi l2c
	int fd = wiringPiI2CSetup(DEVICE);

	if (fd < 0){
		printf("Failed to setup I2C with wiringPi.\n");
		printf(strerror(errno));
	}

    //Find Heading by using HMC5883L interface with Raspberry Pi using Python
	//http://www.electronicwings.com

	//from time import sleep  #import sleep
	// Is this just a python library manifestation - bus = smbus.SMBus(1) 	// or bus = smbus.SMBus(0) for older version boards

	magnetometer_init(fd);     // initialize HMC5883L magnetometer 

	while(!terminate_magnetometer){
    
        //Read Accelerometer raw value
        x = read_raw_data(fd, X_AXIS_H);
        z = read_raw_data(fd, Z_AXIS_H);
        y = read_raw_data(fd, Y_AXIS_H);

        heading = atan2(y, x) + declination;
        
        //Due to declination check for >360 degree
        if(heading > 2*M_PI){
			heading = heading - 2*M_PI;
		}

        //check for sign
        if(heading < 0){
			heading = heading + 2*M_PI;
		}

        //convert into angle
        heading_angle = heading * 180/M_PI;

        sleep(1);
		void *data = malloc(6);
		memcpy (data, s, 6);
		zmq_msg_t msg;
		int rc = zmq_msg_init_size (&msg, 6);
		/* Fill in message content with 'AAAAAA' */
		memset (zmq_msg_data (&msg), 'A', 6);
		/* Send the message to the socket */
		rc = zmq_msg_send (&msg, push_magnet, 0);

		//rc = zmq_msg_init_data (&msg, data, 6, NULL, NULL);
		//rc = zmq_msg_send (&msg, push_magnet, 0);
	}
}