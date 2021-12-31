#include <stdbool.h>
#include "bubble.h"
#include "common.h"

bool ltr_sort(int* ary, int count)
{
    bool swapped = false;
    for (int i = 1; i < count; ++i)
    {
        if (ary[i - 1] > ary[i])
        {
            array_swap_values(ary, i - 1, i);
            swapped = true;
        }
    }
    return swapped;
}

bool rtl_sort(int* ary, int count)
{
    bool swapped = false;
    for (int i = count - 1; i > 0; --i)
    {
        if (ary[i] < ary[i - 1])
        {
            array_swap_values(ary, i - 1, i);
            swapped = true;
        }
    }
    return swapped;
}

void bubble_sort(int* ary, int count)
{
    if (count < 2)
    {
        return;
    }

    while(ltr_sort(ary, count));
}

void cocktailshaker_sort(int* ary, int count)
{
    if (count < 2)
    {
        return;
    }

    /* By applying a bitmask of 1 less than a power of 2, I can cleanly
    * alternate sorting left to right followed by right to left. */
    const int BITMASK = 1;
    bool (*cmp[2])(int*, int) = { ltr_sort, rtl_sort };
    int i = 0;
    while (true)
    {
        if (!cmp[i](ary, count))
        {
            break;
        }
        i = (i + 1) & BITMASK;
    }
}