/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   input.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mtaquet <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/11/26 14:35:06 by mtaquet      #+#   ##    ##    #+#       */
/*   Updated: 2018/12/05 15:01:36 by mtaquet     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "fdf.h"
#include "mlx.h"
#include <sys/stat.h>
#include <fcntl.h>

static int		ft_check_map(t_map *map, char *str)
{
	int n;
	int m;

	n = -1;
	m = 0;
	while (str[++n])
	{
		if (str[n] >= '0' && str[n] <= '9' &&
				(str[n + 1] == ' ' || str[n + 1] == '\n' || str[n + 1] == '\0'))
			m++;
		if (str[n] == '\n')
			if ((m % map->size.x) > 0)
				return (0);
	}
	return (1);
}

static t_point	ft_len(char *str)
{
	int		n;
	t_point	len;

	len.x = 0;
	len.y = 0;
	n = -1;
	while (str[++n] != '\n' && str[n] != '\0')
		if (str[n] >= '0' && str[n] <= '9' &&
				(str[n + 1] == ' ' || str[n + 1] == '\n'))
			len.x++;
	n = -1;
	while (str[++n] != '\0')
		if (str[n] == '\n')
			len.y++;
	return (len);
}

static void		ft_get_all_nb(t_map *map, char *str)
{
	int		n;
	int		m;
	t_point	coord;

	n = -1;
	m = -1;
	if ((str[0] >= '0' && str[0] <= '9') || str[0] == '-')
	{
		coord.x = ++m % map->size.x;
		coord.y = m / map->size.x;
		map->map[coord.y][coord.x] = ft_atoi(&str[n]);
	}
	while (str[++n])
		if (str[n] == ' ' && ((str[n + 1] >= '0'
						&& str[n + 1] <= '9') || str[n + 1] == '-'))
		{
			coord.x = ++m % map->size.x;
			coord.y = m / map->size.x;
			map->map[coord.y][coord.x] = ft_atoi(&str[n]);
		}
	free(str);
}

static char		*ft_get_all(t_map *map, int fd)
{
	char	*all;
	char	*tmp;
	char	buf[1000 + 1];
	int		ret;

	all = ft_memalloc(1);
	while ((ret = read(fd, buf, 1000)))
	{
		buf[ret] = '\0';
		tmp = ft_strdup(all);
		free(all);
		all = ft_strjoin(tmp, buf);
		free(tmp);
	}
	map->size = ft_len(all);
	if (!(ft_check_map(map, all)))
		return (0);
	ret = -1;
	while (all[++ret] != '\0')
		if (all[ret] == '\n')
			all[ret] = ' ';
	return (all);
}

int				ft_get_map(t_map *map, char *file)
{
	int		fd;
	char	*all;

	fd = open(file, O_RDONLY);
	if (fd == -1)
	{
		ft_putstr("No file ");
		ft_putendl(file);
		return (0);
	}
	if (!(all = ft_get_all(map, fd)))
		return (error_msg("Found wrong line length. Exiting."));
	ft_map_alloc(map);
	ft_get_all_nb(map, all);
	ft_limit(map);
	if (close(fd) == -1)
	{
		ft_putstr("No file ");
		ft_putendl(file);
		return (0);
	}
	return (1);
}
