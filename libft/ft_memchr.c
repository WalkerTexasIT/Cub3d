/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bminner <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/08 14:00:15 by bminner           #+#    #+#             */
/*   Updated: 2019/10/08 14:00:16 by bminner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *str, int c, size_t n)
{
	size_t			x;
	unsigned char	*src;

	x = 0;
	src = (unsigned char *)str;
	while (++x <= n)
		if (*(src++) == (unsigned char)c)
			return ((void *)--src);
	return (0);
}
