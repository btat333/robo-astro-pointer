
#include <assert.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include <math.h>
#include <pthread.h>
#include <zmq.h>
#include <ws.h>

#include "../util/zhelpers.h"
#include "../util/models.h"
#include "../util/registry.h"
#include "../util/network.h"
#include "commands.h"

const int conflate = 1;

void* zmq_ctx;
void *push_cmd;

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

void onmessage(ws_cli_conn_t *client,
	const unsigned char *msg, uint64_t size, int type)
{
	char *cli;
	cli = ws_getaddress(client);
    printf("Cmd received: %s",msg);
    fflush(stdout);
    s_send(push_cmd,msg);
}

int main (int argc, char **argv)
{

	zmq_ctx = zmq_ctx_new();

    printf("Initilizing command publish socket.\n");
    push_cmd = zmq_socket (zmq_ctx, ZMQ_PUB); 
    int rc = zmq_bind (push_cmd, COMMAND_PUBLISH_URL);
    if (rc != 0) {
        fprintf (stderr, "Unable to bind command publisher: %s\n", strerror (errno)) ;
        exit(1);
    }

    struct ws_events evs;
	evs.onopen    = &onopen;
	evs.onclose   = &onclose;
	evs.onmessage = &onmessage;
	ws_socket(&evs, COMMAND_WS_PORT, 0, 1000); /* Never returns. */

    zmq_ctx_destroy(zmq_ctx);
	return 0;
}
