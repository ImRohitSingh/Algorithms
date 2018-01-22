#include<stdio.h>
#include<stdlib.h>

//some macro definitions
#define INFINITY 9999
#define NIL -1

/*BELLMAN-FORD:
Defintion:	The Bellman–Ford algorithm is an algorithm that computes 
			shortest paths from a single source vertex to all of the other vertices in a weighted digraph.
			
Variable Description:
	noe - contains number of edges
	nov - contains number of verices
	flag - to identify a negative cycle
	u - a vertex of and edge pointed-from
	v - a vertex of the edge pointed-to
	s - the single source vertex
	
Data Structures:
	d - an array containing the minimum distance of each vertex from the source 's'; d[i] is the distance of the i-th edge...
	p - predecessor array containing the nearest predecessor vertex for each vertex; p[i] is the nearest predecessor for the i-th edge...
	
Initializations:
	flag<--TRUE(graph contains no negative cylce)
	
	d[i]<--0, if i is the source
		<--INFINITY(a maximum value not contained in the graph), otherwise.
		
	p[i]<--NIL(an invalid value), for each i.
	
ALGORITHM:
	if(d[v]>d[u]+cost(u,v)
	{
		d[v]=d[u]+cost(u,v);
		p[v]=u;
	}  ..running (nov-1) times for each edge...
	
	when done repeat the check once again. If the 'if' condition is found 'true' again, report negative cycle..
	
COMPLEXITY: O(|V|.|E|), for the graph G(V,E).

*/

struct edge
{
	int from;
	int to;
	int weight;
};  // structure representing a directed edge and its corresponding weight

typedef struct edge EDGE;   // this renaming though is useless, still it is a good practice to rename bigger struecture names with something shorter

int main(void)
{
	int i,j,noe,nov,*d,*p,s,u,v,flag,temp;  // decraling necessary variables
	EDGE *e;  // pointer to the array of edges 
	
	printf("Enter number of edges the graph contains: \n");
	scanf("%d",&noe);  //accepting the number of edges from the user
	e=calloc(sizeof(struct edge),noe);  // creating space to store the edges
	
	printf("\nEnter %d data: ",noe);
	for(i=0;i<noe;++i)       // run for each edge
	{
		printf("\nEnter information of edge %d: \n",i+1);     
		printf("Enter from,to and weight: ");    
		scanf("%d %d %d",&e[i].from,&e[i].to,&e[i].weight);      // accepting each edge and their weight
	}
	
	printf("\nThe entered graph is:  \n");
	for(i=0;i<noe;++i)
		printf("%d\t%d\t%d\n",e[i].from,e[i].to,e[i].weight);      // displaying the graph
	
	printf("\nEnter number of vertices the graph contains: \n");
	scanf("%d",&nov);  // accpeting the number of vertices from the user
	
	d=calloc(sizeof(int),nov); // creating space for the distance array
	p=calloc(sizeof(int),nov);  // creating space for the predecessor array
	
	printf("\nEnter source vertex: ");
	scanf("%d",&s);  // accpeting the source vertex from the user
	
	// INITIALIZATIONS: according as the Algorithm demands
	d[s]=0;   // since, distance from source to itslef is 0
	for(i=0;i<nov;++i)  // run for each vertex
	{
		if(i!=s)    // if the i-th vertex is not the source vertex...
			d[i]=INFINITY;     // ...then only perform initialization...
		p[i]=NIL;    // intialize the predecessor array for each vertex
	}
	
	for(i=1;i<nov;++i)       // OUTER LOOP: run for (total number of vertex-1) times
	{
		for(j=0;j<noe;++j)    // INNER LOOP: run for each edge
		{
			u=e[j].from;    // extract the node pointed-by from an edge
			v=e[j].to;    // extracct the node pointed-to from the edge
			if(d[v]>d[u]+e[j].weight)
			{
				d[v]=d[u]+e[j].weight;   // update the distance array with the minimum distance from the source vertes 's'
				p[v]=u;      // update the predecessor array with the nearest shortest node
			}              // the whole of this 'if' block performs the Bellman-Ford algorithm
		}  // end of INNER LOOP
		//OPTIONAL: displaying the  distance array for each iteration of the OUTER LOOP
		printf("\nThe distance array after %d-th iteration: \n",i);
		for(j=0;j<nov;++j)
			if(j==0)
				printf("[%d",d[j]);
			else if(j==nov-1)
				printf("%d].\n\n\n",d[j]);
			else
				printf(" %d ",d[j]); 
				
		//OPTIONAL: displaying the  predecessor array for each iteration of the OUTER LOOP 		
		printf("\nThe predecessor array after %d-th iteration: \n",i);
		for(j=0;j<nov;++j)
			if(j==0)
				printf("[%d",p[j]);
			else if(j==nov-1)
				printf("%d].\n\n\n",p[j]);
			else
				printf(" %d ",p[j]); 
	
	}   // end OUTERLOOP
	flag=1;     // 1 represents the 'TRUE' state; that is graph doesn't contain any negative cycle
	for(j=0;j<noe;++j) // run for each edge
	{
		u=e[j].from;      // extract the node pointed-by from an edge
		v=e[j].to;   // extract the node pointed-to from an edge
		if(d[v]>d[u]+e[j].weight)
		{
			flag=0;	// change to 'FALSE' state- graph contains negative cycle
			break;   // no need to repeat further
		}
	}
	if(flag)  // if the graph doesn't contain any negative cycle
	{
		printf("\nResults: \n");
		for(i=0;i<nov;++i) // run for each vertex
			printf("Vertex: %d, Cost: %d, Parent: %d.\n",i,d[i],p[i]);  // print the vertex; cost=shortest distance from source 's'; parent=nearest shortest predecessor;
			
		printf("\nThe path: \n");
		// printing the path from source to each vertex
		for(i=0;i<nov;++i)   // run for each vertex
		{
			if(i!=s)   // no need to print a path for the soource as it contains only one point
			{
			
				printf("%d<-",i);  // each 'i' is actually the desitantion...
				temp=p[i];   // find its predecessor
				while(temp!=s)   // keep on finding corresponding predecessors untill source 's' is reached
				{
					printf("%d<-",temp);    // append to the front of the dynamic path
					temp=p[temp];    // find the predecessor
				}
				printf("%d.\n",temp);   // finally, print the source 's'; here 'temp' contains 's' as that is where the while-loop terminated...
			}
		}
	}
	else       // graph contains negative cycle
		printf("\nNegative cycle exists.\n");	
	return 0;
}    // end main
