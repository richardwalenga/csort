#include "common.h"

void array_swap_values(int* ary, int x, int y)
{
    if (x == y)
    {
        return;
    }
    int temp = ary[x];
    ary[x] = ary[y];
    ary[y] = temp;
}