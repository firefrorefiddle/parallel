#include <stdlib.h>
#include <stdio.h>

#include "time.h"
#include "common.h"
#include "rec_openmp.h"
#include "nrec_openmp.h"
#include "dbl_openmp.h"
#include "seq.h"

static T *mk_test_array (long size)
{
  T *x = (T*) malloc (sizeof(T) * size);  

  if(x == NULL)
    {
      perror("Assign memory for test array");
      exit(2);
    }

  T i;
  for(i=0; i<size; ++i)
    x[i]=i+1;

  return x;
}

static void usage(int argc, char *argv[])
{
  fprintf(stderr, "Usage: %s -m seq|rec|nrec|dbl\n", argv[0]);
}

int main (int argc, char *argv[])
{
  const long size = getenv("N") == NULL ? 100000000 : atoi(getenv("N"));

  printf("Sample size: %ld max num of threads: %d\n", size, omp_get_max_threads());

  struct timespec t0, t1;
 
  T *ar = mk_test_array(size);

  if(argc < 3 || strcmp(argv[1], "-m") != 0)
    {
      usage(argc, argv);
      exit(1);
    }

  void (*method) (T *, T);

  if(strcmp(argv[2], "rec") == 0)
    {
      method = &prefix_scan_rec;
    }
  else if(strcmp(argv[2], "seq") == 0)
    {
      method = &prefix_scan_seq;
    }
  else if(strcmp(argv[2], "nrec") == 0)
    {
      method = &prefix_scan_nrec;
    }
  else if(strcmp(argv[2], "dbl") == 0)
    {
      method = &prefix_scan_dbl;
    }
  else
    {
      usage(argc, argv);
      exit(1);
    }

  clock_gettime(CLOCK_REALTIME, &t0);
  method(ar, size);
  clock_gettime(CLOCK_REALTIME, &t1);

  output("%ld\n", ar, size, true);
  free(ar);

  write_timediff(stderr, t0, t1, size);

  exit(0);
}
