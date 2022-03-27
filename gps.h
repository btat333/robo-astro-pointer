#ifndef GPS_H
#define GPS_H

/* Creates gps listener which publishes gps telemetry events upon reciept of data */
void *create_gps_listener ();
void *create_magnetometer_listener ();

/* Release any dangling objects upon closure of app */
void *end_gps_loop ();
void *end_magnetometer_loop ();

#endif