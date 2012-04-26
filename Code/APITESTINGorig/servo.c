/**
* servo.c
* Written by Keith Chester
* This code is designed to accept a call to control a servo and then take
* care of neccessary overhead.
*/

#define STARTBIT 0xFF
#define HALF 0
#define FULL 1


/**
*void setServo(int servo, int pos)
*@param servo - int, what servo channel are we talking about?
*@param pos - int, the position or the speed of the servo being requested
*@param hf - int, whether or not the servo is in half or full duplex. 0 = half, 1 is full.
*@return void
*
*Sets a motor as half duplex or full duplex. All default as 
*/
void setServo(int servo, int pos, int hf){
	int startBit;

	//If the servo is in full duplex, set it to such.
	if(hf == FULL) servo += 8;
	
	startBit = STARTBIT;

	serialWrite(4, startBit);
	serialWrite(4, servo);
	serialWrite(4, pos);

}
