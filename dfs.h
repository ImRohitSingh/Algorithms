/* DFS */
#include "stack.h"

#define VISITED 1

// function prototypes
int** createMat(int,int);  // to create space for a 2-D array and intialize it with 0
int* createArr(int);  // to create space for an array and intialize it with 0
void populateMat(int **,int,int);  // to populate 2-D array
void displayMat(int **,int,int);   // to display 2-D array
void displayArr(int *,int); // to display an array
void performDFS(int **,int,int);  // to perform DFS

// function definitions

// to create space for a 2-D array and intialize it with 0
int** createMat(int row,int col)
{
	int **arr, i;
	arr = (int **)malloc(row*sizeof(int *));
	for(i = 0; i < row; ++i)
		arr[i] = (int *)calloc(col,sizeof(int));  
	return arr;
}

// to create space for an array and intialize it with 0
int* createArr(int n)
{
	return ((int *)calloc(n,sizeof(int)));
}

// to populate 2-D array
void populateMat(int **arr,int row,int col)
{
	int i, j, choice;
	for( i = 0; i < row; ++i)
		for( j = 0; j < col; ++j)
		{
			printf("\nIs there an edge between vertices (%d) and (%d)?\n 1.YES \n 2.NO \nChoice?",i,j);
			scanf("%d",&choice);	
			if(choice == 1)
				arr[i][j] = 1;
		}	
}  

// to display 2-D array
void displayMat(int **arr,int row,int col)
{
	int i, j;
	printf("\nThe edge matrix is: \n");
	for(i = 0; i < row; ++i)
	{
		for( j = 0; j < col; ++j)
			printf(" %d ",arr[i][j]);
		printf("\n");
	}	
}  

// to display an array
void displayArr(int *arr,int n)
{
	int i;
	for( i = 0; i < n; ++i )
		printf(" %d ",arr[i]);
	printf("\n");	
} 

// to perform DFS
void performDFS(int **arr,int n,int start)  
{
	NODEPTR stack;
	int *vStatus, *path, underflow, overflow, popped, j, k;
	
	path = createArr(n);  // function call to create space for an array and intialize it with 0
	vStatus = createArr(n);  // function call to create space for an array and intialize it with 0
	
	k = 0;
	
	initStack(&stack);  // function call to initialize stack
	push(&stack,start,&overflow); // function call to push 'start'
	underflow = FALSE;
	while(!underflow)  // run until stack becomes empty
	{
		pop(&stack,&popped,&underflow);  // function call to pop an element out
		
		if(!vStatus[popped])  // if the popped node has not been visited
		{
			vStatus[popped] = VISITED;  // visit it
			path[k++] = popped; // add the node to the path array
			
			for( j = 0; j < n; ++j)  // check for all other nodes
				if(arr[popped][j])  // if there is an edge between 'popped' and 'j'
					push(&stack,j,&overflow);  // function call to push the node (or vertex) 'j'
		}	
	}
	
	printf("\nThe required path matrix is: \n");
	displayArr(path,n);
}
