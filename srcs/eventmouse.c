/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   eventmouse.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mtaquet <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/12/04 16:54:17 by mtaquet      #+#   ##    ##    #+#       */
/*   Updated: 2018/12/10 01:07:33 by mtaquet     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "fdf.h"
#include "mlx.h"
#define RIGHT_CLICK		1
#define ROULETTE_UP		5
#define ROULETTE_DOWN	4

void		mouse_press(int x, int y, t_map *map)
{
	map->mouse.status = TRUE;
	map->mouse.x = x;
	map->mouse.y = y;
}

int			mouse_down(int button, int x, int y, t_map *map)
{
	if (button != 1)
		return (0);
	x = y;
	map->mouse.status = FALSE;
	map->mouse.x = -1;
	map->mouse.y = -1;
	return (1);
}

int			deal_mouse(int button, int x, int y, t_map *map)
{
	double	tmp;

	if (button == ROULETTE_DOWN || button == ROULETTE_UP)
	{
		tmp = map->length;
		if ((int)tmp < 10 && button == ROULETTE_UP)
			tmp += 0.9;
		if (button == ROULETTE_DOWN)
			tmp -= tmp / 10;
		if (button == ROULETTE_UP)
			tmp += tmp / 10;
		map->length = (int)tmp;
		if (map->length == 0)
			map->length = 1;
		ft_putmap(map);
	}
	if (button == RIGHT_CLICK)
		mouse_press(x, y, map);
	return (0);
}

static void	mv_up(t_map *map, int x, int y)
{
	if (map->mouse.y < y)
	{
		map->mouse.x = x;
		map->mouse.y = y;
		if (map->vz.y < 0)
		{
			map->vx.y += (1000 - ft_abs(map->vx.x)) / 40;
			map->vy.y += (1000 - ft_abs(map->vy.x)) / 40;
		}
		else if (map->vy.y > 0)
		{
			map->vx.y -= (1000 - ft_abs(map->vx.x)) / 40;
			map->vy.y -= (1000 - ft_abs(map->vy.x)) / 40;
		}
		if (map->vz.y < 1000 && map->vy.y > -1000)
			map->vz.y += 25;
	}
}

int			mouse_mv(int x, int y, t_map *map)
{
	if (x < 0 || y < 0)
		map->mouse.status = FALSE;
	if (map->mouse.status == FALSE)
		return (0);
	mv_up(map, x, y);
	if (map->mouse.y > y)
	{
		map->mouse.x = x;
		map->mouse.y = y;
		if (map->vz.y > 0)
		{
			map->vx.y += (1000 - ft_abs(map->vx.x)) / 40;
			map->vy.y += (1000 - ft_abs(map->vy.x)) / 40;
		}
		else if (map->vy.y > 0)
		{
			map->vx.y -= (1000 - ft_abs(map->vx.x)) / 40;
			map->vy.y -= (1000 - ft_abs(map->vy.x)) / 40;
		}
		if (map->vz.y > -1000)
			map->vz.y -= 25;
	}
	ft_putmap(map);
	return (1);
}
