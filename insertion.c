#include <stdbool.h>
#include "insertion.h"
#include "common.h"

void insertion_sort(int* ary, int count)
{
    if (count < 2)
    {
        return;
    }
    
    for (int i = 1; i < count; ++i)
    {
        int j = i - 1;
        int old = ary[i];
        for (; j >= 0 && ary[j] > old; --j)
        {
            array_swap_values(ary, j, j+1);
        }
        bool shifted = j != i - 1;
        if (shifted)
        {
            /* Need to compensate for the last decrement of j
             * in the loop above */
            ary[j + 1] = old;
        }
    }
}