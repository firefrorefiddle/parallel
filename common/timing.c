#include "timing.h"

void write_timediff(FILE *stream, struct timespec t0, struct timespec t1, long size)
{
  long diff = 
    (t1.tv_sec * 1000000000 + t1.tv_nsec) -
    (t0.tv_sec * 1000000000 + t0.tv_nsec);

  float ns_per_elem = diff * 1.0 / size;

  fprintf(stream, "Elapsed time: %.2f seconds (%.2f ns per element).\n", diff/1000000000.0, ns_per_elem);
}
