#ifndef __TIME_H__
#define __TIME_H__

#include <time.h>
#include <stdio.h>

void write_timediff(FILE *stream, struct timespec t0, struct timespec t1, long size);

#endif
