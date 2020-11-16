/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bminner <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/08 14:00:50 by bminner           #+#    #+#             */
/*   Updated: 2019/10/08 14:00:51 by bminner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *src, int c, size_t n)
{
	char *char_src;

	if (src == 0)
		return (0);
	char_src = (char *)src;
	while (n != 0)
	{
		*char_src = c;
		char_src++;
		n--;
	}
	return (src);
}
