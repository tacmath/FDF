/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   init.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mtaquet <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/12/05 13:34:41 by mtaquet      #+#   ##    ##    #+#       */
/*   Updated: 2018/12/10 00:44:06 by mtaquet     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "fdf.h"
#include "mlx.h"

static void	ft_color_init(t_map *map)
{
	map->color.status = FALSE;
	map->color.colorb.r = 0;
	map->color.colorb.g = 255;
	map->color.colorb.b = 0;
	map->color.colorm.r = 0;
	map->color.colorm.g = 0;
	map->color.colorm.b = 255;
	map->color.colort.r = 255;
	map->color.colort.g = 0;
	map->color.colort.b = 0;
}

static void	ft_map_init(t_map *map)
{
	if (map->size.y > map->size.x)
	{
		map->window.y = (map->size.y / (double)map->size.x) * 800 + 200;
		map->length = (map->window.y - 200) / map->size.y;
		map->window.x = map->length * map->size.x + 200;
	}
	else
	{
		map->window.x = (map->size.x / (double)map->size.y) * 800 + 200;
		map->length = (map->window.x - 200) / map->size.x;
		map->window.y = map->length * map->size.y + 200;
	}
	map->height = 1;
	map->mouse.status = FALSE;
	map->motion.x = 0;
	map->motion.y = 0;
	map->vx.x = 800;
	map->vx.y = 180;
	map->vy.x = -200;
	map->vy.y = 720;
	map->vz.x = 0;
	map->vz.y = -100;
}

int			ft_map_alloc(t_map *map)
{
	int	n;

	n = -1;
	if (!(map->map = malloc(sizeof(short int*) * map->size.y)))
		return (0);
	while (++n < map->size.y)
		if (!(map->map[n] = malloc(sizeof(short int) * map->size.x)))
			return (0);
	ft_map_init(map);
	ft_color_init(map);
	return (1);
}

void		ft_limit(t_map *map)
{
	int x;
	int y;

	map->heightmax = 0;
	map->heightmin = 0;
	y = -1;
	while (++y < map->size.y)
	{
		x = -1;
		while (++x < map->size.x)
		{
			if (map->heightmax < map->map[y][x])
				map->heightmax = map->map[y][x];
			if (map->heightmin > map->map[y][x])
				map->heightmin = map->map[y][x];
		}
	}
}
