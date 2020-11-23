#include "../inc/cub3d.h"

void	sort_sprite(t_pos *pos)
{
	int i;
	int n;
	int	temp;

	i = -1;
	n = -1;
	while (++i < pos->numsprite - 1)
		while (++n < pos->numsprite - i - 1)
			if (pos->spritedist[n] < pos->spritedist[n + 1])
			{
				temp = pos->spriteorder[n];
				pos->spriteorder[n] = pos->spriteorder[n + 1];
				pos->spriteorder[n + 1] = temp;
			}
}

double	**pos_sprite(t_pos *pos)
{
	int		i;
	int		a;
	int		b;
	double	**possprite;

	i = 0;
	a = 0;
	if (!(possprite = (double**)malloc(sizeof(double*) * pos->numsprite)))
		ft_free_all(pos, "malloc possprite");
	while (pos->map[a] != NULL)
	{
		b = -1;
		while (pos->map[a][++b] != '\0')
		{
			if (pos->map[a][b] == '2')
			{
				if (!(possprite[i] = (double*)malloc(sizeof(double) * 2)))
					ft_free_all(pos, "malloc possprite");
				possprite[i][0] = b + 0.5;
				possprite[i++][1] = a + 0.5;
			}
		}
		a++;
	}
	return (possprite);
}

int		count_sprite(t_pos *pos)
{
	int n;
	int a;
	int b;

	n = 0;
	a = -1;
	while (pos->map[++a] != NULL)
	{
		b = -1;
		while (pos->map[a][++b] != '\0')
			if (pos->map[a][b] == '2')
				n++;
	}
	return (n);
}
