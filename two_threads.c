
//http://www.dartmouth.edu/~rc/classes/soft_dev/C_simple_ex.html

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>
#include <math.h>

#define SEED 35791246

void *factorial_thread(void *arg)
{
    int *num = (int *)arg;
    int factResult=1;
    for(int i = 1;i <= *num;i++)
        factResult *= i;
    printf("The factorial of %d is : %d\n",*num,factResult);
}

//Gauss-Legendre method
double piValue(int numIterations)
{
   int niter=numIterations;
   double x,y;
   int i,count=0; /* # of points in the 1st quadrant of unit circle */
   double z;
   double pi;
   /* initialize random numbers */
   srand(SEED);
   count=0;
   for ( i=0; i<niter; i++) {
      x = (double)rand()/RAND_MAX;
      y = (double)rand()/RAND_MAX;
      z = x*x+y*y;
      if (z<=1) count++;
      }
   pi=(double)count/niter*4;
   return pi;
}

void *approx_pi(void *arg)
{
    int *num = (int *)arg;
    double pi = piValue(*num);
    printf("The approx value of pi at %d iterations is %f\n",*num,pi);
}

int main()
{
    int n,m;
    printf("Enter n: ");
    scanf("%d",&n);
    printf("Enter m: ");
    scanf("%d",&m);

    pthread_t factTid;
    pthread_t piTid;
    pthread_create(&factTid,NULL,factorial_thread,(void *)&n);
    pthread_create(&piTid,NULL,approx_pi,(void *)&m);
    pthread_join(factTid,NULL);
    pthread_join(piTid,NULL);
    pthread_exit(NULL);
    return 0;
}
