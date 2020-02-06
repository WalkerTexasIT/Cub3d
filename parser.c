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

	while (cub[i][0] != '\0')
	{
		i++;
		n++;
	}
	return (n + 1);
}

char		**map(char **cub, int i)
{
	int		j;
	char	**map;

	j = 0;
	if (!(map = (char**)malloc(sizeof(char*) * countline(cub, i))))
		return (0);
	while (cub[i][0] != '\0')
	{
		if (!(*map = (char*)malloc(sizeof(char) * count(cub[i]))))
			return (0);
		if (cub[i][j] == '1' || cub[i][j] == '0' || cub[i][j] == '2')
		{
			**map = cub[i][j];
			(**map)++;
			j++;
		}
		else if (cub[i][j] == 'N' || cub[i][j] == 'S' || cub[i][j] == 'E' || cub[i][j] == 'W')
		{
			**map = cub[i][j];
			(**map)++;
			j++;
		}
		else
		{
			(*map)++;
			i++;
			j = 0;
		}
	}
	return (cub);
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

void		check(char **cub, t_ptr *ptr)
{
	int		i;

	i = 0;
	while (cub[i][0] != '\0' && ptr->map != 0)
	{
		if (cub[i][0] == 'R')
		{
			ptr->size_x = sizex(cub, i);
			ptr->size_y = sizey(cub, i);
		}
		else if (cub[i][0] == '1')
			ptr->map = map(cub, i);
		i++;
	}
}

void		parser(char **argv, t_ptr *ptr)
{
	int		fd;
	int		n;
	char	*buff;
	char	*cache;
	char	*temp;
	char	**cub;

	fd = open(argv[1], O_RDONLY);
	while ((n = read(fd, buff, 32)) > 0)
	{
		buff[n] = '\0';
		temp = ft_strjoin(cache, buff);
		ft_free(&cache);
		cache = temp;
	}
	printf("%s\n", cache);
	cub = ft_split(cache, '\n');
	ft_free(&cache);
	check(cub, ptr);
}