/*
  DESCRIPTION: This code aims to make an Dynamical Systems Calculation Suite
               Where one can make embendings, calculate correlation dimension
	       lyapunov exponents and more.
      
  AUTHOR:      Daniel Mejia Raigosa
  DATE:        16, April 2011
  VER:         0.1
*/

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "commonroutines.c"

#define ARGS 4  // Here we defines the number of max arguments
#define TITLESCN "NoLiTiSe" // Program Title
#define VER  "0.1" // Code Version 
#define ANO "2011" // Date of Code 

 int main(void)
//main( int argc, char *argv[] ) // when passing arguments
{
  // Defining Variables
  char archivef[20]
  int men;

  system("clear");
  pimpi(TITLESCN,30);
  printf("  NoLiTiSe - Ver %s  %s \n", VER,ANO);
  printf("  A Tool For Non Linear Time Series Analisys.\n \n");

  //  printf("    ");
  printf(" Whould you like to...\n\t1. Make an Embedding\n\t2. Calculate the Maximum Lyapunov Exponent\n");
  scanf("%d",&men);
  if (men>1)
    { printf("Error!: you haven't selected a right value");
      exit;
    }
  switch(men)
    {
    case 1:
         {
	   printf("Entering Embedding Mode...");
	   printf("What's the filename?");
	   scanf("%s",&archivef[20]);
	   *FILE = fopen(archive,"r");
	 }
    }

  pimpe(TITLESCN,30);
  exit(0);


} // End of Main Code
