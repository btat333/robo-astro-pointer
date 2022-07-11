
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
#include "models.h"
#include "registry.h"
#include "zhelpers.h"

#define DEVICE 0x1e   // HMC5883L magnetometer device address

//some MPU6050 Registers and their Address
#define REGISTER_A 0             //Address of Configuration register A
#define REGISTER_B 0x01          //Address of configuration register B
#define REGISTER_MODE 0x02           //Address of mode register

#define X_AXIS_H 0x03              //Address of X-axis MSB data register
#define Z_AXIS_H 0x05              //Address of Z-axis MSB data register
#define Y_AXIS_H 0x07              //Address of Y-axis MSB data register
#define DEC_OFFSET -0.00669          //define declination angle of location where measurement going to be done
#define PI 3.14159265359    //define pi value

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
	struct MagnetometerMeasurement mm;
	char s[50];

	/* Initialize socket */
	printf("Initilizing magnet data publish socket.\n");
  	void *push_magnet = zmq_socket (zmq_ctx, ZMQ_PUB); 
	/* Bind it to a in-process transport with the address 'magnet' */
	int rc = zmq_bind (push_magnet, MAGNET_PUBLISH_URL);
	assert(rc == 0);

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

	while(1){
    
        //Read Accelerometer raw value
        mm.x = read_raw_data(fd, X_AXIS_H);
        mm.z = read_raw_data(fd, Z_AXIS_H);
        mm.y = read_raw_data(fd, Y_AXIS_H);

		char out[200] = "";
		serialize_magnetometer_data(mm, out);
		s_send(push_magnet,out);
		printf("%s\n",out);
		fflush(stdout);
		sleep(1);
	}
}

int main (int argc, char **argv)
{

	fprintf (stdout, "Initializing zeromq context.\n");

	void* zmq_ctx = zmq_ctx_new();
	int error_num;
	fprintf (stdout, "Initilizing magnetometer.\n");

	create_magnetometer_listener(zmq_ctx);

    zmq_ctx_destroy(zmq_ctx);

	return 0;
}