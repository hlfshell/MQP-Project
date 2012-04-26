#include "ADC/ADC.h"

int main(int argc, char *argv[]){
	int pin;
	double value;
	pin = atoi(argv[1]);
	//Grab the argument that is the pin number we are reading 

	value = adc(pin);
	printf("The value at pin %d is currently %10.10f\n", pin, value);	

	return 0;
}
