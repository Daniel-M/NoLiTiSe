/*
  DESCRIPTION: This Code
      
       AUTHOR: Daniel Mejia Raigosa
         DATE: 
      VERSION: 0.0.1
*/

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
//#include <conio.h>
#include "commonroutines.c"

//#define ARGS 2 // Number of Maximum Arguments (1 means no arguments!)

#define TITLESCN "White Noise Generator - On Dev"

int gen_rand(void)
/* returns random number in range of 0 to 99 */
{
   int n;
   n=rand();  /* n is random number in range of 0 - 99 */
   return(n);
}


/*main(int argc,char *argv[]) // for input arguments, remeber argv[0]=program name argv[1]= first argument and so on */
int main(void)
{
  /* // This section is made for argument validation
	if( argc > ARGS )
	   {
	      printf("Too many arguments supplied.\n");
	      exit(1);
	   {
	else if (argc<ARGS)
	   {
	    
	       printf("Some arguments expected.\n");
	       exit(1);
 	   }

  */
  
  system("clear");
  pimpi(TITLESCN,25);

  int r1,r2,i;
  double x;
  time_t t1;

  FILE *wnfile;
  
  wnfile=fopen("white-noise.txt","w");
  
  srand( time(NULL) );

  while(i<5000)
    {
      
      r1=rand()*rand()/1e8;
      r2=rand()*rand();
      //printf("%d \t %d \t %lf \t %lf \n",r1,r2,log(abs(r1)),sin(r2*M_PI*2e8));
      x=pow(2.0*log(abs(r1)),0.5)*sin(2e9*M_PI*r2);
      //printf(" * %lf\n",x);
      
      fprintf(wnfile,"%lf\n",x);
      i=i+1;
    }

  pimpo(TITLESCN,25);
  exit(0);
} //End of Main Code
