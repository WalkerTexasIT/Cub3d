/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bminner <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/14 16:32:59 by bminner           #+#    #+#             */
/*   Updated: 2019/10/28 15:00:46 by bminner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int			ft_len(long n)
{
	int i;

	i = 0;
	if (n < 0)
	{
		i++;
		n *= -1;
	}
	if (n == 0)
		return (1);
	while (n > 0)
	{
		n /= 10;
		i++;
	}
	return (i);
}

char				*ft_itoa(int n)
{
	char	*dest;
	int		len;
	long	i;

	i = (long)n;
	len = ft_len(i);
	if (!(dest = (char*)malloc(sizeof(char) * (len + 1))))
		return (0);
	dest[len] = '\0';
	if (i < 0)
		dest[0] = '-';
	if (i < 0)
		i *= -1;
	if (i == 0)
		dest[0] = '0';
	while (i > 0)
	{
		dest[len - 1] = (i % 10) + 48;
		i /= 10;
		len--;
	}
	return (dest);
}
