#ifndef __COMMON_H__
#define __COMMON_H__

#define T long

typedef enum { true=1, false=0 } bool;
static inline bool odd(T n) 
{
  return n % 2 != 0;
}

#endif
