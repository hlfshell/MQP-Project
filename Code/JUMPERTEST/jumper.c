/**
*
*/

#define JUMPERBIT 3
#define JUMPERREGISTER 0xE8000004

int main(){
	int bit;
	unsigned int bitmask;
	unsigned int readvalue;

	bit = JUMPERBIT;
	bitmask = 1 << bit;
	//Set appropiate bit in bitmask - shift over bit bits

	readvalue = peek16(JUMPERREGISTER);

	readvalue = readvalue & bitmask;
	//Isolate the bit we want
	readvalue = readvalue >> bit;
	//shift to right to force return value to 0 or 1

	system("rm -f /var/run/studentCode.pid");

	if(readvalue == 1)
		system("/RUNCODE/runMe");


	return 0;
}
