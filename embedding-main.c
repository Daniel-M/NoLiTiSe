/*
  FILE NAME:   embedding-main.c
  DESCRIPTION: This code consist of a simple embedding process by passing 
               the data origin file name as argv[1] and the resulting embedding
	       dimention as argv[2] when executing the program.
	       the program creates the file "filename-embedding.ext" as a 
	       result of the successful working.
	       Max Data handling 10000 data lines 
      
  AUTHOR:      Daniel Mejia Raigosa
  DATE:        21, April 2011
  VERSION:     1.2 
*/

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "commonroutines.c"

#define ARGS 3  // Here we defines the number of max arguments remember that argv[0] its the program name
#define TITLESCN "Embedding" // Program Title
#define VER  "1.2" // Code Version 
#define ANO "2011" // Date of Code 
#define CHAPER 20 // Number of allowed characters
#define MAXDATA 10000  //Maximum Data Input


/* HERE COMES THE MAIN FUNCTION */

main( int argc, char *argv[] ) // when passing arguments
{
 // This section is made for argument validation
   if( argc > ARGS ){
     printf("Too many arguments supplied.\n");
     printf("\tUsage: %s file.ext embedding-dimension\n \n",TITLESCN);
     exit(1);
   }
   else if (argc < ARGS){
     printf("Missing Arguments!!.\n");
     printf("\tUsage: %s file.ext embedding-dimension\n \n",TITLESCN);
     exit(1);
   }

   char resp[0],originfn[CHAPER],dimarg[CHAPER],filename[CHAPER],fileext[CHAPER];
  double in1[MAXDATA];  //Floating Point
  int m,dim,cont,maxcont;
  
  FILE *origin;         // File handler
  FILE *destination;

  /* Starting Main Code */

  characternumber(argv[1],CHAPER); //Confirm Character allowed values
  characternumber(argv[2],CHAPER);

  strcpy(originfn,argv[1]);   //Convert file names
  strcpy(dimarg,argv[2]);

  dim=atoi(dimarg);

  double x[MAXDATA][dim]; //Declare the emdending vector

  strcpy(filename,strtok(argv[1],".")); // separate data files
  strcpy(fileext,strstr(originfn,"."));

  strcpy(filename,strcat(filename,"-embedded")); //create a filename
  strcat(filename,fileext);
  
  opendatafile(&origin,originfn,"r"); // Data File Handling on origin
  opendatafile(&destination,filename,"w"); // Data File Handling on destination


  system("clear");
  pimpi(TITLESCN,30);
  printf("\n This tool will help you on the embedding process...\n");

  printf(" * Data origin file: \'%s\'\n",originfn);
  printf(" * Embedding dimension: %d\n",dim);
  printf(" Are you sure you want to continue?[y/n]:");
  scanf("%c",&resp);
  if (resp[0]=='y')
    {
      printf("\n\tSuccess!!!\n");
      printf("\n * Embedding output file: \'%s\'\n",filename);
      
      
      
      /*  Read Contents on the file originfn and makes an embeding of dimension dim*/
      cont=0; //initialize counter
      while(!feof(origin)) //checks if the end of file is reached
	{
	  fscanf(origin,"%lf\n",&in1[cont]);
	  cont=cont+1;
	}
      fclose(origin);
      
      printf("\n\tTotal lines read: %d",cont);
      maxcont=cont;
      
  /* here comes the embedding proccess */
      
      for(cont=0;cont<maxcont;cont++)
	{
	  for(m=0;m<dim;m++)
	    {
	      x[cont][m]=in1[m+cont];
	    }
	}

      /* Now make the out put file */
      


      for(cont=0;cont<maxcont;cont++) //checks if the end of file is reached
	{
	  for(m=0;m<dim;m++)
	    {   
	      fprintf(destination,"%lf\n",x[cont][m]);
	    }
           fprintf(destination,"\n");
	}

      fclose(destination);

      /*  */

      printf("\n\tWrote %d lines on Output File : %s",maxcont*m,filename);
      printf("\n\tEmbedding: %d\n",dim);
      pimpe(TITLESCN,30);
      exit(0);
    }
  else
    {
      printf(" \n Exiting...\n\n");
      exit(0);
    }
  

} // End of Main Code
