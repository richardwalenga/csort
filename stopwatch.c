#include "stopwatch.h"
#include <math.h>

clock_t stopwatch_start()
{
    return clock();
}

int stopwatch_elapsed_milliseconds(clock_t started)
{
    double diff = clock() - started;
    const int MILLISECS_PER_SEC = 1000;
    int elapsed_milliseconds = round(diff / CLOCKS_PER_SEC * MILLISECS_PER_SEC);
    return elapsed_milliseconds;
}