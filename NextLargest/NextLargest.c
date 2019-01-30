/* Take a 6-digit positive integer consisting of digits 1,2,3,4,5,6 as input. The number must use all 
	the digits 1,2,3,4,5,6 and use each digit exactly once (see sample input and output below). Store it in an 
	integer variable. Compute the next largest 6-digit number containing each digit from 1,2,3,4,5,6 exactly 
	once. Print it on the screen. 
	
	Sample input and output. 
	Enter number: 324651. 
	The next largest number is 325146. 
*/
#include "nextLargest.h"  

int main() 
// This driver handles number of all digits
{ 
    int num;
	char* digits;
	
	printf("Please enter a number: \n");
	scanf("%d",&num);
	
	digits = allocateSpace(numberOfDigits(num)); /* function calls to allocate space for the character array 
								 and count the number of digits */
	
	sprintf(digits, "%d", num); // function call convert integer to char[]
    
	digits = findNextLargest(digits, numberOfDigits(num));  /* function calls to find the next greater number and modify the same array to store the result
										and count the number of digits */
										
	printf("Next number with same set of digits is %s.",digits); 
	
    return 0; 
}
