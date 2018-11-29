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
	if (key == 69 || key == 78 || (key >= 123 && key <= 126))
		ft_putmap(map);
    if (key == 53)
    {
        ft_free_map(map);
        exit(1);
    }
    return (1);
}
