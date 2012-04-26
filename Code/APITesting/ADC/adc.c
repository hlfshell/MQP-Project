#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <assert.h> 
#include <string.h>

#include "ADC.h"


volatile unsigned int *control, *status, *data, *led;

int getChannel(int chan){
	switch(chan){
		case 1: return 1;
		case 2: return 2;
		case 3: return 8;
		case 4: return 4;
		case 5: return 32;
	}
}

void static inline twi_select(unsigned char addr, unsigned char dir) {
	unsigned int timeout = 0;

	*control = START|TWSIEN;        // Send start signal

	usleep(1);

	while((*control & IFLG) == 0)
		if(timeout++ > 10000) {
			//Timeout occurs
			printf("timeout has occured\n");
			*control = STOP|TWSIEN; // Send stop signal
			exit(-1);
		}
	if((*status != MT_START) && (*status != MT_REP_START)) {
		//Can't send the start signal!
		*control = STOP|TWSIEN; // Send stop signal;
		exit(-1);
	}
	
	//If you've reached here the start signal was successfully sent.
	*data = addr | dir;     // Send SLA+W/R
	usleep(1);

	*control = (*control & ~IFLG) | ACK;
	usleep(1);

	while((*control & IFLG) == 0) ;

	if((*status != MT_SLA_ACK) && (*status != MR_SLA_ACK)) {
		//Slave did not ACK select signal
		*control = STOP|TWSIEN; // Send stop signal
		exit(-1);
		
	}
	//Slave selected successfully
}

void static inline twi_write(unsigned char dat) {
	//Write data
	*data = dat;
	usleep(100);

	*control = (*control & ~IFLG) | ACK;
	usleep(100);
	while((*control & IFLG) == 0x0);        // Wait for an I2C event


	if((*status != ST_DATA_ACK) && (*status != MT_DATA_ACK )) {
		//Slave did not acknowledge (ACK) data!
		exit(1);
	}

	//Slave acknolwedged the data
}

double adc(int chan){
	volatile unsigned int *fpga, *sram;
	unsigned int i;
	int devmem, channel;
	unsigned int *twi_regs, *regs;
	unsigned long int almost;
	double final;
	

	devmem = open("/dev/mem", O_RDWR|O_SYNC);
	assert(devmem != -1);

	twi_regs = (unsigned int *)mmap(0, getpagesize(), PROT_READ|PROT_WRITE, MAP_SHARED, devmem, 0xF1011000);

	regs = (unsigned int *)mmap(0, getpagesize(), PROT_READ|PROT_WRITE, MAP_SHARED, devmem,  0xe8000000);

	led = &regs[GLED];
        control = &twi_regs[CONTROL];
        data = &twi_regs[DATA];
        status = &twi_regs[STATUS];

	fpga = (unsigned int *)mmap(0, 0x1004, PROT_READ|PROT_WRITE, MAP_SHARED, devmem, 0xE8100000);
       	sram = &fpga[SRAM];

	twi_select(AVR_ADDR, WRITE);

	channel = getChannel(chan);

	twi_write(channel | 0x40);

	*control = STOP|TWSIEN; // Send stop signal

//EWD: Implement this in a more elegant way. That is write out all FF's then print values as they are available.
//2KSPS => a new sample is available every 500uS
//	printf("0x%x\n", sram[1023]);
//	printf("int = %d\n", sram[1023]);
	
	almost = sram[1023];
	almost = almost & 0x00000FFF;

	final = almost * 0.000814413;

	return final;	

}



