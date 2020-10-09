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

#include "cub3d.h"

void	free_value(t_pos *pos)
{
	if (pos->spriteOrder)
		free(pos->spriteOrder);
	if (pos->linkN)
		free(pos->linkN);
	if (pos->linkS)
		free(pos->linkS);
	if (pos->linkE)
		free(pos->linkE);
	if (pos->linkW)
		free(pos->linkW);
	if (pos->linksprite)
		free(pos->linksprite);
}

void	ft_free_map(t_pos *pos)
{
	int i;

	i = 0;
	if (pos->map)
	{
		while (pos->map[i] != 0)
		{
			if (pos->map[i])
				free(pos->map[i++]);
		}
		free(pos->map);
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
	printf("%s\n", ret);
	free_value(pos);
	free_all_txt(pos->txt);
	ft_free_map(pos);
	mlx_destroy_window(pos->mlx_ptr, pos->win_ptr);
	exit(0);
}
