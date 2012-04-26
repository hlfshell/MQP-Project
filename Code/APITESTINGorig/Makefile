all: test

test: main.o serialHandler.o motor.o servo.o
	gcc -g main.o serialHandler.o motor.o servo.o -o test

main.o: main.c
	gcc -g -c main.c

serialHandler.o: serialHandler.c
	gcc -g -c serialHandler.c

motor.o: motor.c
	gcc -g -c motor.c

servo.o: servo.c
	gcc -g -c servo.c

clean:
	rm -f test *.o a.out
