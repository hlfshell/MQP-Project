#include<unistd.h>
#include<sys/types.h>
#include<sys/mman.h>
#include<stdio.h>
#include<fcntl.h>

/*
  Features that the old peekXX/pokeXX did not have:
  1. Support for 8/16/32 bit READ/WRITE in one function
  2. Support for decimal and binary values
  3. The value return is returned (to become the status code)
 */
int peekpoke(off_t addr, int intval, int dowrite, int bits) {
  off_t page;
  int fd;
  unsigned char *start;
  unsigned char *chardat, charval;
  unsigned short *shortdat, shortval; 
  unsigned int *intdat;
  
  fd = open("/dev/mem", O_RDWR|O_SYNC);
  if (fd == -1) {
    perror("open(/dev/mem):");
    return 0;
  }
  page = addr & 0xfffff000;
  start = mmap(0, getpagesize(), PROT_READ|PROT_WRITE, MAP_SHARED, fd, page);
  if (start == MAP_FAILED) {
    perror("mmap:");
    return 0;
  }
  if (bits == 8) {
    charval = (unsigned char)intval;
    chardat = start + (addr & 0xfff);
    if (dowrite) {
      *chardat = charval;
    }
    if (!dowrite) {
      intval = (unsigned int)*chardat;
    }
  } else if (bits == 16) {
    shortval = (unsigned short)intval;
    shortdat = (unsigned short *)(start + (addr & 0xfff));
    if (dowrite) {
      *shortdat = shortval;
    }
    else if(!dowrite) {
      intval = (unsigned int)*shortdat;
    }
  } else { // bits == 32
    intdat = (unsigned int *)(start + (addr & 0xfff));
    if (dowrite) {
      *intdat = intval;
    }
    if (!dowrite) {
      intval = *intdat;
    }
  }
  if (!dowrite) {
    printf("0x%X\n", intval);
  }
  close(fd);
  return intval;
}

void poke8(off_t addr, int intval){
	peekpoke(addr, intval, 1, 8);
}

int peek8(off_t addr, int intval){
	return peekpoke(addr, intval, 0, 8);
}

int peek16(off_t addr, int intval){
	return peekpoke(addr, intval, 0, 16);
}

void poke16(off_t addr, int intval){
	peekpoke(addr, intval, 1, 16);
}

void poke32(off_t addr, int intval){
	peekpoke(addr, intval, 1, 32);
}

int peek32(off_t addr, int intval){
	return peekpoke(addr, intval, 0, 32);
}
