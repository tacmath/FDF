/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   event.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mtaquet <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/11/29 04:34:44 by mtaquet      #+#   ##    ##    #+#       */
/*   Updated: 2018/12/04 14:35:17 by mtaquet     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "fdf.h"
#include "mlx.h"

int	deal_press_key(int key, t_map *map)
{
	if (key == 69)
		map->height += map->height / 40;
	if (key == 78)
		map->height -= map->height / 40;
	if (key == 126)
		map->motion.y -= 8;
	if (key == 125)
		map->motion.y += 8;
	if (key == 124)
		map->motion.x += 8;
	if (key == 123)
		map->motion.x -= 8;
	if (map->color.status == TRUE && key >= 18 && key <= 20)
	{
		if (key == 18)
			ft_color_change(&(map->color.colort));
		if (key == 19)
                        ft_color_change(&(map->color.colorm));
		if (key == 20)
                        ft_color_change(&(map->color.colorb));
		ft_putmap(map);		
	}
	if (key == 69 || key == 78 || (key >= 123 && key <= 126))
		ft_putmap(map);
	return (0);
}

int	deal_key(int key, t_map *map)
{
	if (key == 8 && map->color.status == FALSE)
		map->color.status = TRUE;
	else if (key == 8)
		map->color.status = FALSE;
	if (key == 8)
		ft_putmap(map);
    if (key == 53)
    {
        ft_free_map(map);
        exit(1);
    }
    return (1);
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
            map->vy.y += 0.025;
        else if (map->vy.y > 0)
            map->vy.y -= 0.025;
        if (map->vz.y < 1 && map->vy.y > -1)
            map->vz.y += 0.025;
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
    }
	ft_putmap(map);
	return (1);
}
