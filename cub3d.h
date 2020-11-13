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
	double	posx;
	double	posy;
	double	dirx;
	double	diry;
	double	raydirx;
	double	raydiry;
	double	planex;
	double	planey;
	int		mapx;
	int		mapy;
	int		maphit;
	int		mapheight;
	double	deltadistx;
	double	deltadisty;
	double	sidedistx;
	double	sidedisty;
	int		stepx;
	int		stepy;
	int		side;
	double	perpwalldist;
	int		lineheight;
	int		drawstart;
	int		drawend;
	int		color_c;
	int		color_f;
	t_txt	*txt;
	t_key	*key;
	char	*linkn;
	char	*links;
	char	*linke;
	char	*linkw;
	char	*linksprite;
	double	wallx;
	int		tex_x;
	int		tex_y;
	double	step;
	double	texpos;
	double	*spritedist;
	int		numsprite;
	int		*spriteorder;
	double	**possprite;
	double	spritex;
	double	spritey;
	double	intDet;
	double	transformx;
	double	transformy;
	int		spritescreenx;
	int		spriteheight;
	int		drawstarty;
	int		drawstartx;
	int		drawendx;
	int		drawendy;
	int		spritewidth;
	int		stripe;
	double	*zbuffer;
}				t_pos;

int				parser(char **argv, t_pos *pos);
void			rot(t_pos *pos, char RorL);
char			*ft_strnum(char *string, int n);
void			ft_free_all(t_pos *pos, char *ret);
int				finish(t_pos *pos);
void			make_bmp(t_pos *pos);
int				whitespace(char c);
void			verif_xpm_file(t_pos *pos);
void			ft_free_map(t_pos *pos, char **map);

#endif
