#include "../inc/cub3d.h"

int		verifcase(t_pos *pos, int i, int j)
{
	int		len;
	char	c;

	len = 0;
	if (i > pos->mapheight || i < 0)
		ft_free_all(pos, "erreur mapp");
	while (pos->map[i][len])
		len++;
	if (j < 0 || j > len)
		ft_free_all(pos, "erreur map");
	c = pos->map[i][j];
	if (c != '0' && c != '1' && c != '2')
		ft_free_all(pos, "erreur map");
	if (c == '1')
		pos->maphit = 1;
	return (1);
}

void	check_void_next(t_pos *pos, int i, int j, char dir)
{
	if (dir == 'N')
	{
		pos->maphit = 0;
		while (pos->maphit == 0 && verifcase(pos, i, j) == 1)
			i--;
	}
	if (dir == 'S')
	{
		pos->maphit = 0;
		while (pos->maphit == 0 && verifcase(pos, i, j) == 1)
			i++;
	}
	if (dir == 'E')
	{
		pos->maphit = 0;
		while (pos->maphit == 0 && verifcase(pos, i, j) == 1)
			j++;
	}
	if (dir == 'W')
	{
		pos->maphit = 0;
		while (pos->maphit == 0 && verifcase(pos, i, j) == 1)
			j--;
	}
}

int		verifmap(t_pos *pos)
{
	int i;
	int n;

	i = 0;
	while (pos->map[i])
	{
		n = 0;
		while (pos->map[i][n])
		{
			if (pos->map[i][n] == '0' || pos->map[i][n] == '2')
			{
				check_void_next(pos, i, n, 'N');
				check_void_next(pos, i, n, 'S');
				check_void_next(pos, i, n, 'E');
				check_void_next(pos, i, n, 'W');
			}
			n++;
		}
		i++;
	}
	return (1);
}

int		get_color_rgb(char *string, int i)
{
	int color;

	color = 0;
	while (string[i] >= '0' && string[i] <= '9' && string[i] != '\0')
	{
		color *= 10;
		color += (int)(string[i] - 48);
		i++;
	}
	return (color);
}

int		color_for_c(char *string)
{
	int r;
	int g;
	int b;
	int i;

	i = 0;
	while ((string[i] < '0' || string[i] > '9') && string[i] != '\0')
		i++;
	r = get_color_rgb(string, i);
	i += ft_len((long)r) + 1;
	g = get_color_rgb(string, i);
	i += ft_len(g) + 1;
	b = get_color_rgb(string, i);
	return (r * 256 * 256 + g * 256 + b);
}
