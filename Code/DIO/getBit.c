/**
getBit.c
Bit Switch Statements

This .c file returns the bit value of the pin requested.
*/

/**
int getBit(int pin)
Accepts a pin # from digital I/O board and returns its corresponding bit.

@param pin - A pin from the digital I/O board
@return int - the bit to call from this pin's register.
*/
int getBit(int pin){
	switch(pin){
		case 1: return 0;
		case 2: return 2;
		case 3: return 4;
		case 4: return 6;
		case 5: return 8;
		case 6: return 1;
		case 7: return 2;
		case 8: return 3;
		case 9: return 4;
		case 10: return 5;
		case 11: return 6;
		case 12: return 7;
		case 13: return 8;
		case 14: return 9;
		case 15: return 10;
	}
}
