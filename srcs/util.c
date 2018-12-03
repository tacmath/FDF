/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   util.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mtaquet <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/11/26 11:53:23 by mtaquet      #+#   ##    ##    #+#       */
/*   Updated: 2018/12/03 12:41:00 by mtaquet     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "fdf.h"
#include "mlx.h"

int	ft_sqr(int nb)
{
    int n;
    
    n = 0;
    while (n * n < nb)
        n++;
    return (n);
}

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
	free(map->win_ptr);
	free(map->mlx_ptr);
	free(map);
}

void	ft_pointswap(t_point *a, t_point *b)
{
	t_point tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}
