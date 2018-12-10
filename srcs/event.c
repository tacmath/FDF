/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   event.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mtaquet <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/11/29 04:34:44 by mtaquet      #+#   ##    ##    #+#       */
/*   Updated: 2018/12/10 00:42:13 by mtaquet     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "fdf.h"
#include "mlx.h"
#define KEY_ESCAPE	53
#define KEY_PLUS	69
#define KEY_MINUS	78
#define KEY_UP		126
#define KEY_DOWN	125
#define KEY_RIGHT	124
#define KEY_LEFT	123
#define KEY_ONE		18
#define KEY_TWO		19
#define KEY_THREE	20
#define KEY_C		8
#define KEY_P		35

int		deal_press_key(int key, t_map *map)
{
	if (key == KEY_PLUS)
		map->height += map->height / 40;
	if (key == KEY_MINUS)
		map->height -= map->height / 40;
	if (key == KEY_UP)
		map->motion.y += 8;
	if (key == KEY_DOWN)
		map->motion.y -= 8;
	if (key == KEY_RIGHT)
		map->motion.x -= 8;
	if (key == KEY_LEFT)
		map->motion.x += 8;
	if (map->color.status == TRUE && key >= KEY_ONE && key <= KEY_THREE)
	{
		if (key == KEY_ONE)
			ft_color_change(&(map->color.colort));
		if (key == KEY_TWO)
			ft_color_change(&(map->color.colorm));
		if (key == KEY_THREE)
			ft_color_change(&(map->color.colorb));
		ft_putmap(map);
	}
	if (key == KEY_PLUS || key == KEY_MINUS || (key >= 123 && key <= 126))
		ft_putmap(map);
	return (0);
}

void	chage_projection(t_map *map)
{
	if (map->vx.x == 1000)
	{
		map->vx.x = 800;
		map->vx.y = 180;
		map->vy.x = -200;
		map->vy.y = 720;
		map->vz.y = -100;
	}
	else if (map->vx.x == 800)
	{
		map->vx.x = 500;
		map->vx.y = 450;
		map->vy.x = -500;
		map->vy.y = 450;
		map->vz.y = -100;
	}
	else
	{
		map->vx.x = 1000;
		map->vx.y = 0;
		map->vy.x = 0;
		map->vy.y = 900;
		map->vz.y = -100;
	}
}

int		deal_key(int key, t_map *map)
{
	if (key == KEY_C && map->color.status == FALSE)
		map->color.status = TRUE;
	else if (key == KEY_C)
		map->color.status = FALSE;
	if (key == KEY_P)
		chage_projection(map);
	if (key == KEY_C || key == KEY_P)
		ft_putmap(map);
	if (key == KEY_ESCAPE)
	{
		ft_free_map(map);
		exit(1);
	}
	return (1);
}

int		ft_destroy(t_map *map)
{
	ft_free_map(map);
	exit(1);
	return (1);
}
