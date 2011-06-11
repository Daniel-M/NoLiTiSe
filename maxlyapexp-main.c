/*
  DESCRIPTION: Algorithm Sprot Page 253
      
       AUTHOR: Daniel Mejia Raigosa
         DATE: 
      VERSION: 0.0.1
*/

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "commonroutines.c"

#define ARGS 3 // Number of Maximum Arguments (1 means no arguments!)
#define TITLESCN "Maximal Lyapunov Exponent"

main(int argc,char *argv[]) // for input arguments, remeber argv[0]=program name argv[1]= first argument and so on
{
 // This section is made for argument validation
	if( argc > ARGS )
	  {
		printf("Too many arguments supplied.\n");
		printf(" Usage\'$ %s file-with-data.ext\' dim \n",argv[0]);
		printf("\n \t dim - Embedding Dimension\n \t t - Time for lyapunov exponent evaluation\n");
	  }
	else if (argc < ARGS)
	  {
		printf("Some arguments expected.\n");
		printf(" Usage\'$ %s file-with-data.ext\' dim \n",argv[0]);
		printf("\n \t dim - Embedding Dimension\n \t t - Time for lyapunov exponent evaluation\n");
	  }

	double ts[MAXDATA],lyap,sum1,sum2;
        int j,k,l,m,n,N;  // int max value 2,147,483,647 use long int for more data
	char originfn[CHAPER],filename[CHAPER],fileext[CHAPER];
	time_t t1,t2,t3,t4;

	FILE *salida;

	characternumber(argv[1],CHAPER); //Confirm Character allowed values
	
	strcpy(originfn,argv[1]);   //Convert file names
	
	m=atoi(argv[2]);
	
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

	
	for(l=0;l<(N-k-m-1);l++)
	    {
		n=m;
		sum2=0;
		
		for(n=m;n<(N-k);n++)
		  {
		    sum1=0;
		    
		    for(j=0;j<m;j++)
		      {
			sum1=pow(ts[l-j+k]-ts[n-j+k],2)+sum1;
			j=j+1;

		      }
		    
		    sum2+=log(sum1);
		    
		  } 
		
		lyap=sum2/(2.0*(N-k-m+1));

		fprintf(salida,"%d \t %lf \t %lf \t  %lf\n",l,sum2,lyap);
		//	printf(" \n Exponent for %d point calculated as %lf\n",l,lyap);
		l=l+1;
	       }



	printf("\n * Results saved on file \'%s\'\n",filename);
	    
	(void)time(&t4);
	
	printf("\n * It took %ld minutes to overall process \n",(t4-t3)/60);
	    
	pimpe(TITLESCN,25);
	exit(0);



} //End of Main Code
