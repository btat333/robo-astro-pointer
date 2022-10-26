
#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>

#include <pthread.h>
#include <unistd.h>
#include <wiringPi.h>
#include <zmq.h>

#include "../util/zhelpers.h"
#include "../util/models.h"
#include "../util/registry.h"
#include "pointer_util.h"

#include "pointer.h"

const int conflate = 1;

#define RADEC_STRING "RADEC"
#define PLANET_STRING "PLANET"
#define SAT_STRING "SAT"
#define CAL_STRING "CAL"
#define HOME_STRING "HOME"

void* zmq_ctx;
pthread_mutex_t attitude_mutex;
pthread_mutex_t command_mutex;
pthread_mutex_t ra_dec_mutex;

Matrix eci_2_body_dcm;
Command current_command;
RADec dir;

int has_attitude = 0;
int has_command = 0;

void * listen_acs_updates ()
{

    /* Initialize socket */
    printf("Initilizing acs subscription socket.\n");
    void* pull = zmq_socket(zmq_ctx, ZMQ_SUB);
    int rc = zmq_connect (pull, ATTITUDE_SUBSCRIBE_URL);
	assert(rc == 0);
    rc = zmq_setsockopt (pull, ZMQ_SUBSCRIBE, EMPTY_TOPIC, EMPTY_TOPIC_LENGTH);
	assert(rc == 0);

    while(1){
	  
        /* Block until a message is available to be received from socket */
        char *string = s_recv(pull);
        pthread_mutex_lock(&attitude_mutex);
        eci_2_body_dcm = parse_attitude_data(string);

        has_attitude = 1;

        pthread_mutex_unlock(&attitude_mutex);
    }

}

void * listen_command_updates ()
{

    /* Initialize socket */
    printf("Initilizing command subscription socket.\n");
    void* pull = zmq_socket(zmq_ctx, ZMQ_SUB);
    int rc = zmq_connect (pull, COMMAND_SUBSCRIBE_URL);
	assert(rc == 0);
    rc = zmq_setsockopt (pull, ZMQ_SUBSCRIBE, EMPTY_TOPIC, EMPTY_TOPIC_LENGTH);
	assert(rc == 0);

    while(1){
	  
        /* Block until a message is available to be received from socket */
        char *string = s_recv(pull);

        pthread_mutex_lock(&command_mutex);
        Command comm = parse_command(string);
        has_command = 1;
        fprintf(stdout, "Has command.");

        if (comm.command_type == RADEC_STRING) {
            pthread_mutex_lock(&ra_dec_mutex);
            dir = parse_direction(comm.data);
            pthread_mutex_unlock(&ra_dec_mutex);

        } else if (comm.command_type == PLANET_STRING) {

        } else if (comm.command_type == SAT_STRING ) {

        }

        pthread_mutex_unlock(&command_mutex);
        
    }

}

void * update_pointing ()
{

    
    /* Initialize socket */
	printf("Initilizing pointer service.\n");

    int local_has_attitude = 0;
    int local_has_command = 0;

    if (wiringPiSetup() == -1)							/* initializes wiringPi setup */
    {
        fprintf (stderr, "Unable to start wiringPi: %s\n", strerror (errno)) ;
        exit(1);
    }

    pinMode(0, OUTPUT);

    while(1)
    {

        // Wait for magnetometer mutex lock
        pthread_mutex_lock(&command_mutex);
        local_has_command = has_command;
        pthread_mutex_unlock(&command_mutex);

        if (local_has_command) {

            // Wait for magnetometer mutex lock
            pthread_mutex_lock(&command_mutex);
            Command latest_command = current_command;
            pthread_mutex_unlock(&command_mutex);

            if (latest_command.command_type == RADEC_STRING || 
                latest_command.command_type == PLANET_STRING || 
                latest_command.command_type == SAT_STRING ) {

                // Has attitude arrived yet?
                pthread_mutex_lock(&attitude_mutex);
                local_has_attitude = has_attitude;
                pthread_mutex_unlock(&attitude_mutex);

                if (local_has_attitude) {

                    pthread_mutex_lock(&attitude_mutex);
                    Matrix latest_attitude = eci_2_body_dcm;
                    pthread_mutex_unlock(&attitude_mutex);

                    if (latest_command.command_type == RADEC_STRING) {

                        pthread_mutex_lock(&ra_dec_mutex);
                        RADec local_dir = parse_direction(latest_command.data);
                        pthread_mutex_unlock(&ra_dec_mutex);

                        point_direction(latest_attitude, local_dir);

                        sleep(1);

                    } else if (latest_command.command_type == PLANET_STRING) {
                        
                    } else if (latest_command.command_type == SAT_STRING) {

                    }

                } else {
                    sleep(1);
                }
            
            } else if (latest_command.command_type == CAL_STRING) {

            } else if (latest_command.command_type == HOME_STRING ) {
                point_home();
            }
        }
    }
}

int main(int argc, char **argv)
{
    
	fprintf (stdout, "Initializing zeromq context.\n");

    pthread_t attitude_reciever_listener;
    pthread_t command_listener;
    pthread_t pointer_thread;

	zmq_ctx = zmq_ctx_new();
    pthread_mutex_init(&attitude_mutex,NULL);
    pthread_mutex_init(&command_mutex,NULL);
    pthread_mutex_init(&ra_dec_mutex,NULL);
	int error_num;
	fprintf (stdout, "Initilizing attitude listener.\n");

	if (error_num = pthread_create(&attitude_reciever_listener, NULL, listen_acs_updates, NULL))
	{
		fprintf (stderr, "Unable to start attitude listener: %s\n", strerror (error_num)) ;
		return 1 ;
	}
	fprintf (stdout, "Initilizing command listener.\n");
	if (error_num = pthread_create(&command_listener, NULL, listen_command_updates, NULL))
	{
		fprintf (stderr, "Unable to start command listener: %s\n", strerror (error_num)) ;
		return 1 ;
	}
	if (error_num = pthread_create(&pointer_thread, NULL, update_pointing, NULL))
	{
		fprintf (stderr, "Unable to start pointer: %s\n", strerror (error_num)) ;
		return 1 ;
	}

	// Close out the threads as they shut down
	fprintf(stdout, "Awaiting closure of threads.\n");
	pthread_join(attitude_reciever_listener, NULL);
	pthread_join(command_listener, NULL);
	pthread_join(pointer_thread, NULL);
    zmq_ctx_destroy(zmq_ctx);
    pthread_mutex_destroy(&attitude_mutex);
    pthread_mutex_destroy(&command_mutex);
	return 0;
}