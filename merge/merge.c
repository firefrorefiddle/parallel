#include <stdio.h>
#include <stdlib.h>

#include <timing.h>
#include <common.h>
#include <helper.h>

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


void mk_test_arrays(T **a, T **b, T **c, long n, long m)
{
  *a = (T*) malloc (sizeof(T) * n);    
  *b = (T*) malloc (sizeof(T) * m);    
  *c = (T*) malloc (sizeof(T) * (n+m));

  if(*a == NULL || *b == NULL || *c == NULL)
    {
      perror("Assign memory for test array");
      exit(2);
    } 
}

void mk_test_arrays_interleaved (T **a, T **b, T **c, long n, long m)
{
  mk_test_arrays (a, b, c, n, m);

  long i, j;
  
  int num = 2;
  T *ar[2];
  ar[0] = *a;
  ar[1] = *b;
  long ind[2] = {0, 0};
  long lim[2] = {n, m};

  for(i=0; i<m+n; ++i)
    {
      if(num == 2)
	j = i % 2; // else it stays the same as there is only one ar remaining

      if(ind[j] >= lim[j]) /* one array is exhausted, only use the 
			      other one from now on */
	{	  
	  num = 1;
	  j = (j+1) % 2;
	}
      
      ar[j][ind[j]++]=i+1;
    }
}

void merge_seq (T *a, T *b, T *c, long n, long m)
{
  long i=0, j=0, k=0;

  while (i<n&&j<m) {
    c[k++] = (a[i]<b[j]) ? a[i++] : b[j++];
  }

  while (i<n) c[k++] = a[i++];
  while (j<m) c[k++] = b[j++];

}

static void usage(int argc, char *argv[])
{
  fprintf(stderr, "Usage: %s -m seq\n", argv[0]);
}

int main (int argc, char *argv[])
{
  T *a, *b, *c;
  struct timespec t0, t1;

  const long n = getenv("N") == NULL ? 100 : atoi(getenv("N"));
  const long m = getenv("M") == NULL ? 100 : atoi(getenv("M"));

  printf("n: %ld m: %ld max num of threads: %d\n", n, m, omp_get_max_threads());

  void (*merge_method) (T *,  T *,  T *, long, long);
  void (*mk_method)    (T **, T **, T **, long, long);

  if(argc < 3 || strcmp(argv[1], "-m") != 0)
    {
      usage(argc, argv);
      exit(1);
    }

  mk_method = &mk_test_arrays_interleaved;

  if(strcmp(argv[2], "seq") == 0)
    {
      merge_method = &merge_seq;
    }
  else
    {
      usage(argc, argv);
      exit(1);
    }

  (*mk_method) (&a, &b, &c, n, m);
  debug_ar (a, n);
  debug_ar (b, m);

  clock_gettime(CLOCK_REALTIME, &t0);
  (*merge_method) (a, b, c, n, m);
  clock_gettime(CLOCK_REALTIME, &t1);

  output("%ld\n", c, n+m, true);

  free(a);  free(b);  free(c);

  write_timediff(stderr, t0, t1, n+m);

  exit(0);
}
