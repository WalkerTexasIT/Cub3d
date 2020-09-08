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

void	ft_free_all(t_pos *pos)
{
	ft_free_map(pos);
	mlx_destroy_window(pos->mlx_ptr, pos->win_ptr);
	exit(0);
}
