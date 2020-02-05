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

int			ft_free(char **cache)
{
	if (*cache)
	{
		free(*cache);
		*cache = 0;
	}
	return (0);
}

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
