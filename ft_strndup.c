/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bminner <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/24 11:20:01 by bminner           #+#    #+#             */
/*   Updated: 2019/10/24 11:20:05 by bminner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char		*ft_strncpy(char *dest, const char *s, size_t n)
{
	size_t i;

	i = 0;
	while (s[i] != 0 && i < n)
	{
		dest[i] = s[i];
		i++;
	}
	while (i < n)
	{
		dest[i] = '\0';
		i++;
	}
	return (dest);
}

void		ft_bzero(void *src, size_t n)
{
	char *char_src;

	if (src == 0)
		return ;
	char_src = (char *)src;
	while (n != 0)
	{
		*char_src = 0;
		char_src++;
		n--;
	}
}

char		*ft_strndup(const char *s, size_t n)
{
	char		*dest;

	if (!(dest = malloc(sizeof(char) * (n + 1))))
		return (0);
	dest = ft_strncpy(dest, s, n);
	dest[n] = 0;
	return (&*dest);
}

char		*ft_strnum(char *string, int n)
{
	char	*dest;
	int		len;
	int		i;

	len = ft_strlen(string);
	if (!(dest = (char*)malloc(sizeof(char) * (len - n + 1))))
		return (0);
	i = 0;
	while (string[n] != '\0' && string[n] != '\n')
		dest[i++] = string[n++];
	dest[i] = '\0';
	return (dest);
}
