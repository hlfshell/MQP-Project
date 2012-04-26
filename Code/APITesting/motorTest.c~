
#include "serialHandler.h"

int main(int argc, char *argv[]){
	int input1, input2, input3, input4;

	input1 = atoi(argv[1]);
	input2 = atoi(argv[2]);
	input3 = atoi(argv[3]);
	input4 = atoi(argv[4]);


	if(input4 == 1){
		printf("Attempting motor %d at speed %d.\n", input1, input2);

		setMotor(input1, input2);
	}
	else if(input4 == 0){
		printf("Attempting servo %d at position %d.\n", input1, input2);
		
		setServo(input1, input2, input3);
	}

	return 0;
}
