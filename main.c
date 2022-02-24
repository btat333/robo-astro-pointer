

#include <stdio.h>
#include <string.h>
#include <errno.h>

#include <pthread.h>
#include <wiringPi.h>
#include <wiringSerial.h>

#include "gps.h"
#include "pointer.h"

int main ()
{
	pthread_t gps_reciever_listener;
	pthread_t magnetometer_listener;
	pthread_t pointer_gps_listener;

	pthread_create(&gps_reciever_listener, NULL, create_gps_listener, NULL);
	pthread_create(&magnetometer_listener, NULL, create_magnetometer_listener, NULL);
	pthread_create(&pointer_gps_listener, NULL, listen_gps_updates, NULL);

	while(1){}
	return 0;
}