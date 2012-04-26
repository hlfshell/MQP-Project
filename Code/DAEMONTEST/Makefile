all: daemonTest resetButton

daemonTest: daemon.o peekpoke.o
	gcc -g daemon.o peekpoke.o -o daemonTest

resetButton: resetButton.o peekpoke.o
	gcc -g resetButton.o peekpoke.o -o resetButton

resetButton.o: resetButton.c peekpoke.c
	gcc -g -c resetButton.c

daemon.o: daemon.c peekpoke.c
	gcc -g -c daemon.c

peekpoke.o: peekpoke.c peekpoke.h
	gcc -g -c peekpoke.c

clean:
	rm -f daemonTest resetButton *.o a.out
