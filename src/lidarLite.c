/*
LidarLite - Wiring based interface to LidarLite for RaspberryPi and ODROID C1
Copyright (c) 2015, Answer 17
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:
    * Redistributions of source code must retain the above copyright
      notice, this list of conditions and the following disclaimer.
    * Redistributions in binary form must reproduce the above copyright
      notice, this list of conditions and the following disclaimer in the
      documentation and/or other materials provided with the distribution.
    * Neither the name of the organization nor the
      names of its contributors may be used to endorse or promote products
      derived from this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL ANSWER 17 BE LIABLE FOR ANY
DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

    #include "lidarLite.h"
    
    bool _dbg;
   
    // Initialize wiring I2C interface to LidarLite
    int lidar_init(bool dbg) {
            int fd;
            _dbg = dbg;
            if (_dbg) printf("LidarLite V0.1");
            fd = wiringPiI2CSetup(LIDAR_LITE_ADRS);
            if (fd != -1) 
                lidar_status(fd);  // Dummy request to wake up device
            return(fd);
            }        

    // Read distance in cm from LidarLite
    int lidar_read(int fd) {
           int hiVal, loVal, i=0;
           
           // send "measure" command
           hiVal = wiringPiI2CWriteReg8(fd, MEASURE_REG, MEASURE_VAL);
           if (_dbg) printf("write res=%d\n", hiVal);
           delay(20);

           // read first byte 
           hiVal = _read_byte(fd, DISTANCE_REG_HI) ;             
           if (_dbg) printf ("Hi=%d", hiVal);
       
           // Read second byte and append with first 
           loVal = _read_byte(fd, DISTANCE_REG_LO) ;        
           if (_dbg) printf(" Lo=%d\n", loVal);
           
           return ( (hiVal << 8) + loVal);
    }
    
   unsigned char lidar_version(int fd) {
            return( (unsigned char) wiringPiI2CReadReg8(fd, VERSION_REG) );
            }
         
    unsigned char lidar_status(int fd) {
            return( (unsigned char) wiringPiI2CReadReg8(fd, STATUS_REG) );
            }
            
    void lidar_status_print(unsigned char status) {
printf("STATUS BYTE: 0x%x ", (unsigned int) status);
if (status == 0) printf("clear\n");
if (status & STAT_BUSY) printf("busy \n");              
if (status & STAT_REF_OVER) printf("reference overflow \n");            
if (status & STAT_SIG_OVER) printf("signal overflow \n");            
if (status & STAT_PIN) printf("mode select pin \n");                 
if (status & STAT_SECOND_PEAK) printf("second peak \n");         
if (status & STAT_TIME) printf("active between pairs \n");                
if (status & STAT_INVALID) printf("no signal \n");             
if (status & STAT_EYE) printf(" eye safety \n");                 
    }    
    
    // Read a byte from I2C register.  Repeat if not ready
    int _read_byte(int fd, int reg) {
    int i, val;
         while (true) {
            val = wiringPiI2CReadReg8(fd, reg);
            if (val != ERROR_READ) 
                return(val);
            else {
                delay (20) ;		// ms
                if (i++ > 50) {
                   // Timeout
                   return (ERROR_READ);
                   }
              }
         }   
    }