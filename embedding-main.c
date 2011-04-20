/*
  DESCRIPTION: This code consist of a simple embedding process by passing 
               the data file as argv[1] and the resulting embedding on
	       argv[2], also the embedding delay as argv[3] of the program
      
  AUTHOR:      Daniel Mejia Raigosa
  DATE:        20, April 2011
  VER:         Makin'
*/

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "commonroutines.c"

#define ARGS 4  // Here we defines the number of max arguments remember that argv[0] its the program name
#define TITLESCN "NoLiTiSe" // Program Title
#define VER  "0.0.1" // Code Version 
#define ANO "2011" // Date of Code 


/* HERE COMES THE MAIN FUNCTION */

main( int argc, char *argv[] ) // when passing arguments
{
 // This section is made for argument validation
        if( argc > ARGS ){
	        printf("Too many arguments supplied.\n");
	}
	else if (argc < ARGS){
	        printf("Missed Arguments!!.\n");
		printf("\tExiting...\n \n");
	}
	else{
	  printf("the input arguments were : %s %s %s\n",argv[1],argv[2],argv[3]);
	}

	/* Defining Variables */ 

  char destinationfn[20], originfn[20],dinarg[5];
  double c1,c2,c3;
  int dim,longitud,i;
  
  FILE *origin;         // File handler
  FILE *destination;

  /* Starting Main Code */

  longitud=strlen(argv[1]);
  strcpy(originfn,argv[1]);

  opendatafile(&origin,originfn,"r"); // Data File Handling

  printf("origin file name:");
  for(i=0;i<longitud;i++)
    {
      printf("%c",originfn[i]);
    }
  printf("\n");

  fscanf(origin,"%lf %lf %lf",&c1,&c2,&c3);
  fclose(origin);
  printf("\nCol1: %lf\nCol2: %lf\nCol3: %lf\n",c1,c2,c3);
  exit(0);

} // End of Main Code
