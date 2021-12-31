#include "selection.h"
#include "common.h"

void selection_sort(int* ary, int count)
{
    if (count < 2)
    {
        return;
    }
    
    for (int i = 0; i < (count - 1); ++i)
    {
        int min_idx = i;
        for (int j = i + 1; j < count; ++j)
        {
            if (ary[min_idx] > ary[j])
            {
                min_idx = j;
            }
        }
        if (i != min_idx)
        {
            array_swap_values(ary, i, min_idx);
        }
    }
}