#include <stdio.h> 
#include <string.h>
#include <stdlib.h>
// function prototypes
int numberOfDigits(int); // to count the number of digits
char* allocateSpace(int);  // to create space for an array
void swap(char *, char *); // to swap to digits
char* findNextLargest(char [],int);  // to find the next greater number and modify the same array to store the result
char* insertionSort(char [],int,int);  // to perform insertion sort from a given index till the end


// function definitions
int numberOfDigits(int n) 
// to count the number of digits
{
	int count = 0;
	while(n!=0)
	{
		++count;
		n/=10;	
	}	
	return count;
}

char* allocateSpace(int n)
// to create space for an array
{
	return (char *)malloc(n*sizeof(char));
}

void swap(char *a, char *b) 
// to swap two digits 
{ 
    char temp = *a; 
    *a = *b; 
    *b = temp; 
}

char* insertionSort(char number[],int i,int n)
// to perform insertion sort from a given index till the end
{
	int k, j;
	char temp;
	for(k = i; k < n; ++k)
	{
		temp = number[k];
		for(j = k-1; j>=i && number[j]>temp; --j)
			number[j+1] = number[j];
		number[j+1] = temp;	
	}
	return number;
}

char* findNextLargest(char number[], int n) 
/* Given a number as a char array number[], this function finds the 
 next greater number.  It modifies the same array to store the result */
{ 
    int i, j, k;
	char temp; 
	/* Start from the right most digit and find the first digit that is 
          smaller than the digit next to it. */
    for (i = n-1; i > 0; i--) 
        if (number[i] > number[i-1]) 
           break; 
  
    /* If no such digit is found, then all digits are in descending order 
         means there cannot be a greater number with same set of digits */
    if (i==0) 
    { 
        printf("This is the largest possible number."); 
        exit(0); 
    } 
  
    /* Find the smallest digit on right side of (i-1)-th digit that is 
            greater than number[i-1]  */
    int x = number[i-1], smallest = i; 
    for (j = i+1; j < n; j++) 
        if (number[j] > x && number[j] < number[smallest]) 
            smallest = j; 
  
    // Swap the above found smallest digit with number[i-1] 
    swap(&number[smallest], &number[i-1]); 
  
    // Sort the digits after (i-1) in ascending order 
    number = insertionSort(number,i,n);   // function call to perform Insertion Sort
      
    return number; 
}  
