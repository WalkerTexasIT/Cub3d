/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bminner <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/14 10:49:57 by bminner           #+#    #+#             */
/*   Updated: 2019/10/14 10:50:00 by bminner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		ft_verif(char const *s1, char const *set)
{
	int i;
	int n;

	i = 0;
	while (s1[i] != '\0')
	{
		n = 0;
		while (set[n] != '\0')
		{
			if (s1[i] == set[n])
				break ;
			n++;
		}
		if (set[n] == '\0')
			return (1);
		i++;
	}
	return (0);
}

static int		ft_check(char const *s1, char const *set, int place)
{
	int n;
	int i;

	n = 0;
	if (place == 1)
		n = ft_strlen(s1) - 1;
	while (s1[n] != '\0')
	{
		i = 0;
		while (set[i] != '\0')
		{
			if (s1[n] == set[i])
				break ;
			i++;
		}
		if (set[i] == '\0')
			return (n);
		if (place == 1)
			n--;
		else
			n++;
	}
	return (n);
}

char			*ft_strtrim(char const *s1, char const *set)
{
	int		n;
	int		i;
	char	*dest;
	int		g;

	if (s1 == 0 || set == 0)
		return (0);
	if (ft_verif(s1, set) == 0)
	{
		dest = (char*)malloc(sizeof(char) * 1);
		dest[0] = '\0';
		return (dest);
	}
	g = 0;
	n = ft_check(s1, set, 0);
	i = ft_check(s1, set, 1);
	if (!(dest = (char*)malloc(sizeof(char) * ((i - n) + 2))))
		return (0);
	while (s1[n + g] != '\0' && (n + g) <= i)
	{
		dest[g] = s1[n + g];
		g++;
	}
	dest[g] = '\0';
	return (dest);
}
