#ifndef __TELEMETRYUTIL_H_INCLUDED__
#define __TELEMETRYUTIL_H_INCLUDED__

#define MAGNET_PACKET "magnet"
#define GPS_PACKET "gps"
#define X_MNEMONIC "x"
#define Y_MNEMONIC "y"
#define Z_MNEMONIC "z"
#define ALT_MNEMONIC "alt"
#define LAT_MNEMONIC "lat"
#define LONG_MNEMONIC "long"
#define SATNUM_MNEMONIC "satnum"
#define HDOP_MNEMONIC "hdop"

void* create_tlm_string(char* packet, char* mnemonic,  char* value, char* out_string);
void* create_tlm_double(char* packet, char* mnemonic,  double value, char* out_string);
void* publish_tlm_string(void* push, char* packet, char* mnemonic,  char* value);
void* publish_tlm_double(void* push, char* packet, char* mnemonic,  double value);

#endif