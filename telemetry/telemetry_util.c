#include <zmq.h>

#include "telemetry_util.h"
#include "../util/zhelpers.h"

void* create_tlm_string(char* packet, char* mnemonic,  char* value, char* out_string) 
{
    int f = sprintf( out_string, "%s.%s:%s", packet, mnemonic, value);
    assert(f >= 0);
}

void* create_tlm_double(char* packet, char* mnemonic,  double value, char* out_string) 
{
    printf("%f\n",value);
    int f = sprintf( out_string, "%s.%s:%lf", packet, mnemonic, value);
    assert(f >= 0);
}

void* publish_tlm_string(void* push, char* packet, char* mnemonic,  char* value) 
{
    char out[200] = "";
    create_tlm_string(packet, mnemonic,  value, out);
    s_send(push,out);
}

void* publish_tlm_double(void* push, char* packet, char* mnemonic,  double value) 
{
    char out[200] = "";
    create_tlm_double(packet, mnemonic,  value, out);
    s_send(push,out);
}