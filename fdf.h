#ifndef FDF_H
# define FDF_H
# include "libft/includes/get_next_line.h"

struct		s_len
{
	size_t	x;
	size_t	y;
};

typedef struct s_len t_len;

struct		s_fdf
{
	void	*mlx_ptr;
	void	*win_ptr;
	char	*map;
	t_len	len;
	int	x;
	int	y;
	int	z;
};

typedef struct s_fdf t_fdf;

#endif
