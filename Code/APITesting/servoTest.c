
#include "SERIAL/serialHandler.h"

int main(int argc, char *argv[]){
	int input1, input2, input3;

	input1 = atoi(argv[1]);
	input2 = atoi(argv[2]);
	input3 = atoi(argv[3]);

	system("./DIOTest 4 0 0");

	printf("Attempting servo %d at position %d.\n", input1, input2);	
	
	setServo(input1, input2, input3);

	return 0;
}
