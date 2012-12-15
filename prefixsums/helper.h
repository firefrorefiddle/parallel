#ifndef __HELPER_H__
#define __HELPER_H__

static void output (const char *fmt, T *ar, long size, bool justafew);

static inline void debug_ar (T *ar, long size)
{
#ifdef DEBUG
  output("%ld, ", ar, size, false);
  printf("\n");
#endif
}

#endif
