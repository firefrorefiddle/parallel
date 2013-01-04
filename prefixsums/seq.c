#include "seq.h"
#include <common.h>

void prefix_scan_seq(T *x, long n)
{
  long i;

  for(i=1; i<n; ++i)
    {
      x[i]+=x[i-1];
    }
}
