#include "../inc/cub3d.h"

void	define_second(char c, t_pos *pos, int a, int b)
{
	if (c == 'W')
	{
		pos->dirx = -1;
		pos->diry = 0;
		pos->planex = 0;
		pos->planey = -0.66;
	}
	pos->posx = (double)a + 0.1;
	pos->posy = (double)b + 0.1;
}

void	define(char c, t_pos *pos, int a, int b)
{
	if (c == 'N')
	{
		pos->dirx = 0;
		pos->diry = -1;
		pos->planex = 0.66;
		pos->planey = 0;
	}
	if (c == 'E')
	{
		pos->dirx = 1;
		pos->diry = 0;
		pos->planex = 0;
		pos->planey = 0.66;
	}
	if (c == 'S')
	{
		pos->dirx = 0;
		pos->diry = 1;
		pos->planex = -0.66;
		pos->planey = 0;
	}
	define_second(c, pos, a, b);
}

int		sizey(char **cub, int i, int j)
{
	int		n;

	n = 0;
	while (cub[i][j] < '0' || cub[i][j] > '9')
		j++;
	while (cub[i][j] >= '0' && cub[i][j] <= '9')
	{
		n *= 10;
		n += cub[i][j] - 48;
		j++;
	}
	if (n > 1080)
		n = 1080;
	if (n < 0)
		n = 0;
	return (n);
}

int		sizex(t_pos *pos, char **cub, int i)
{
	int		n;
	int		j;

	n = 0;
	j = 0;
	while (cub[i][j] < '0' || cub[i][j] > '9')
		j++;
	while (cub[i][j] >= '0' && cub[i][j] <= '9')
	{
		n *= 10;
		n += cub[i][j] - 48;
		j++;
	}
	pos->size_y = sizey(cub, i, j);
	if (n > 1920)
		n = 1920;
	if (n < 0)
		n = 0;
	return (n);
}
