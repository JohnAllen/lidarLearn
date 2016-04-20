#include <fstream>
#include <iostream>
#include <sys/stat.h>
#include <wiringPi.h>
#include <cstdlib>
#include <cstdio>
#include "../include/lidarLite.h"
#include <unistd.h>

using namespace std;

const int PAN_MAX = 2000;
const int PAN_MIN = 1700;

const int TILT_MAX = 1125;
const int TILT_MIN = 900;

int READS_PER_LINE = 30;

int scanObject(void)
{
    res = lidar_read(fd);
    printf("%3.0d cm \n", res);
    usleep(20000);
    
    int i,j;

    for(i = 0; < 
    printf("beginning object scan\n");
    pwmWrite(1, 75); 
    pwmWrite(2, 75); 
    return 0;
}

int main(int argc, char ** argv)
{

    if (wiringPiSetup () == -1) //using wPi pin numbering
        exit (1) ;
    cout << "wiring pi setup" << endl;

    int fd, res;
    fd = lidar_init(false);

    if (fd == -1) {
        printf("Couldn't initialize the lidar.\n");
    }


    pinMode(1, PWM_OUTPUT);
    pinMode(2, PWM_OUTPUT);
    
    pwmSetMode(0); 
    pwmSetClock(384); //clock at 50kHz (20us tick)
    pwmSetRange(1000); //range at 1000 ticks (20ms)

    // set both servos to starting position
    pwmWrite(1, 70); 
    pwmWrite(2, 70); 
        
    while (1==1) 
    {
        if (getchar() == 32)
        {
            //run scan...
            scanObject();
        }        
    }
    return 0 ;
}
