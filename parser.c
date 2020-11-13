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

void	set_path(t_pos *pos, char *line)
{
	if (line[0] == 'N' && line[1] == 'O')
		if(!(pos->linkn = ft_strnum(line, 3)))
			return (ft_free_all(pos, "erreur map"));
	if (line[0] == 'S' && line[1] == 'O')
		if(!(pos->links = ft_strnum(line, 3)))
			return (ft_free_all(pos, "erreur map"));
	if (line[0] == 'E' && line[1] == 'A')
		if(!(pos->linke = ft_strnum(line, 3)))
			return (ft_free_all(pos, "erreur map"));
	if (line[0] == 'W' && line[1] == 'E')
		if(!(pos->linkw = ft_strnum(line, 3)))
			return (ft_free_all(pos, "erreur map"));
	if (line[0] == 'S' && line[1] == ' ')
		if(!(pos->linksprite = ft_strnum(line, 2)))
			return (ft_free_all(pos, "erreur map"));
}

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
		{
			i--;
		}
	}
	if (dir == 'S')
	{
		pos->maphit = 0;
		while (pos->maphit == 0 && verifcase(pos, i ,j) == 1)
			i++;
	}
	if (dir == 'E')
	{
		pos->maphit = 0;
		while (pos->maphit == 0 && verifcase(pos, i ,j) == 1)
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
		while(pos->map[i][n])
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

int		color_for_c(char *string)
{
	int color;
	int r;
	int g;
	int b;

	while ((*string < '0' || *string > '9') && *string != '\0')
		string++;
	r = 0;
	g = 0;
	b = 0;
	while (*string != ',' && *string != '\0')
	{
		r *= 10;
		r += (int)(*string - 48);
		string++;
	}
	string++;
	while(*string != ',' && *string != '\0')
	{
		g *= 10;
		g += (int)(*string - 48);
		string++;
	}
	string++;
	while (*string != '\0')
	{
		b *= 10;
		b += (int)(*string - 48);
		string++;
	}
	return (r * 256 * 256 + g * 256 + b);
}

void		define(char c, t_pos *pos, int a, int b)
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

int			count(char *cub)
{
	int i;

	i = 0;
	while (cub[i] != '\0')
	{
		i++;
	}
	return (i);
}

int			countline(t_pos *pos, char **cub, int i)
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

char		**map(char **cub, int i, t_pos *pos)
{
	int		j;
	char	**map;
	int		a;
	int		b;

	a = 0;
	if (!(map = (char**)malloc(sizeof(char*) * (countline(pos, cub, i) + 1))))
		ft_free_all(pos, "malloc map **");
	while (cub[i] != 0)
	{
		j = 0;
		b = 0;
		if (!(map[a] = (char*)malloc(sizeof(char) * (count(cub[i]) + 1))))
			ft_free_all(pos, "malloc map *");
		while (cub[i][j] != '\0')
		{
			if (cub[i][j] == '0' || cub[i][j] == '1' || cub[i][j] == '2' || cub[i][j] == ' ')
				map[a][b++] = cub[i][j];
			if (cub[i][j] == 'N' || cub[i][j] == 'S' || cub[i][j] == 'E' || cub[i][j] == 'W')
			{
				define(cub[i][j], pos, a, b);
				map[a][b++] = '0';
			}
			j++;
		}
		map[a][b] = '\0';
		a++;
		i++;
	}
	map[a] = NULL;
	return (map);
}

int			sizey(char **cub, int i, int j)
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

int			sizex(t_pos *pos, char **cub, int i)
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

int			check_if_map(t_pos *pos, char **map, int i)
{
	int n;

	n = 0;
	if (!pos->linke || !pos->linkn || !pos->links || !pos->linkw || !pos->linksprite)
		return (0);
	if (pos->size_x == 0 || pos->size_y == 0 || pos->color_f == 0 || pos->color_c == 0)
		return (0);
	while (map[i][n] != '\n' && map[i][n] != '\0')
	{
		if (map[i][n++] == '1')
			return (1);
		n++;
	}
	return (0);
}

void		check(char **cub, t_pos *pos)
{
	int		i;

	i = 0;
	pos->map = 0;
	while (cub[i] != NULL)
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
			pos->map = map(cub, i, pos);
			ft_free_map(pos, cub);
			return ;
		}
		i++;
	}
	ft_free_map(pos, cub);
	ft_free_all(pos, "erreur map");
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
