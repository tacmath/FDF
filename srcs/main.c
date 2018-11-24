#include "fdf.h"
#include <sys/stat.h>
#include <fcntl.h>

void	ft_free_struct(t_fdf *map)
{
	size_t n;

	n = -1;
	while (++n < map->size.y)
		free(map->map[n]);
	free(map->map);
	free(map);
}


int main(int ac, char **av)
{
	t_fdf	*map;

	if (ac != 2)
		return (0);
	if (!(map = malloc(sizeof(t_fdf))))
		return (0);
	ft_get_map(map, av[1]);
	ft_free_struct(map);
	return (1);
}
