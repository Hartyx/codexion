#include "codexion.h"

int	heap_init(t_heap *heap, int cap)
{
	heap->size = 0;
	heap->cap = cap;
	heap->nodes = malloc(sizeof(t_node) * cap);
	if (!heap->nodes)
		return (1);
	return (0);
}

void	heap_destroy(t_heap *heap)
{
	free(heap->nodes);
	heap->nodes = NULL;
	heap->size = 0;
}

int	heap_push(t_heap *heap, long key, int id)
{
	if (heap->size >= heap->cap)
		return (1);
	heap->nodes[heap->size].key = key;
	heap->nodes[heap->size].id = id;
	heap->size++;
	sift_up(heap, heap->size - 1);
	return (0);
}

int	heap_top_id(t_heap *heap)
{
	if (heap->size == 0)
		return (0);
	return (heap->nodes[0].id);
}

void	heap_pop(t_heap *heap)
{
	if (heap->size == 0)
		return ;
	heap->size--;
	heap->nodes[0] = heap->nodes[heap->size];
	sift_down(heap, 0);
}