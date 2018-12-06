/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   draw.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mtaquet <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/11/29 04:34:57 by mtaquet      #+#   ##    ##    #+#       */
/*   Updated: 2018/12/05 14:46:54 by mtaquet     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "fdf.h"
#include "mlx.h"

void			ft_colorswap(t_rgb *c1, t_rgb *c2)
{
	t_rgb tmp;

	tmp = *c1;
	*c1 = *c2;
	*c2 = tmp;
}

void			ft_color_change(t_rgb *color)
{
	if ((*color).b < 255 && (*color).g == 0)
		(*color).b += 15;
	else if ((*color).g < 255 && (*color).r == 0)
		(*color).g += 15;
	else if ((*color).g == 255 && (*color).b > 0)
		(*color).b -= 15;
	else if ((*color).r < 255 && (*color).b == 0)
		(*color).r += 15;
	else if ((*color).r == 255 && (*color).g > 0)
		(*color).g -= 15;
	else if ((*color).r > 0)
		(*color).r -= 15;
}

void			ft_pixel(t_map *map, int x, int y)
{
	t_rgb	color;
	int		h;

	if (map->color.status == TRUE)
	{
		h = map->linelenth;
		color.r = map->color.start.r + ((map->color.end.r -
					map->color.start.r) * map->color.n) / h;
		color.g = map->color.start.g + ((map->color.end.g -
					map->color.start.g) * map->color.n) / h;
		color.b = map->color.start.b + ((map->color.end.b -
					map->color.start.b) * map->color.n) / h;
		map->color.n++;
		mlx_pixel_put(map->mlx_ptr, map->win_ptr, x, y,
			ft_rgb(color.r, color.g, color.b));
	}
	else
		mlx_pixel_put(map->mlx_ptr, map->win_ptr, x, y, 0xFFFFFF);
}

static t_rgb	ft_colordivide(t_rgb c1, t_rgb c2, int div, int mul)
{
	c1.r = ((c1.r * mul) / div) + ((c2.r * (div - mul)) / div);
	c1.g = ((c1.g * mul) / div) + ((c2.g * (div - mul)) / div);
	c1.b = ((c1.b * mul) / div) + ((c2.b * (div - mul)) / div);
	return (c1);
}

void			ft_colorput(t_map *map, int start, int end)
{
	if (map->color.status == FALSE)
		return ;
	map->color.n = 0;
	if (start > 0)
		map->color.start = ft_colordivide(map->color.colort,
				map->color.colorm, map->heightmax, start);
	else if (start < 0)
		map->color.start = ft_colordivide(map->color.colorb,
				map->color.colorm, map->heightmin, start);
	else
		map->color.start = map->color.colorm;
	if (end > 0)
		map->color.end = ft_colordivide(map->color.colort,
				map->color.colorm, map->heightmax, end);
	else if (end < 0)
		map->color.end = ft_colordivide(map->color.colorb,
				map->color.colorm, map->heightmin, end);
	else
		map->color.end = map->color.colorm;
}
