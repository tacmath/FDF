/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   draw.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mtaquet <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/11/29 04:34:57 by mtaquet      #+#   ##    ##    #+#       */
/*   Updated: 2018/12/10 00:19:38 by mtaquet     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "fdf.h"
#include "mlx.h"

static void	ft_linex(t_map *map, t_point start, t_point *pix, double dir)
{
	if ((int)(dir * ((*pix).x - start.x) + start.y) != (*pix).y)
	{
		while ((int)(dir * ((*pix).x - start.x) + start.y) != (*pix).y)
		{
			ft_pixel(map, (*pix).x - 1, (*pix).y);
			if ((int)(dir * ((*pix).x - start.x) + start.y) > (*pix).y)
				(*pix).y++;
			else
				(*pix).y--;
		}
	}
	else
		ft_pixel(map, (*pix).x - 1, (*pix).y);
	(*pix).x++;
}

void		ft_put_line(t_map *map, t_point start, t_point end)
{
	double	dir;
	t_point	pix;

	if (end.x < start.x)
		ft_colorswap(&(map->color.start), &(map->color.end));
	if (end.x < start.x)
		ft_pointswap(&end, &start);
	map->linelength = ft_sqr(ft_abs(ft_power(end.x - start.x, 2)
				+ ft_power(ft_abs(end.y - start.y), 2)));
	pix.x = start.x + 1;
	if ((dir = end.x - start.x) != 0)
		dir = (end.y - start.y) / dir;
	pix.y = start.y;
	while (pix.x <= end.x)
		ft_linex(map, start, &pix, dir);
	if ((end.x - start.x) == 0)
		while (end.y != pix.y)
		{
			ft_pixel(map, pix.x - 1, pix.y);
			if (end.y > pix.y)
				pix.y++;
			else
				pix.y--;
		}
}

static void	ft_put_colone(t_map *map, int x, int y)
{
	t_point	start;
	t_point	end;

	if (y >= map->size.y - 1)
		return ;
	start.x = map->start.x + ((map->vy.x * y + map->vx.x * x +
		map->vz.x * map->map[y][x] * map->height) * map->length) / 1000;
	start.y = map->start.y + ((map->vy.y * y + map->vx.y * x +
		map->vz.y * map->map[y][x] * map->height) * map->length) / 1000;
	end.x = start.x + ((map->vy.x + map->vz.x * (map->map[y + 1][x]
		- map->map[y][x]) * map->height) * map->length) / 1000;
	end.y = start.y + ((map->vy.y + map->vz.y * (map->map[y + 1][x]
		- map->map[y][x]) * map->height) * map->length) / 1000;
	ft_colorput(map, map->map[y][x], map->map[y + 1][x]);
	if ((start.x < 0 && end.x < 0) || (end.x > map->window.x && start.x >
		map->window.x) || (start.y < 0 && end.y < 0) ||
		(end.y > map->window.y && start.y > map->window.y))
		return ;
	ft_put_line(map, start, end);
}

static void	ft_put_point(t_map *map, int x, int y)
{
	t_point	start;
	t_point	end;

	ft_put_colone(map, x, y);
	if (x >= map->size.x - 1)
		return ;
	start.x = map->start.x + ((map->vx.x * x + map->vy.x * y
		+ map->vz.x * map->map[y][x] * map->height) * map->length) / 1000;
	start.y = map->start.y + ((map->vx.y * x + map->vy.y * y
		+ map->vz.y * map->map[y][x] * map->height) * map->length) / 1000;
	end.x = start.x + ((map->vx.x + map->vz.x * (map->map[y][x + 1]
		- map->map[y][x]) * map->height) * map->length) / 1000;
	end.y = start.y + ((map->vx.y + map->vz.y * (map->map[y][x + 1]
		- map->map[y][x]) * map->height) * map->length) / 1000;
	ft_colorput(map, map->map[y][x], map->map[y][x + 1]);
	if ((start.x < 0 && end.x < 0) || (end.x > map->window.x && start.x >
		map->window.x) || (start.y < 0 && end.y < 0) ||
		(end.y > map->window.y && start.y > map->window.y))
		return ;
	ft_put_line(map, start, end);
}

void		ft_putmap(t_map *map)
{
	int	x;
	int	y;

	mlx_clear_window(map->mlx_ptr, map->win_ptr);
	map->start.x = (map->window.x - (map->length * ((map->size.x - 1) *
		map->vx.x + (map->size.y - 1) * map->vy.x) / 1000)) / 2 + map->motion.x;
	map->start.y = (map->window.y - (map->length * ((map->size.y - 1) *
		map->vy.y + (map->size.x - 1) * map->vx.y) / 1000)) / 2 + map->motion.y;
	y = -1;
	while (++y < map->size.y)
	{
		x = -1;
		while (++x < map->size.x)
			ft_put_point(map, x, y);
	}
}
