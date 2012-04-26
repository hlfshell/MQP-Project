#include <errno.h>                                                              
#include <sys/types.h>                                                          
#include <unistd.h>                                                             
#include <fcntl.h>                                                              
#include <sys/stat.h>                                                           
#include <string.h>                                                             
#include <stdlib.h>                                                             
#include <stdio.h>                                                              
               
#define GPIODIRECTION ((void *) 0xE8000028)
#define GPIODATA ((void *) 0xE8000018)
#define DIOWRITE ((void *) 0xE8000008)
                                                                 
int pidManager(){                                                               
        char PID[10];                                                           
        int pidNum;                                                             
        ssize_t writeValue;                                                     
                                                                                
        //Open a file, exclusively check if it exists (or fail),                
        //write to it, make it accessible to all.                               
        int fd = open("/var/run/studentCode.pid", O_RDWR|O_CREAT|O_EXCL, S_IROTH|S_IWOTH|S_IWGRP|S_IRGRP);                                                      
        if(fd < 0){                                                             
                return -1;                                                      
        }                                                                       
        int myPID = getpid();                                                   
        pidNum = sprintf(PID, "%d", myPID);                                     
        writeValue = write(fd, PID, strlen(PID));                               
        if(writeValue <= 0){                                                    
                return -1;                                                      
        }                                                                       
        close(fd);                                                              
        return 1;                                                               
}       

void resetDIOs(){
	poke16(GPIODIRECTION, 0x00);
	poke16(GPIODATA, 0x00);
	poke16(DIOWRITE, 0xFFFF);
}

void resetMotors(){
	setMotor(1, 64);
	setMotor(2, 64);
	setMotor(3, 64);
	setMotor(4, 64);
}

void fullReset(){
	resetDIOs();
	resetMotors();
	resetServo();
	usleep(125000);
	resetServo();
}

void initializeRobot(){
	int pidResult;

	pidResult = pidManager();

	fullReset();
}

