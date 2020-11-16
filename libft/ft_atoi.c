/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bminner <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/08 13:58:56 by bminner           #+#    #+#             */
/*   Updated: 2019/10/28 14:14:20 by bminner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		trans(const char *str, int n)
{
	long long val;

	val = 0;
	while (str[n] != '\0')
	{
		if (str[n] < '0' || str[n] > '9')
			break ;
		val = val * 10 + str[n] - 48;
		n++;
	}
	return (val);
}

int				ft_atoi(const char *str)
{
	int			n;
	long long	val;
	int			s;

	n = 0;
	val = 0;
	s = 0;
	while (str[n] == ' ' || (str[n] >= '\t' && str[n] <= '\r'))
		n++;
	if (str[n] == '-')
	{
		s = 1;
		n++;
	}
	if (str[n] == '+' && s == 0)
		n++;
	val = trans(str, n);
	if (s == 1)
		val *= -1;
	return (val);
}
