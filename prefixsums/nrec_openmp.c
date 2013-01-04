#include <stdlib.h>
#include <common.h>
#include <helper.h>

void prefix_scan_nrec(T *x, long n)
{
  int i, k, kk;


  for (k=1; k<n; k=kk)
    {
		
      kk = k<<1; // double

#ifndef NO_PARALLEL
#pragma omp parallel shared(x)
      {
#pragma omp for
#endif

	for (i=kk-1; i<n; i+=kk)
	  {
	    x[i] = x[i-k]+x[i]; 
	  } 

#ifndef NO_PARALLEL
      }
#endif
    }

  for (k=k>>1; k>1; k=kk)
    {
      kk = k>>1; // halve

#ifndef NO_PARALLEL
#pragma omp parallel shared(x)
      {
#pragma omp for
#endif


	for (i=k-1; i<n-kk; i+=k)
	  {
	    x[i+kk] = x[i]+x[i+kk]; 
	  } 
		
#ifndef NO_PARALLEL
      }
#endif

    }

}
