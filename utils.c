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

int			ft_strlen(const char *src)
{
	int n;

	n = 0;
	if (src == 0)
		return (0);
	while (src[n] != '\0')
		n++;
	return (n);
}

char		*ft_strjoin(char const *cache, char const *buff)
{
	char	*dest;
	int		n;
	int		i;

	if (!(dest = malloc(ft_strlen(cache) + ft_strlen(buff) + 1)))
		return (0);
	n = 0;
	i = 0;
	if (cache != 0)
		while (cache[n] != '\0')
		{
			dest[n] = cache[n];
			n++;
		}
	while (buff[i] != '\0')
	{
		dest[n + i] = buff[i];
		i++;
	}
	dest[n + i] = '\0';
	return (dest);
}

char		*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*dest;
	int				n;

	if (s == 0)
		return (0);
	if (start > ft_strlen(s))
	{
		if (!(dest = (char*)malloc(sizeof(char) * 1)))
			return (0);
		dest[0] = '\0';
		return (dest);
	}
	if (!(dest = (char*)malloc(sizeof(char) * (len + 1))))
		return (0);
	n = 0;
	while (s[start] != '\0' && len > (unsigned long)n)
	{
		dest[n] = s[start];
		n++;
		start++;
	}
	dest[n] = '\0';
	return (dest);
}

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
		swipe1 = pos->dirX;
		pos->dirX = (pos->dirX * cos(Rotate)) - (pos->dirY * sin(Rotate));
		pos->dirY = (swipe1 * sin(Rotate)) + (pos->dirY * cos(Rotate));
		swipe2 = pos->planeX;
		pos->planeX = (pos->planeX * cos(Rotate)) - (pos->planeY * sin(Rotate));
		pos->planeY = (swipe2 * sin(Rotate)) + (pos->planeY * cos(Rotate));
	}
	else
	{
		swipe1 = pos->dirX;
		pos->dirX = (pos->dirX * cos(-Rotate)) - (pos->dirY * sin(-Rotate));
		pos->dirY = (swipe1 * sin(-Rotate)) + (pos->dirY * cos(-Rotate));
		swipe2 = pos->planeX;
		pos->planeX = (pos->planeX * cos(-Rotate)) - (pos->planeY * sin(-Rotate));
		pos->planeY = (swipe2 * sin(-Rotate)) + (pos->planeY * cos(-Rotate));
	}
}
