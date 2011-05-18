/*
  FILE NAME:   correlation-main.c
  DESCRIPTION: This Code calculates the correlation dimention of the data
               stored on a given file passed by arguments on argv[1], and
	       with his correlation dimension passed as argv[2].
	       The Maximum data input is 25000, it can be modified on the
	       #define MAXDATA
      
  AUTHOR:      Daniel Mejia Raigosa
  DATE:        17, May 2011
  VERSION:     2.0.1
*/

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

#include "commonroutines.c"

#define ARGS 3 // Number of Maximum Arguments (1 means no arguments!)
#define TITLESCN "Correlation Dimension" // Program Title
#define VER "2.0.1" // Version of the code
#define ANO "2011" // Date of code
#define MAXDATA 4100  //Maximum Data Input
#define CHAPER 20 // Number of allowed characters
#define PASO 0.05 // The minimum radius for neighbor separation
#define LIMITE 10.0 // The Maximum radios for neighbor separation
#define MAXEMB 20 // Maximum Embedding Dimension


double corsum(double data[],int size, int dim, double e)
{
  /** i recorre la SdT con j un paso más adelante como
  dice la ecuación
      C(e)=(2/(N(N-1)))Sum_i Sum_{j=i+1}  
  */
  double csum,norm=0,sum=0;
  int i,j=1,d;
  for(i=0;i<size;i+=dim)
    {
      for(j=i+dim;j<size;j+=dim)
	{
	  for(d=0;d<dim;d++){
	    norm+=pow(data[i+d]-data[j+d],2);
	    //printf("\n data[%d] %lf , data[%d] %lf\n",i+d,data[i+d],j,data[j+d]);
	   
	  }
	  sum+=heaviside(e-norm);
	  // printf("\n norm= %lf \t sum = %lf",norm,sum);
	  norm=0;
	}
    }
  csum=( 2.0/(size*(size-1.0)) )*sum;
  //printf("sum = %lf size=%d \t csum=%.19lf",sum,size,csum );
  return csum;
}


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
	    printf(" Usage\'$ %s file-with-data.ext\' embedding-dimension\n",argv[0]);
	    printf(" If embedding-dimension = 0 the program makes various embeddings on \n file-with-data\n\n");
	  }
	else if (argc<ARGS)
	  {
	    
	    printf("Some arguments expected.\n");
	    printf(" Usage\'$ %s file-with-data.ext\' embedding-dimension\n",argv[0]);
	    printf(" If embedding-dimension = 0 the program makes various embeddings on \n file-with-data\n\n");           
 	  }
	
	/* Here begins the interesting part */



	//variable definition

	double D,psum,c,ns,epsilon;
        int cont,N,i,imax,j,jmax,dim;  // int max value 2,147,483,647 use long int for more data
	char dimarg[CHAPER],originfn[CHAPER],resp[0],filename[CHAPER],fileext[CHAPER];
	time_t t1,t2,t3,t4;

	double x[MAXDATA]; //Declare the emdending vector



	FILE *salida;
	
	characternumber(argv[1],CHAPER); //Confirm Character allowed values
	characternumber(argv[2],CHAPER);
	
	strcpy(originfn,argv[1]);   //Convert file names
	strcpy(dimarg,argv[2]);

	dim=atoi(dimarg);
	
	double csum;
	
	system("clear"); //clear screen
	pimpi(TITLESCN,25); //pimps start up

	/* ************************** IF NO DIMENSION GIVEN ************************** */

	if (dim==0)
	  {
	    printf("\n This tool will calculate the correlation sum \n And the correlation dimension...\n\n");
	    printf(" * Data origin file: \'%s\'\n\n",originfn);
	    printf(" [!] I'll make different embeddings and then calculate the convergence\n   of the correlation sum for various epsilon values\n\n");
	    printf(" * Epsilon values range : %lf to %lf\n",PASO,LIMITE);
	    printf(" * Epsilon steps: %lf\n\n",PASO);

	    (void)time(&t3); 

	    datadquire(originfn,x,&N);
	    
	    printf("\n * Total Readed Data Lines : %d \n",N);

	    dim=1;

	    strcpy(filename,strtok(argv[1],".")); // separate data files
	    strcpy(fileext,strstr(originfn,"."));
	    
	    strcpy(filename,strcat(filename,"-cor")); //create a filename
	   
	    strcat(filename,fileext);
	    opendatafile(&salida,filename,"w");

	    while(dim<MAXEMB+1)
	      {
		(void) time(&t1);
		printf("\n * Making an embedding of %d of %d \n",dim,MAXEMB);
		printf("\n * Calculating correlation sum now...\n \t It will took a while, be patient...\n");
		fprintf(salida,"### Embedding dimension = %d\n",dim);
		epsilon=LIMITE;
		


		while (epsilon>PASO)
		  {
		    csum=corsum(x,N,dim,epsilon);
		    
		    D=-log(csum)/log(epsilon);

		    fprintf(salida,"%lf  %.19lf %.19lf\n",epsilon,csum,D);

		    //printf("\n * Correlation sum now: %.19lf\n",csum);

		    epsilon=epsilon-PASO;
		  }
		fprintf(salida,"\n");
		dim=dim+1;
		
		(void)time(&t2); 
		
		printf("\n * It took me %ld seconds to process the data",(t2-t1));
	      }
	    
	    (void)time(&t4); 
	    printf("\n * It took %ld minutes to overall process \n",(t4-t3)/60);
	    pimpe(TITLESCN,25);
	    exit(0);
	  }


	/* **************************  DIMENSION GIVEN ************************** */

	else
	  {
	printf("\n This tool will calculate the correlation sum \n And the correlation dimension...\n\n");
	printf(" * Data origin file: \'%s\'\n\n",originfn);
	printf(" * Embedding dimension: %d\n",dim);
	printf(" [!] I'll calculate the convergence of the correlation sum for various epsilon values...\n\n");
	printf(" * Epsilon values range : %lf to %lf\n",PASO,LIMITE);
	printf(" * Epsilon steps: %lf\n\n",PASO);
	

	/* Data Reading */
	

	
       
	    /* Calculate vector the difference */

	/*
	    imax=i;
	    jmax=j;
	    // N=0;

	    
	    for(i=0;i<imax;i++)
	      {

		for(j=i+1;j<imax;j++)
		  {	   
		    ns=0;

		    for(cont=0;cont<jmax;cont++)
		      {
		
			aij[cont]=x[i][cont]-x[j][cont];
			
			ns=pow((aij[cont]),2)+ns;
			//printf("\n * aij[%d]= %lf  aij[%d]^2= %lf ns=%lf  - %d - %d",cont,aij[cont],cont,pow(aij[cont],2),ns,i,j);
					
		      }

		    nor[i+j-1]=sqrt(ns);
		    // printf("\n * nor[%d]= %lf",i+j-1,nor[i+j-1]);
		  }
		//		N=N+1;
	      }

	    // printf("\n * nor[%d]= %lf - %d - %d",i+j,nor[i+j],i,j);

		strcpy(filename,strtok(argv[1],".")); // separate data files
		strcpy(fileext,strstr(originfn,"."));
		
		strcpy(filename,strcat(filename,"-cor")); //create a filename
		strcat(filename,fileext);
		opendatafile(&salida,filename,"w");
	*/
		/* Calculate the correlation Sum */
	/*
	    epsilon=PASO;
	    
	    while(epsilon<LIMITE)
	      {
	    
		
		csum=0;
		psum=0;
		
		
		for(i=0;i<imax;i++)
		  {
		    for(j=i+1;j<imax;j++)
		      {
			
			psum=heaviside(epsilon-nor[i+j]); // the argument of the sum
			csum=csum + psum;  // here the sum it's stored gradually
			//printf("\n * %d , %d - psum = H(e-nor[%d])= H(%lf - %lf) \n\t  = H(%lf) = %lf - csum= %lf\n",i,j,i+j,epsilon,nor[i+j],epsilon-nor[i+j],psum,csum);
		      }
		    
		  }
		//	here must be the total correlation sum
		
		//printf("\n * The Pre-correlation sum gives: %lf",csum);
		
		csum = (2.0/(N*(N-1.0)))*csum;
		
		
		
		//printf("\n * The correlation sum gives: %.19lf\n",csum);
		
		D=log(csum)/log(epsilon);
		
		//	printf("\n * The correlation dimension of data : %.19lf\n",D);
		
		//(void) time(&t2);
		
		//printf("\n * It took %.3lf %u seconds to process the data",(t2-t1),t2-t1);
		

		fprintf(salida,"%lf  %.19lf  %.19lf\n",epsilon,csum,D);		
		//		printf("\n * epsilon= %lf - csum= %.19lf - D= %.19lf",epsilon,csum,D);

		epsilon=epsilon + PASO;
	      }
	    fclose(salida);

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
	      }
	      //} 
*/
	  }
	

	


		pimpe(TITLESCN,25);
		
		exit(0);
	      
	      
} //End of Main Code
