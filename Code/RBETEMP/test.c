#include <stdio.h>
#include <sys/time.h>

#define size_of_array 4000 //allocating memory for the array
#define fill_array 512 //filling the array with this value

// Function prototype:
struct timeval timediff (struct timeval *time1, struct timeval *time2);

int main() {
	struct timeval time1; 		 // First timestamp
	struct timezone tz1;  		 // First timezone (not really used)
	struct timeval time2; 		 //Second timestamp
	int status; 				 // Returned status code	
	struct timeval timeDiffTest; //Difference Timestamp
	int i; 						 //variable for while loop
	int *Pointer_array; 		 //declares pointer that will be used in the array
	int *Pointer_base; 			 //holds the array base value that it will be starting at

	Pointer_array = calloc(size_of_array, sizeof(int)); //allocating array and setting pointer
	Pointer_base = Pointer_array; 						
//keeps base value of array
	
/*******************************TEST 
1*******************************************/
	status = gettimeofday(&time1, &tz1); //gets time before test
	printf("This is test 1\n");
	printf("status = %d, tv_sec = %ld, tv_usec = %ld\n", status, time1.tv_sec, time1.tv_usec);
	
	i=0; 
	while (i < size_of_array) {
		*(Pointer_array + 1) +=10;
		i++;
	}
	
	status = gettimeofday(&time2, &tz1); //gets second time after test is done
	printf("status = %d, tv_sec = %ld, tv_usec = %ld\n", status, time2.tv_sec,time2.tv_usec);
	
	timeDiffTest = timediff(&time1, &time2); //finds the difference and stores
	
	printf("tv_sec = %ld, tv_usec = %ld\n", timeDiffTest.tv_sec,timeDiffTest.tv_usec);
	
/*******************************TEST 
2*******************************************/
	
	status = gettimeofday(&time1, &tz1); //gets time before test
	printf("This is test 2\n");
	printf("status = %d, tv_sec = %ld, tv_usec = %ld\n", status, time1.tv_sec,time1.tv_usec);
	
	i=0;
	while (i < size_of_array) {
		*Pointer_array +=10;
		Pointer_array++;
		i++;
	}
	
	status = gettimeofday(&time2, &tz1); //gets second time after test is done
	printf("status = %d, tv_sec = %ld, tv_usec = %ld\n", status, time2.tv_sec,time2.tv_usec);
	
	timeDiffTest = timediff(&time1, &time2); //finds the difference and stores
	
	printf("tv_sec = %ld, tv_usec = %ld\n", timeDiffTest.tv_sec,timeDiffTest.tv_usec);

/*******************************TEST 
3*******************************************/

	status = gettimeofday(&time1, &tz1); //gets time before test
	printf("This is test 3\n");
	printf("status = %d, tv_sec = %ld, tv_usec = %ld\n", status, time1.tv_sec,time1.tv_usec);
	
	i=0;
	while (i < size_of_array) {
		Pointer_array[i] += 10;
		i++;
	}
		
	status = gettimeofday(&time2, &tz1); //gets second time after test is done
	printf("status = %d, tv_sec = %ld, tv_usec = %ld\n", status, time2.tv_sec,time2.tv_usec);
		
	timeDiffTest = timediff(&time1, &time2); //finds the difference and stores
		
	printf("tv_sec = %ld, tv_usec = %ld\n", timeDiffTest.tv_sec,timeDiffTest.tv_usec);	

	
/*******************************TEST 
4*******************************************/
	status = gettimeofday(&time1, &tz1); //gets time before test
	printf("This is test 4\n");
	printf("status = %d, tv_sec = %ld, tv_usec = %ld\n", status, time1.tv_sec,time1.tv_usec);
	i=0;		
	while (i < size_of_array) {
		Pointer_array[i] = fill_array;
		i++;
	}

			
	status = gettimeofday(&time2, &tz1); //gets second time after test is done
	printf("status = %d, tv_sec = %ld, tv_usec = %ld\n", status, time2.tv_sec,time2.tv_usec);
			
	timeDiffTest = timediff(&time1, &time2); //finds the difference and stores
			
	printf("tv_sec = %ld, tv_usec = %ld\n", timeDiffTest.tv_sec,timeDiffTest.tv_usec);	
	
	return 0;

}


/* timediff -- Calculates the difference between two timestamps.
 * @param time1 Pointer to the first time
 * @param time2 Pointer to the second time.
 * @return time2 minus time1, expressed as seconds and microseconds
 *    in a timeval struct (not a pointer).
 * Note: Return value is only valid ff time 2 is later than time 1.
 * Both seconds and microseconds will always be zero or positive. 
 */

struct timeval timediff (struct timeval *time1, struct timeval *time2) {
	struct timeval diff; //declares struc diff
		 
	if (time1->tv_usec > time2->tv_usec) { //if-then statement used if carry-over needed
		time2->tv_usec += 999999;
		time2->tv_sec -= 1;
	}

	diff.tv_sec = (time2->tv_sec - time1->tv_sec); //basic subtract seconds
	diff.tv_usec = (time2->tv_usec - time1->tv_usec); //basic subtract microseconds
	
	return diff; //returns the new struct 
}


