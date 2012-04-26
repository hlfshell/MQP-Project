#include <termios.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/signal.h>
#include <sys/types.h>

#define BAUDRATE B9600
#define MODEMDEVICE "/dev/ttts4"
#define _POSIX_SOURCE 1         //POSIX compliant source
#define FALSE 0
#define TRUE 1

#define STARTBIT 0xFF

volatile int STOP=FALSE;

void signal_handler_IO (int status);    //definition of signal handler
int wait_flag=TRUE;                     //TRUE while no signal received
long Baud_Rate = 9600;         // default Baud Rate (110 through 38400)
long BAUD;                      // derived baud rate from command line
long DATABITS;
long STOPBITS;
long PARITYON;
long PARITY;
int Data_Bits = 8;              // Number of data bits
int Stop_Bits = 1;              // Number of stop bits
int Parity = 0;                 // Parity as follows:
                  // 00 = NONE, 01 = Odd, 02 = Even, 03 = Mark, 04 = Space
int Format = 1;
FILE *input;
FILE *output;
int status;

main(int argc, char *argv[])
{
	int fd, tty, c, res, i, error, servo, speed, startBit;

	struct sigaction saio;
	struct termios newtio, oldtio;
	struct termios oldkey;

	servo = atoi(argv[1]);
	speed = atoi(argv[2]);
	

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

	startBit = STARTBIT;
	

      	write(fd, &startBit, 1);
      	write(fd, &servo, 1);
      	write(fd, &speed, 1);
	

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

