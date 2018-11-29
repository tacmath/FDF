/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   draw.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mtaquet <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/11/29 04:34:57 by mtaquet      #+#   ##    ##    #+#       */
/*   Updated: 2018/11/29 06:07:35 by mtaquet     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "fdf.h"
#include "mlx.h"

void	ft_pixel(t_map *map, int x, int y, int color)
{
    mlx_pixel_put(map->mlx_ptr, map->win_ptr, x, y, color);
}

void	ft_put_line(t_map *map, t_point start, t_point end)
{
    double dir;
    t_point pix;
    
    if (end.x < start.x)
        ft_pointswap(&end, &start);
    pix.x = start.x;
    if ((dir = end.x - start.x) != 0)
        dir = (end.y - start.y) / dir;
    pix.y = start.y;
    while (pix.x < end.x)
    {
        if ((int)(dir * (pix.x - start.x) + start.y) != pix.y)
        {
            //				ft_pixel(map, pix.x, pix.y, ft_rgb(255/2, 255/2, 255/2));
            //				ft_pixel(map, pix.x - 1, pix.y + 1, ft_rgb(255/2, 255/2, 255/2));
            while ((int)(dir * (pix.x - start.x) + start.y) != pix.y)
            {
                ft_pixel(map, pix.x, pix.y, ft_rgb(255, 255, 255));
                if ((int)(dir * (pix.x - start.x) + start.y) > pix.y)
                    pix.y++;
                else
                    pix.y--;
            }
        }
        else
            ft_pixel(map, pix.x, pix.y, ft_rgb(255, 255, 255));
        pix.x++;
    }
    if ((end.x - start.x) == 0)
        while (end.y != pix.y)
        {
            ft_pixel(map, pix.x, pix.y, ft_rgb(255, 255, 255));
            if (end.y > pix.y)
                pix.y++;
            else
                pix.y--;
        }
}

void	ft_put_point(t_map *map, int x, int y)
{
    t_point start;
    t_point end;
    
    if (x < map->size.x - 1)
    {
        start.x = map->start.x + (map->vx.x * x) * map->lenth;
        start.y = map->start.y + (map->vx.y * x + map->vy.y * y + map->vz.y * map->map[y][x] * map->height) * map->lenth;
        end.x = map->start.x + (map->vx.x * (x + 1)) * map->lenth;
        end.y = map->start.y + (map->vx.y * (x + 1) + map->vy.y * y + map->vz.y * map->map[y][x + 1] * map->height) * map->lenth;
        ft_put_line(map, start, end);
    }
    if (y < map->size.y - 1)
    {
        start.x = map->start.x + (map->vy.x * y + map->vx.x * x) * map->lenth;
        start.y = map->start.y + (map->vy.y * y + map->vz.y * map->map[y][x] * map->height) * map->lenth;
        end.x = map->start.x + (map->vy.x * (y + 1) + map->vx.x * x) * map->lenth;
        end.y = map->start.y + (map->vy.y * (y + 1) + map->vz.y * map->map[y + 1][x] * map->height) * map->lenth;
        ft_put_line(map, start, end);
    }
}

void	ft_putmap(t_map *map)
{
    int x;
    int y;
    
    mlx_clear_window(map->mlx_ptr, map->win_ptr);
    map->start.x = (map->window.x - map->lenth * (map->size.x - 1) * map->vx.x)/2 + map->motion.x;
    map->start.y = (map->window.y - map->lenth * (map->size.y - 1) * map->vy.y)/2 + map->motion.y;
    y = -1;
    while (++y < map->size.y)
    {
        x = -1;
        while (++x < map->size.x)
            ft_put_point(map, x, y);
    }
}
