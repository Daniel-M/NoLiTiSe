 /*
  FILE NAME:   commonroutines.c
  DESCRIPTION: This code consist of a collection of useful self-made routines
      
  AUTHOR:      Daniel Mejia Raigosa
  DATE:        20, April 2011
  VERSION:     1.1
*/

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

// pide un valor tomando en cuenta el mensaje y el intervalo [xmin,xmax] valida entradas uso var = pidevalor(...)
double askvalue(char mensaje[200], double xmin, double xmax) 
{
    double x;
    
    do
      {
	printf("%s",mensaje);
	scanf("%lf",&x);
	
	if(x<xmin || x>xmax)
	  {
	    printf("Error en el Valor Ingresado,\n Verifique que si este en el rango Valido! [%lf,%lf] \n",xmin,xmax);

	  }
      }while (x<xmin || x>xmax);

    return x;
   
}//end ask value

 // adorna ingresando el titulo y numero de caracteres del marco
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

 // adorna ingresando el titulo y numero de caracteres del marco
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
  if (*filepointer==NULL){   //handle errors
    system("clear");
    printf("===============FATAL ERROR===================="); 
    printf("\n An Error has ocurred during file reading !!\n");
    printf(" The file \'%s\' seems to be Unexistent!!\n Exiting...\n",filename);
    printf("==============================================\n");
    exit(1);
  }


}
