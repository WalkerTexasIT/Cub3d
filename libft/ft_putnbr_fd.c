/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bminner <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/15 13:54:49 by bminner           #+#    #+#             */
/*   Updated: 2019/10/15 13:54:51 by bminner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void		ft_putchar(char c, int fd)
{
	write(fd, &c, 1);
}

static int		max(int n, int fd)
{
	if (n == -2147483648)
	{
		ft_putchar('-', fd);
		ft_putchar('2', fd);
		n = 147483648;
	}
	return (n);
}

void			ft_putnbr_fd(int n, int fd)
{
	if (fd < 0)
		return ;
	n = max(n, fd);
	if (n < 0)
	{
		ft_putchar('-', fd);
		n *= -1;
	}
	if (n > 9)
	{
		ft_putnbr_fd(n / 10, fd);
		ft_putchar((n % 10) + 48, fd);
	}
	else
		ft_putchar(n + 48, fd);
}
