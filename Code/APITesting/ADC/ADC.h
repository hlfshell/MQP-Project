/*
*
*/


#ifndef ADC_H
#define ADC_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <assert.h>
#include <string.h>
#include "twsi.h"

double adc(int chan);


#endif
