/*
  DESCRIPTION: This Code
      
       AUTHOR: Daniel Mejia Raigosa
         DATE: 
      VERSION: 0.0.1
*/

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "commonroutines.c"

#define ARGS 4 // Number of Maximum Arguments (1 means no arguments!)
#define TITLESCN "Lyapunov Exponent"

main(int argc,char *argv[]) // for input arguments, remeber argv[0]=program name argv[1]= first argument and so on
{
 // This section is made for argument validation
	if( argc > ARGS )
	  {
		printf("Too many arguments supplied.\n");
	  }
	else if (argc < ARGS)
	  {
		printf("Some arguments expected.\n");
	  }

	double ts[MAXDATA],lyap,sum1,sum2;
        int j,k,l,m,n,N;  // int max value 2,147,483,647 use long int for more data
	char originfn[CHAPER],filename[CHAPER],fileext[CHAPER];
	time_t t1,t2,t3,t4;

	FILE *salida;

	characternumber(argv[1],CHAPER); //Confirm Character allowed values
	
	strcpy(originfn,argv[1]);   //Convert file names
	
	m=atoi(argv[2]);
	k=atoi(argv[3]);
	
	system("clear"); //clear screen
	pimpi(TITLESCN,25); //pimps start up

	(void)time(&t3); 
	



	datadquire(originfn,ts,&N);


	strcpy(filename,strtok(argv[1],".")); // separate data files
	strcpy(fileext,strstr(originfn,"."));
	strcpy(filename,strcat(filename,"-lyap")); //create a filename	
	strcat(filename,fileext);

	opendatafile(&salida,filename,"w");

	sum1=0;
	sum2=0;
	n=m;
	j=0;
	l=0;

	printf(" \n Calculating %d Exponents for %s\n",N,originfn);
	
	fprintf(salida,"### Lyapunov Exponent of data set %s\n",originfn);
	
	    while(l<N-k-1)
	      {
		n=m;
		
		while(n<N-k)
		  {
		    sum1=0;
		    sum2=0;
		    j=0;
		    while(j<m-1)
		      {
			sum1=pow(ts[l-j+k]-ts[n-j+k],2)+sum1;
			//printf(" suma1 %lf\n",sum1);
			j=j+1;
		      }
		    
		    sum2=log(sum1)+sum2;
		    //		printf(" suma2 %lf\n",sum2);
		    n=n+1;
		  } 
		
		lyap=sum2/(2.0*(N-k-m+1));
		fprintf(salida,"%d \t %lf \t %lf \t  %lf\n",l,sum1,sum2,lyap);
		//	printf(" \n Exponent for %d point calculated as %lf\n",l,lyap);
		l=l+1;
	      }



	printf("\n * Results saved on file \'%s\'\n",filename);
	    
	(void)time(&t4);
	
	printf("\n * It took %ld minutes to overall process \n",(t4-t3)/60);
	    
	pimpe(TITLESCN,25);
	exit(0);



} //End of Main Code
