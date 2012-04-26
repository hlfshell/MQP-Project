all: DIOTest

DIOTest: DIOTest.o peekpoke.o DIhandler.o DOhandler.o getBit.o
	gcc -g DIOTest.o peekpoke.o DIhandler.o DOhandler.o getBit.o -o DIOTest

DIOTest.o: DIOTest.c DIO.h
	gcc -g -c DIOTest.c

peekpoke.o: peekpoke.c peekpoke.h
	gcc -g -c peekpoke.c

DIhandler.o: DIhandler.c DIO.h
	gcc -g -c DIhandler.c

DOhandler.o: DOhandler.c DIO.h
	gcc -g -c DOhandler.c

getBit.o: getBit.c
	gcc -g -c getBit.c

#CLEAN
clean:
	rm -f DIOTest *.o a.out
