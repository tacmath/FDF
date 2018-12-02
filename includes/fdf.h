#ifndef FDF_H
# define FDF_H
# include "../libft/includes/libft.h"
# define TRUE 1
# define FALSE 0

struct		s_size
{
	int	x;
	int	y;
};

typedef struct s_size t_size;

struct		s_point
{
	int	x;
	int	y;
};

typedef struct s_point t_point;

struct		s_mouse
{
	char	status;
	int		x;
	int		y;
};

typedef struct s_mouse t_mouse;

struct		s_coord
{
	double	x;
	double	y;
	double	z;
};

typedef struct s_coord t_coord;

struct          s_rgb
{
        unsigned char r;
	unsigned char g;
	unsigned char b;
};

typedef struct s_rgb t_rgb;

struct          s_color
{
	int n;
	char status;
        t_rgb start;
	t_rgb end;
	t_rgb colort;
	t_rgb colorm;
	t_rgb colorb;
};

typedef struct s_color t_color;

struct		s_map
{
	void	*mlx_ptr;
	void	*win_ptr;
	char	**map;
	int	lenth;
	double	height;
	t_size	size;
	t_size	window;
	t_size	motion;
	t_point start;
	t_mouse mouse;
	t_color color;
	t_mouse test;			//enlever si plus besoin
	t_coord vx;
	t_coord vy;
	t_coord vz;
};

typedef struct s_map t_map;

void	ft_color_init(t_map *map);
void    ft_color_change(t_rgb *color);
int		ft_rgb(unsigned int r, unsigned int g, unsigned int b);
int		deal_key(int key, t_map *map);
void	ft_pointswap(t_point *a, t_point *b);
void	ft_free_map(t_map *map);
void	ft_pixel(t_map *map, int x, int y);
void	ft_put_line(t_map *map, t_point start, t_point end);
void	ft_put_point(t_map *map, int x, int y);
void	ft_colorput(t_map *map, int start, int end);
void	ft_putmap(t_map *map);
int		ft_get_map(t_map *map, char *file);

#endif
