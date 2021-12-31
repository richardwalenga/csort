#include <stdbool.h>
#include <stdlib.h>
#include "heap.h"

static const int ROOT_INDEX = 1;
static const int NOTHING = -1;

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
    bool is_root;
    int index;
    const Heap* heap;
} HeapNode;

HeapNode* heapnode_init(const Heap*, int);
int heapnode_getvalue(const HeapNode*);
void heapnode_setvalue(const HeapNode*, int);
void heapnode_heapify_down(const HeapNode*);
void heapnode_heapify_up(const HeapNode*);
HeapNode* heapnode_left(const HeapNode*);
HeapNode* heapnode_right(const HeapNode*);
HeapNode* heapnode_parent(const HeapNode*);
HeapNode* heapnode_from_index(const HeapNode*, int);
void heapnode_try_swap_value(const HeapNode*, const HeapNode*, HeapifyDirection);
Heap* heap_init(bool, int);
bool heap_is_out_of_range(const Heap*, int);
int heap_peek(const Heap*);
void heap_store(Heap* heap, int num);
int heap_take(Heap*);

HeapNode* heapnode_init(const Heap* heap, int index)
{
    HeapNode* node = malloc(sizeof(HeapNode));
    node->heap = heap;
    node->is_root = index == ROOT_INDEX;
    node->index = index;
    return node;
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
    HeapNode* left = heapnode_left(node);
    HeapNode* right = heapnode_right(node);
    if (left == NULL && right == NULL)
    {
        return;
    }

    HeapNode* other = right;
    if (left != NULL && right != NULL)
    {
        /* Favor the smallest or largest child node as a swap partner
         * depending on if one is working with a min or max heap.
         * The comparer will return true if the first value meets this
         * criteria. */
        if (node->heap->comparer(
            heapnode_getvalue(left), heapnode_getvalue(right)))
        {
            other = left;
        }
    }
    else if (left != NULL)
    {
        other = left;
    }
    heapnode_try_swap_value(node, other, DOWN);
    free(left);
    free(right);
}

void heapnode_heapify_up(const HeapNode* node)
{
    HeapNode* parent = heapnode_parent(node);
    if (parent == NULL)
    {
        return;
    }
    heapnode_try_swap_value(node, parent, UP);
    free(parent);
}

HeapNode* heapnode_left(const HeapNode* node)
{
    return heapnode_from_index(node, 2 * node->index);
}

HeapNode* heapnode_right(const HeapNode* node)
{
    return heapnode_from_index(node, 2 * node->index + 1);
}

HeapNode* heapnode_parent(const HeapNode* node)
{
    HeapNode* parent = NULL;
    if (!node->is_root)
    {
        parent = heapnode_init(node->heap, node->index / 2);
    }
    return parent;
}

HeapNode* heapnode_from_index(const HeapNode* node, int index)
{
    HeapNode* ret = NULL;
    if (!heap_is_out_of_range(node->heap, index))
    {
        ret = heapnode_init(node->heap, index);
    }
    return ret;
}

void heapnode_try_swap_value(const HeapNode* node, const HeapNode* other, HeapifyDirection direction)
{
    if (node == NULL || other == NULL)
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

Heap* heap_init(bool is_min, int capacity)
{
    Heap* heap = malloc(sizeof(Heap));
    heap->size = 0;
    heap->storage = malloc(sizeof(int) * (capacity+1));
    heap->comparer = is_min ? min_comparer : max_comparer;
    return heap;
}

void heap_store(Heap* heap, int num)
{
    ++heap->size;
    heap->storage[heap->size] = num;
    bool setting_root = heap->size == ROOT_INDEX;
    if (!setting_root)
    {
        HeapNode* added = heapnode_init(heap, heap->size);
        heapnode_heapify_up(added);
        free(added);
    }
}

bool heap_is_out_of_range(const Heap* heap, int index)
{
    return index > heap->size;
}

int heap_peek(const Heap* heap)
{
    return (heap->size > 0) ? heap->storage[ROOT_INDEX] : NOTHING;
}

int heap_take(Heap* heap)
{
    int taken = heap->storage[ROOT_INDEX];
    --heap->size;
    heap->storage[ROOT_INDEX] = heap->storage[heap->size];
    if (heap->size > 1)
    {
        HeapNode* root_node = heapnode_init(heap, ROOT_INDEX);
        heapnode_heapify_down(root_node);
        free(root_node);
    }
    return taken;
}

void heap_sort(int* ary, int count)
{
    Heap* heap = heap_init(true, count);
    int i = 0;
    for (; i < count; ++i)
    {
        heap_store(heap, ary[i]);
    }
    for (i = 0; i < count; ++i)
    {
        ary[i] = heap_take(heap);
    }
    free(heap);
}