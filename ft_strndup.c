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
