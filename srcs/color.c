/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   draw.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mtaquet <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/11/29 04:34:57 by mtaquet      #+#   ##    ##    #+#       */
/*   Updated: 2018/11/29 06:37:18 by mtaquet     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "fdf.h"
#include "mlx.h"

void	ft_color_init(t_map *map)
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

void	ft_color_change(t_rgb *color)
{
	if ((*color).b == 0)
		(*color).b = 255;
	else if ((*color).g == 0)
	{
		(*color).g = 255;
		(*color).b = 0;
	}
	else if ((*color).r == 0)
        {
                (*color).r = 255;
                (*color).b = 0;
		(*color).g = 0;
        }
	else
	{
		(*color).r = 0;
                (*color).b = 255;
                (*color).g = 0;
	}
}

void	ft_pixel(t_map *map, int x, int y)
{
	t_rgb color;
	
	if (map->color.status == TRUE)
	{
		color.r = map->color.start.r + ((map->color.end.r - map->color.start.r) / map->lenth) * map->color.n;
		color.g = map->color.start.g + ((map->color.end.g - map->color.start.g) / map->lenth) * map->color.n;
		color.b = map->color.start.b + ((map->color.end.b - map->color.start.b) / map->lenth) * map->color.n;
		map->color.n++;
		mlx_pixel_put(map->mlx_ptr, map->win_ptr, x, y, ft_rgb(color.r, color.g, color.b));
	}
	else
		mlx_pixel_put(map->mlx_ptr, map->win_ptr, x, y, 0xFFFFFF);
}

void	ft_colorput(t_map *map, int start, int end)
{
	if (map->color.status == FALSE)
		return ;
	map->color.n = 0;
	if (start > 0)
         	map->color.start = map->color.colort;
	else if (start < 0)
		map->color.start = map->color.colorb;
        else
		map->color.start = map->color.colorm;
        if (end > 0)
        	map->color.end = map->color.colort;
	else if (end < 0)
		map->color.end = map->color.colorb;
        else
        	map->color.end = map->color.colorm;
}
