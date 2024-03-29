
#ifndef __REGISTRY_H_INCLUDED__
#define __REGISTRY_H_INCLUDED__

// Addresses
#define COMMAND_WS_PORT 5560
#define TELEMETRY_WS_PORT 5559
#define TELEMETRY_PUBLISH_URL "tcp://localhost:5558"
#define TELEMETRY_SUBSCRIBE_URL "tcp://*:5558"
#define GPS_PUBLISH_URL "tcp://*:5555"
#define GPS_SUBSCRIBE_URL "tcp://localhost:5555" // Port number for GPS reciever data
#define COMMAND_PUBLISH_URL "tcp://*:5561"
#define COMMAND_SUBSCRIBE_URL "tcp://localhost:5561"
#define MAGNET_PUBLISH_URL "tcp://*:5556"
#define MAGNET_SUBSCRIBE_URL "tcp://localhost:5556" // Port number for GPS reciever data
#define ATTITUDE_PUBLISH_URL "tcp://*:5557"
#define ATTITUDE_SUBSCRIBE_URL "tcp://localhost:5557" // Port number for GPS reciever data

// Topic configuration
#define GPS_TOPIC "GPS "    // GPS Data Topic
#define MAGNET_TOPIC "MAG "    // Magnetometer Data Topic
#define ATTITUDE_TOPIC "ATT "    // Attitude Data Topic
#define EMPTY_TOPIC ""  // Subscribes to all messages

#define EMPTY_TOPIC_LENGTH 0 // The length of the empty topic string
#define TOPIC_LENGTH 5    // GPS Data Topic

// PUBSUB Configuration
enum endpoint_type {pub, sub};

#endif