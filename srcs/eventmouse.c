/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   eventmouse.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mtaquet <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/12/04 16:54:17 by mtaquet      #+#   ##    ##    #+#       */
/*   Updated: 2018/12/04 16:56:30 by mtaquet     ###    #+. /#+    ###.fr     */
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
	if (map->mouse.status == FALSE || x < 0 || y < 0)
		return (0);
	if (map->mouse.y < y)
	{
		map->mouse.x = x;
		map->mouse.y = y;
		if (map->vz.y < 0)
			map->vy.y += 25;
		else if (map->vy.y > 0)
			map->vy.y -= 25;
		if (map->vz.y < 1000 && map->vy.y > -1000)
			map->vz.y += 25;
	}
	if (map->mouse.y > y)
	{
		map->mouse.x = x;
		map->mouse.y = y;
		if (map->vz.y > 0)
			map->vy.y += 25;
		else if (map->vy.y > 0)
			map->vy.y -= 25;
		if (map->vz.y > -1000)
			map->vz.y -= 25;
	}
	ft_putmap(map);
	return (1);
}
