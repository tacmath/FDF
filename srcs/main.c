/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   main.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mtaquet <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/11/26 11:53:23 by mtaquet      #+#   ##    ##    #+#       */
/*   Updated: 2018/11/29 06:29:33 by mtaquet     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "fdf.h"
#include "mlx.h"

void	mouse_press(int x, int y, t_map *map)
{
	map->mouse.status = TRUE;
	map->mouse.x = x;
	map->mouse.y = y;
}

int	mouse_down(int button, int x, int y, t_map *map)
{
	if (button != 1)
		return (0);
	x = y;
	map->mouse.status = FALSE;
	map->mouse.x = -1;
	map->mouse.y = -1;
	return (1);
}

int deal_mouse(int button, int x, int y, t_map *map)
{
	double tmp;

	if (button == 4 || button == 5)
	{
		tmp = map->lenth;
		if ((int)tmp < 10 && button == 5)
			tmp += 0.9;
		if (button == 4)
			tmp -= tmp / 10;
		if (button == 5)
			tmp += tmp / 10;
		map->lenth = (int)tmp;
		if (map->lenth == 0)
			map->lenth = 1;
		ft_putmap(map);
	}
	if (button == 1)
		mouse_press(x, y, map);
	return (0);
}

int mouse_mv(int x, int y, t_map *map)
{
	if (map->mouse.status == FALSE)
		return (0);
	if (map->mouse.y < y)
	{
		map->mouse.x = x;
		map->mouse.y = y;
		if (map->vz.y < 0)
			map->vy.y += 0.025;
		else if (map->vy.y > 0)
			map->vy.y -= 0.025;
		if (map->vz.y < 1 && map->vy.y > -1)
			map->vz.y += 0.025;
		ft_putmap(map);
	}
	if (map->mouse.y > y)
	{
		map->mouse.x = x;
		map->mouse.y = y;
		if (map->vz.y > 0)
			map->vy.y += 0.025;
		else if (map->vy.y > 0)
			map->vy.y -= 0.025;
		if (map->vz.y > -1)
			map->vz.y -= 0.025;
		ft_putmap(map);
	}
	return (1);
}

int main(int ac, char **av)
{
	t_map	*map;

	if (ac < 2)
		return (0);
	if (!(map = malloc(sizeof(t_map))))
		return (0);
	if (!(ft_get_map(map, av[1])))
		return (0);
	map->mlx_ptr = mlx_init();
	map->win_ptr = mlx_new_window(map->mlx_ptr, map->window.x, map->window.y, "FDF");
	ft_putmap(map);
	mlx_mouse_hook(map->win_ptr, deal_mouse, map);
	mlx_hook(map->win_ptr, 6, 0, mouse_mv, map);
	mlx_hook(map->win_ptr, 5, 0, mouse_down, map);
	mlx_key_hook(map->win_ptr, deal_key, map);
	mlx_loop(map->mlx_ptr);
	return (1);
}
