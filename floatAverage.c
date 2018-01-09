/*
  Reads in a list of files which comprise of just integers
  Then computes the average compared to an expected value (arg 1)
  Finally outputs a probability distribution to file "res.dat"

  Usage : computeAverage [int expected averge] [list of files]

  NB expected average is required to determine range of probability distribution 


  Sept 2004
*/


#include <stdio.h>
#include <math.h>
#include <stdlib.h>
//#include <time.h>

//#include "/Users/rsgraham/recipes_c-ansi/recipes/nrutil.h"
//#include "/Users/rsgraham/recipes_c-ansi/misc/nrutil.c"



static void logFreq(float sum, int frequency[], float dx, float sampStart, int sampFreq);
static void saveFreq(char filename[],int freq[], float start, float dx, int nSamples, int nLoops);


int main(int argc, char *argv[] )
{
  long nPoints=0;
  int i, ENTNUMBER=20, ZSAMPFREQ;
  float ZSAMPFIN, ZSAMPSTART, DZ, vary, value;
  double total=0.0, varyTotal=0.0;
  int *zFrequency; // holds frequency of generated numbers


  FILE *inFilePtr;


  // check correct number of arguments
  if(argc<3){
    printf("Usage: computeAverage [int expected average] [list of files]\n");
    exit(EXIT_FAILURE);
  }

  printf("Found %d files\n",argc-2);
  

  ENTNUMBER = atoi(argv[1]);

  
  printf("User specified expected average as %d\n",ENTNUMBER);


  


  ZSAMPFREQ =100;//2*ENTNUMBER+1;//sampling density for Z
  ZSAMPFIN=2.0*ENTNUMBER+1.5;//0.999*ENTNUMBER  
  ZSAMPSTART=0.5;
  DZ=((ZSAMPFIN-ZSAMPSTART)/(1.0*ZSAMPFREQ));
  //zFrequency = ivector(1,100);




  for(i=2; i<=argc-1; i++){
    if( ( inFilePtr = fopen( argv[i] , "r") ) == NULL ){
      printf("Can't open file %s\n",argv[i]);
      exit(EXIT_FAILURE);
    }

    printf("File %d open \n",i-1 );

      fscanf(inFilePtr,"%e",&value);
      
      //printf("Read %f\n",value);

      while( !feof( inFilePtr ) ){
	total += (value-1.0*ENTNUMBER);
	varyTotal += (value-ENTNUMBER)*(value-ENTNUMBER);
	nPoints++;
	//logFreq(1.0*value, zFrequency, DZ , ZSAMPSTART,  ZSAMPFREQ);
	fscanf(inFilePtr,"%e",&value);
	//printf("Read %f\n",value);
	      
	  //printf("%d\n",value);
      }
      
      fclose(inFilePtr);
      
    
  }
  
  printf("There are %d data points\n",nPoints);

  
  //saveFreq("res.dat",zFrequency, ZSAMPSTART, DZ,ZSAMPFREQ, nPoints);
  
  //printf("Data written to ./res.dat\n");

  printf("Average = %e or %f\n",1.0*total/(1.0*nPoints),1.0*total/(1.0*nPoints)+ENTNUMBER);

  vary= 1.0/(nPoints-1)*varyTotal - 1.0/(nPoints-1)/nPoints*total*total;
  printf("Standard error=%f\n",sqrt(vary/(1.0*nPoints)));

  //______ Put results in form that can be used by vi editor____________________________
  printf("\n%f  %f\n\n",1.0*total/(1.0*nPoints)+ENTNUMBER,sqrt(vary/(1.0*nPoints)));

  return 0;
  
}

static void logFreq(float sum, int frequency[], float dx, float sampStart, int sampFreq)
{
  int i, flag;

    i=1;
    flag=0;
    //sum=1.0*countLakes(startPtr);

    while(flag<0.5){
      if(i<=sampFreq){
	if(sum<= sampStart+(i*dx)  )  {
	  if(sum>( (sampStart+(i-1)*dx) )  )  {
	    frequency[i]++;
	    flag=1;
	  }
	}
	i++;
      }
      else{
	flag=1.0;
      }
    }//flag test loop
    
}



static void saveFreq(char filename[], int freq[], float start, float dx, int nSamples, int nLoops)
{
  int i;
  FILE *cfPtr;

  cfPtr=fopen(filename,"w");
  
  for( i=1; i<=nSamples; i++){
      //printf("%f %f\n", start+(i-0.5)*dx , 1.0*freq[i]/(1.0*nLoops*dx)  );
    fprintf(cfPtr,"%f %e\n", start+(i-0.5)*dx , 1.0*freq[i]/(1.0*nLoops*dx)  );
  }
    
  fclose(cfPtr);
   
  


}


