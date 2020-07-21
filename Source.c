#include <stdio.h>
#include <emmintrin.h>

int main() {
	    int first;
	   int second;
	   printf("Moahmmed Alhamadah\n");
	    printf("Enter the first integer: ");
	    scanf_s("%d",&first);
	    
	    printf("Enter the second integer: ");
	    scanf_s("%d",&second);
	   
	    int result = (first*first) + (second*second);
	
	    printf("The sum of squares is: %d\n",result);

	//unsigned int num = 256;
	int byte1 = 0xff & (first);
	int byte2 = 0xff & (first >> 8);
	int byte3 = 0xff & (first >> 16);
	int byte4 = 0xff & (first >> 24);

	int sum = byte1 + byte2 + byte3 + byte4;
	//printf("%d + %d + %d + %d", byte1, byte2, byte3, byte4);

	printf("the sum = %d", sum);


	return 0;
}