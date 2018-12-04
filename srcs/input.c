/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   input.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mtaquet <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/11/26 14:35:06 by mtaquet      #+#   ##    ##    #+#       */
/*   Updated: 2018/12/04 14:09:03 by mtaquet     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "fdf.h"
#include "mlx.h"
#include <sys/stat.h>
#include <fcntl.h>

static void		ft_limit(t_map *map)
{
	int x;
	int y;

	map->heightmax = 0;
	map->heightmin = 0;
	y = -1;
	while (++y < map->size.y)
	{
		x = -1;
		while (++x < map->size.x)
		{
			if (map->heightmax < map->map[y][x])
				map->heightmax = map->map[y][x];
			if (map->heightmin > map->map[y][x])
				map->heightmin = map->map[y][x];
		}
	}
}
static int ft_check_map(t_map *map, char *str)
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
	int n;
	t_point len;

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

static void	ft_get_all_nb(t_map *map, char *str)
{
	int	n;
	int	m;
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

static char	*ft_get_all(t_map *map, int fd)
{
	char	*all;
	char	*tmp;
	char	buf[1000 + 1];
	int	ret;

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

static int	ft_map_alloc(t_map *map)
{
	int	n;

	n = -1;
	if (!(map->map = malloc(sizeof(char*) * map->size.y)))
		return (0);
	while (++n < map->size.y)
		if (!(map->map[n] = malloc(sizeof(char) * map->size.x)))
			return (0);
	if (map->size.y > map->size.x)
	{
		map->window.y =  (map->size.y / (double)map->size.x) * 800 + 200;
		map->lenth = (map->window.y -200) / map->size.y;
		map->window.x =  map->lenth * map->size.x + 200;
	}
	else
	{
		map->window.x =  (map->size.x / (double)map->size.y) * 800 + 200;
		map->lenth = (map->window.x -200) / map->size.x;
		map->window.y =  map->lenth * map->size.y + 200;
	}
	map->height = 1;
	map->mouse.status = FALSE;
	map->motion.x = 0;
	map->motion.y = 0;
	map->vx.x = 1;
	map->vx.y = 0;
	map->vy.x = 0;
	map->vy.y = 1;
	map->vz.x = 0;
	map->vz.y = 0;
	ft_color_init(map);
	return (1);	
}

int	ft_get_map(t_map *map, char *file)
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
