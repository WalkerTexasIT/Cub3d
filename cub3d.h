/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bminner <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/03 16:36:45 by bminner           #+#    #+#             */
/*   Updated: 2020/02/03 16:36:46 by bminner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# include <mlx.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <math.h>

typedef struct	s_ptr {
	void	*mlx_ptr;
	void	*win_ptr;
	int		x;
	int		y;
	int		size_x;
	int		size_y;
	char	**map;
}				t_ptr;

typedef struct	s_pos {
	double	posX;
	double	posY;
	double	dirX;
	double	dirY;
}				t_pos;

int			ft_strlen(const char *src);
char		*ft_strjoin(char const *cache, char const *buff);
char		*ft_strndup(const char *s, size_t n);
void		ft_bzero(void *src, size_t n);
void		parser(char **argv, t_ptr *ptr, t_pos *pos);
char		*ft_substr(char const *s, unsigned int start, size_t len);
char		**ft_split(char const *s, char c);

#endif