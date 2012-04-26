/**
setDirection.c

This .c file contains setDirection, which will set whether a particular pin
is an output or an input.

Pins that belong to the DIO Header ignore this, as they have a different
write-to register. GPIO pins, however, can not be properly written to
unless you properly declare a direction.
*/

#include "DIO.h"

/**
void setDirection(int pin, int direction)

@param pin - 1-15 - what pin we are changing the direction of.
@param direction - 0 or 1 - 0 is an input, 1 is an output
*/
void setDirection(int pin, int direction){
	int bit;

	if(pin < 6) return;
	
	if(pin < 1 || pin > 15) return;

	bit = getBit(pin);
}
