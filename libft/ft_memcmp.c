/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bminner <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/08 14:00:24 by bminner           #+#    #+#             */
/*   Updated: 2019/10/08 14:00:25 by bminner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_memcmp(const void *str1, const void *str2, size_t n)
{
	unsigned char	*first;
	unsigned char	*second;

	first = (unsigned char *)str1;
	second = (unsigned char *)str2;
	while (n != 0)
	{
		if (*first != *second)
			return (*first - *second);
		first++;
		second++;
		n--;
	}
	return (0);
}
