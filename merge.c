#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "main.h"
#include "merge.h"

int* array_slice(const int* src, int start_idx, int end_idx)
{
    int length = end_idx - start_idx + 1;
    size_t num_bytes = sizeof(int) * length;
    int* dest = malloc(num_bytes);
    memcpy(dest, src+start_idx, num_bytes);
    return dest;
}

void merge_sort(int* ary, int count)
{
    if (count < 10)
    {
        small_sort(ary, count);
        return;
    }

    int mid_idx = count / 2;
    int* x = array_slice(ary, 0, mid_idx-1);
    int* y = array_slice(ary, mid_idx, count-1);
    int x_cnt = mid_idx;
    int y_cnt = count - mid_idx;
    int x_idx, y_idx;
    x_idx = y_idx = 0;
    merge_sort(x, x_cnt);
    merge_sort(y, y_cnt);
    for (int i = 0; i < count; ++i)
    {
        bool can_take_x = x_idx < x_cnt;
        bool can_take_y = y_idx < y_cnt;
        if (can_take_x && (!can_take_y || x[x_idx] <= y[y_idx]))
        {
            ary[i] = x[x_idx++];
        }
        else
        {
            ary[i] = y[y_idx++];
        }
    }
    free(x);
    free(y);
}