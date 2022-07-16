# COMMAND SERVICE/BROKER
Reads commands from external and distributes internally to each service

## List of Commands
### Robot Arm
* Point
* Laser Status
* Home
### GPS
* Calibrate
### Executive Service?
* Reboot?

## List of Endpoints
* Command Reciept - Bound subscription recieves commands from external
* Command Distribute - Allows internal services to connect and recieve telemetry