#include <stdlib.h>
#include "common.h"
#include "helper.h"

void prefix_scan_rec(T *x, long n)
{
  if (n==1) 
    return; // base

  T *y = (T*) malloc (sizeof(T) * n/2);

  long i;

#ifndef NO_PARALLEL
#pragma omp parallel private(i) shared(y)
  {
#pragma omp for
#endif

    for (i=0; i<n/2; i++) 
      y[i] = x[2*i] + x[2*i + 1];

#ifndef NO_PARALLEL
  }
#endif

  debug_ar(y, n/2);

  prefix_scan_rec(y,n/2);

  x[1] = y[0];

#ifndef NO_PARALLEL
#pragma omp parallel private(i) shared(x)
  {
#pragma omp for
#endif

    for (i=1; i<n/2; i++) 
      {
	x[2*i] = y[i-1] + x[2*i];
	x[2*i+1] = y[i];
      }

#ifndef NO_PARALLEL
  }
#endif

  if (odd(n)) 
    x[n-1] = y[n/2-1]+x[n-1];

  debug_ar(y, n/2);

  free (y);
}
