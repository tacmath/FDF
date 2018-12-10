/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   fdf.h                                            .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mtaquet <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/12/05 14:37:32 by mtaquet      #+#   ##    ##    #+#       */
/*   Updated: 2018/12/10 02:18:51 by mtaquet     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H
# include "libft.h"
# define TRUE 1
# define FALSE 0

struct					s_point
{
	int					x;
	int					y;
};

typedef struct s_point	t_point;

struct					s_mouse
{
	char				status;
	int					x;
	int					y;
};

typedef struct s_mouse	t_mouse;

struct					s_rgb
{
	unsigned char		r;
	unsigned char		g;
	unsigned char		b;
};

typedef struct s_rgb	t_rgb;

struct					s_color
{
	int					n;
	char				status;
	t_rgb				start;
	t_rgb				end;
	t_rgb				colort;
	t_rgb				colorm;
	t_rgb				colorb;
};

typedef struct s_color	t_color;

struct					s_map
{
	void				*mlx_ptr;
	void				*win_ptr;
	char				**map;
	int					length;
	int					linelength;
	double				height;
	int					heightmax;
	int					heightmin;
	t_point				size;
	t_point				window;
	t_point				motion;
	t_point				start;
	t_mouse				mouse;
	t_color				color;
	t_point				vx;
	t_point				vy;
	t_point				vz;
};

typedef struct s_map	t_map;

int						ft_destroy(t_map *map);
void					ft_color_change(t_rgb *color);
int						ft_rgb(unsigned int r, unsigned int g, unsigned int b);
int						deal_key(int key, t_map *map);
int						deal_press_key(int key, t_map *map);
void					ft_pointswap(t_point *a, t_point *b);
void					ft_free_map(t_map *map);
void					ft_pixel(t_map *map, int x, int y);
void					ft_put_line(t_map *map, t_point start, t_point end);
void					ft_colorput(t_map *map, int start, int end);
void					ft_putmap(t_map *map);
int						ft_get_map(t_map *map, char *file);
int						ft_sqr(int nb);
void					ft_colorswap(t_rgb *c1, t_rgb *c2);
int						deal_mouse(int button, int x, int y, t_map *map);
int						mouse_down(int button, int x, int y, t_map *map);
void					mouse_press(int x, int y, t_map *map);
int						mouse_mv(int x, int y, t_map *map);
int						error_msg(char *str);
int						ft_map_alloc(t_map *map);
void					ft_limit(t_map *map);

#endif
