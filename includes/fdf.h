#ifndef FDF_H
# define FDF_H
# include "../libft/includes/libft.h"
//# include "../minilibx/mlx.h"

struct		s_size
{
	size_t	x;
	size_t	y;
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
	int	x;
	int	y;
	int	z;
};

typedef struct s_coord t_coord;

struct		s_map
{
	void	*mlx_ptr;
	void	*win_ptr;
	char	**map;
	size_t	lenth;
	t_size	size;
	t_point start;
	t_coord vector;
};

typedef struct s_map t_map;

int	ft_get_map(t_map *map, char *file);

#endif
