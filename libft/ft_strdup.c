/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bminner <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/11 15:45:18 by bminner           #+#    #+#             */
/*   Updated: 2019/10/11 15:49:09 by bminner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	int		len;
	int		n;
	char	*dest;

	n = 0;
	len = ((ft_strlen(s1)) + 1);
	if ((dest = ((char *)malloc(sizeof(char) * len))))
	{
		while (n < len)
		{
			dest[n] = (char)s1[n];
			n++;
		}
		return (dest);
	}
	return (0);
}
