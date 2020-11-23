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
# include "../minilibx_opengl/mlx.h"
# include "../libft/libft.h"
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
	double	transx;
	double	transy;
	int		ssx;
	int		spriteheight;
	int		dsy;
	int		dsx;
	int		dex;
	int		dey;
	int		spritewidth;
	int		stripe;
	double	*zbuffer;
	int		x;
	double	cam_x;
	int		hit;
}				t_pos;

/*
** bmp.c
*/
static void		set_value_bmp(unsigned char *string, int i);
static int		bmp_header(t_pos *pos, int fd, int size);
static int		rgb_data(t_pos *pos, int x, int y);
static int		bmp_data(t_pos *pos, int fd, int n);
void			make_bmp(t_pos *pos);
/*
** dda.c
*/
void			dda_drawlimit(t_pos *pos);
void			dda_hit(t_pos *pos);
void			dda_sidedist(t_pos *pos);
void			dda_value(t_pos *pos);
void			dda_while(t_pos *pos);
/*
** ddraw.c
*/
void			dda_drawsecond(t_pos *pos, int i, int n);
void			dda_draw(t_pos *pos);
/*
** ft_free.c
*/
void			free_value(t_pos *pos);
void			ft_free_map(t_pos *pos, char **map);
void			free_all_txt(t_txt *txt);
void			ft_free_all(t_pos *pos, char *ret);
int				finish(t_pos *pos);
/*
** ft_strndup.c
*/
char			*ft_strnum(char *string, int n);
/*
** key.c
*/
int				initkeysecond(t_pos *pos);
void			initkeysec(t_pos *pos);
int				initkey(t_pos *pos);
void			keyinit(t_pos *pos);
int				key(int key, void *structure);
/*
** main.c
*/
int				init(t_pos *pos);
t_pos			*initpos(void);
void			boucle(t_pos *pos);
/*
** parsemap.c
*/
int				check_if_map(t_pos *pos, char **map, int i);
int				count(char *cub);
int				cline(t_pos *pos, char **cub, int i);
void			map(char **cub, int i, t_pos *pos);
void			map_second(char *cub, int a, t_pos *pos);
/*
** parser.c
*/
void			verif_xpm_file(t_pos *pos);
int				check_second(t_pos *pos, int i, char **cub);
void			check(char **cub, t_pos *pos);
char			**get_line(int fd);
int				parser(char **argv, t_pos *pos);
/*
** rgb.c
*/
int				verifcase(t_pos *pos, int i, int j);
void			check_void_next(t_pos *pos, int i, int j, char dir);
int				verifmap(t_pos *pos);
int				get_color_rgb(char *string, int i);
int				color_for_c(char *string);
/*
** sprite.c
*/
void			init_all_value(t_pos *pos);
void			sprite_draw(t_pos *pos);
void			sprite_value(t_pos *pos, int i);
void			sprite_ordist(t_pos *pos);
void			init_sprite(t_pos *pos);
/*
** spritesecond.c
*/
void			sort_sprite(t_pos *pos);
double			**pos_sprite(t_pos *pos);
int				count_sprite(t_pos *pos);
/*
** tex.c
*/
void			set_path(t_pos *pos, char *line);
void			set_null_value(t_pos *pos);
int				texturing(t_pos *pos, int texnum);
t_txt			*make_data_adress(t_txt *txt);
void			init_tex(t_pos *pos);
/*
** utils.c
*/
void			ft_putstr(char *str);
int				get_color(char *s);
void			rot(t_pos *pos, char r_l);
int				whitespace(char c);
/*
** value.c
*/
void			define_second(char c, t_pos *pos, int a, int b);
void			define(char c, t_pos *pos, int a, int b);
int				sizey(char **cub, int i, int j);
int				sizex(t_pos *pos, char **cub, int i);

#endif
