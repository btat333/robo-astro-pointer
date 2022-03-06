# robo-astro-pointer

# Next steps:
# How to wait for all threads to close gracefully so that I can still kill the program? Make the program recieve the ctrl-c kill command
# Address the warning messages about the errors returning 1 to a void method.  How to make the threads handle errors and shut down gracefully?
# Create a struct to hold the object instead of publishing a string
# Define behavior of application with respect to updates of each type of data.  How frequent is compass data?

# To Run:

# gcc -o robo gps.c pointer.c main.c -l wiringPi -l czmq -l pthread


# Requirements
# Magnification of 25mm plosl with XT6 = 48x
# AFoV of XT6 = 52
# True Field of View ~ 1 deg
# The robo pointer shall provide an estimated star position no worse than 1 deg, 3 sigma 


# Verification
# Accelerometer error - atan(1/1000) ~ 0.1 deg
# Magnetometer error - 1 to 2 deg
# -- Current induced magnetic error - B = mu_0*i/(2*pi*r), i is current of r-pi, r is distance to magnetometer
# GPS -> Topocentric Reference frame error
# Earth Orientation Parameter Error
# Stepper Motor Max Error -




