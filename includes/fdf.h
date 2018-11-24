#ifndef FDF_H
# define FDF_H
# include "../libft/includes/libft.h"

struct		s_size
{
	size_t	x;
	size_t	y;
};

typedef struct s_size t_size;

struct		s_coord
{
	size_t	x;
	size_t	y;
	size_t	z;
};

typedef struct s_coord t_coord;

struct		s_fdf
{
	void	*mlx_ptr;
	void	*win_ptr;
	char	**map;
	int	lenth;
	t_size	size;
	t_coord start;
};

typedef struct s_fdf t_fdf;

int	ft_get_map(t_fdf *map, char *file);

#endif
