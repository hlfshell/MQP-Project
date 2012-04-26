#include <math.h>
#include <stdio.h>

int main(){
	int a[91];
	int i;

	for(i=1; i<91; i++)
		a[i]=(int) sin((double) i);

	for(i = 1; i<91; i++)
		printf("a[%d]=%d\r\n", i, a[i]);

}
