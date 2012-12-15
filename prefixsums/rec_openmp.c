#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#include "time.h"
#include "common.h"

#define T long


static inline bool odd(T n) 
{
  return n % 2 != 0;
}

static void output (const char *fmt, T *ar, long size, bool justafew)
{
  long i;
  long limit = size;

  if(justafew==true)
    limit = size > 10 ? 10 : size;

  for(i=0; i<limit; ++i)
    {
      printf(fmt, ar[i]);
    }

  if(justafew==true)
    {    
      if(limit >= size - 10)
	limit = limit = limit + 1;
      else
	limit = size - 10;

      for(i=limit; i<size; ++i)
	{
	  printf(fmt, ar[i]);
	}
    }
}

static inline void debug_ar (T *ar, long size)
{
#ifdef DEBUG
  output("%ld, ", ar, size, false);
  printf("\n");
#endif
}

void scan(T *x, long n)
{
  if (n==1) 
    return; // base

  T *y = (T*) malloc (sizeof(T) * n/2);

  long i;

#pragma omp parallel shared(y)
  {
#pragma omp for
    for (i=0; i<n/2; i++) 
      y[i] = x[2*i] + x[2*i + 1];
  }

  debug_ar(y, n/2);

  scan(y,n/2);

  x[1] = y[0];

#pragma omp parallel private(i) shared(x)
  {
#pragma omp for
    for (i=1; i<n/2; i++) 
      {
	x[2*i] = y[i-1] + x[2*i];
	x[2*i+1] = y[i];
      }
  }

  if (odd(n)) 
    x[n-1] = y[n/2-1]+x[n-1];

  debug_ar(y, n/2);

  free (y);
}

static T *mk_test_array (long size)
{
  T *x = (T*) malloc (sizeof(T) * size);  

  T i;
  for(i=0; i<size; ++i)
    x[i]=i+1;

  return x;
}

int main (int argc, char *argv[])
{
  const long size = 100000000;

  struct timespec t0, t1;
 
  T *ar = mk_test_array(size);

  clock_gettime(CLOCK_REALTIME, &t0);
  scan(ar, size);
  clock_gettime(CLOCK_REALTIME, &t1);

  output("%ld\n", ar, size, true);
  free(ar);

  write_timediff(stderr, t0, t1, size);

}