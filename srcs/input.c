/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   input.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mtaquet <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/11/26 14:35:06 by mtaquet      #+#   ##    ##    #+#       */
/*   Updated: 2018/12/10 07:57:10 by mtaquet     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "fdf.h"
#include "mlx.h"
#include <sys/stat.h>
#include <fcntl.h>

static int      ft_len(char *str)
{
	int             n;
	int             nb;

	nb = 0;
	if ((str[0] >= '0' && str[0] <= '9') || str[0] == '-')
		nb++;
	n = -1;
	while (str[++n])
		if (((str[n + 1] >= '0' && str[n + 1] <= '9') || str[n + 1] == '-') &&
				str[n] == ' ')
			nb++;
	return (nb);
}

static int		ft_check(t_map *map, char *str)
{
	int n;

	n = -1;
	while (str[++n])
		if ((str[n] < '0' || str[n] > '9')  && str[n] != ' ' && str[n] != '-')
		{
			n = -1;
			while (++n < map->size.y - 1)
				free(map->map[n]);
			free(map->map);
			return (error_msg("Found wrong caracter. Exiting."));
		}
	n = -1;
	if (ft_len(str) != map->size.x)
	{
		n = -1;
		while (++n < map->size.y - 1)
			free(map->map[n]);
		free(map->map);
		return (error_msg("Found wrong line length. Exiting."));
	}
	return (1);
}

static short int		*ft_get_nb(t_map *map, char *str)
{
	int		n;
	int		m;
	short int	*line;

	if (!(line = malloc(sizeof(short int) * map->size.x)))
		return (0);
	n = -1;
	m = -1;
	if ((str[0] >= '0' && str[0] <= '9') || str[0] == '-')
		line[++m] = ft_atoi(str);
	while (str[++n])
		if (str[n] == ' ' && ((str[n + 1] >= '0'
			&& str[n + 1] <= '9') || str[n + 1] == '-'))
			line[++m] = ft_atoi(&str[n]);
	free(str);
	return (line);
}

static int		ft_map_realloc(t_map *map, char *str)
{
	short int	**tmp;
	int		n;

	if (!(tmp = malloc(sizeof(short int*) * map->size.y)))
		return (0);
	n = -1;
	while (++n < map->size.y - 1)
		tmp[n] = map->map[n];
	free(map->map);
	if (!(tmp[n] = ft_get_nb(map, str)))
		return (0);
	map->map = tmp;
	return (1);
}

static int		ft_get_all(t_map *map, int fd)
{
	char	*line;

	if (get_next_line(fd, &line) == 1)
	{
		map->size.x = ft_len(line);
		map->size.y++;
		if (!ft_check(map, line))
			return (0);
		if (!(map->map = malloc(sizeof(short int*))))
			return (0);
		if (!(map->map[0] = ft_get_nb(map, line)))
			return (0);
	}
	while (get_next_line(fd, &line) == 1)
	{
		map->size.y++;
		if (!ft_check(map, line))
			return (0);
		if (!ft_map_realloc(map, line))
			return (0);
	}
	if (map->size.x == 0)
		return (0);
	return (1);
}

int				ft_get_map(t_map *map, char *file)
{
	int		fd;

	fd = open(file, O_RDONLY);
	if (fd == -1 || read(fd, 0, 0) == -1)
	{
		ft_putstr("No file ");
		ft_putendl(file);
		return (0);
	}
	map->size.x = 0;
	map->size.y = 0;
	if (!(ft_get_all(map, fd)))
		return (0);
	ft_map_init(map);
	ft_limit(map);
	if (close(fd) == -1)
	{
		ft_putstr("No file ");
		ft_putendl(file);
		return (0);
	}
	return (1);
}
