#ifndef _STOPWATCH_H
#define _STOPWATCH_H

#include <time.h>

clock_t stopwatch_start();
int stopwatch_elapsed_milliseconds(clock_t);

#endif