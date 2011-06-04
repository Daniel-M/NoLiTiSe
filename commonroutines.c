 /*
  FILE NAME:   commonroutines.c
  DESCRIPTION: This code consist of a collection of useful self-made routines
      
  AUTHOR:      Daniel Mejia Raigosa
  DATE:        17, May 2011
  VERSION:     2.1.1
*/

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

#define MAXDATA 10000  //Maximum Data Input
#define CHAPER 20 // Number of allowed characters


//***************************************************************************

// Aks a 'double' value on the range [xmin,xmax] by the message mensaje[200]
double askvalue(char mensaje[200], double xmin, double xmax) 
{
    double x;
    
    do
      {
	printf("%s",mensaje);
	scanf("%lf",&x);
	
	if(x<xmin || x>xmax)
	  {    
	    printf("\n\tError!!!\n\tThe input value is out of the allowed range [%lf,%lf] \n",xmin,xmax);

	  }
      }while (x<xmin || x>xmax);

    return x;
   
}//end ask value

//***************************************************************************

 // Pimp program on the start up
// usage pimpi(program name,some in number)
void pimpi(char titulo[40],int n)
{
    double i;
    printf("\n/");
    for(i=1;i<=n;i=i++)
      {
	printf("-");
      }

    printf(" %s ",titulo);

    for(i=1;i<=n;i=i++)
      {
	printf("-");
      }
    
    printf("\\ \n");

}//end pimpi

//********************************************************************

 // Pimps program on exit, used whit pimpi and as pimpi
void pimpe(char titulo[40],int n) 
{
    double i,t;
    printf("\n\\");
    for(i=1;i<=n;i=i++)
      {
	printf("_");
      }

    t = strlen(titulo);
    t = t + 2;

    for(i=1;i<=n+t;i=i++)
      {
	printf("_");
      }
    
    printf("/ \n");

}//end pimpe


//********************************************************************


void opendatafile(FILE **filepointer,char *filename,char *option)
{
 
/* This Function serves as a file handler wich evitates crashes
  this function is a kind of remplacement of :

  origin=fopen(originfn,"r"); // open data origin 

  if (origin==NULL){   //handle errors
    system("clear");
    printf("===============FATAL ERROR===================="); 
    printf("\n An Error has ocurred during file reading !!\n");
    printf(" The file \'%s\' seems to be Unexistent!!\n Exiting...\n",argv[1]);
    printf("==============================================\n");
    exit(1);
  }

*/

/* usage opendatafile(&filepointer,filename,option["r","w"...])*/

*filepointer=fopen(filename,option); // open file
 if (*filepointer==NULL) //handle reading error 
    {   
    system("clear");
    printf("===============FATAL ERROR===================="); 
    printf("\n An Error has ocurred during file reading !!\n");
    printf(" The file \'%s\' seems to be Unexistent!!\n Exiting...\n",filename);
    printf("==============================================\n");
    exit(1);
  }
}


//*************************************************************************


/* This function Test the correct use of the character number */

void characternumber(char *caracter,int CHAPERA)
{
  int longitud;
  longitud=strlen(caracter);
  if (longitud>CHAPERA)
    {
    system("clear");
    printf("===============FATAL ERROR======================="); 
    printf("\n Max input arguments character allowed are %d\n",CHAPERA);
    printf(" The argument %s \n character lenght was %d !!\n",caracter,longitud);
    printf(" Please use less charactares to success.\n Exiting...\n");
    printf("=================================================\n");
    exit(1);
    }
}


//*************************************************************************


int heaviside(double x)
{

  /* this is the heaviside step function
    
          /
          | 1  if x >=0
    H(x)=<
          | 0  if x < 0
   	  \
  */
  if(x>=0)
    {
      return 1;
    }
  else if(x<0)
    {
      return 0;
    }
}


//***************************************************************************


void datadquire(char *filename,double x[],int *Nmax)
{
  char info[25];
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
      fscanf(filedata,"%s\n",&info);
      x[i]=atof(info);
      printf(" * Reading line %d : x[%d] %.10lf\n",N,i,j+1,x[i]);
      i=i+1;
    }
  *Nmax=N;
  fclose(filedata);
}


//***************************************************************************


