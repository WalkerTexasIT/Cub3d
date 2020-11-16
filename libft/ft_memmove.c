/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bminner <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/08 14:00:41 by bminner           #+#    #+#             */
/*   Updated: 2019/10/08 14:00:42 by bminner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *str1, const void *str2, size_t n)
{
	size_t			x;
	unsigned char	*dest;
	unsigned char	*src;

	if (str1 == 0 && str2 == 0)
		return (0);
	x = 0;
	dest = (unsigned char *)str1;
	src = (unsigned char *)str2;
	if (dest > src)
		while (x < n)
		{
			dest[n - 1] = src[n - 1];
			n--;
		}
	else
		while (x < n)
		{
			dest[x] = src[x];
			x++;
		}
	return (str1);
}
