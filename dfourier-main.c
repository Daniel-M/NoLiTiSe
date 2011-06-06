/*
  FILE NAME:   dfourier-main.c
  DESCRIPTION: 
  AUTHOR:      Daniel Mejia Raigosa
  DATE:        24, May 2011
  VERSION:     0.0.1 
*/

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <complex.h>

#include "commonroutines.c"

#define ARGS 2 // Number of Maximum Arguments (1 means no arguments!)
#define TITLESCN "Discrete Fourier Transform" // Program Title
#define VER "0.0.1" // Version of the code
#define ANO "2011" // Date of code
#define dt 0.0057600368642359307 // Sampling Interval (data series)


#undef I
#define j _Complex_I

  /* **************************  MAIN FUNCTION ************************** */

main(int argc,char *argv[]) // for input arguments, remeber argv[0]=program name argv[1]= first argument and so on
{
  /* This section is made for argument validation */
	if(argc > ARGS)
	  {
	    printf("Too many arguments supplied.\n");
	    printf(" Usage\'$ %s file-with-data.ext\'\n\n",argv[0]);
	    exit(1);
	  }
	else if (argc<ARGS)
	  {
	    
	    printf("Some arguments expected.\n");
	    printf(" Usage\'$ %s file-with-data.ext\'\n\n",argv[0]);
	    exit(1);
 	  }
  
	double complex skbar,sum;
	double sn[MAXDATA],pskbar[MAXDATA],k;
	char originfn[CHAPER],filename[CHAPER], fileext[CHAPER];
	
	int N,i,l;
	time_t t1,t2,t3,t4;

	FILE *pspectrum;
	
	characternumber(argv[1],CHAPER); //Confirm Character allowed values

	strcpy(originfn,argv[1]);   //Convert file names
 	      
	datadquire(originfn,sn,&N);

	/* Make the transform */
	
	printf("\n * Creating data file");
	
	k=-N/2;
	sum=0;
	l=0;
	
	strcpy(filename,strtok(argv[1],".")); // separate data files
	strcpy(fileext,strstr(originfn,"."));
	
	strcpy(filename,strcat(filename,"-pspectrum")); //create a filename
	
	strcat(filename,fileext);

	opendatafile(&pspectrum,filename,"w");

	fprintf(pspectrum,"### Discriete Fourier Transform Power Spectrum\n");
	
	printf(" * Data origin file: \'%s\'\n\n",originfn);
	printf("\n * Calculating the power spectrum");
	
	while(k<N/2.0)
	  {
	    for(i=1;i<N;i++)
	      {
		sum=sn[i-1]*cexp((2*M_PI*j*k*i)/N)+sum;

	      }

	    skbar=sum/sqrt(N);

	    //printf("\n * %d %lf  Calculated: %lf",l,k, cabs(skbar));

	    fprintf(pspectrum,"%lf %lf %lf\n",k/(N*dt),cabs(skbar),k);
	    k=k+1;
	    l=l+1;
	  }

	fclose(pspectrum);
	printf("\n * Power spectrum Calculated");
	printf("\n * Results saved on file \'%s\'\n",filename);
	
} //End of Main Code
