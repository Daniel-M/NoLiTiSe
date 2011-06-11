/*
  FILE NAME:   localslopes-main.c
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

#define ARGS 3 // Number of Maximum Arguments (1 means no arguments!)
#define TITLESCN "Linear Fitting of Data" // Program Title
#define VER "1.2.1" // Version of the code
#define ANO "2011" // Date of code
#define MINT 1 //Minimal tau
#define PASO 1  //Step of tau
#define INTERV 5 // inverval for linear fit
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
      //printf(" * Reading line %d : %.6E %.6E\n",N,x[i],y[i]);
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

	double x[MAXDATA],y[MAXDATA],A[MAXDATA],B[MAXDATA],sigma2[MAXDATA],mean,variance;
	double delta,a,b,covab,s,sx,sy,sxx,sxy,sigma2a,sigma2b;
        int cont,N,MAXT,tau,interval,k;  // int max value 2,147,483,647 use long int for more data
	char originfn[CHAPER],filename[CHAPER],fileext[CHAPER];

	FILE *salida;
	FILE *Mean;
	FILE *local;
	
	characternumber(argv[1],CHAPER); //Confirm Character allowed values

	strcpy(originfn,argv[1]);   //Convert file names
	
	interval=atoi(argv[2]);
	
       	system("clear"); //clear screen
	pimpi(TITLESCN,25); //pimps start up


	printf("\n This tool will calculate some statistical properties...\n\n");
	printf(" * Linear Fitting of Data File: \'%s\'\n",originfn);
	
	datadquire2d(originfn,x,y,&N);
	
	printf(" * Total Readed Data Lines : %d \n\n",N);
	
	
	
	/* Calculation of the Mean and the Variance sigma squared */
	
	
	printf(" * Making Calculations... \n\n",N);
	printf(" [!] Fitting to y=Ax+B \n\n");
	
	strcpy(filename,strtok(argv[1],".")); // separate data files
	strcpy(fileext,strstr(originfn,"."));
	
	strcpy(filename,strcat(filename,"-winlinfit")); //create a filename
	
	strcat(filename,fileext);
	opendatafile(&salida,filename,"w");
	
	fprintf(salida,"### Local slopes of Data File  %s \n",originfn);
	fprintf(salida,"### Fitted to y=Ax+B \n");
	fprintf(salida,"###   A \t  B \t  sigma2_A \t  sigma2_B\n");
	
	tau=0;
	k=0;
	
	while(tau<N)
	  {
	    mean=0.0;
	    variance=0.0;
	    
	    for(cont=tau;cont<tau+interval;cont=cont+2)
	      {
		mean+=y[cont]+y[cont+1];
	      }
	    
	    mean=mean/interval;
	    
	    for(cont=tau;cont<tau+interval;cont++)
	      {
		sigma2[cont]=pow(y[cont]-mean,2);
		variance=sigma2[cont] + variance;
	      }
	    
	    variance=variance/(interval-1);
	    
	    
	    for(cont=tau;cont<tau+interval;cont++)
	      {
		s+=1/pow(sigma2[cont],2);
	      }
	    
	    for(cont=tau;cont<tau+interval;cont++)
	      {
		sx+=x[cont]/pow(sigma2[cont],2);
	      }
	    
	    for(cont=tau;cont<tau+INTERV;cont++)
	      {
		sxx+=pow(x[cont],2)/pow(sigma2[cont],2);
	      }
	    
	    for(cont=tau;cont<tau+interval;cont++)
	      {
		sy+=y[cont]/pow(sigma2[cont],2);
	      }
	    
	    for(cont=tau;cont<tau+interval;cont++)
	      {
		sxy+=(x[cont]*y[cont])/pow(sigma2[cont],2);
	      }
	    
	    delta=s*sxx-pow(sx,2);
	    
	    b = (sxx*sy-sx*sxy)/delta;
	    
	    a = (s*sxy-sx*sy)/delta;
	    
	    A[k]=a;
	    
	    covab=-sx/delta;
	    
	    sigma2a=sxx/delta;
	    sigma2b=s/delta;
	    
	    /* Now Calculate */
	    /*
	      printf("\n * tau = %d \t Interval = %d\n",tau,interval);
	      
	      printf(" * y-Mean = %.6E\n * Mean y-Variance = %.6E\n\n",originfn,mean,variance);
	    */
	    printf(" * A = %.6E \t Variance of A = %.6E\n\n",a,sigma2a);
	    
	    fprintf(salida,"%.6E\t%.6E\t%.6E\t%.6E\n",a,b,sigma2a,sigma2b);
	    
	    tau=tau+interval;
	    k=k+1;
	  }
	
	fclose(salida);
	
	//*************************************************************

	a=0;
	
	for(cont=0;cont<N/interval+1;cont++)
	  {
	    a+=A[cont];
	    //printf("\n\n [!] The mean slope is %lf + %lf,  %d + %d\n\n",a,A[cont],cont,N/interval);
	  }
	
	a=a/(N/interval+1);
	variance=0;
	
	for(cont=0;cont<N/interval+1;cont++)
	  {
	    sigma2[cont]=pow(A[cont]-a,2);
	    variance=sigma2[cont] + variance;
	  }
	
	variance=variance/(N/interval);
	
	sigma2a=variance;

	printf("\n\n [!] The mean slope is %.6E - S.E.M = %.6E\n\n",a,sqrt(variance/(N/interval)));
	

	printf("\n * Window of %d points line-fiting saved on file \'%s\'",interval,filename);

	b=0;
	
	for(cont=0;cont<N/interval+1;cont++)
	  {
	    b+=B[cont];
	    //printf("\n\n [!] The mean slope is %lf + %lf,  %d + %d\n\n",a,A[cont],cont,N/interval);
	  }
	
	b=b/(N/interval+1);

	variance=0;
	
	for(cont=0;cont<N/interval+1;cont++)
	  {
	    sigma2[cont]=pow(B[cont]-a,2);
	    variance=sigma2[cont] + variance;
	  }
	
	variance=variance/(N/interval);

	sigma2b=variance;

	strcpy(filename,strtok(argv[1],".")); // separate data files
	strcpy(fileext,strstr(originfn,"."));
	
	strcpy(filename,strcat(filename,"-meanslope")); //create a filename
	
	strcat(filename,fileext);
	opendatafile(&Mean,filename,"w");
	
	fprintf(Mean,"### Linear Fitting of data file  %s \n");
	fprintf(Mean,"### Fitted to y=Ax+B \n### A = %.6E \t B= %.6E\n",a,b);
	fprintf(Mean,"### Variance of A = %.6E \n### Variance of B = %.6E \n",sigma2a,sigma2b);
	fprintf(Mean,"### x\ty\n",sigma2a,sigma2b);

	for(cont=0;cont<N;cont++)
	  {
	    sx=a*x[cont]-b;
	    fprintf(Mean,"%lf\t%lf\n",x[cont],sx);
	  }
	   
	
	printf("\n * Mean Linear Fitting saved on\'%s\'",filename);

	fclose(Mean);	

	//**********************************************************

	strcpy(filename,strtok(argv[1],".")); // separate data files
	strcpy(fileext,strstr(originfn,"."));
	
	strcpy(filename,strcat(filename,"-slopes")); //create a filename
	
	strcat(filename,fileext);
	opendatafile(&local,filename,"w");
	
	fprintf(local,"### Local Slopes m=(Y_{i+1}-Y_{i})/(X_{i+1}-X_{i}) of data file \n### \'%s\'\n",argv[1]);

	sx=0;
	sxy=0;

	for(cont=0;cont<N;cont++)
	  {
	    sx=(y[cont+1]-y[cont])/(x[cont+1]-x[cont]);
	    sxy+=sx;
	    fprintf(local,"%.6E\n",sx);
	  }
	   
	//	sxy=sxy/(N-1);
	
	fprintf(local,"### Mean = %.6E , %.6E",sxy/(N-1),sxy/(N));
	printf("\n\n * Local slopes saved on\'%s\'",filename);

	fclose(local);	

	pimpe(TITLESCN,25);
	exit(0);
	
	
} //End of Main Code
