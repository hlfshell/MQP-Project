/**
DOhandler.c
Digital output Handler

This .c file handles all writing to digital I/Os.
*/

#include "DIO.h"



/**
void set2Output(int pin, int value)
Sets the direction of a bit on the GPIO Header to output 
if we are writing to it.

@param pin - accepts a pin # of the IO board, valid from 6 to 15
*/
void set2Output(int pin){
	int bit;
	unsigned int bitmask;
	unsigned int writevalue;
	int temp, read;
        int mask;
	
	bit = getBit(pin);

	read = peek16(GPIODIRECTION);

	//  Create a mask with all 1, except the desired bit = 0;
	mask = 1;
	mask = mask << bit;
        mask = ~mask;

	// Force desired bit to 0; leave the rest unchanged.
	writevalue = read & mask;

	// Set the desired bit = 1
	temp = 1;
	temp = temp << bit; 
	writevalue = temp | writevalue;

	poke16(GPIODIRECTION, writevalue);
}


/**
void setDO(int pin, int value)
Writes a 0 or 1 to requested pin.

@param pin - accepts a pin # of the IO board, valid from 1 to 15
@param value - accepts a value, either 0 or 1.
*/
void setDO(int pin, int value){
	int bit;
	unsigned int bitmask;
	unsigned int writevalue;
	int temp, read;
        int mask;

	if(pin < 1 || pin > 15) return;
	if(value < 0 || value > 1) return;
	// if(getDI(pin) == value) return;

	bit = getBit(pin); // Which bit in the register goes with this pin?

	if(pin >= 6) set2Output(pin); // Set direction to output

	if(pin <= 5) read = peek16(DIOHEADERREAD);
	else read = peek16(GPIODATA);

	//  Create a mask with all 1, except the desired bit = 0;
	mask = 1;
	mask = mask << bit;
        mask = ~mask;

	// Force desired bit to 0; leave the rest unchanged.
	writevalue = read & mask;

	// Set the desired bit = value
	temp = value;
	temp = temp << bit; 
	writevalue = temp | writevalue;

	//Now write to the appropiate place.

	if(pin <= 5) poke16(DIOHEADERWRITE, writevalue);
	else poke16(GPIODATA, writevalue);

}

