#include <stdlib.h>

#include <common.h>
#include <helper.h>

void prefix_scan_dbl(T *x, long n)
{
  long k, i;

  T *y = (T*) malloc (n*sizeof(T));
  T *t;

  for (k=1; k<n; k<<=1) {

#ifndef NO_PARALLEL
#pragma omp parallel shared(y) shared(x)
    {
#pragma omp for
#endif
      
      for (i=0; i<k; i++) 
	{
	  y[i] = x[i];
	}

#ifndef NO_PARALLEL
#pragma omp for
#endif
      for (i=k; i<n; i++) 
	{
	  y[i] = x[i-k]+x[i];
	}

#ifndef NO_PARALLEL
    }
#endif
       
    t = x; x = y; y = t; // swap
  }

}
