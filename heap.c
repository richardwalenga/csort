#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include "heap.h"

static const int ROOT_INDEX = 1;
static const int INVALID_INDEX = -1;

typedef enum
{
    DOWN = 0,
    UP = 1
} HeapifyDirection;

typedef struct Heap
{
    int size;
    int* storage;
    bool (*comparer)(int, int);
} Heap;

typedef struct HeapNode
{
    int index;
    const Heap* heap;
} HeapNode;

typedef struct OptionalInt
{
    bool has_value;
    int value;
} OptionalInt;

void heapnode_init(HeapNode*, const Heap*, int);
bool heapnode_exists(const HeapNode*);
int heapnode_getvalue(const HeapNode*);
void heapnode_setvalue(const HeapNode*, int);
void heapnode_heapify_down(const HeapNode*);
void heapnode_heapify_up(const HeapNode*);
HeapNode heapnode_left(const HeapNode*);
HeapNode heapnode_right(const HeapNode*);
HeapNode heapnode_parent(const HeapNode*);
HeapNode heapnode_from_index(const HeapNode*, int);
void heapnode_try_swap_value(const HeapNode*, const HeapNode*, HeapifyDirection);
void heap_init(Heap*, bool, int);
void heap_destruct(Heap*);
bool heap_is_out_of_range(const Heap*, int);
OptionalInt heap_peek(const Heap*);
void heap_store(Heap* heap, int num);
OptionalInt heap_take(Heap*);

void heapnode_init(HeapNode* node, const Heap* heap, int index)
{
    node->heap = heap;
    node->index = index;
}

bool heapnode_exists(const HeapNode* node)
{
    return node != NULL && node->heap != NULL && node->index != INVALID_INDEX;
}

int heapnode_getvalue(const HeapNode* node)
{
    return node->heap->storage[node->index];
}

void heapnode_setvalue(const HeapNode* node, int new_val)
{
    node->heap->storage[node->index] = new_val;
}

void heapnode_heapify_down(const HeapNode* node)
{
    HeapNode left = heapnode_left(node);
    HeapNode right = heapnode_right(node);
    bool left_exists = heapnode_exists(&left);
    bool right_exists = heapnode_exists(&right);
    if (!left_exists && !right_exists)
    {
        return;
    }

    HeapNode* other = &right;
    if (left_exists && right_exists)
    {
        /* Favor the smallest or largest child node as a swap partner
         * depending on if one is working with a min or max heap.
         * The comparer will return true if the first value meets this
         * criteria. */
        if (node->heap->comparer(
            heapnode_getvalue(&left), heapnode_getvalue(&right)))
        {
            other = &left;
        }
    }
    else if (left_exists)
    {
        other = &left;
    }
    heapnode_try_swap_value(node, other, DOWN);
}

void heapnode_heapify_up(const HeapNode* node)
{
    HeapNode parent = heapnode_parent(node);
    heapnode_try_swap_value(node, &parent, UP);
}

HeapNode heapnode_left(const HeapNode* node)
{
    int new_index = node != NULL ? 2 * node->index : INVALID_INDEX;
    return heapnode_from_index(node, new_index);
}

HeapNode heapnode_right(const HeapNode* node)
{
    int new_index = node != NULL ? 2 * node->index + 1 : INVALID_INDEX;
    return heapnode_from_index(node, new_index);
}

HeapNode heapnode_parent(const HeapNode* node)
{
    int new_index = node == NULL || node->index == ROOT_INDEX ? INVALID_INDEX : (node->index / 2);
    HeapNode parent;
    heapnode_init(&parent, node->heap, new_index);
    return parent;
}

HeapNode heapnode_from_index(const HeapNode* node, int index)
{
    int new_index = node == NULL || heap_is_out_of_range(node->heap, index) ? INVALID_INDEX : index;
    HeapNode ret;
    heapnode_init(&ret, node->heap, new_index);
    return ret;
}

void heapnode_try_swap_value(const HeapNode* node, const HeapNode* other, HeapifyDirection direction)
{
    if (!heapnode_exists(node) || !heapnode_exists(other))
    {
        return;
    }

    int val = heapnode_getvalue(node);
    int other_val = heapnode_getvalue(other);
    bool (*comparer)(int, int) = node->heap->comparer;
    if (direction == DOWN && comparer(other_val, val))
    {
        heapnode_setvalue(node, other_val);
        heapnode_setvalue(other, val);
        heapnode_heapify_down(other);
    }
    else if (direction == UP && comparer(val, other_val))
    {
        heapnode_setvalue(node, other_val);
        heapnode_setvalue(other, val);
        heapnode_heapify_up(other);
    }
}

bool min_comparer(int x, int y)
{
    return x < y;
}

bool max_comparer(int x, int y)
{
    return x > y;
}

void heap_init(Heap* heap, bool is_min, int capacity)
{
    heap->size = 0;
    heap->storage = malloc(sizeof(int) * (capacity+1));
    heap->comparer = is_min ? min_comparer : max_comparer;
}

void heap_destruct(Heap* heap)
{
    free(heap->storage);
}

void heap_store(Heap* heap, int num)
{
    ++heap->size;
    heap->storage[heap->size] = num;
    bool setting_root = heap->size == ROOT_INDEX;
    if (!setting_root)
    {
        HeapNode added;
        heapnode_init(&added, heap, heap->size);
        heapnode_heapify_up(&added);
    }
}

bool heap_is_out_of_range(const Heap* heap, int index)
{
    return heap == NULL || index > heap->size;
}

OptionalInt heap_peek(const Heap* heap)
{
    OptionalInt ret;
    if (heap != NULL && heap->size > 0)
    {
	ret.has_value = true;
	ret.value = heap->storage[ROOT_INDEX];
    }
    return ret;
}

OptionalInt heap_take(Heap* heap)
{
    OptionalInt taken = heap_peek(heap);
    if (!taken.has_value) return taken;

    heap->storage[ROOT_INDEX] = heap->storage[heap->size--];
    if (heap->size > 1)
    {
        HeapNode root_node;
        heapnode_init(&root_node, heap, ROOT_INDEX);
        heapnode_heapify_down(&root_node);
    }
    return taken;
}

void heap_sort(int* ary, int count)
{
    Heap heap;
    Heap* heap_ptr = &heap;
    heap_init(heap_ptr, true, count);
    int i = 0;
    for (; i < count; ++i)
    {
        heap_store(heap_ptr, ary[i]);
    }
    for (i = 0; i < count; ++i)
    {
        OptionalInt taken = heap_take(heap_ptr);
        assert(taken.has_value == true);
        ary[i] = taken.value;
    }
    heap_destruct(heap_ptr);
}
