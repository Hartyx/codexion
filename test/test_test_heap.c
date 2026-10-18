#include "codexion.h"

int	main(void)
{
	t_heap	h;
	long	keys[6] = {50, 10, 30, 10, 20, 5};
	int		i;

	if (heap_init(&h, 10))
		return (1);
	i = 0;
	while (i < 6)
	{
		heap_push(&h, keys[i], i + 1);
		i++;
	}
	while (h.size > 0)
	{
		printf("id=%d key=%ld\n", heap_top_id(&h), h.nodes[0].key);
		heap_pop(&h);
	}
	heap_destroy(&h);
	return (0);
}