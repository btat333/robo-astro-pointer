# robo-astro-pointer

## Next steps:
- How to wait for all threads to close gracefully so that I can still kill the program? Make the program recieve the ctrl-c kill command
- Address the warning messages about the errors returning 1 to a void method.  How to make the threads handle errors and shut down gracefully?
- Create a struct to hold the object instead of publishing a string
- Define behavior of application with respect to updates of each type of data.  How frequent is compass data?
- Add 'self test' for calibration - temperature specific compensation
 

## To Run:

```
gcc -o gps gps.c -l zmq -l wiringPi

gcc -o acs acs.c ../util/models.c -l zmq -l pthread

gcc -o pointer pointer.c ../util/models.c -l zmq

gcc -o robo ./star_tracker/star_tracker.c ./star_tracker/camera.c gps.c pointer.c main.c -l wiringPi -lczmq -l pthread -l vips `pkg-config --cflags --libs glib-2.0` -lm
```

## Requirements
- Magnification of 25mm plosl with XT6 = 48x
- AFoV of XT6 = 52
- True Field of View ~ 1 deg
- The robo pointer shall provide an estimated star position no worse than 1 deg, 3 sigma 


## Verification
- Accelerometer error - atan(1/1000) ~ 0.1 deg
- Magnetometer error - 1 to 2 deg
- Current induced magnetic error - B = mu_0*i/(2*pi*r), i is current of r-pi, r is distance to magnetometer
- GPS -> Topocentric Reference frame error (geodetic vs. geocentric information - 0.2 degrees)
- ITRF Error ->  Precession, Nutation ( < 1 degree)
- UT1 error -> need to convert from UTC to UT1 using UT1-UTC file (1/86400 * 360 degrees error = 0.004 deg)
- Stepper Motor Max Error - ?

## FSW reference
- https://www.jhuapl.edu/Content/techdigest/pdf/V20-N04/20-04-Malcom.pdf




