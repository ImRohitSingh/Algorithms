/* DFS (main) */
#include <stdio.h>
#include <stdlib.h>
#include "dfs.h"

int main(void)
/* For vertex number, start with 0 ( not 1 ) 
	Note: In case of multiple matches for a node, the lower one gets pushed first */
{
	int **a, n, start;
	
	printf("\nEnter number of vertices: \n");
	scanf("%d",&n);
	
	
	if(n <= 0) // too few vertices
	{
		printf("\nToo few vertices!\n");
		exit(0);
	}
		
	a = createMat(n,n);  // function call to create space for a 2-D array and intialize it with 0
	populateMat(a,n,n); // function call to populate 2-D array
	displayMat(a,n,n);  // function to display 2-D array
		
	printf("\nEnter starting vertex (or node): \n");
	scanf("%d",&start);
	
	
	if(start >= n) // start node does not exist
	{
		printf("\nStart node does not exist!\n");
		exit(0);
	}
	
	performDFS(a,n,start);  // function call to perform DFS with start node 'start'
	
	return 0;
}
