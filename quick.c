#include "quick.h"
#include "common.h"

/* Organizes the values between the high and low indexes where the
 * chosen pivot is moved to a new index where all values greater than
 * the pivot are to its right. The new index for the pivot is returned. */
int partition(int* ary, int low, int high)
{
    int pivot = ary[high];
    /* initialize the index below low because the index is guaranteed
     * to be incremented before the pivot is moved to its new home. */
    int new_pivot_index = low - 1;
    for (int i = low; i < high; ++i)
    {
        if (ary[i] <= pivot)
        {
            array_swap_values(ary, ++new_pivot_index, i);
        }
    }
    /* There will always be at least one swap call since if this is the
     * first time, it means every value checked is greater than the pivot. */
    array_swap_values(ary, ++new_pivot_index, high);
    return new_pivot_index;
}

void sort_between_indexes(int* ary, int low, int high)
{
    if (low < high)
    {
        int pivot_index = partition(ary, low, high);
        sort_between_indexes(ary, low, pivot_index-1);
        sort_between_indexes(ary, pivot_index+1, high);
    }
}

void quick_sort(int* ary, int count)
{
    sort_between_indexes(ary, 0, count-1);
}