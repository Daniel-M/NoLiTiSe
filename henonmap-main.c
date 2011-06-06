/*
  DESCRIPTION: This Code creates an time series
      
       AUTHOR: Daniel Mejia Raigosa
         DATE: 
      VERSION: 0.0.1
*/

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "commonroutines.c"

#define ARGS 6 // Number of Maximum Arguments (1 means no arguments!)
#define TITLESCN "Henon Map Time Series"

void henoniterate(double xi, double yi,double *Xi, double *Yi, double a, double b, int N)
{
      *Xi=1-a*pow(xi,2)+b*yi;
      *Yi=xi;
}


main(int argc,char *argv[]) // for input arguments, remeber argv[0]=program name argv[1]= first argument and so on */

{
  // This section is made for argument validation

	if (argc > ARGS)
	   {
	      printf("Too many arguments supplied.\n");
	      exit(1);
	   }
	else if (argc<ARGS)
	   {
	    
	       printf("Some arguments expected.\n");
	       exit(1);
 	   }
 
	pimpi(TITLESCN,25);

	int points,i,select;
	double x,y,xi,yi,a=1.4,b=0.3;
	char salida[CHAPER];

	FILE *henondataxay;
	FILE *henondatax;
	FILE *henondatay;
	FILE *henondataxy;

	characternumber(argv[1],CHAPER); //Confirm Character allowed values
	
	strcpy(salida,argv[1]);   //Convert file names

	points=atoi(argv[1]);

	if (0<points<1000 || points<0)
	  {
	    printf("  [!] Invalid point number (negative or less than 1000), changing number of points to 1000...\n");
	    points=1000;
	  }
	else if(points==0)
	  {
	    printf(" [!] points=0 set the number of points to 1e9...\n");
	    points=1000000000;
	  }

	a=atof(argv[2]);
	b=atof(argv[3]);
	xi=atof(argv[4]);
	yi=atof(argv[5]);

	henondataxay=fopen("henon-xy.txt","w");
	henondatax=fopen("henon-x.txt","w");
	henondatay=fopen("henon-y.txt","w");
	henondataxy=fopen("henon-x+y.txt","w");

	fprintf(henondataxay,"### Henon Map : a= %lf \t b=%lf X_0= %lf \t Y_0=%lf\n",a,b,xi,yi);
	fprintf(henondataxay,"### Henon Map : a= %lf \t b=%lf X_0= %lf \t Y_0=%lf\n",a,b,xi,yi);
	fprintf(henondataxay,"### Henon Map : a= %lf \t b=%lf X_0= %lf \t Y_0=%lf\n",a,b,xi,yi);
	fprintf(henondataxay,"### Henon Map : a= %lf \t b=%lf X_0= %lf \t Y_0=%lf\n",a,b,xi,yi);
	fprintf(henondataxay,"### X_n \t Y_n\n");
	fprintf(henondatax,"### X_n\n");
	fprintf(henondatay,"### Y_n\n");
	fprintf(henondataxy,"### X_n + Y_n\n");

	for(i=0;i<points;i=i++)
	  {

	    henoniterate(xi,yi,&x,&y,a,b,points);

	    fprintf(henondataxay,"%lf \t %lf\n",x,y);
	    fprintf(henondatax,"%lf\n",x);
	    fprintf(henondatay,"%lf \t %lf\n",y);
	    fprintf(henondataxy,"%lf\n",x+y);

	    xi=x;
	    yi=y;
	  }

	fclose(henondataxay);
	fclose(henondatax);
	fclose(henondatay);
	fclose(henondataxy);
	
	pimpe(TITLESCN,25);
	exit(0);

} //End of Main Code
