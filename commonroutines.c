/*
   DESCRIPTION: Some routines for practical handling
   AUTHOR:      Daniel Mejia Raigosa
   DATE:        19, March 2011
   VERSION:     1.0
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
   
}//Fin Pidevalor

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

}//Fin adornoi

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

}//Fin adornoi
