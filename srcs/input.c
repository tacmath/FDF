#include "fdf.h"
#include <sys/stat.h>
#include <fcntl.h>

static t_size	ft_len(char *str)
{
	int n;
	t_size len;

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

static void	ft_get_all_nb(t_fdf *map, char *str)
{
	int	n;
	int	m;
	t_size	coord;

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

static char	*ft_get_all(t_fdf *map, int fd)
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
	ret = -1;
	while (all[++ret] != '\0')
		if (all[ret] == '\n')
			all[ret] = ' ';
	return (all);
}

static int	ft_map_alloc(t_fdf *map)
{
	size_t	n;

	n = -1;
	if (!(map->map = malloc(sizeof(char*) * map->size.y)))
		return (0);
	while (++n < map->size.y)
		if (!(map->map[n] = malloc(sizeof(char) * map->size.x)))
			return (0);
	map->lenth = 100;
	map->start.x = 200;
	map->start.y = 100;
	map->start.z = 0;
	return (1);	
}

int	ft_get_map(t_fdf *map, char *file)
{
	int	fd;
	char	*all;
	
	fd = open(file, O_RDONLY);
	if (fd == -1)
		return (0);
	all = ft_get_all(map, fd);
	ft_map_alloc(map);
	ft_get_all_nb(map, all);
	if (close(fd) == -1)
		return (0);
	return (1);
}
