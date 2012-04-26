all: com

com: com.o
	gcc -g3 -o com com.o

com.o: com.c
	gcc -g -c com.c

clean:
	rm -f com *.o a.out

