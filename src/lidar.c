#include "../include/lidarLite.h"
#include <time.h>

void main(int argc,char *argv[])
{
    int fd, res;

    fd = lidar_init(false);
    
    if (fd == -1) {
        printf("Couldn't initialize the lidar.\n");
//        exit();
    } 

    while (1==1) {

        res = lidar_read(fd);
        printf("%3.0d cm \n", res);
        delay(20);
    }
}
