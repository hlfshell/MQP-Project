/**
*
*/
#include "peekpoke.h"
#include "DIO.h"

int main(){
	initializeRobot();
	setDO(1, 0);
	usleep(500000);
	setDO(1, 1); 
	return 0;
}
