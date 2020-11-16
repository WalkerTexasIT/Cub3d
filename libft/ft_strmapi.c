/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bminner <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/15 09:38:08 by bminner           #+#    #+#             */
/*   Updated: 2019/10/15 09:38:10 by bminner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char			*dest;
	unsigned int	n;

	n = 0;
	if (s == 0 || (*f) == 0)
		return (0);
	if ((dest = (char*)malloc(sizeof(*dest) * ft_strlen(s) + 1)))
	{
		while (s[n] != '\0')
		{
			dest[n] = (*f)(n, s[n]);
			n++;
		}
		dest[n] = '\0';
		return (dest);
	}
	else
		return (0);
}
