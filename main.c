/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bminner <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/03 09:04:11 by bminner           #+#    #+#             */
/*   Updated: 2020/02/03 09:04:13 by bminner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

//gcc -I minilibx_opengl -framework OpenGl -framework Appkit -L minilibx_opengl -lmlx *.c

void	sort_sprite(t_pos *pos)
{
	int i;
	int n;
	int	temp;

	i = -1;
	n = -1;
	while (++i < pos->numsprite - 1)
		while (++n < pos->numsprite - i - 1)
			if (pos->spritedist[n] < pos->spritedist[n + 1])
			{
				temp = pos->spriteorder[n];
				pos->spriteorder[n] = pos->spriteorder[n + 1];
				pos->spriteorder[n + 1] = temp;
			}
}

double	**pos_sprite(t_pos *pos)
{
	int		i;
	int		a;
	int		b;
	double	**possprite;

	i = 0;
	a = -1;
	if (!(possprite = (double**)malloc(sizeof(double*) * pos->numsprite)))
		ft_free_all(pos, "malloc possprite");
	while (pos->map[++a] != NULL)
	{
		if (!(possprite[i] = (double*)malloc(sizeof(double) * 2)))
			ft_free_all(pos, "malloc possprite");
		b = -1;
		while (pos->map[a][++b] != '\0')
		{
			if (pos->map[a][b] == '2')
			{
				possprite[i][0] = b + 0.5;
				possprite[i++][1] = a + 0.5;
			}
		}
	}
	return (possprite);
}

int		count_sprite(t_pos *pos)
{
	int n;
	int a;
	int b;

	n = 0;
	a = -1;
	while (pos->map[++a] != NULL)
	{
		b = -1;
		while (pos->map[a][++b] != '\0')
			if (pos->map[a][b] == '2')
				n++;
	}
	return (n);
}

void	init_all_value(t_pos *pos)
{
	if (!(pos->spriteorder = (int*)malloc(sizeof(int) * pos->numsprite)))
		ft_free_all(pos, "malloc spriteorder");
	if (!(pos->spritedist = (double*)malloc(sizeof(double) * pos->numsprite)))
		ft_free_all(pos, "malloc spriteorder");
	pos->possprite = pos_sprite(pos);
	if (!(pos->zbuffer = (double*)malloc(sizeof(double) * pos->size_x)))
		ft_free_all(pos, "zbuffer malloc");
}

void	init_sprite(t_pos *pos)
{
	int i;
	int	y;
	int	d;
	int	color;

	i = 0;
	while (i < pos->numsprite)
	{
		pos->spriteorder[i] = i;
		pos->spritedist[i] = ((pos->posx - pos->possprite[i][0]) * (pos->posx * pos->possprite[i][0]) + (pos->posy - pos->possprite[i][1]) * (pos->posy - pos->possprite[i][1]));
		i++;
	}
	if (pos->numsprite > 1)
		sort_sprite(pos);
	i = 0;
	while (i < pos->numsprite)
	{
		pos->spritex = pos->possprite[pos->spriteorder[i]][0] - pos->posx;
		pos->spritey = pos->possprite[pos->spriteorder[i]][1] - pos->posy;
		pos->intDet = 1.0 / (pos->planex * pos->diry - pos->dirx * pos->planey);
		//pos->intDet = 1.0 / (pos->diry * pos->planex - -pos->dirx * -pos->planey);
		pos->transformx = pos->intDet * (pos->diry * pos->spritex - pos->dirx * pos->spritey);
		pos->transformy = pos->intDet * (-pos->planey * pos->spritex + pos->planex * pos->spritey);
		pos->spritescreenx = (int)((pos->size_x / 2) * (1 + pos->transformx / pos->transformy));
		pos->spriteheight = abs((int)(pos->size_y / pos->transformy));
		pos->drawstarty = -pos->spriteheight / 2 + pos->size_y / 2;
		pos->drawstarty = (pos->drawstarty < 0) ? 0 : pos->drawstarty;
		pos->drawendy = pos->spriteheight / 2 + pos->size_y / 2;
		pos->drawendy = (pos->drawendy >= pos->size_y) ? pos->size_y - 1 : pos->drawendy;
		pos->spritewidth = abs((int)(pos->size_y / pos->transformy));
		pos->drawstartx = -pos->spritewidth / 2 + pos->spritescreenx;
		pos->drawstartx = (pos->drawstartx < 0) ? 0 : pos->drawstartx;
		pos->drawendx = pos->spritewidth / 2 + pos->spritescreenx;
		pos->drawendx = (pos->drawendx >= pos->size_x) ? pos->size_x - 1 : pos->drawendx;
		pos->stripe = pos->drawstartx;
		while (pos->stripe < pos->drawendx)
		{
			pos->tex_x = (int)(256 * (pos->stripe - (-pos->spritewidth / 2 + pos->spritescreenx)) * pos->txt->width[4] / pos->spritewidth) / 256;
			if (pos->transformy > 0 && pos->stripe > 0 && pos->stripe < pos->size_x && pos->transformy < pos->zbuffer[pos->stripe])
			{
				y = pos->drawstarty;
				while (y < pos->drawendy)
				{
					d = (y) * 256 - pos->size_y * 128 + pos->spriteheight * 128;
					pos->tex_y = ((d * pos->txt->height[4]) / pos->spriteheight) / 256;
					color = pos->txt->txt[4][pos->txt->width[4] * pos->tex_y + pos->tex_x];
					if ((color & 0x00FFFFFF) != 0)
						pos->img_data[(pos->size_x * y) + pos->stripe] = color;
					y++;
				}
			}
			pos->stripe++;
		}
		i++;
	}
}

int		texturing(t_pos *pos, int texnum)
{
	int		color;

	pos->tex_y = (int)pos->texpos & (pos->txt->height[texnum] - 1);
	pos->texpos += pos->step;
	color = (int)pos->txt->txt[texnum][pos->txt->height[texnum] * pos->tex_y + pos->tex_x];
	return (color);
}

t_txt	*make_data_adress(t_txt *txt)
{
	int i;

	i = 0;
	if (!(txt->chartxt = (char**)malloc(sizeof(char*) * 5)))
		return (NULL);
	while (i < 5)
	{
		txt->chartxt[i] = mlx_get_data_addr(txt->voidtxt[i], &txt->bits[i], &txt->sl[i], &txt->end[i]);
		i++;
	}
	i = 0;
	if (!(txt->txt = (int**)malloc(sizeof(int*) * 5)))
		return (NULL);
	while (i < 5)
	{
		txt->txt[i] = (int*)txt->chartxt[i];
		i++;
	}
	return (txt);
}

void	init_tex(t_pos *pos)
{
	verif_xpm_file(pos);
	if (!(pos->txt->voidtxt = (void**)malloc(sizeof(void*) * 5)))
		return (ft_free_all(pos, "malloc void**"));
	if (!(pos->txt->voidtxt[0] = (void*)mlx_xpm_file_to_image(pos->mlx_ptr, pos->linkn,
		&pos->txt->width[0], &pos->txt->height[0])))
		return (ft_free_all(pos, "xpm to ... N"));
	if (!(pos->txt->voidtxt[1] = (void*)mlx_xpm_file_to_image(pos->mlx_ptr, pos->links,
		&pos->txt->width[1], &pos->txt->height[1])))
		return (ft_free_all(pos, "xpm to ... S"));
	if (!(pos->txt->voidtxt[2] = (void*)mlx_xpm_file_to_image(pos->mlx_ptr, pos->linke,
		&pos->txt->width[2], &pos->txt->height[2])))
		return (ft_free_all(pos, "xpm to ... E"));
	if (!(pos->txt->voidtxt[3] = (void*)mlx_xpm_file_to_image(pos->mlx_ptr, pos->linkw,
		&pos->txt->width[3], &pos->txt->height[3])))
		return (ft_free_all(pos, "xpm to ... W"));
	if (!(pos->txt->voidtxt[4] = (void*)mlx_xpm_file_to_image(pos->mlx_ptr, pos->linksprite,
		&pos->txt->width[4], &pos->txt->height[4])))
		return (ft_free_all(pos, "xpm to ... W"));
	if (make_data_adress(pos->txt) == NULL)
		return (ft_free_all(pos, "malloc in data adress"));
}

int		algo(t_pos *pos)
{
	int		x;
	double	cam_x;
	int		hit;
	int		y;
	int		color;
	int		n;
	int		i;

	//printf("Dir(%f, %f) Pos(%f, %f) Plane(%f, %f)\n", pos->dirx, pos->diry, pos->posx, pos->posy, pos->planex, pos->planey);
	x = -1;
	while (++x < pos->size_x)
	{
		hit = 0;
		cam_x = 2 * (double)x / (double)pos->size_x - 1;
		pos->raydirx = pos->dirx + pos->planex * cam_x;
		pos->raydiry = pos->diry + pos->planey * cam_x;
		pos->mapx = (int)pos->posx;
		pos->mapy = (int)pos->posy;
		pos->deltadistx = fabs(1 / pos->raydirx);
		pos->deltadisty = fabs(1 / pos->raydiry);
		if (pos->raydirx < 0)
		{
			pos->stepx = -1;
			pos->sidedistx = (pos->posx - pos->mapx) * pos->deltadistx;
		}
		else
		{
			pos->stepx = 1;
			pos->sidedistx = (pos->mapx + 1.0 - pos->posx) * pos->deltadistx;
		}
		if (pos->raydiry < 0)
		{
			pos->stepy = -1;
			pos->sidedisty = (pos->posy - pos->mapy) * pos->deltadisty;
		}
		else
		{
			pos->stepy = 1;
			pos->sidedisty = (pos->mapy + 1.0 - pos->posy) * pos->deltadisty;
		}
		while (hit == 0)
		{
			if (pos->sidedistx < pos->sidedisty)
			{
				pos->sidedistx += pos->deltadistx;
				pos->mapx += pos->stepx;
				pos->side = 0;
			}
			else
			{
				pos->sidedisty += pos->deltadisty;
				pos->mapy += pos->stepy;
				pos->side = 1;
			}
			if (pos->map[pos->mapy][pos->mapx] == '1')
				hit = 1;
		}
		if (pos->side == 0)
			pos->perpwalldist = ((double)pos->mapx - pos->posx + (1 - pos->stepx) / 2) / pos->raydirx;
		else
			pos->perpwalldist = ((double)pos->mapy - pos->posy + (1 - pos->stepy) / 2) / pos->raydiry;
		pos->lineheight = (int)((double)pos->size_y / pos->perpwalldist);
		pos->drawstart = -pos->lineheight / 2 + pos->size_y / 2;
		if (pos->drawstart < 0)
			pos->drawstart = 0;
		pos->drawend = pos->lineheight / 2 + pos->size_y / 2;
		if (pos->drawend >= pos->size_y)
			pos->drawend = pos->size_y - 1;
		// wall
		if (pos->side == 0)
			pos->wallx = pos->posy + pos->perpwalldist * pos->raydiry;
		else
			pos->wallx = pos->posx + pos->perpwalldist * pos->raydirx;
		pos->wallx -= floor((pos->wallx));
		pos->tex_x = (int)(pos->wallx * pos->txt->width[0]);
		if(pos->side == 0 && pos->raydirx > 0)
			pos->tex_x = pos->txt->width[0] - pos->tex_x - 1;
		if(pos->side == 1 && pos->raydiry < 0)
			pos->tex_x = pos->txt->width[0] - pos->tex_x - 1;
		pos->step = 1.0 * (double)pos->txt->height[0] / (double)pos->lineheight;
		pos->texpos = (pos->drawstart - pos->size_y / 2 + pos->lineheight / 2) * pos->step;
		i = 0;
		n = x;
		while (i < pos->drawstart) // sol
		{
			pos->img_data[n] = pos->color_c;
			n += pos->size_x;
			i++;
		}
		while (i < pos->drawend) // wall
		{
			if (pos->side == 0 && pos->raydirx < 0)
				pos->img_data[n] = texturing(pos, 3);
			else if (pos->side == 0 && pos->raydirx > 0)
				pos->img_data[n] = texturing(pos, 2);
			else if (pos->side == 1 && pos->raydiry < 0)
				pos->img_data[n] = texturing(pos, 0);
			else if (pos->side == 1 && pos->raydiry > 0)
				pos->img_data[n] = texturing(pos, 1);
			n += pos->size_x;
			i++;
		}
		while (i < pos->size_y) // plafond
		{
			pos->img_data[n] = pos->color_f;
			n += pos->size_x;
			i++;
		}
		pos->zbuffer[x] = pos->perpwalldist;
	}
	init_sprite(pos);
	mlx_put_image_to_window(pos->mlx_ptr, pos->win_ptr, pos->img_ptr, 0 ,0);
	return (0);
}

int		initkey(t_pos *pos)
{
	if (pos->key->key_w == 1) // W
	{
		if (pos->map[(int)pos->posy][(int)(pos->posx + pos->dirx * MoveSpeed + (pos->dirx < 0 ? -0.2 : 0.2))] != '1')
			pos->posx += pos->dirx * MoveSpeed;
		if (pos->map[(int)(pos->posy + pos->diry * MoveSpeed + (pos->diry < 0 ? -0.2 : 0.2))][(int)pos->posx] != '1')
			pos->posy += pos->diry * MoveSpeed;
		pos->key->key_w = 0;
	}
	if (pos->key->key_d == 1) // D
	{
		if (pos->map[(int)pos->posy][(int)(pos->posx - pos->diry * MoveSpeed + (-pos->diry < 0 ? -0.2 : 0.2))] != '1')
			pos->posx += -pos->diry * MoveSpeed;
		if (pos->map[(int)(pos->posy + pos->dirx * MoveSpeed + (pos->dirx < 0 ? -0.2 : 0.2))][(int)pos->posx] != '1')
			pos->posy += pos->dirx * MoveSpeed;
		pos->key->key_d = 0;
	}
	if (pos->key->key_s == 1) // S
	{
		if (pos->map[(int)pos->posy][(int)(pos->posx - pos->dirx * MoveSpeed + (-pos->dirx < 0 ? -0.2 : 0.2))] != '1')
			pos->posx -= pos->dirx * MoveSpeed;
		if (pos->map[(int)(pos->posy - pos->diry * MoveSpeed + (-pos->diry < 0 ? -0.2 : 0.2))][(int)pos->posx] != '1')
			pos->posy -= pos->diry * MoveSpeed;
		pos->key->key_s = 0;
	}
	if (pos->key->key_a == 1) // A
	{
		if (pos->map[(int)pos->posy][(int)(pos->posx + pos->diry * MoveSpeed + (pos->diry < 0 ? -0.2 : 0.2))] != '1')
			pos->posx += pos->diry * MoveSpeed;
		if (pos->map[(int)(pos->posy + pos->diry * MoveSpeed + (-pos->dirx < 0 ? -0.2 : 0.2))][(int)pos->posx] != '1')
			pos->posy += -pos->dirx * MoveSpeed;
		pos->key->key_a = 0;
	}
	if (pos->key->key_right == 1) // fleche droite
		rot(pos, 'R');
	if (pos->key->key_left == 1) // fleche gauche
		rot(pos, 'L');
	if (pos->win_ptr)
		mlx_clear_window(pos->mlx_ptr, pos->win_ptr);
	algo(pos);
	return (0);
}

void	keyinit(t_pos *pos)
{
	t_key	key;

	pos->key = &key;
	pos->key->key_w = 0;
	pos->key->key_s = 0;
	pos->key->key_a = 0;
	pos->key->key_d = 0;
	pos->key->key_left = 0;
	pos->key->key_right = 0;
}

int		init(t_pos *pos)
{
	int i;
	int j;
	int n;

	pos->mlx_ptr = mlx_init();
	pos->win_ptr = mlx_new_window(pos->mlx_ptr, pos->size_x, pos->size_y, "NBA 1k83");
	pos->img_ptr = mlx_new_image(pos->mlx_ptr, pos->size_x, pos->size_y);
	pos->charimg_data = mlx_get_data_addr(pos->img_ptr, &i, &j, &n);
	pos->img_data = (int*)pos->charimg_data;
	init_tex(pos);
	pos->numsprite = count_sprite(pos);
	init_all_value(pos);
	keyinit(pos);
	algo(pos);
	return (0);
}

int		key(int key, void *structure)
{
	t_pos	*pos;

	pos = (t_pos*)structure;
	if (key == 13)
		pos->key->key_w = 1;
	if (key == 1)
		pos->key->key_s = 1;
	if (key == 2)
		pos->key->key_d = 1;
	if (key == 0)
		pos->key->key_a = 1;
	if (key == 124)
		pos->key->key_right = 1;
	if (key == 123)
		pos->key->key_left = 1;
	if (key == 53)
		ft_free_all(pos, "");
	if (key == 17)
		ft_free_all(pos, "");
	return (0);
}

t_pos	*initpos(void)
{
	t_pos	*pos;

	if (!(pos = (t_pos*)malloc(sizeof(t_pos*))))
		exit(0);
	return (pos);
}

void	boucle(t_pos *pos)
{
	mlx_hook(pos->win_ptr, 2, 0, key, pos);
	mlx_hook(pos->win_ptr, 3, 0, key, pos);
	mlx_hook(pos->win_ptr, 17, 0, finish, pos);
	mlx_loop_hook(pos->mlx_ptr, initkey, pos);
	mlx_loop(pos->mlx_ptr);
}

void	set_null_value(t_pos *pos)
{
	if (!(pos->txt = malloc(sizeof(t_txt))))
		return (ft_free_all(pos, "malloc t_txt"));
	pos->map = NULL;
	pos->txt->voidtxt = NULL;
	pos->txt->chartxt = NULL;
	pos->spriteorder = NULL;
	pos->linkn = NULL;
	pos->links = NULL;
	pos->linkw = NULL;
	pos->linke = NULL;
	pos->linksprite = NULL;
}

int		main(int argc, char **argv)
{
	t_pos	pos;

	if (argc < 2)
		return (0);
	set_null_value(&pos);
	//if (!(pos = (t_pos*)malloc(sizeof(t_pos*))))
	//	return (0);
	if (parser(argv, &pos) == -1)
		return (0);
	//printf("%d\n", ft_strncmp(argv[2], "--save", 6));
	init(&pos);
	if (argc == 3)
		if (ft_strncmp(argv[2], "--save", 6) == 0)
			make_bmp(&pos);
	boucle(&pos);
	return (0);
}
