#include "../inc/cub3d.h"

int		check_if_map(t_pos *pos, char **map, int i)
{
	int n;

	n = 0;
	if (!pos->linke || !pos->linkn || !pos->links || !pos->linkw
				|| !pos->linksprite)
		return (0);
	if (pos->size_x == 0 || pos->size_y == 0 || pos->color_f == 0
				|| pos->color_c == 0)
		return (0);
	while (map[i][n] != '\n' && map[i][n] != '\0')
	{
		if (map[i][n++] == '1')
			return (1);
		n++;
	}
	return (0);
}

int		count(char *cub)
{
	int i;

	i = 0;
	while (cub[i] != '\0')
	{
		i++;
	}
	return (i);
}

int		cline(t_pos *pos, char **cub, int i)
{
	int n;

	n = 0;
	while (cub[i] != 0)
	{
		i++;
		n++;
	}
	pos->mapheight = n;
	return (n + 1);
}

void	map(char **cub, int i, t_pos *pos)
{
	int		j;
	int		a;
	int		b;

	a = 0;
	if (!(pos->map = (char**)malloc(sizeof(char*) * (cline(pos, cub, i) + 1))))
		ft_free_all(pos, "malloc map **");
	while (cub[++i] != 0)
	{
		map_second(cub[i], a, pos);
		a++;
	}
	pos->map[a] = NULL;
}

void	map_second(char *cub, int a, t_pos *pos)
{
	int b;
	int j;

	j = 0;
	b = 0;
	if (!(pos->map[a] = (char*)malloc(sizeof(char) * (count(cub) + 1))))
		ft_free_all(pos, "malloc map *");
	while (cub[j])
	{
		if (cub[j] == '0' || cub[j] == '1' || cub[j] == '2'
				|| cub[j] == ' ')
			pos->map[a][b++] = cub[j];
		if (cub[j] == 'N' || cub[j] == 'S' || cub[j] == 'E'
				|| cub[j] == 'W')
		{
			define(cub[j], pos, a, b);
			pos->map[a][b++] = '0';
		}
		j++;
	}
	pos->map[a][b] = '\0';
}
