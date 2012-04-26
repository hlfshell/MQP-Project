
#include "SERIAL/serialHandler.h"

int main(int argc, char *argv[]){
	int input1, input2;

	input1 = atoi(argv[1]);
	input2 = atoi(argv[2]);


	printf("Attempting motor %d at speed %d.\n", input1, input2);
	

	setMotor(input1, input2);

	return 0;
}
