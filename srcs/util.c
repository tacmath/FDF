/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   util.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mtaquet <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/11/26 11:53:23 by mtaquet      #+#   ##    ##    #+#       */
/*   Updated: 2018/11/28 12:28:31 by mtaquet     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "fdf.h"
#include "mlx.h"
#include <sys/stat.h>
#include <fcntl.h>

int		ft_rgb(unsigned int r, unsigned int g, unsigned int b)
{
	return ((r << 16) | (g << 8) | b);
}

void	ft_free_map(t_map *map)
{
	int n;

	n = -1;
	while (++n < map->size.y)
		free(map->map[n]);
	free(map->map);
	free(map);
}

int	deal_key(int key, t_map *map)
{
	if (key == 53)
	{
		ft_free_map(map);
		exit(1);
	}
	return (1);
}

void	ft_pixel(t_map *map, int x, int y, int color)
{
	mlx_pixel_put(map->mlx_ptr, map->win_ptr, x, y, color);
}

void	ft_pointswap(t_point *a, t_point *b)
{
	t_point tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}
