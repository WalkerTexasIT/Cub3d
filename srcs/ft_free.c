/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bminner <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/08 11:16:20 by bminner           #+#    #+#             */
/*   Updated: 2020/03/08 11:16:21 by bminner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	free_value(t_pos *pos)
{
	if (pos->spriteorder)
		free(pos->spriteorder);
	if (pos->linkn)
		free(pos->linkn);
	if (pos->links)
		free(pos->links);
	if (pos->linke)
		free(pos->linke);
	if (pos->linkw)
		free(pos->linkw);
	if (pos->linksprite)
		free(pos->linksprite);
}

void	ft_free_map(t_pos *pos, char **map)
{
	int i;

	i = 0;
	if (map)
	{
		while (map[i])
		{
			free(map[i]);
			i++;
		}
		free(map);
	}
}

void	free_all_txt(t_txt *txt)
{
	int i;

	i = 0;
	if (txt->voidtxt)
		free(txt->voidtxt);
	if (txt->chartxt)
		free(txt->chartxt);
}

void	ft_free_all(t_pos *pos, char *ret)
{
	if (ret[0] != '\n')
		ft_putstr(ret);
	free_value(pos);
	if (ft_strncmp(ret, "erreur map", 10))
		free_all_txt(pos->txt);
	ft_free_map(pos, pos->map);
	if (ft_strncmp(ret, "erreur map", 10))
		mlx_destroy_window(pos->mlx_ptr, pos->win_ptr);
	exit(0);
}

int		finish(t_pos *pos)
{
	ft_free_all(pos, "");
	return (0);
}
