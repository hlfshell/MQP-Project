#include "peekpoke.h"
#include "DIO.h"

#define GPIODDIRECTION ((void *) 0xE800002C)
#define GPIODDATA ((void *) 0xE800001C)

/**                                                                                
*resetServo()                                                                      
*This is an emergency reset of the servos.                                         
*This will not stop all servos permenately and should not                          
*be used for a full servo stop. It is for when a failed signal                     
*is sent to the servo controller and it locks up.                                  
*/                                                                                 
void resetServo(){                                                                 
        int addr;                                                                  
        int bit;                                                                   
        unsigned int bitmask;                                                      
        unsigned int writevalue;                                                   
        int temp, read;                                                            
        int mask;                                                                  
                                                                                   
        bit = 15; // Which bit in the register goes with this pin?                 
                                            
	read = peek16(GPIODDIRECTION);
	//  Create a mask with all 1, except the desired bit = 0;
	mask = 1;
	mask = mask << bit;
        mask = ~mask;

	// Force desired bit to 0; leave the rest unchanged.
	writevalue = read & mask;

	// Set the desired bit = value
	temp = 1;
	temp = temp << bit; 
	writevalue = temp | writevalue;

	//Now write to the appropiate place.

	poke16(GPIODDIRECTION, writevalue);
                                       
        read = peek16(GPIODDATA);                                                  
                                                                                   
        //  Create a mask with all 1, except the desired bit = 0;                  
        mask = 1;                                                                  
        mask = mask << bit;                                                        
        mask = ~mask;                                                              
                                                                                   
        // Force desired bit to 0; leave the rest unchanged.                       
        writevalue = read & mask;                   
                                                                                   
        // Set the desired bit = value                                             
        temp = 0;                                                                  
        temp = temp << bit;                                                        
        writevalue = temp | writevalue;                                            
                                                                                   
        //Now write to the appropiate place.                                       
                                                                                   
        poke16(GPIODDATA, writevalue);                                             
                                                                                   
        //  Create a mask with all 1, except the desired bit = 0;                  
        mask = 1;                                                                  
        mask = mask << bit;                                                        
        mask = ~mask;                                                              
                                                                                   
        // Force desired bit to 0; leave the rest unchanged.                       
        writevalue = read & mask;                                                  
                                                                                   
        // Set the desired bit = value                                             
        temp = 1;                                                                  
        temp = temp << bit;                                                        
        writevalue = temp | writevalue;                                            
                                                                                   
        //Now write to the appropiate place.                                       
                                                                                   
        poke16(GPIODDATA, writevalue);                                             
}                         
