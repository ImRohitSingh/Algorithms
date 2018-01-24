/* The Program contains the Main of the Forward.java file. This is an exemplar of how to 
   run the program. (There can be several  other variations of the same.)
   
   Contains three classes:
 	 		a) InvalidNodeException when 'pivot' is an extrapolating point
 			b) InvalidStepLengthException when the interpolating points an not equi-distant
 			c) ForwardDriver containing the main() - It creates, populates all desired data raising 
 						exceptions wherever some may occur. Then it creates a reference of the Forward class
 						using which it invokes the method forwardCal() of that class. 
    
    */

import java.util.Scanner;     // importing the Scanner class of the 'util' package to accept necessary inputs from the user
import ForwardInterpolation.*;   // importing the created package which contains the methods to accept and calculate the process

class InvalidNodeException extends Exception
{
	// class to deal with the exception of the 'pivot' node not lying between the interpolating points
}

class InvalidStepLengthException extends Exception
{
	// class to deal with the exception of the 'step-length' not being uniform
}

public class ForwardDriver 
{    
	public static void main(String[] args) 
	{    // start of main
		Scanner obj=new Scanner(System.in);   //creating object of the scanner class
		// declaring and initializing necessary variables
		double x[],y[][],pivot=0,h,temp;
		int n;
		boolean check=true;     
		System.out.println("\nPlease enter number of nodes...\n");
		n=obj.nextInt();      // accepting from the user the number of nodes to be inserted
		// creating the arrays 
		x=new double[n];
		y=new double[n][n];     
		
		for(int loop=0;loop<n;++loop)
		{
			System.out.print("\nEnter the value of x"+loop+": ");
			x[loop]=obj.nextDouble();   // accepting interpolating points
			System.out.print("\nEnter the value of y"+loop+": ");
			y[0][loop]=obj.nextDouble();  // accepting corresponding functional values
		}
		h=x[1]-x[0];  // calculating step-length
		h=Double.parseDouble(String.format("%.1f",h));   // for some inputs the floating point representations can hamper the desired result; so setting precision for such floating point numbers
		
		System.out.println("\nEnter x for finding f(x): ");
		pivot=obj.nextDouble();   // accepting the point at which the functional value is required
		obj.close();  // to prevent leaking; object 'obj' closed
		try
		{
			if(pivot<x[0] || pivot>x[n-1])  // if condition to check if the user given point is an extrapolating point
			{
				check=false;  // changing the value of the check variable to keep a note that an exception has taken place
				InvalidNodeException ine=new InvalidNodeException();
				throw ine;
			}
		}
		catch(InvalidNodeException obj1)  // corresponding catch block
		{
			System.out.println(obj1);  // print exception
		}
		try
		{
			for(int loop=0;loop<n-1;++loop)
			{
				temp=x[loop+1]-x[loop];
				temp=Double.parseDouble(String.format("%.1f",temp));        // for some inputs the floating point representations can hamper the desires result; so setting precision for such floating point numbers
				if(temp!=h)  // if condition to check if the interpolating points are not equi-space
				{
					check=false;   // changing the value of the check variable to keep a note that an exception has taken place
					InvalidStepLengthException iine=new InvalidStepLengthException();
					throw iine;
				}
			}
		}
		catch(InvalidStepLengthException obj2)  // corresponding catch block
		{
			System.out.println(obj2); // print exception
		}
		if(check)   // if no exception has occurred
		{
			Forward forward=new Forward(x,y,n,pivot);  // create an object of the 'Forward' class and pass the accepted inputs through the parameterized constructor
			forward.forwardCal();  // call the method to perform Newton's Forward Interpolation using the recently object created
		}
		else  // if exception has occurred
		{
			System.out.println("\nINHERENT ERROR.\n");    // there are some errors in the entered entries
		}
	}  // end of main
} // end of class