/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   event.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mtaquet <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/11/29 04:34:44 by mtaquet      #+#   ##    ##    #+#       */
/*   Updated: 2018/11/29 05:48:42 by mtaquet     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "fdf.h"
#include "mlx.h"

int	deal_key(int key, t_map *map)
{
//	ft_putnbr(key);
	if (key == 8 && map->color.status == FALSE)
		map->color.status = TRUE;
	else if (key == 8)
		map->color.status = FALSE;
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
	if (key == 69)
		map->height += map->height / 10;
	if (key == 78)
		map->height -= map->height / 10;
	if (key == 126)
		map->motion.y -= 50;
	if (key == 125)
		map->motion.y += 50;
	if (key == 124)
		map->motion.x += 50;
	if (key == 123)
		map->motion.x -= 50;
	if (key == 8 || key == 69 || key == 78 || (key >= 123 && key <= 126))
		ft_putmap(map);
    if (key == 53)
    {
        ft_free_map(map);
        exit(1);
    }
    return (1);
}
