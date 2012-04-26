all: test

test: main.o motorOutput.o
	gcc -g main.o motorOutput.o -o test

main.o: main.c serialHandler.h
	gcc -g -c main.c

motorOutput.o: motorOutput.c
	gcc -g -c motorOutput.c

clean:
	rm -f test *.o a.out
