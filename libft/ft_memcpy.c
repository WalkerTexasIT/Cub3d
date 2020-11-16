/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bminner <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/08 14:00:33 by bminner           #+#    #+#             */
/*   Updated: 2019/10/08 14:00:34 by bminner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *str1, const void *str2, size_t n)
{
	char		*dest;
	const char	*src;

	if (str1 == 0)
		return (0);
	dest = (char *)str1;
	src = (const char *)str2;
	while (n != 0)
	{
		*dest = *src;
		dest++;
		src++;
		n--;
	}
	return (str1);
}
