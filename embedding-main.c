/*
  DESCRIPTION: This code consist of a simple embedding process by passing
               the embedding delay as an argument of the program
      
  AUTHOR:      Daniel Mejia Raigosa
  DATE:        16, April 2011
  VER:         0.1
*/

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "commonroutines.c"

#define ARGS 4  // Here we defines the number of max arguments remember that argv[0] its the program name
#define TITLESCN "NoLiTiSe" // Program Title
#define VER  "0.1" // Code Version 
#define ANO "2011" // Date of Code 

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

  char destinationf[20], originf[20],m[5];
  int dim,longitud,i;
  longitud=strlen(argv[1]);
  strcpy(originf,argv[1]);
  printf("originf:");
  for(i=0;i<longitud;i++)
    {
      printf("%c",originf[i]);
    }
  printf("\n");


} // End of Main Code
