/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bminner <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/11 15:51:39 by bminner           #+#    #+#             */
/*   Updated: 2019/10/11 15:51:40 by bminner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
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
