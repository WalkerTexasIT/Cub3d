/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bminner <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/12 12:17:19 by bminner           #+#    #+#             */
/*   Updated: 2019/10/14 14:07:04 by bminner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*dest;
	int		n;
	int		i;

	if (s1 == 0 || s2 == 0)
		return (0);
	if ((dest = malloc(ft_strlen(s1) + ft_strlen(s2) + 1)))
		n = 0;
	else
		return (0);
	i = 0;
	while (s1[n] != '\0')
	{
		dest[n] = s1[n];
		n++;
	}
	while (s2[i] != '\0')
	{
		dest[n + i] = s2[i];
		i++;
	}
	dest[n + i] = '\0';
	return (dest);
}
