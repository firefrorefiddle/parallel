#include <stdio.h>
#include "common.h"

void output (const char *fmt, T *ar, long size, bool justafew)
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
