/*
  FILE NAME:   statistical-main.c
  DESCRIPTION: Calculates the mean, the variance and the autocorrelation
               function C(t) for various lags 't' in the range 1 to argv[2]
	       Usage $./statistical-main.out file-with-data.ext max-tau-separation.
  AUTHOR:      Daniel Mejia Raigosa
  DATE:        24, May 2011
  VERSION:     1.1.2 
*/

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

#include "commonroutines.c"

#define ARGS 3 // Number of Maximum Arguments (1 means no arguments!)
#define TITLESCN "Statistical Properties" // Program Title
#define VER "1.1.2" // Version of the code
#define ANO "2011" // Date of code
#define MAXDATA 4100  //Maximum Data Input
#define CHAPER 20 // Number of allowed characters

#define MINT 1 //Minimal tau
#define PASO 1  //Step of tau
//#define MAXT 200 //Max tau


void datadquire(char *filename,double x[],int *Nmax)
{
  int N,i,j,cont;
  FILE *filedata;

  opendatafile(&filedata,filename,"r"); //open the file for reading	
  cont=0; //initialize counter
  i=0;
  j=0;
  N=0;
  while(!feof(filedata)) //checks if the end of file is reached
    {
     	  N=N+1;
	  fscanf(filedata,"%lf\n",&x[i]);
	  (" * Reading line %d : x[%d] %lf\n",N,i,j+1,x[i]);
     
      i=i+1;
    }
  *Nmax=N;
  fclose(filedata);
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

	double x[MAXDATA],autocor,mean,variance;
        int cont,N,i,MAXT,tau;  // int max value 2,147,483,647 use long int for more data
	char originfn[CHAPER],filename[CHAPER],fileext[CHAPER];

	FILE *salida;
	
	characternumber(argv[1],CHAPER); //Confirm Character allowed values

	strcpy(originfn,argv[1]);   //Convert file names

	MAXT=atoi(argv[2]);
	
	system("clear"); //clear screen
	pimpi(TITLESCN,25); //pimps start up


	    printf("\n This tool will calculate some statistical properties...\n\n");
	    printf(" * Data origin file: \'%s\'\n",originfn);

	    datadquire(originfn,x,&N);
	    
	    printf(" * Total Readed Data Lines : %d \n\n",N);



	    /* Calculation of the Mean and the Variance sigma squared */


	    printf(" * Calculating mean value and variance now... \n",N);

	    mean=0.0;
	    variance=0.0;

	    for(cont=0;cont<N;cont=cont+2)
	      {
		 mean=x[cont]+x[cont+1]+mean;
		variance=pow(x[cont]-mean,2) + variance;
		 
	      }

	    mean=mean/N;
	    variance=variance/(N-1);

	    printf("\n * The calculated mean is: %.6lf\n",mean);  

	    printf(" * The calculated variance is: %.6lf\n",variance);
	    

	    /* Now Calculate the Autocorrelation function */


	    printf("\n * Calculating the autocorrelation function now for various lags \'t\'...\n");
	    printf(" * \'t\' values range : %d to %d \t \'t\' step = %d\n",MINT,MAXT,PASO);

	    strcpy(filename,strtok(argv[1],".")); // separate data files
	    strcpy(fileext,strstr(originfn,"."));
	    
	    strcpy(filename,strcat(filename,"-autocor")); //create a filename
	   
	    strcat(filename,fileext);
	    opendatafile(&salida,filename,"w");

	    fprintf(salida,"### Atocorrelation sum of %s \n### Total Mean = %lf\n### Total Variance = %lf\n### Tau    C(Tau)\n",originfn,mean,variance);

	    tau=MINT;

	    while(tau<MAXT+1)
	      {
		i=0;
		autocor=0.0;
		variance=0.0;

		while(i<(N-tau))
		  {
		    autocor=(x[i]-mean)*(x[i+tau]-mean)+autocor;
		    variance=pow(x[i]-mean,2) + variance;
		    i=i+1;
		  }
		
		variance=variance/(N-tau);
		autocor=autocor/variance;

		fprintf(salida,"%d\t%lf\n",tau,autocor);
		tau=tau+PASO;
	      }

	    fclose(salida);
	    	    
	    printf("\n * Results saved on file \'%s\'",filename);
	    
	    pimpe(TITLESCN,25);
	    exit(0);

	      
} //End of Main Code
