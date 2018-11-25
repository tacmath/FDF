#include "fdf.h"
#include <sys/stat.h>
#include <fcntl.h>

void	ft_free_struct(t_map *map)
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
	t_map	*map;

	if (ac != 2)
		return (0);
	if (!(map = malloc(sizeof(t_map))))
		return (0);
	ft_get_map(map, av[1]);
/*	map->mlx_ptr = mlx_init();
**	map->win_ptr = mlx_new_window(map->mlx_ptr, 1000, 600, "FDF");
**	mlx_loop(map->mlx_ptr);
*/	ft_free_struct(map);
	return (1);
}
