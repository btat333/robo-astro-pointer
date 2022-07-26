
#include <assert.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include <math.h>
#include <pthread.h>
#include <ws.h>
#include <zmq.h>

#include "../util/zhelpers.h"
#include "../util/models.h"
#include "../util/registry.h"
#include "../util/network.h"
#include "telemetry.h"
#include "telemetry_util.h"

#define FRAME_TYPE 1
#define THREAD_LOOP 1
#define TIMEOUT_DURATION 1000
#define MESSAGE_TARGET NULL

const int conflate = 1;

void* zmq_ctx;

struct GPSPointSolution gps;
struct MagnetometerMeasurement magnetometer_data;

void * listen_magnet_updates ()
{

    /* Initialize socket */
    printf("Initilizing magnetometer subscription socket.\n");
    int conflate = 1;
    int bind = 0;
    void* pull = create_subscription(zmq_ctx, MAGNET_SUBSCRIBE_URL, conflate, bind); 
    void* push = create_publisher(zmq_ctx, TELEMETRY_PUBLISH_URL, bind);

    while(1){
	  
        /* Block until a message is available to be received from socket */
        char *string = s_recv(pull);
        magnetometer_data = parse_magnetomer_data(string);
		printf("%s\n",string);
		fflush(stdout);

		publish_tlm_double(push, MAGNET_PACKET, X_MNEMONIC, magnetometer_data.x);
		publish_tlm_double(push, MAGNET_PACKET, Y_MNEMONIC, magnetometer_data.y);
		publish_tlm_double(push, MAGNET_PACKET, Z_MNEMONIC, magnetometer_data.z);
    }

}

void * listen_gps_updates ()
{

    /* Initialize socket */
    printf("Initilizing gps subscription socket.\n");
    int conflate = 1;
    int bind = 0;
    void* pull = create_subscription(zmq_ctx, GPS_SUBSCRIBE_URL, conflate, bind); 
    void* push = create_publisher(zmq_ctx, TELEMETRY_PUBLISH_URL, bind);

    while(1){
	  
        /* Block until a message is available to be received from socket */
        char *string = s_recv(pull);
        gps = parse_gps(string);

        printf("%lf",gps.altitude);
		publish_tlm_double(push, GPS_PACKET, ALT_MNEMONIC, gps.altitude);
		publish_tlm_double(push, GPS_PACKET, LAT_MNEMONIC, gps.latitude);
		publish_tlm_double(push, GPS_PACKET, LONG_MNEMONIC, gps.longitude);
		publish_tlm_double(push, GPS_PACKET, SATNUM_MNEMONIC, gps.sat_num);
		publish_tlm_double(push, GPS_PACKET, HDOP_MNEMONIC, gps.hdop);
    }

}

// Event handlers for web socket
void onopen(ws_cli_conn_t *client)
{
	char *cli;
	cli = ws_getaddress(client);
	printf("Connection opened, addr: %s\n", cli);
}

void onclose(ws_cli_conn_t *client)
{
	char *cli;
	cli = ws_getaddress(client);
	printf("Connection closed, addr: %s\n", cli);
}

void * broker_republish ()
{

    struct ws_events evs;
	evs.onopen    = &onopen;
	evs.onclose   = &onclose;
	ws_socket(&evs, TELEMETRY_WS_PORT, THREAD_LOOP, TIMEOUT_DURATION);

    /* Initialize socket */
    printf("Initilizing broker socket.\n");
    int conflate = 0;
    int bind = 1;
    void* pull = create_subscription(zmq_ctx, TELEMETRY_SUBSCRIBE_URL, conflate, bind); 

    while(1){
	  
        /* Block until a message is available to be received from socket */
        char *string_received = s_recv(pull);
	    size_t frame_size = strlen(string_received);
        printf("size:%d\n",frame_size);
        ws_sendframe(MESSAGE_TARGET, string_received, frame_size, FRAME_TYPE);
    }

}

int main (int argc, char **argv)
{

	fprintf (stdout, "Initializing zeromq context.\n");

    pthread_t gps_reciever_listener;
    pthread_t magnetometer_listener;
    pthread_t broker;

	zmq_ctx = zmq_ctx_new();
	int error_num;
	fprintf (stdout, "Initilizing gps listener.\n");

	if (error_num = pthread_create(&gps_reciever_listener, NULL, listen_gps_updates, NULL))
	{
		fprintf (stderr, "Unable to start gps listener: %s\n", strerror (error_num)) ;
		return 1 ;
	}
	fprintf (stdout, "Initilizing magnetometer listener.\n");
	if (error_num = pthread_create(&magnetometer_listener, NULL, listen_magnet_updates, NULL))
	{
		fprintf (stderr, "Unable to start magnetometer listener: %s\n", strerror (error_num)) ;
		return 1 ;
	}
    if (error_num = pthread_create(&broker, NULL, broker_republish, NULL))
	{
		fprintf (stderr, "Unable to start broker: %s\n", strerror (error_num)) ;
		return 1 ;
	}

	// Close out the threads as they shut down
	fprintf(stdout, "Awaiting closure of threads.\n");
	pthread_join(gps_reciever_listener, NULL);
	pthread_join(magnetometer_listener, NULL);
	pthread_join(broker, NULL);
    zmq_ctx_destroy(zmq_ctx);
	return 0;
}
