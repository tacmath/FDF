#include "fdf.h"
#include <sys/stat.h>
#include <fcntl.h>

t_len	ft_len(char *str)
{
	int n;
	t_len len;

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

void	ft_get_all_nb(t_fdf *map, char *str)
{
	int n;
	int m;
	char *nb;

	n = -1;
	nb = ft_memalloc(map->len.y * map->len.x);
	m = 0;
	if ((str[0] >= '0' && str[0] <= '9') || str[0] == '-')
		nb[m++] = ft_atoi(&str[n]);
	while (str[++n])
		if (str[n] == ' ' && ((str[n + 1] >= '0'
			&& str[n + 1] <= '9') || str[n + 1] == '-'))
			nb[m++] = ft_atoi(&str[n]);
	free(str);
	map->map = nb;
}

char	*ft_get_all(t_fdf *map, int fd)
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
	map->len = ft_len(all);
	ret = -1;
	while (all[++ret] != '\0')
		if (all[ret] == '\n')
			all[ret] = ' ';
	return (all);
}

int	ft_get_map(t_fdf *map, char *ficher)
{
	int	fd;
	char	*all;
	
	fd = open(ficher, O_RDONLY);
	if (fd == -1)
		return (0);
	all = ft_get_all(map, fd);
	ft_get_all_nb(map, all);
	if (close(fd) == -1)
		return (0);
	return (1);
}


int main(int ac, char **av)
{
	t_fdf	*map;

	if (ac != 2)
		return (0);
	if (!(map = malloc(sizeof(t_fdf))))
		return (0);
	ft_get_map(map, av[1]);
	free(map->map);
	free(map);
	return (1);
}
