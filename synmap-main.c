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

#define ARGS 8 // Number of Maximum Arguments (1 means no arguments!)
#define TITLESCN "Syntetic Map Time Series"
#define LIMITP 500 //limit for minumun points

void syntiterate(double xi, double yi,double zi,double *Xi, double *Yi,double *Zi, double a, double b,double c,int N)
{
      *Xi=a+b*pow(yi,2)+c*zi;
      *Yi=xi;
      *Zi=yi;
}


main(int argc,char *argv[]) // for input arguments, remeber argv[0]=program name argv[1]= first argument and so on */

{
  // This section is made for argument validation

	if (argc > ARGS)
	   {
	      printf("Too many arguments supplied.\n");
	      printf(" Usage\n \'%s\' N a b c xo yo zo\n",argv[0]);
	      printf(" N - Number of points\n a,b,c - Parameters(use a=1.76 b=-1 c=-0.1)\n xo,yo,zo Initial conditions");
	      exit(1);
	   }
	else if (argc<ARGS)
	   {
	    
	       printf("Some arguments expected.\n");
	      printf(" Usage\n \'%s\' N a b c xo yo zo\n",argv[0]);
	      printf(" N - Number of points\n a,b,c - Parameters(use a=1.76 b=-1 c=-0.1)\n xo,yo,zo Initial conditions\n\n");
	       exit(1);
 	   }
 
	pimpi(TITLESCN,25);

	int points,i,select;
	double x,y,z,xi,yi,zi,a,b,c;
	char salida[CHAPER];

	FILE *dataxayaz;
	FILE *datax;
	FILE *datay;
	FILE *dataz;
	FILE *dataxyz;

	points=atoi(argv[1]);

	if (points<LIMITP)
	  {
	    printf("  [!] Invalid points number \'%d\' (negative or less than %d), changing number of points to %d...\n",points,LIMITP,LIMITP);
	    points=LIMITP;
	  }
	else if(points==0)
	  {
	    printf(" [!] points=0 set the number of points to 1e9...\n");
	    points=1000000000;
	  }

	a=atof(argv[2]);
	b=atof(argv[3]);
	c=atof(argv[4]);
	xi=atof(argv[5]);
	yi=atof(argv[6]);
	zi=atof(argv[7]);

	dataxayaz=fopen("syntetic-xyz.txt","w");
	datax=fopen("syntetic-x.txt","w");
	datay=fopen("syntetic-y.txt","w");
	dataz=fopen("syntetic-z.txt","w");
	dataxyz=fopen("syntetic-x+y+z.txt","w");

	fprintf(dataxayaz,"### Syntetic Map : X_{n+1}=a+b*Y_{n}^2+c*Z_{n} Y_{n+1}=Y_{n} Z_{n+1}=Y_{n}\n### a= %lf \t b=%lf c= %lf X_0= %lf \t Y_0=%lf\n",a,b,c,xi,yi,zi);
	fprintf(datax,"### Syntetic Map : X_{n+1}=a+b*Y_{n}^2+c*Z_{n} Y_{n+1}=Y_{n} Z_{n+1}=Y_{n}\n### a= %lf \t b=%lf c= %lf X_0= %lf \t Y_0=%lf\n",a,b,c,xi,yi,zi);
	fprintf(datay,"### Syntetic Map : X_{n+1}=a+b*Y_{n}^2+c*Z_{n} Y_{n+1}=Y_{n} Z_{n+1}=Y_{n}\n### a= %lf \t b=%lf c= %lf X_0= %lf \t Y_0=%lf\n",a,b,c,xi,yi,zi);
	fprintf(dataz,"### Syntetic Map : X_{n+1}=a+b*Y_{n}^2+c*Z_{n} Y_{n+1}=Y_{n} Z_{n+1}=Y_{n}\n### a= %lf \t b=%lf c= %lf X_0= %lf \t Y_0=%lf\n",a,b,c,xi,yi,zi);
	fprintf(dataxyz,"### Syntetic Map : X_{n+1}=a+b*Y_{n}^2+c*Z_{n} Y_{n+1}=Y_{n} Z_{n+1}=Y_{n}\n### a= %lf \t b=%lf c= %lf X_0= %lf \t Y_0=%lf\n",a,b,c,xi,yi,zi);
	
	fprintf(dataxayaz,"### X_n \t Y_n \t Z_n\n");
	fprintf(datax,"### X_n\n");
	fprintf(datay,"### Y_n\n");
	fprintf(datay,"### Z_n\n");
	fprintf(dataxyz,"### X_n + Y_n + Z_n\n");

	for(i=0;i<points;i=i++)
	  {

	    syntiterate(xi,yi,zi,&x,&y,&z,a,b,c,points);

	    fprintf(dataxayaz,"%E \t %E \t %E\n",x,y,z);
	    fprintf(datax,"%E\n",pow(x,2));
	    fprintf(datay,"%E\n",y);
	    fprintf(dataz,"%E\n",z);
	    fprintf(dataxyz,"%E\n",x+y);

	    zi=yi;
	    xi=x;
	    yi=y;

	  }

	fclose(dataxayaz);
	fclose(datax);
	fclose(datay);
	fclose(dataz);
	fclose(dataxyz);
	
	pimpe(TITLESCN,25);
	exit(0);

} //End of Main Code
