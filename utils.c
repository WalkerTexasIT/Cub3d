/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bminner <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/04 21:46:55 by bminner           #+#    #+#             */
/*   Updated: 2020/02/04 21:46:55 by bminner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		get_color(char *s)
{
	int r;
	int g;
	int b;
	int ret;

	r = ft_atoi(s);
	g = ft_atoi(s);
	b = ft_atoi(s);
	ret = (r * 65536) + (g * 256) + b;
	return (ret);
}

void	rot(t_pos *pos, char RorL)
{
	double swipe1;
	double swipe2;

	if (RorL == 'R')
	{
		swipe1 = pos->dirx;
		pos->dirx = (pos->dirx * cos(Rotate)) - (pos->diry * sin(Rotate));
		pos->diry = (swipe1 * sin(Rotate)) + (pos->diry * cos(Rotate));
		swipe2 = pos->planex;
		pos->planex = (pos->planex * cos(Rotate)) - (pos->planey * sin(Rotate));
		pos->planey = (swipe2 * sin(Rotate)) + (pos->planey * cos(Rotate));
		pos->key->key_right = 0;
	}
	else
	{
		swipe1 = pos->dirx;
		pos->dirx = (pos->dirx * cos(-Rotate)) - (pos->diry * sin(-Rotate));
		pos->diry = (swipe1 * sin(-Rotate)) + (pos->diry * cos(-Rotate));
		swipe2 = pos->planex;
		pos->planex = (pos->planex * cos(-Rotate)) - (pos->planey * sin(-Rotate));
		pos->planey = (swipe2 * sin(-Rotate)) + (pos->planey * cos(-Rotate));
		pos->key->key_left = 0;
	}
}

int		whitespace(char c)
{
	if (c == '\t' || c == '\r' || c == '\v' || c == '\f' || c == ' ')
		return (1);
	return (0);
}
