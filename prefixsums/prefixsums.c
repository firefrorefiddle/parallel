#include <stdlib.h>

#include "time.h"
#include "common.h"
#include "rec_openmp.h"

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
  prefix_scan_rec(ar, size);
  clock_gettime(CLOCK_REALTIME, &t1);

  output("%ld\n", ar, size, true);
  free(ar);

  write_timediff(stderr, t0, t1, size);

}
