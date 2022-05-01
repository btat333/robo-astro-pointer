
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
#include <zmq.h>
#include "registry.h"
#include "zhelpers.h"

#include "gps.h"


void *create_gps_listener (void* zmq_ctx)
{
  int serial_port; 
  char dat,buff[100],GGA_code[3];	
  unsigned char IsitGGAstring=0;
  unsigned char GGA_index=0;
  unsigned char is_GGA_received_completely = 0;

  /* Initialize socket */
  printf("Initilizing gps data publish socket.\n");
  void *push_gps = zmq_socket (zmq_ctx, ZMQ_PUB); 
  int rc = zmq_bind (push_gps, GPS_PUBLISH_URL);
  if (rc != 0) {
	fprintf (stderr, "Unable to bind gps publisher: %s\n", strerror (errno)) ;
	exit(1);
  }
  
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

  printf("Waiting for gps data from reciever.\n");
  while(1){
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
			char out[200] = "";
			strcat(out, buff);
			s_send(push_gps,out);
			is_GGA_received_completely = 0;
		}
	}
}

int main (int argc, char **argv)
{

	fprintf (stdout, "Initializing zeromq context.\n");

	void* zmq_ctx = zmq_ctx_new();
	int error_num;
	fprintf (stdout, "Initilizing gps.\n");

	create_gps_listener(zmq_ctx);

    zmq_ctx_destroy(zmq_ctx);

	return 0;
}

