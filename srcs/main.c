/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   main.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mtaquet <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/11/26 11:53:23 by mtaquet      #+#   ##    ##    #+#       */
/*   Updated: 2018/11/28 17:41:36 by mtaquet     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "fdf.h"
#include "mlx.h"
#include <sys/stat.h>
#include <fcntl.h>

void	ft_put_line(t_map *map, t_point start, t_point end)
{
	double dir;
	t_point pix;

	if (end.y < start.y)
		ft_pointswap(&end, &start);
	pix.x = start.x;
	if (end.x < start.x)
	{
		pix.x = end.x;
		end.x = start.x;
	}
	if ((dir = (end.x - pix.x)) != 0)
		dir = (end.y - start.y) / dir;
	pix.y = dir * pix.x + start.y;
	while (pix.x != end.x)
	{
		if ((int)(dir * pix.x + start.y) != pix.y)
		{
//				ft_pixel(map, pix.x, pix.y, ft_rgb(255/2, 255/2, 255/2));
//				ft_pixel(map, pix.x - 1, pix.y + 1, ft_rgb(255/2, 255/2, 255/2));
			while ((int)(dir * pix.x + start.y) != pix.y)
				ft_pixel(map, pix.x, pix.y++, ft_rgb(255, 255, 255));
		}
		else
			ft_pixel(map, pix.x, pix.y, ft_rgb(255, 255, 255));
		pix.x++;
	}
	if ((int)dir == 0)
		while (end.y != pix.y)
				ft_pixel(map, pix.x, pix.y++, ft_rgb(255, 255, 255));
}

void	ft_put(t_map *map, int x, int y)
{
	t_point start;
	t_point end;

	if (x < map->size.x - 1)
	{
		start.x = map->start.x + map->vx.x * x * map->lenth;
		start.y = map->start.y + map->vx.y * x * map->lenth + map->vy.y * y * map->lenth + map->vz.y * map->map[y][x] * map->lenth;
		end.x = start.x + map->vx.x * map->lenth;
		end.y = start.y + map->vx.y * map->lenth /*- map->vz.y * map->map[y][x + 1] * map->lenth*/;
		ft_put_line(map, start, end);
	}
	if (y < map->size.y - 1)
	{
		start.x = map->start.x + map->vy.x * y * map->lenth + map->vx.x * x * map->lenth;
		start.y = map->start.y + map->vy.y * y * map->lenth + map->vz.y * map->map[y][x] * map->lenth;
		end.x = start.x + map->vy.x * map->lenth;
		end.y = start.y + map->vy.y * (map->lenth + 1) - map->vz.y * map->map[y][x] * map->lenth;
		ft_put_line(map, start, end);
	}
}

void	ft_putmap(t_map *map)
{
	int x;
	int y;

	map->start.x = (map->window.x - map->lenth * (map->size.x - 1) * map->vx.x)/2;
	map->start.y = (map->window.y - map->lenth * (map->size.y - 1) * map->vy.y)/2;
	y = -1;
	while (++y < map->size.y)
	{
		x = -1;
		while (++x < map->size.x)
			ft_put(map, x, y);
	}
}

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
		mlx_clear_window(map->mlx_ptr, map->win_ptr);
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
	if (map->mouse.x -5 - (y - map->mouse.y / 10) <= x
		&& map->mouse.x + 5 + (y - map->mouse.y / 10)>= x && map->mouse.y < y)
	{
		map->mouse.x = x;
		map->mouse.y = y;
		if (map->vy.y <= -1)
			map->vy.y = 1;
		map->vy.y -= 0.025;
		map->vz.y -= 0.025;
		mlx_clear_window(map->mlx_ptr, map->win_ptr);
		ft_putmap(map);
	}
	if (map->mouse.x -5 - (y - map->mouse.y / 10) <= x
		&& map->mouse.x + 5 + (y - map->mouse.y / 10)>= x && map->mouse.y > y)
	{
		map->mouse.x = x;
		map->mouse.y = y;
		if (map->vy.y >= 1)
			map->vy.y = -1;
		map->vy.y += 0.025;
		map->vz.y += 0.025;
		mlx_clear_window(map->mlx_ptr, map->win_ptr);
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
