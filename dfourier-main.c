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

#include "commonroutines.c"

#define ARGS 2 // Number of Maximum Arguments (1 means no arguments!)
#define TITLESCN "Discrete Fourier Transform" // Program Title
#define VER "0.0.1" // Version of the code
#define ANO "2011" // Date of code



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
  
	double skbar[1],sn[MAXDATA],norm,k,dt=0.0057600368642359307;
	char originfn[CHAPER],filename[CHAPER], fileext[CHAPER];
	
	int N,i,l;
	time_t t1,t2,t3,t4;

	FILE *pspectrum;
	FILE *ftransform;
	
	characternumber(argv[1],CHAPER); //Confirm Character allowed values

	strcpy(originfn,argv[1]);   //Convert file names
 	      
	pimpi(TITLESCN,25);

	datadquire(originfn,sn,&N);

	/* Make the transform */
	
	printf("\n * Creating data file");
       	
	//open pspectrum
	strcpy(filename,strtok(argv[1],".")); // separate data files
	strcpy(fileext,strstr(originfn,"."));
	
	strcpy(filename,strcat(filename,"-pspectrum")); //create a filename
	
	strcat(filename,fileext);

	opendatafile(&pspectrum,filename,"w");

	printf("\n * Saving Power Spectrum to \'%s\'\n",filename);

	//open ftransform
	strcpy(filename,strtok(argv[1],".")); // separate data files
	strcpy(fileext,strstr(originfn,"."));
	
	strcpy(filename,strcat(filename,"-ftransform")); //create a filename
	
	strcat(filename,fileext);

	opendatafile(&ftransform,filename,"w");

	printf("\n * Saving Fourier Transform to \'%s\'\n",filename);

	fprintf(pspectrum,"### Discriete Fourier Transform Power Spectrum\n");
	fprintf(pspectrum,"### Data Origin : %s\n",argv[1]);
	fprintf(pspectrum,"### Sampling interval dt = %.6E\n",dt);
	fprintf(pspectrum,"### k/Ndt   S(k/Ndt)\n");

	fprintf(ftransform,"### Discriete Fourier Transform coeficients\n");
	fprintf(ftransform,"### k  k/Ndt  sum (real)sn*cos(2pi*k*n/N) (imaginary)sn*sin(2pi*k*n/N)\n");
	
	printf(" * Data origin file: \'%s\'\n\n",originfn);

      	printf("\n * Calculating the Power Spectrum and the Fourier Transform");

	skbar[0]=0;  // Real part
	skbar[1]=0; // Imaginary part

	k=-N/2;

	while(k<N/2.0)
	  {

	    /* Fourier transform : sum sn cos() + i* sum sn*sin() */

	    for(i=1;i<N;i++) // Real Part of Fourier Transform
	      {
		skbar[0]+=sn[i-1]*cos((2*M_PI*k*i)/N);
	      }
	    skbar[0]=skbar[0]/sqrt(N);

	    for(i=1;i<N;i++) // Imaginary part of Fourier Transform
	      {
		skbar[1]+=sn[i-1]*sin((2*M_PI*k*i)/N);
	      }
	    skbar[1]=skbar[1]/sqrt(N);

	    //printf("\n * %d %lf  Calculated: %lf",l,k, cabs(skbar));
	    
	    norm=pow(skbar[0],2)+pow(skbar[1],2);

	    fprintf(pspectrum,"%.6E\t%.6E\n",k/(N*dt),norm);
	    fprintf(ftransform,"%.6E\t%.6E\t%.6E\t%.6E\n",k,k/(N*dt),skbar[0],skbar[1]);
	    k=k+1;
	  }

	fclose(pspectrum);
	fclose(ftransform);

	printf("\n * Power spectrum and Fourier Transform Calculated!\n");
	pimpe(TITLESCN,25);
	exit(0);
	
} //End of Main Code
