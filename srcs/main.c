/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   main.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mtaquet <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/11/26 11:53:23 by mtaquet      #+#   ##    ##    #+#       */
/*   Updated: 2018/11/26 16:03:45 by mtaquet     ###    #+. /#+    ###.fr     */
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

	if (end.x < start.x)
		ft_swap(&(end.x), &(start.x));
	if (end.y < start.y)
		ft_swap(&(end.y), &(start.y));
	if ((dir = (end.x - start.x)) != 0)
		dir = (end.y - start.y) / dir;
	pix.x = start.x;
	pix.y = dir * pix.x + start.y;
	while (pix.x < end.x)
	{
		if ((int)(dir * pix.x + start.y) > pix.y)
		{
//				ft_pixel(map, pix.x, pix.y, ft_rgb(255/2, 255/2, 255/2));
//				ft_pixel(map, pix.x - 1, pix.y + 1, ft_rgb(255/2, 255/2, 255/2));
			while ((int)(dir * pix.x + start.y) > pix.y)
				ft_pixel(map, pix.x, pix.y++, ft_rgb(255, 255, 255));
		}
		else
			ft_pixel(map, pix.x, pix.y, ft_rgb(255, 255, 255));
		pix.x++;
	}
	if ((int)dir == 0)
		while (end.y > pix.y)
				ft_pixel(map, pix.x, pix.y++, ft_rgb(255, 255, 255));
}

void	ft_put(t_map *map, int x, int y)
{
	t_point start;
	t_point end;

	if (x < map->size.x - 1)
	{
		start.x = map->start.x + map->vx.x * x * map->lenth;
		start.y = map->start.y + map->vx.y * x * map->lenth + map->vy.y * y * map->lenth;
		end.x = start.x + map->vx.x * map->lenth;
		end.y = start.y + map->vx.y * map->lenth;
		ft_put_line(map, start, end);
	}
	if (y < map->size.y - 1)
	{
		start.x = map->start.x + map->vy.x * y * map->lenth + map->vx.x * x * map->lenth;
		start.y = map->start.y + map->vy.y * y * map->lenth;
		end.x = start.x + map->vy.x * map->lenth;
		end.y = start.y + map->vy.y * map->lenth;
		ft_put_line(map, start, end);
	}
}

int main(int ac, char **av)
{
	t_map	*map;
	int x;
	int y;

	if (ac != 2)
		return (0);
	if (!(map = malloc(sizeof(t_map))))
		return (0);
	ft_get_map(map, av[1]);
	map->mlx_ptr = mlx_init();
	map->win_ptr = mlx_new_window(map->mlx_ptr, map->window.x, map->window.y, "FDF");
	y = -1;
	while (++y < map->size.y)
	{
		x = -1;
		while (++x < map->size.x)
			ft_put(map, x, y);
	}
	mlx_key_hook(map->win_ptr, deal_key, (void*)map);
	mlx_loop(map->mlx_ptr);
	ft_free_map(map);
	return (1);
}
