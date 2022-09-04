#include <assert.h>
#include <errno.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#include <wiringPi.h>
#include <wiringSerial.h>
#include <wiringPiI2C.h>

#define DEVICE 0x1e   // HMC5883L magnetometer device address

//some MPU6050 Registers and their Address
#define REGISTER_A 0             //Address of Configuration register A
#define REGISTER_B 0x01          //Address of configuration register B
#define REGISTER_MODE 0x02           //Address of mode register

#define REGISTER_A_MODE 0x71 // 8-average, 15 hz default, positive self test measurement
#define REGISTER_A_OFF_MODE 0x71 // 8-average, 15 hz default, normal measurement
#define REGISTER_B_MODE 0xA0 // Gain = 5
#define REGISTER_MODE_MODE 0x00 // Continuous measurement mode
#define X_AXIS_H 0x03              //Address of X-axis MSB data register
#define Z_AXIS_H 0x05              //Address of Z-axis MSB data register
#define Y_AXIS_H 0x07              //Address of Y-axis MSB data register
#define DEC_OFFSET -0.00669          //define declination angle of location where measurement going to be done
#define PI 3.14159265359    //define pi value


int magnetometer_init(int fd){

    int err = 0;

    //write to Configuration Register A
    err = wiringPiI2CWriteReg8(fd, REGISTER_A, REGISTER_A_MODE);

    if (err == -1){
        printf(strerror(errno));
        return err;
    }

    //Write to Configuration Register B for gain
    err = wiringPiI2CWriteReg8(fd, REGISTER_B, REGISTER_B_MODE);

    if (err == -1){
        return err;
    }

    //Write to mode Register for selecting mode
    err = wiringPiI2CWriteReg8(fd, REGISTER_MODE, REGISTER_MODE_MODE);

    if (err == -1){
        return err;
    }

    return 0;
}

double read_raw_data(int fd, int addr){
    
    //Read raw 16-bit value
    int high = wiringPiI2CReadReg8(fd, addr);
    int low = wiringPiI2CReadReg8(fd, addr+1);

    //concatenate higher and lower value
    double value = ((high << 8) | low);

    //to get signed value from module
    if(value > 32768){
        value = value - 65536;
    }

    return value;
}


int main (int argc, char **argv)
{
    // Initialize wiring pi l2c
    int fd = wiringPiI2CSetup(DEVICE);

    if (fd < 0){
        printf("Failed to setup I2C with wiringPi.\n");
        printf(strerror(errno));
    }

    float xMax, yMax, xMin, yMin, zMax, zMin = 0.0;

    printf("Configuring magnetometer.");
    magnetometer_init(fd);     // initialize HMC5883L magnetometer 

    sleep(1);

    clock_t initial_time = clock();
    double elapsed = 0;
    double total = 30;
    int i = -1;
    while(elapsed < total) {
        i++;

        printf("Elapsed: %lf\n",elapsed);
    
        //Read Accelerometer raw value
        float x = read_raw_data(fd, X_AXIS_H);
        float z = read_raw_data(fd, Z_AXIS_H);
        float y = read_raw_data(fd, Y_AXIS_H);
        printf("(%lf,%lf,%lf)",x,y,z);

        if (i == 0) {
            xMin = x;
            yMin = y;
            zMin = z;
        }

        xMax = fmax(xMax, x);
        yMax = fmax(yMax, y);
        zMax = fmax(zMax, z);
        xMin = fmin(xMin, x);
        yMin = fmin(yMin, y);
        zMin = fmin(zMin, z);
        printf("(%lf,%lf,%lf)\n",xMax,yMax,zMax);

        elapsed = (double) (clock() - initial_time)/CLOCKS_PER_SEC*1000*6;

        sleep(1);
    }

    //write to Configuration Register A
    int err = wiringPiI2CWriteReg8(fd, REGISTER_A, REGISTER_A_OFF_MODE);

    if (err == -1){
        printf(strerror(errno));
        return err;
    }

    printf("X Max:%f\n",xMax);
    printf("Y Max:%f\n",yMax);
    printf("Z Max:%f\n",zMax);
    printf("X Min:%f\n",xMin);
    printf("Y Min:%f\n",yMin);
    printf("Z Min:%f\n",zMin);
}
