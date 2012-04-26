all: jumperCheck

jumperCheck: jumper.o peekpoke.o
	gcc -g jumper.o peekpoke.o -o jumperCheck

jumper.o: jumper.c peekpoke.c
	gcc -g -c jumper.c

peekpoke.o: peekpoke.c peekpoke.h
	gcc -g -c peekpoke.c

clean:
	rm -f jumperCheck *.o a.out
