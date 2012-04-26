all: motorTest DIOTest ADCTest libwpirbe.so

install: libwpirbe.so
	cp libwpirbe.so /usr/lib/
	cp DIO/DIO.h DIO/peekpoke.h SERIAL/serialHandler.h ADC/ADC.h /usr/include/

#MOTOR
motorTest: motorTest.o motor.o
	gcc -g -mcpu=arm9 motorTest.o motor.o -o motorTest

motorTest.o: motorTest.c SERIAL/serialHandler.h
	gcc -g -mcpu=arm9 -c motorTest.c

motor.o: MOTOR/motor.c
	gcc -g -mcpu=arm9 -c MOTOR/motor.c

#SERVO
servoTest: servoTest.o  motor.o
	gcc -g -mcpu=arm9 servoTest.o motor.o -o servoTest

servoTest.o: servoTest.c SERIAL/serialHandler.h
	gcc -g -mcpu=arm9 -c servoTest.c

#DIO
DIOTest: DIOTest.o peekpoke.o DIhandler.o DOhandler.o getBit.o ledControl.o resetServo.o
	gcc -g -mcpu=arm9 DIOTest.o peekpoke.o DIhandler.o DOhandler.o getBit.o ledControl.o resetServo.o -o DIOTest

DIOTest.o: DIOTest.c DIO/DIO.h
	gcc -g -mcpu=arm9 -c DIOTest.c

peekpoke.o: DIO/peekpoke.c DIO/peekpoke.h
	gcc -g -mcpu=arm9 -c DIO/peekpoke.c

DIhandler.o: DIO/DIhandler.c DIO/DIO.h
	gcc -g -mcpu=arm9 -c DIO/DIhandler.c

DOhandler.o: DIO/DOhandler.c DIO/DIO.h
	gcc -g -mcpu=arm9 -c DIO/DOhandler.c

getBit.o: DIO/getBit.c
	gcc -g -mcpu=arm9 -c DIO/getBit.c

ledControl.o: DIO/ledControl.c DIO/peekpoke.h
	gcc -g -mcpu=arm9 -c DIO/ledControl.c

resetServo.o: DIO/resetServo.c DIO/peekpoke.h DIO/DIO.h
	gcc -g -mcpu=arm9 -c DIO/resetServo.c

#ADC
ADCTest: ADCTest.o adc.o
	gcc -g -mcpu=arm9 ADCTest.o adc.o -o ADCTest

ADCTest.o: ADCTest.c ADC/ADC.h ADC/adc.c
	gcc -g -mcpu=arm9 -c ADCTest.c

adc.o: ADC/adc.c ADC/twsi.h ADC/ADC.h
	gcc -g -mcpu=arm9 -c ADC/adc.c


#INITIALIZER
init.o: INIT/init.c DIO/peekpoke.c MOTOR/motor.c DIO/resetServo.c
	gcc -g -mcpu=arm9 -c INIT/init.c


#LIBRARY
libwpirbe.so: init.o adc.o peekpoke.o DIhandler.o DOhandler.o motor.o getBit.o ledControl.o
	gcc -shared -o libwpirbe.so init.o adc.o peekpoke.o DIhandler.o DOhandler.o motor.o getBit.o ledControl.o resetServo.o


#CLEAN
clean:
	rm -f motorTest servoTest DIOTest ADCTest libwpirbe.so *.o a.out
	rm -f /etc/lib/libwpirbe.so
	rm -f /etc/include/DIO.h /etc/include/peekpoke.h /etc/include/serialHandler.h /etc/include/ADC.h
