#include <assert.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "main.h"
#include "bubble.h"
#include "heap.h"
#include "insertion.h"
#include "merge.h"
#include "quick.h"
#include "selection.h"
#include "stopwatch.h"

sort_func_def small_sort = insertion_sort;

typedef struct Sorter
{
    const char* name;
    sort_func_def sort_func;
} Sorter;

bool array_sorted(const int* ary, int count)
{
    for (int i = 0; i < (count - 1); ++i)
    {
        if (ary[i] > ary[i + 1])
        {
            return false;
        }
    }
    return true;
}

int* get_randoms(int capacity, int max_exclusive)
{
    srand(time(NULL));
    size_t num_bytes = sizeof(int) * capacity;
    int* randoms = malloc(num_bytes);
    int i = capacity;
    while (i--)
    {
        randoms[i] = rand() % max_exclusive;
    }
    return randoms;
}

int main(int argc, char *argv[])
{
    const int CAPACITY = 20000;
    const int MAX_EXCLUSIVE = 100000;
    int* const randoms = get_randoms(CAPACITY, MAX_EXCLUSIVE);
    const size_t ary_size = sizeof(int) * CAPACITY;
    int* const to_sort = malloc(ary_size);
    const int num_sorters = 7;
    Sorter sorters[num_sorters];
    sorters[0].name = "Bubble";
    sorters[0].sort_func = bubble_sort;
    sorters[1].name = "Cocktail Shaker";
    sorters[1].sort_func = cocktailshaker_sort;
    sorters[2].name = "Insertion";
    sorters[2].sort_func = insertion_sort;
    sorters[3].name = "Selection";
    sorters[3].sort_func = selection_sort;
    sorters[4].name = "Heap";
    sorters[4].sort_func = heap_sort;
    sorters[5].name = "Merge";
    sorters[5].sort_func = merge_sort;
    sorters[6].name = "Quick";
    sorters[6].sort_func = quick_sort;
    for (int i = 0; i < num_sorters; ++i)
    {
        memcpy(to_sort, randoms, ary_size);
        Sorter sorter = sorters[i];
        clock_t start = stopwatch_start();
        sorter.sort_func(to_sort, CAPACITY);
        int elapsed = stopwatch_elapsed_milliseconds(start);
        bool is_sorted = array_sorted(to_sort, CAPACITY);
        printf("%s Sort finished %s in %d milliseconds\n",
            sorter.name, is_sorted ? "successfully" : "unsuccessfully", elapsed);
    }
    free(randoms);
    free(to_sort);
}