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

#include "../inc/cub3d.h"

void	verif_xpm_file(t_pos *pos)
{
	char	*path;
	int		n;
	int		len;

	n = 0;
	while (n < 5)
	{
		path = (n == 0) ? pos->linkn : path;
		path = (n == 1) ? pos->links : path;
		path = (n == 2) ? pos->linke : path;
		path = (n == 3) ? pos->linkw : path;
		path = (n == 4) ? pos->linksprite : path;
		len = ft_strlen(path);
		if (path[len - 1] != 'm' || path[len - 2] != 'p'
				|| path[len - 3] != 'x' || path[len - 4] != '.')
			ft_free_all(pos, "erreur map");
		n++;
	}
}

int		check_second(t_pos *pos, int i, char **cub)
{
	if (cub[i][0] == 'R')
		pos->size_x = sizex(pos, cub, i);
	else if (cub[i][0] == 'N' && cub[i][1] == 'O')
		set_path(pos, cub[i]);
	else if (cub[i][0] == 'S' && cub[i][1] == 'O')
		set_path(pos, cub[i]);
	else if (cub[i][0] == 'W' && cub[i][1] == 'E')
		set_path(pos, cub[i]);
	else if (cub[i][0] == 'E' && cub[i][1] == 'A')
		set_path(pos, cub[i]);
	else if (cub[i][0] == 'S' && cub[i][1] == ' ')
		set_path(pos, cub[i]);
	else if (cub[i][0] == 'F')
		pos->color_f = color_for_c(cub[i]);
	else if (cub[i][0] == 'C')
		pos->color_c = color_for_c(cub[i]);
	else if (check_if_map(pos, cub, i) == 1)
	{
		map(cub, i - 1, pos);
		ft_free_map(pos, cub);
		return (0);
	}
	return (1);
}

void	check(char **cub, t_pos *pos)
{
	int		i;

	i = 0;
	pos->map = 0;
	while (cub[i] != NULL)
	{
		if (!check_second(pos, i, cub))
			return ;
		i++;
	}
	ft_free_map(pos, cub);
	ft_free_all(pos, "erreur map");
}

char	**get_line(int fd)
{
	char	**map;
	char	buff[10001];
	int		n;

	n = read(fd, buff, 10000);
	buff[n] = '\0';
	map = ft_split(buff, '\n');
	return (map);
}

int		parser(char **argv, t_pos *pos)
{
	int		fd;
	char	**map;

	fd = open(argv[1], O_RDONLY);
	map = get_line(fd);
	pos->color_c = 0;
	pos->color_f = 0;
	pos->size_x = 0;
	pos->size_y = 0;
	check(map, pos);
	if (verifmap(pos) == 0)
		ft_free_all(pos, "erreur map");
	return (0);
}
