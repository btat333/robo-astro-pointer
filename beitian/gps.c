
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
//#include "zhelpers.h"

#include "gps.h"

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

// File scope variables
bool terminate_gps = false;
bool terminate_magnetometer = false;
void *push_gps;
void *push_magnet;

int main (int argc, char **argv)
{

	fprintf (stdout, "Initializing zeromq context.\n");

	void* zmq_ctx = zmq_ctx_new();
	int error_num;
	fprintf (stdout, "Initilizing gps.\n");

	create_gps_listener(zmq_ctx);

	return 0;
}

void *create_gps_listener (void* zmq_ctx)
{
  int serial_port; 
  char dat,buff[100],GGA_code[3];	
  unsigned char IsitGGAstring=0;
  unsigned char GGA_index=0;
  unsigned char is_GGA_received_completely = 0;
  terminate_gps = false;

  /* Initialize socket */
  //printf("Initilizing gps data publish socket.\n");
  push_gps = zmq_socket (zmq_ctx, ZMQ_PUB); 
  int rc = zmq_bind (push_gps, "tcp://*:5555");
  if (rc != 0) {
	fprintf (stderr, "Unable to bind gps publisher: %s\n", strerror (errno)) ;
	exit(1);
  }
  assert(rc == 0);
  
  if ((serial_port = serialOpen ("/dev/ttyS0", 9600)) < 0)		/* open serial port */
  {
    fprintf (stderr, "Unable to open serial device: %s\n", strerror (errno)) ;
    exit(1);
  }

  if (wiringPiSetup () == -1)							/* initializes wiringPi setup */
  {
    fprintf (stderr, "Unable to start wiringPi: %s\n", strerror (errno)) ;
    exit(1);
  }

  //printf("Waiting for gps data from reciever.\n");
  while(!terminate_gps){
	  
		if(serialDataAvail (serial_port) )		/* check for any data available on serial port */
		  { 
			dat = serialGetchar(serial_port);		/* receive character serially */		

			if(dat == '$'){
				IsitGGAstring = 0;
				GGA_index = 0;
			}
			else if(IsitGGAstring ==1){
				buff[GGA_index++] = dat;
				if(dat=='\r')
					//fprintf(stdout,"loop");
					is_GGA_received_completely = 1;
				}
			else if(GGA_code[0]=='G' && GGA_code[1]=='G' && GGA_code[2]=='A'){
				IsitGGAstring = 1;
				GGA_code[0]= 0; 
				GGA_code[0]= 0;
				GGA_code[0]= 0;		
				}
			else{
				GGA_code[0] = GGA_code[1];
				GGA_code[1] = GGA_code[2];
				GGA_code[2] = dat;
			}
		  }
		if(is_GGA_received_completely==1){
			/* Create a new message, allocating 6 bytes for message content */
			// void *data = malloc(6);
			// memcpy (data, buff, 6);
			zmq_msg_t msg;
			int rc = zmq_msg_init_size (&msg, 6);
			assert(rc == 0);
			/* Fill in message content with 'AAAAAA' */
			memset (zmq_msg_data (&msg), 'A', 6);
			/* Send the message to the socket */

			rc = zmq_msg_send (&msg, push_gps, 0);
			if(rc < 0) {
    			fprintf (stderr, "Error code %d\n", errno);
    			fprintf (stderr, "Unable to publish gps message %s\n", strerror (errno));
				exit(1);
			}
			// rc = zmq_msg_init_data (&msg, data, 6, NULL, NULL);
			// rc = zmq_msg_send (&msg, push_gps, 0);
			is_GGA_received_completely = 0;
		}
	}
}
