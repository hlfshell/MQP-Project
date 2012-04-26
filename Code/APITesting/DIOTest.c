/**
DIOTest

Test program to test DIO.h, DOhandler.c, and DIhandler.c
*/

#include "DIO/DIO.h"


/**
int main(int readorwrite, int pin, int value)

@param readorwrite - 0 or 1 - 0 = read. 1 = write
@param pin - 1-15 - Which pin of the peripheral board is this?
@param value - 0 or 1 - What to write to the pin. Ignored if this is a read.
*/
int main(int argc, char *argv[]) {
	int readorwrite;
	int pin;
	int value;

	if (argc < 4) {
	   printf("Usage: DIOTest rw pin value\n");
           return 1;
	}

	readorwrite = atoi(argv[1]);
	pin = atoi(argv[2]);
	value = atoi(argv[3]);

	if(readorwrite == 0){
		value = getDI(pin);
		printf("Pin %d is currently set to %d.\n", pin, value);
	} else if(readorwrite == 1){
		setDO(pin, value);
		printf("Pin %d has been set to %d.\n", pin, value);
	} else if (readorwrite == 3){
		setLED(value);
		printf("Active or Status LED flipped.\n");
	} else if (readorwrite == 4){
		resetServo();
	}

	return 0;
}
