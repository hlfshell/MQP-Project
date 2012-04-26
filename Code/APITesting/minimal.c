#include <stdio.h>
#include <fcntl.h>
#include <sys/mman.h>

//GPIO Header Registers
#define GPIODATA ((void *) 0xE8000018)
#define GPIODIRECTION ((void *) 0xE8000028)

/*
Minimal function to test GPIO by writing and reading port.
 */

int main() {
  unsigned long page, addr1, addr2;
  int fd;
  unsigned char *start;

  // These are addresses in our address space.
  volatile unsigned short *direction_ptr;
  volatile unsigned short *data_ptr;

  unsigned short readValue;
  unsigned short writeValue;

  unsigned int bit = 1; // Which bit to set to zero
  unsigned short setMask; // Mask with all 0's except desired bit = 1
  unsigned short clearMask; // Mask with all 1's except desired bit = 0

  // First, map the I/O devices into our address space.
  addr1 = (unsigned long) GPIODIRECTION;
  addr2 = (unsigned long) GPIODATA; // Convert to long int for bit manipulation

  fd = open("/dev/mem", O_RDWR|O_SYNC);
  if (fd == -1) {
    perror("open(/dev/mem):");
    return -1;
  }

  // Extract the page number.
  page = addr2 & 0xfffff000;

  start = mmap(0, getpagesize(), PROT_READ|PROT_WRITE, MAP_SHARED, fd, page);
  // Has to be ran as root

  if (start == MAP_FAILED) {
    perror("mmap:");
    close(fd);
    return -1;
  }

  // Use the offsets to calculate addresses in our address space
  direction_ptr = (volatile unsigned short *) (start + (addr1 & 0xfff));
  data_ptr = (volatile unsigned short *) (start + (addr2 & 0xfff));

  // OK, what do we need to do?

  // First, we need to set the direction register to OUT
  // for the bit we want.

  // Create the masks
   setMask = 1;
   setMask = setMask << bit;
   clearMask = ~setMask;

  readValue = *direction_ptr; // Current value of the register
  asm volatile ("nop;nop;nop;nop;nop;"); // Why do we need this, anyway?

  // Now set the direction flag
  writeValue = readValue | setMask;
  *direction_ptr = writeValue;
  asm volatile ("nop;nop;nop;nop;nop;");

  readValue = *direction_ptr; // Updated value of the register
  asm volatile ("nop;nop;nop;nop;nop;");

  printf("Direction register. desired = %x, actual = %x\n",
     writeValue, readValue);

  // Next step: set the output to zero
  readValue = *data_ptr; // Current value of the register
  asm volatile ("nop;nop;nop;nop;nop;");

  writeValue = readValue & clearMask;
  *data_ptr = writeValue;
  asm volatile ("nop;nop;nop;nop;nop;");

  readValue = *data_ptr; // Updated value of the register
  asm volatile ("nop;nop;nop;nop;nop;");

  printf("Data register. desired = %x, actual = %x\n",
     writeValue, readValue);

  // Clean up
  int stat1 = munmap(start, getpagesize());
  int stat2 = close(fd);

  printf("Exiting minimal. stat 1 = %d, stat2 = %d\n",
	stat1, stat2);

  return 0;
}

