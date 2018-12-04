/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   main.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mtaquet <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/11/26 11:53:23 by mtaquet      #+#   ##    ##    #+#       */
/*   Updated: 2018/12/04 15:30:09 by mtaquet     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "fdf.h"
#include "mlx.h"

int ft_destroy(t_map *map)
{
	ft_free_map(map);
	exit(1);
	return (1);
}

int main(int ac, char **av)
{
	t_map	*map;

	if (ac != 2)
		return (error_msg("Usage : ./fdf <filename> [ case_size z_size ]"));
	if (!(map = malloc(sizeof(t_map))))
		return (0);
	if (!(ft_get_map(map, av[1])))
		return (0);
	map->mlx_ptr = mlx_init();
	map->win_ptr = mlx_new_window(map->mlx_ptr,
		map->window.x, map->window.y, "FDF");
	ft_putmap(map);
	mlx_mouse_hook(map->win_ptr, deal_mouse, map);
	mlx_hook(map->win_ptr, 2, 0, deal_press_key, map);
	mlx_hook(map->win_ptr, 17, 0, ft_destroy, map);
	mlx_hook(map->win_ptr, 6, 0, mouse_mv, map);
	mlx_hook(map->win_ptr, 5, 0, mouse_down, map);
	mlx_key_hook(map->win_ptr, deal_key, map);
	mlx_loop(map->mlx_ptr);
	return (1);
}
