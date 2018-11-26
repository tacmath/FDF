#ifndef FDF_H
# define FDF_H
# include "../libft/includes/libft.h"

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

struct		s_coord
{
	double	x;
	double	y;
};

typedef struct s_coord t_coord;

struct		s_map
{
	void	*mlx_ptr;
	void	*win_ptr;
	char	**map;
	size_t	lenth;
	t_size	size;
	t_size	window;
	t_point start;
	t_coord vx;
	t_coord vy;
	t_coord vz;
};

typedef struct s_map t_map;

int		ft_rgb(unsigned int r, unsigned int g, unsigned int b);
int		deal_key(int key, void *param);
void	ft_swap(int *a, int *b);
void	ft_free_map(t_map *map);
void	ft_pixel(t_map *map, int x, int y, int color);
int		ft_get_map(t_map *map, char *file);

#endif
