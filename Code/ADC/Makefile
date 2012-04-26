all: adctest

adctest: adctest.o adc.o
	gcc -g adctest.o adc.o -o adctest

adctest.o: adctest.c ADC.h adc.c
	gcc -g -c adctest.c

adc.o: adc.c ADC.h
	gcc -g -c adc.c

clean:
	rm -f adctest *.o a.out
