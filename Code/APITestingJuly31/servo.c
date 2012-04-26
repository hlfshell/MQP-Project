/**
* servo.c
* Written by Keith Chester
* This code is designed to accept a call to control a servo and then take
* care of neccessary overhead.
*/
#include "serialHandler.h"

#define STARTBIT 0xFF
#define HALF 0
#define FULL 1

volatile int STOP=FALSE;

/**
*void setServo(int servo, int pos)
*@param servo - int, what servo channel are we talking about?
*@param pos - int, the position or the speed of the servo being requested
*@param hf - int, whether or not the servo is in half or full duplex. 0 = half, 1 is full.
*@return void
*
*Sets a motor as half duplex or full duplex. All default as 
*/
void setServo(int servo, int pos, int hf){
	int fd, tty, c, res, i, error;

	int startBit;

	//If the servo is in full duplex, set it to such.
	if(hf == FULL) servo += 8;
	
	startBit = STARTBIT;

	struct sigaction saio;
	struct termios newtio, oldtio;
	struct termios oldkey;
	

	//open the device(com port) to be non-blocking (read will return immediately)
	fd = open("/dev/ttts4", O_RDWR | O_NOCTTY | O_NONBLOCK);
	if (fd < 0)
	{
		perror("dev/ttts4");
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

	write(fd, &startBit, 1);
      	write(fd, &servo, 1);
      	write(fd, &pos, 1);

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
