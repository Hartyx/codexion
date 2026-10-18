#include "codexion.h"

int	node_less(t_node *a, t_node *b)
{
	if (a->key != b->key)
		return (a->key < b->key);
	return (a->id < b->id);
}

void	heap_swap(t_node *a, t_node *b)
{
	t_node	tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

void	sift_up(t_heap *heap, int i)
{
	int	parent;

	while (i > 0)
	{
		parent = (i - 1) / 2;
		if (!node_less(&heap->nodes[i], &heap->nodes[parent]))
			return ;
		heap_swap(&heap->nodes[i], &heap->nodes[parent]);
		i = parent;
	}
}

void	sift_down(t_heap *heap, int i)
{
	int	best;
	int	left;
	int	right;

	while (1)
	{
		best = i;
		left = 2 * i + 1;
		right = 2 * i + 2;
		if (left < heap->size
			&& node_less(&heap->nodes[left], &heap->nodes[best]))
			best = left;
		if (right < heap->size
			&& node_less(&heap->nodes[right], &heap->nodes[best]))
			best = right;
		if (best == i)
			return ;
		heap_swap(&heap->nodes[i], &heap->nodes[best]);
		i = best;
	}
}