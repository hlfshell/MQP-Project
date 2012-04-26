/**
DIO.h
Digital Input and Output Header File

Contains all register address and neccessary header files
for digital input and output management.
*/

#ifndef DIO_H
#define DIO_H

#include "peekpoke.h"

//DIO Header Registers
#define DIOHEADERREAD ((void *) 0xE8000004)
#define DIOHEADERWRITE ((void *) 0xE8000008)

//GPIO Header Registers
#define GPIODATA ((void *) 0xE8000018)
#define GPIODIRECTION ((void *) 0xE8000028)

//Function Prototypes for DOhandler.c
void setDO(int pin, int value);
void setDirection(int pin);

//Function Prototypes for DIhandler.c
int getDI(int pin);

//Function Prototypes for getBit.c
int getBit(int pin);

//Function Prototypes for ledControl.c
void setLED(int onoff);

#endif
