/*
  FILE NAME:   correlation-main.c
  DESCRIPTION: This Code calculates the correlation dimention of the data
               stored on a given file passed by arguments on argv[1]
      
  AUTHOR:      Daniel Mejia Raigosa
  DATE:        24, April 2011
  VERSION:     0.1
*/

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "commonroutines.c"

#define ARGS 2 // Number of Maximum Arguments (1 means no arguments!)
#define TITLESCN "Correlation Dimention" // Program Title
#define VER "0.1" // Version of the code
#define ANO "2011" // Date of code
#define MAXDATA 10000  //Maximum Data Input
#define CHAPER 20 // Number of allowed characters
#define epsilon 0.001 // the radius for neighbor separation

main(int argc,char *argv[]) // for input arguments, remeber argv[0]=program name argv[1]= first argument and so on
{
  /* This section is made for argument validation */
	if(argc > ARGS)
	  {
		printf("Too many arguments supplied.\n");
	        printf(" Usage\'$ %s file-with-data.ext\'\n\n",argv[0]);
	  }
	else if (argc<ARGS)
	  {
	  
		printf("Some arguments expected.\n");
                printf(" Usage\'$ %s file-with-data.ext\'\n\n",argv[0]);
	  }


	/* Here begins the interesting part */

//variable definition

	double csum,D,psum,x[MAXDATA];
        int cont,N,i,j;  // int max value 2,147,483,647 use long int for more data
	char originfn[CHAPER];

	FILE *origin;
	
	characternumber(argv[1],CHAPER); //confirm argument allowed number on 'ommonroutines.c'
	strcpy(originfn,argv[1]); //copy file name of data origin

	system("clear");
	pimpi(TITLESCN,25); //pimps start up
	
	printf("\n This tool will calculate the correlation sum \n And the correlation dimension...\n\n");
	printf(" * Data origin file: \'%s\'\n",originfn);
	
	/* Data Reading */

	opendatafile(&origin,originfn,"r"); //open the file for reading	
	
	cont=0; //initialize counter
	while(!feof(origin)) //checks if the end of file is reached
	  {
	
	    printf(" * Reading line %d\n",cont);
	    fscanf(origin,"%f\n",&x[cont]);
	    cont=cont+1;
	  }
	fclose(origin);
	
	printf("\n * Total Readed Lines : %d\n",cont);
	printf("\n * Calculating correlation Sum Now...\n");
	
	/* Making the correlation Sum */
	
	csum=0;
	psum=0;
      	
	for(i=0;i<cont;i++)
	  {
	    for(j=i+1;j<cont;j++)
	      {
	
		psum=heaviside(epsilon-fabs(x[i]-x[j])); // the argument of the sum
		csum=csum + psum;  // here the sum it's stored gradually
		printf("\n * %d , %d The pre-correlation sum gives: %lf , %lf\n",i,j,psum,csum);
	      }

	  }
	//	here must be the total correlation sum
	
	csum = (2.0/(cont*(cont-1)))*csum;

	printf("\n * The correlation sum gives: %lf\n",csum);

	pimpe(TITLESCN,25);

	exit(0);

	

} //End of Main Code
