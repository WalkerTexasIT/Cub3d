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
# include "./minilibx_opengl/mlx.h"
# include "./libft/libft.h"
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <math.h>
# define MoveSpeed 0.1
# define Rotate 0.05

typedef struct	s_key {
	int		key_w;
	int		key_s;
	int		key_a;
	int		key_d;
	int		key_left;
	int		key_right;
}				t_key;


typedef struct	s_txt {
	void	**voidtxt;
	char	**chartxt;
	int		**txt;
	int		height[5];
	int		width[5];
	int		bits[5];
	int		sl[5];
	int		end[5];
}				t_txt;

typedef struct	s_pos {
	int		size_x;
	int		size_y;
	void	*mlx_ptr;
	void	*win_ptr;
	void	*img_ptr;
	char	*charimg_data;
	int		*img_data;
	char	**map;
	double	posX;
	double	posY;
	double	dirX;
	double	dirY;
	double	rayDirX;
	double	rayDirY;
	double	planeX;
	double	planeY;
	int		mapX;
	int		mapY;
	int		maphit;
	int		mapheight;
	double	deltaDistX;
	double	deltaDistY;
	double	sideDistX;
	double	sideDistY;
	int		stepX;
	int		stepY;
	int		side;
	double	perpWallDist;
	int		lineHeight;
	int		drawStart;
	int		drawEnd;
	int		colorC;
	int		colorF;
	t_txt	*txt;
	t_key	*key;
	char	*linkN;
	char	*linkS;
	char	*linkE;
	char	*linkW;
	char	*linksprite;
	double	wallX;
	int		texX;
	int		texY;
	double	step;
	double	texPos;
	double	*spriteDistance;
	int		numSprite;
	int		*spriteOrder;
	double	**posSprite;
	double	spriteX;
	double	spriteY;
	double	intDet;
	double	transformX;
	double	transformY;
	int		spriteScreenX;
	int		spriteHeight;
	int		drawStartY;
	int		drawStartX;
	int		drawEndX;
	int		drawEndY;
	int		spriteWidth;
	int		stripe;
	double	*ZBuffer;
}				t_pos;

int				parser(char **argv, t_pos *pos);
void			ft_free_map(t_pos *pos);
void			rot(t_pos *pos, char RorL);
char			*ft_strnum(char *string, int n);
void			ft_free_all(t_pos *pos, char *ret);
int				finish(t_pos *pos);
void			make_bmp(t_pos *pos);
int				whitespace(char c);

#endif
