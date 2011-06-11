/*
  FILE NAME:   lifit-main.c
  DESCRIPTION: Calculates the mean, the variance and the autocorrelation
               function C(t) for various lags 't' in the range 1 to argv[2]
	       Usage $./statistical-main.out file-with-data.ext max-tau-separation.
  AUTHOR:      Daniel Mejia Raigosa
  DATE:        24, May 2011
  VERSION:     2.1.1 
*/

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

#include "commonroutines.c"

#define ARGS 2 // Number of Maximum Arguments (1 means no arguments!)
#define TITLESCN "Linear Fitting of Data" // Program Title
#define VER "1.2.1" // Version of the code
#define ANO "2011" // Date of code
#define MINT 1 //Minimal tau
#define PASO 1  //Step of tau
//#define MAXT 200 //Max tau


void datadquire2d(char *filename,double x[],double y[],int *Nmax)
{
  char info1[25],info2[25];
  int N,i;
  FILE *filedata;

  opendatafile(&filedata,filename,"r"); //open the file for reading	
  
  i=0;//initialize counter
  N=0;

  while(!feof(filedata)) //checks if the end of file is reached
    {  
      N=N+1;
      fscanf(filedata,"%s %s\n",&info1,&info2);
      x[i]=atof(info1);
      y[i]=atof(info2);
      //      printf(" * Reading line %d : x[%d] %.10lf\n",N,i,j+1,x[i]);
      i=i+1;
    }
  *Nmax=N;
  fclose(filedata);
  //  printf(" * Total Readed Lines %d\n",N);
}


  /* **************************  MAIN FUNCTION ************************** */


main(int argc,char *argv[]) // for input arguments, remeber argv[0]=program name argv[1]= first argument and so on
{
  /* This section is made for argument validation */
	if(argc > ARGS)
	  {
	    printf("Too many arguments supplied.\n");
	    printf(" Usage\'$ %s file-with-data.ext\' max-tau-separation\n\n",argv[0]);
	    exit(1);
	  }
	else if (argc<ARGS)
	  {
	    
	    printf("Some Arguments Expected\n");
	    printf(" Usage\'$ %s file-with-data.ext\' max-tau-separation\n\n",argv[0]);
	    exit(1);
 	  }
	
	/* Here begins the interesting part */



	//variable definition

	double x[MAXDATA],y[MAXDATA],sigma2[MAXDATA],mean,variance;
	double delta,a,b,covab,s,sx,sy,sxx,sxy,sigma2a,sigma2b;
        int cont,N,MAXT,tau;  // int max value 2,147,483,647 use long int for more data
	char originfn[CHAPER],filename[CHAPER],fileext[CHAPER];

	FILE *salida;
	
	characternumber(argv[1],CHAPER); //Confirm Character allowed values

	strcpy(originfn,argv[1]);   //Convert file names

       	system("clear"); //clear screen
	pimpi(TITLESCN,25); //pimps start up


	    printf("\n This tool will calculate some statistical properties...\n\n");
	    printf(" * Linear Fitting of Data File: \'%s\'\n",originfn);

	    datadquire2d(originfn,x,y,&N);
	    
	    printf(" * Total Readed Data Lines : %d \n\n",N);



	    /* Calculation of the Mean and the Variance sigma squared */


	    printf(" * Making Calculations... \n",N);

	    mean=0.0;
	    variance=0.0;

	    for(cont=0;cont<N;cont=cont+2)
	      {
		 mean+=y[cont]+y[cont+1];
	      }

	    mean=mean/N;
	    
	    for(cont=0;cont<N;cont++)
	      {
		sigma2[cont]=pow(y[cont]-mean,2);
		variance=sigma2[cont] + variance;
	      }

	    variance=variance/(N-1);

	    
	    for(cont=0;cont<N;cont++)
	      {
		s+=1/pow(sigma2[cont],2);
	      }

	    for(cont=0;cont<N;cont++)
	      {
		sx+=x[cont]/pow(sigma2[cont],2);
	      }

	    for(cont=0;cont<N;cont++)
	      {
		sxx+=pow(x[cont],2)/pow(sigma2[cont],2);
	      }

	    for(cont=0;cont<N;cont++)
	      {
		sy+=y[cont]/pow(sigma2[cont],2);
	      }

	    for(cont=0;cont<N;cont++)
	      {
		sxy+=(x[cont]*y[cont])/pow(sigma2[cont],2);
	      }

	    delta=s*sxx-pow(sx,2);
	    
	    b= (sxx*sy-sx*sxy)/delta;

	    a= (s*sxy-sx*sy)/delta;

	    covab=-sx/delta;

	    sigma2a=sxx/delta;
	    sigma2b=s/delta;

	    /* Now Calculate */


	    printf(" * y-Mean = %.6E\n * Mean y-Variance = %.6E\n\n",originfn,mean,variance);
	    printf(" [!] Fitted to y=Ax+B \n\n * A = %.6E \t B= %.6E\n\n",a,b);
	    printf(" * Variance of A = %.6E \n * Variance of B = %.6E\n",sigma2a,sigma2b);
	    printf(" * Covariance of AB = %.6E \n",covab);

	    strcpy(filename,strtok(argv[1],".")); // separate data files
	    strcpy(fileext,strstr(originfn,"."));
	    
	    strcpy(filename,strcat(filename,"-linfit")); //create a filename
	   
	    strcat(filename,fileext);
	    opendatafile(&salida,filename,"w");

	    fprintf(salida,"### Linear Fitting of data file  %s \n### Total y Mean = %.6E\n### Mean y Variance = %.6E\n",originfn,mean,variance);
	    fprintf(salida,"### Fitted to y=Ax+B \n### A = %.6E \t B= %.6E\n",a,b);
	    fprintf(salida,"### Variance of A = %.6E \n### Variance of B = %.6E \n",sigma2a,sigma2b);
	    fprintf(salida,"### Covariance of AB = %.6E \n",covab);

	    for(cont=0;cont<N;cont++)
	      {
		fprintf(salida,"%lf %lf\n",x[cont],a*x[cont]+b);
	      }
	   

	    fclose(salida);
	    	    
	    printf("\n * Results saved on file \'%s\'",filename);
	    
	    pimpe(TITLESCN,25);
	    exit(0);

	      
} //End of Main Code
