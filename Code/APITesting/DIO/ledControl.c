/**
*
*/
#include "DIO.h"

#define LEDACTIVE 1
#define LEDSTATUS 2
#define GPIODDATA ((void *) 0xE800001C)
#define GPIODDIRECTION ((void *) 0xE800002C)

void setLED(int onoff){
	int bit;
        unsigned int bitmask;
        unsigned int writevalue;
        int temp, read;
        int mask;
	int LED;
	
	if(onoff > 2) LED = LEDSTATUS;
	else LED = LEDACTIVE;

	if(onoff == 3) onoff = 0;
	else if(onoff == 4) onoff = 1;

        if(LED == LEDACTIVE) bit = 2;
	else bit = 1;

        read = peek16(GPIODDIRECTION);

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

        poke16(GPIODDIRECTION, writevalue);

	//Direction is set, now write the data.

        read = peek16(GPIODDATA);

	 //  Create a mask with all 1, except the desired bit = 0;
        mask = 1;
        mask = mask << bit;
        mask = ~mask;

        // Force desired bit to 0; leave the rest unchanged.
        writevalue = read & mask;

        // Set the desired bit = onoff
        temp = onoff;
        temp = temp << bit;
        writevalue = temp | writevalue;

        poke16(GPIODDATA, writevalue);


}
