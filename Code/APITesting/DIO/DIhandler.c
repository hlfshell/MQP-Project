/**
DIhandler.c
Digital Input Handler

This .c file handles all reading of digital I/Os.
*/

#include "DIO.h"

/**
void set2Input(int pin, int value)
Sets the direction of a bit on the GPIO Header to input 
if we are reading from it.

@param pin - accepts a pin # of the IO board, valid from 6 to 15
*/
void set2Input(int pin){
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

	// Set the desired bit = 0
	temp = 0;
	temp = temp << bit; 
	writevalue = temp | writevalue;

	poke16(GPIODIRECTION, writevalue);
}



/**
int getDI(int pin)
Reads a digital input from requested pin and returns either low or high
(0 or 1)

@param pin - accepts a pin # of the IO board, valid from 1 to 15
@return int - 0 or 1, high or low
*/
int getDI(int pin){
	int bit;
	unsigned int bitmask;
	unsigned int readvalue;

	if(pin < 1 || pin > 15) return 0; //error check

	//We must make sure that input pins are set high each time we
	//read them for DIO HEADER pins only.
        // This is because they are open-drain.
	if(pin <= 5) setDO(pin, 1);

	//Likewise, for GPIO pins we must set the pin as an input.
	else if(pin >= 6) set2Input(pin);

	bit = getBit(pin);
	bitmask = 1 << bit;
	//Set appropiate bit in bitmask - shift over bit bits

	if(pin <= 5) readvalue = peek16(DIOHEADERREAD);
	else if(pin >= 6) readvalue = peek16(GPIODATA);

	readvalue = readvalue & bitmask;
	//Isolate the bit we want
	readvalue = readvalue >> bit;
	//shift to right to force return value to 0 or 1

	return readvalue;
}
