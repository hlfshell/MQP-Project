/**
* motor.c
* Written by Keith Chester
* This code will allow users to use simple functions to control
* motor outputs.
*/
#include "serialHandler.h"

#define BAUDBIT 0xAA
#define CHECKSUM 0x7F
#define STARTADDRESS 128



/**
*void setMotor(int motor, int speed)
*@param motor - int, what motor are we controlling?
*@param speed - int, 0-127. What speed are we writing to the motor?
*/
void setMotor(int motor, int speed){
	int fd, tty, c, res, i, error, address, checksum, command, baud;

	if(motor % 2 == 1) command = 7;
	else command = 6;
	
	if(motor < 3) address = STARTADDRESS;
	else address = STARTADDRESS + 1;

	baud = BAUDBIT;

	checksum = (address + command + speed) & CHECKSUM;

	struct sigaction saio;
	struct termios newtio, oldtio;
	struct termios oldkey;
	

	//open the device(com port) to be non-blocking (read will return immediately)
	fd = open("/dev/ttts7", O_RDWR | O_NOCTTY | O_NONBLOCK);
	if (fd < 0)
	{
		perror("dev/ttts7X");
		exit(-1);
	}

	//install the serial handler before making the device asynchronous
	saio.sa_handler = signal_handler_IO;
	sigemptyset(&saio.sa_mask);   //saio.sa_mask = 0;
	saio.sa_flags = 0;
	saio.sa_restorer = NULL;
	sigaction(SIGIO,&saio,NULL);

	// allow the process to receive SIGIO
	fcntl(fd, F_SETOWN, getpid());
	// Make the file descriptor asynchronous (the manual page says only
	// O_APPEND and O_NONBLOCK, will work with F_SETFL...)
	fcntl(fd, F_SETFL, FASYNC);

	tcgetattr(fd,&oldtio); // save current port settings 
	// set new port settings for canonical input processing 
	newtio.c_cflag = BAUD | CRTSCTS | DATABITS | STOPBITS | PARITYON | PARITY | CLOCAL | CREAD;
	newtio.c_iflag = IGNPAR;
	newtio.c_oflag = 0;
	newtio.c_lflag = 0;       //ICANON;
	newtio.c_cc[VMIN]=1;
	newtio.c_cc[VTIME]=0;
	tcflush(fd, TCIFLUSH);
      	tcsetattr(fd,TCSANOW,&newtio);

	printf("Baud = %d, address = %d, command = %d, speed = %d, checksum = %d\n", baud, address, command, speed, checksum);

	write(fd, &baud, 1);
	write(fd, &address, 1);
	write(fd, &command, 1);
	write(fd, &speed, 1);
	write(fd, &checksum, 1);

      	// restore old port settings
      	tcsetattr(fd,TCSANOW,&oldtio);
      	tcsetattr(tty,TCSANOW,&oldkey);
      	close(tty);
      	close(fd);        //close the com port
  
}

void signal_handler_IO (int status)
{
//    printf("received SIGIO signal.\n");
   wait_flag = FALSE;
}

