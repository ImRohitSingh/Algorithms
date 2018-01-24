/* 
 Problem: Newton's Forward Interpolation
 Definition: A function f(x) whose functional values known for the equi-distant points x0,x1,...,xn. 
 			An interpolating point is supplied, say xm is supplied where the value f(xm) need to
 			be calculated where, x0<=xm<=xn.
 
 Package Name: Forward Interpolation
 	Purpose: Contains two classes:
 	 		a) Forward to perform the ForwardInterpolation Algorithm.
 			b) InvalidPhaseException when the 'phase' of the problem is found to be invalid
 	
 	Class Forward:-
 		Instances:
 		 Data Structures:
 		 	x[] - holding interpolating points
 		 	y[][] - holding functional values at respective points
 		 Variables:
 			n - Number of nodes
 			pivot - the user-give interpolating point where the functional values is required
 			
 		Methods:
 			Forward() - parameterized constructor to initialize the instances with user supplied data
 			differencesCal - calculates the forward differences
 			showDifferences()- displays the differences in table form
 			fact() - finds the factorial of a number
 			forwardCal - calculation of f(pivot)...
 		
 	InvalidPhaseException is a sub-class of the super-class Exception.
 	
 	
 	
 */
package ForwardInterpolation;

class InvalidPhaseException extends Exception   
{
	// class to deal with the exception of the phase 'u' being out of the interval (0,1)
}

public class Forward 
{
	double x[];     // array to hold interpolating points of the interpolating polynomial
	double y[][];   // two-dimensional array to hold the functional values of the interpolating polynomial at the respective nodes
	int n;         // variable to store number of nodes
	double pivot;   // variable to store the node at which the functional value is to be found out
	public Forward(double x[],double y[][],int n,double pivot)   // parameterized constructor; passing all the instance variables 
	{
		// creating array
		this.x=new double[n];			
		this.y=new double[n][n];     
		// initializations
		this.x=x;
		this.y=y;
		this.n=n;
		this.pivot=pivot;       
	}
	public void differencesCal()      //  function definition to calculate differences
	{
		for(int loop1=1;loop1<n;++loop1)     // outer loop running from the second node to the last node
			for(int loop2=0;loop2<n-loop1;++loop2)    // inner loop running from the first node
				y[loop1][loop2]=y[loop1-1][loop2+1]-y[loop1-1][loop2];   // calculating the differences and storing it to the functional value arrays
	}
	public void showDifferences()       //  function definition to show the differences
	{
		System.out.print("\n\n_____________________________________________\n\n");
		System.out.print("\n x(i)\t y(i)\t y1(i)\t y2(i)\t y3(i)\t y4(i)");
		System.out.print("\n\n_____________________________________________\n\n");
		for(int loop1=0;loop1<n;++loop1)
		{
			System.out.print("\n "+x[loop1]);
			for(int loop2=0;loop2<n-loop1;++loop2)
			{
				System.out.printf("   %.3f",y[loop2][loop1]);
			}
			System.out.print("\n");
		}
	}
	int fact(int a)          // function definition to calculate factorial of integer 'a'
	{
		int fac=1;
		while(a!=0)
		{
			fac=fac*a;
			--a;
		}
		
		return fac;
	}
	public void forwardCal()      // function definition to calculate the functional value at 'pivot'
	{
		int i,f,k=0,m,l;   
		double u,sum=0,temp;   // declaring and initializing necessary variables
		differencesCal();       // function call to calculate the differences
		
		showDifferences();   // function call to show the differences
		
		i=0;       // initializing a counter variable
		do
		{
			if(x[i]<pivot && pivot<x[i+1])   // condition to reach the point where 'pivot' is exactly between to given nodes
				k=1;     // initializing to stop the loop; required point is reached
			else
				++i;   // keep on increasing the index by 1 to reach the next node
		}
		while(k!=1);   // stopping condition

		f=i;      // storing the index of the node immediately after which, 'pivot' is present
		u=(pivot-x[f])/(x[f+1]-x[f]);     // calculating phase
		try
		{
			if(u<0.0 || u>1.0)       // Newton's Forward requires this phase, u to belong in (0,1)
			{
				InvalidPhaseException ipe=new InvalidPhaseException();
				throw ipe;
			}
		}
		catch(InvalidPhaseException obj2)   // This catch block handles the exception of phase u being out of the interval
		{
			System.out.println(obj2);
			System.exit(1);    // Stop the program permanently
		}
		System.out.println("\n\n u="+u);     // Print phase
		l=n-i+1;  // an attempt to avoid "noise-level"    
		if(l>n)   // condition avoid StringIndexOutOfBoundsException
			l=n;  // initializing accordingly
		else 
			n=l;    // initializing accordingly
		/*System.out.println("\ni="+i);
		System.out.println("\nn="+n);*/
		sum=0;      // initializing sum to its initial value
		for(int loop1=0;loop1<n;++loop1)     // outer loop
		{
			temp=1;    // variable used to calculate coefficients
			for(int loop2=0;loop2<loop1;++loop2)  // inner loop to find the successive products 
			{
				temp=temp*(u-loop2);
			}   // end of inner loop
			m=fact(loop1);   // denominator of the coefficients
			sum=sum+temp*(y[loop1][f]/m);    // multiplying the coefficients and the multipliers and storing the desired sum
		}  // end of outer loop
		System.out.println("\n\n f("+pivot+")="+sum+".");    // printing sum
		
		
	}   // end of method
}
