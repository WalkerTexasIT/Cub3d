/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bminner <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/04 21:37:17 by bminner           #+#    #+#             */
/*   Updated: 2020/02/04 21:37:18 by bminner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void		define(char c, t_pos *pos, int a, int b)
{
	if (c == 'N')
	{
		pos->dirX = 0;
		pos->dirY = -1;
	}
	if (c == 'E')
	{
		pos->dirX = 1;
		pos->dirY = 0;
	}
	if (c == 'S')
	{
		pos->dirX = 0;
		pos->dirY = 1;
	}
	if (c == 'W')
	{
		pos->dirX = -1;
		pos->dirY = 0;
	}
	pos->posX = (double)a + 0.5;
	pos->posY = (double)b + 0.5;
}

int			count(char *cub)
{
	int i;
	int n;

	i = 0;
	n = 0;
	while (cub[i] != '\0')
	{
		if (cub[i] != ' ')
			n++;
		i++;
	}
	return (n);
}

int			countline(char **cub, int i)
{
	int n;

	while (cub[i] != 0)
	{
		i++;
		n++;
	}
	return (n + 1);
}

char		**map(char **cub, int i, t_ptr *ptr, t_pos *pos)
{
	int		j;
	char	**map;
	int		a;
	int		b;

	a = 0;
	if (!(map = (char**)malloc(sizeof(char*) * countline(cub, i))))
		return (0);
	while (cub[i] != 0)
	{
		j = 0;
		b = 0;
		if (!(map[a] = (char*)malloc(sizeof(char) * count(cub[i]))))
			return (0);
		while (cub[i][j] != '\0')
		{
			if (cub[i][j] == '0' || cub[i][j] == '1' || cub[i][j] == '2')
				map[a][b++] = cub[i][j];
			if (cub[i][j] == 'N' || cub[i][j] == 'S' || cub[i][j] == 'E' ||cub[i][j] == 'W')
			{
				define(cub[i][j], pos, a, b);
				map[a][b++] = '0';
			}
			j++;
		}
		a++;
		i++;
	}
	return (map);
}

int			sizey(char **cub, int i)
{
	int		n;
	int		j;

	n = 0;
	j = 0;
	while (cub[i][j] >= '0' && cub[i][j] <= '9')
		j++;
	while (cub[i][j] != ' ')
		j++;
	j++;
	while (cub[i][j] < '0' || cub[i][j] > '9')
	{
		n *= 10;
		n += cub[i][j] - 48;
		j++;
	}
	return (n);
}

int			sizex(char **cub, int i)
{
	int		n;
	int		j;

	n = 0;
	j = 0;
	while (cub[i][j] >= '0' && cub[i][j] <= '9')
		j++;
	while (cub[i][j] < '0' || cub[i][j] > '9')
	{
		n *= 10;
		n += cub[i][j] - 48;
		j++;
	}
	return (n);
}

void		check(char **cub, t_ptr *ptr, t_pos *pos)
{
	int		i;

	i = 0;
	while (cub[i][0] != '\0' && pos->map == 0)
	{
		if (cub[i][0] == 'R')
		{
			pos->size_x = sizex(cub, i);
			pos->size_y = sizey(cub, i);
		}
		else if (cub[i][0] == '1')
			pos->map = map(cub, i, ptr, pos);
		i++;
	}
}

char		**get_line(int fd)
{
	char	**map;
	char	buff[10001];
	int		n;

	n = read(fd, buff, 10000);
	buff[n] = '\0';
	map = ft_split(buff, '\n');
	return (map);
}

void		parser(char **argv, t_ptr *ptr, t_pos *pos)
{
	int		fd;
	char	**map;

	fd = open(argv[1], O_RDONLY);
	map = get_line(fd);
	check(map, ptr, pos);
}