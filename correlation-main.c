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
#include <time.h>

#include "commonroutines.c"

#define ARGS 3 // Number of Maximum Arguments (1 means no arguments!)
#define TITLESCN "Correlation Dimension" // Program Title
#define VER "0.1" // Version of the code
#define ANO "2011" // Date of code
#define MAXDATA 24600  //Maximum Data Input
#define CHAPER 20 // Number of allowed characters
#define epsilon 0.001 // the radius for neighbor separation
#define m 5 //Test

main(int argc,char *argv[]) // for input arguments, remeber argv[0]=program name argv[1]= first argument and so on
{
  /* This section is made for argument validation */
	if(argc > ARGS)
	  {
		printf("Too many arguments supplied.\n");
	        printf(" Usage\'$ %s file-with-data.ext\' embedding-dimension\n\n",argv[0]);
	  }
	else if (argc<ARGS)
	  {
	  
		printf("Some arguments expected.\n");
                printf(" Usage\'$ %s file-with-data.ext\' embedding-dimension\n\n",argv[0]);
	  }


	/* Here begins the interesting part */

//variable definition

	double csum,D,psum,c;
        int cont,N,i,j,dim;  // int max value 2,147,483,647 use long int for more data
	char dimarg[CHAPER],originfn[CHAPER],resp[0],filename[CHAPER],fileext[CHAPER];
	time_t t1,t2;


	FILE *origin;
	FILE *salida;
	
	characternumber(argv[1],CHAPER); //Confirm Character allowed values
	characternumber(argv[2],CHAPER);
	
	strcpy(originfn,argv[1]);   //Convert file names
	strcpy(dimarg,argv[2]);

	dim=atoi(dimarg);

	double x[MAXDATA][dim]; //Declare the emdending vector

	system("clear");
	pimpi(TITLESCN,25); //pimps start up
	
	printf("\n This tool will calculate the correlation sum \n And the correlation dimension...\n\n");
	printf(" * Data origin file: \'%s\'\n",originfn);
	
	/* Data Reading */

	(void) time(&t1);
	opendatafile(&origin,originfn,"r"); //open the file for reading	
	
	cont=0; //initialize counter
	i=0;
	  
	while(!feof(origin)) //checks if the end of file is reached
	  {
	    for(i=0;i<MAXDATA;i++)
	      {
		for(j=0;j<dim;j++)
		  {
		    fscanf(origin,"%lf\n",&x[i][i+j]);
		    printf(" * Reading line %d : x[%d][%d] %lf\n",i+j,i+1,j+1,x[i][i+j]);

		  }
		printf("\n");
	      }
	    
	  }
	N=i+j;
	fclose(origin);


	printf("\n * Total Readed Lines : %d\n",N);
	printf("\n * Calculating correlation sum now...\n");
	
       
	
	/* Making the correlation Sum */

	/*	
	csum=0;
	psum=0;
      	
	for(i=0;i<cont;i++)
	  {
	    for(j=i+1;j<N;j++)
	      {
	
		psum=heaviside(epsilon-fabs(x[i]-x[j])); // the argument of the sum
		csum=csum + psum;  // here the sum it's stored gradually
		//printf("\n * %d , %d The pre-correlation sum gives: %lf , %lf\n",i,j,psum,csum);
	      }

	  }
	//	here must be the total correlation sum

	//printf("\n * The Pre-correlation sum gives: %lf",csum);

	csum = (2.0/(N*(N-1.0)))*csum;

	(void) time(&t2);

	printf("\n * The correlation sum gives: %.19lf\n",csum);

	D=log(csum)/log(epsilon);

	printf("\n * The correlation dimension of data : %.19lf\n",D);
	printf("\n * It took %.3lf seconds to process the data",t2-t1);
	
	strcpy(filename,strtok(argv[1],".")); // separate data files
	strcpy(fileext,strstr(originfn,"."));
	
	strcpy(filename,strcat(filename,"-cor")); //create a filename
	strcat(filename,fileext);
	printf("\n\n\t[?] Save results to output file \'%s\'? [y/n]: ",filename);
	scanf("%c",&resp);

	if (resp[0]=='y')
	  {

	    opendatafile(&salida,filename,"w");


	    fprintf(salida,"\n/");
	    for(i=1;i<=25;i=i++)
	      {
		fprintf(salida,"-");
	      }
	    
	    fprintf(salida," %s ",TITLESCN);
	    
	    for(i=1;i<=25;i=i++)
	      {
		fprintf(salida,"-");
	      }
	    
	    fprintf(salida,"\\ \n");
	    
	    //	    fprintf(salida," * Data origin file: \'%s\'\n",originfn);
	    fprintf(salida,"\n * Total Readed Lines : %d\n",N);
	    fprintf(salida,"\n * The correlation sum gives: %.19lf\n",csum);
	    fprintf(salida,"\n * The correlation dimension of data : %.19lf\n",D);
	    fprintf(salida,"\n * It took %.3lf seconds to process the data",t2-t1);
	    

	    fprintf(salida,"\n\\");
	    for(i=1;i<=25;i=i++)
	      {
		fprintf(salida,"_");
	      }
	    
	    c = strlen(TITLESCN);
	    c = c + 2;
	    
	    for(i=1;i<=25+c;i=i++)
	      {
		fprintf(salida,"_");
	      }
	    
	    fprintf(salida,"/ \n");
	    
	  }
	*/
	pimpe(TITLESCN,25);

	exit(0);

	

} //End of Main Code
