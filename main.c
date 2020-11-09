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

void	sortSprite(t_pos *pos)
{
	int i;
	int n;
	int	temp;

	i = -1;
	n = -1;
	while (++i < pos->numSprite - 1)
		while (++n < pos->numSprite - i - 1)
			if (pos->spriteDistance[n] < pos->spriteDistance[n + 1])
			{
				temp = pos->spriteOrder[n];
				pos->spriteOrder[n] = pos->spriteOrder[n + 1];
				pos->spriteOrder[n + 1] = temp;
			}
}

double	**posSprite(t_pos *pos)
{
	int		i;
	int		a;
	int		b;
	double	**posSprite;

	i = 0;
	a = -1;
	if (!(posSprite = (double**)malloc(sizeof(double*) * pos->numSprite)))
		ft_free_all(pos, "malloc posSprite");
	while (pos->map[++a] != NULL)
	{
		if (!(posSprite[i] = (double*)malloc(sizeof(double) * 2)))
			ft_free_all(pos, "malloc posSprite");
		b = -1;
		while (pos->map[a][++b] != '\0')
		{
			if (pos->map[a][b] == '2')
			{
				posSprite[i][0] = b + 0.5;
				posSprite[i++][1] = a + 0.5;
			}
		}
	}
	return (posSprite);
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
	if (!(pos->spriteOrder = (int*)malloc(sizeof(int) * pos->numSprite)))
		ft_free_all(pos, "malloc spriteOrder");
	if (!(pos->spriteDistance = (double*)malloc(sizeof(double) * pos->numSprite)))
		ft_free_all(pos, "malloc spriteOrder");
	pos->posSprite = posSprite(pos);
	if (!(pos->ZBuffer = (double*)malloc(sizeof(double) * pos->size_x)))
		ft_free_all(pos, "ZBuffer malloc");
}

void	init_sprite(t_pos *pos)
{
	int i;
	int	y;
	int	d;
	int	color;

	i = 0;
	while (i < pos->numSprite)
	{
		pos->spriteOrder[i] = i;
		pos->spriteDistance[i] = ((pos->posX - pos->posSprite[i][0]) * (pos->posX * pos->posSprite[i][0]) + (pos->posY - pos->posSprite[i][1]) * (pos->posY - pos->posSprite[i][1]));
		i++;
	}
	if (pos->numSprite > 1)
		sortSprite(pos);
	i = 0;
	while (i < pos->numSprite)
	{
		pos->spriteX = pos->posSprite[pos->spriteOrder[i]][0] - pos->posX;
		pos->spriteY = pos->posSprite[pos->spriteOrder[i]][1] - pos->posY;
		pos->intDet = 1.0 / (pos->planeX * pos->dirY - pos->dirX * pos->planeY);
		//pos->intDet = 1.0 / (pos->dirY * pos->planeX - -pos->dirX * -pos->planeY);
		pos->transformX = pos->intDet * (pos->dirY * pos->spriteX - pos->dirX * pos->spriteY);
		pos->transformY = pos->intDet * (-pos->planeY * pos->spriteX + pos->planeX * pos->spriteY);
		pos->spriteScreenX = (int)((pos->size_x / 2) * (1 + pos->transformX / pos->transformY));
		pos->spriteHeight = abs((int)(pos->size_y / pos->transformY));
		pos->drawStartY = -pos->spriteHeight / 2 + pos->size_y / 2;
		pos->drawStartY = (pos->drawStartY < 0) ? 0 : pos->drawStartY;
		pos->drawEndY = pos->spriteHeight / 2 + pos->size_y / 2;
		pos->drawEndY = (pos->drawEndY >= pos->size_y) ? pos->size_y - 1 : pos->drawEndY;
		pos->spriteWidth = abs((int)(pos->size_y / pos->transformY));
		pos->drawStartX = -pos->spriteWidth / 2 + pos->spriteScreenX;
		pos->drawStartX = (pos->drawStartX < 0) ? 0 : pos->drawStartX;
		pos->drawEndX = pos->spriteWidth / 2 + pos->spriteScreenX;
		pos->drawEndX = (pos->drawEndX >= pos->size_x) ? pos->size_x - 1 : pos->drawEndX;
		pos->stripe = pos->drawStartX;
		while (pos->stripe < pos->drawEndX)
		{
			pos->texX = (int)(256 * (pos->stripe - (-pos->spriteWidth / 2 + pos->spriteScreenX)) * pos->txt->width[4] / pos->spriteWidth) / 256;
			if (pos->transformY > 0 && pos->stripe > 0 && pos->stripe < pos->size_x && pos->transformY < pos->ZBuffer[pos->stripe])
			{
				y = pos->drawStartY;
				while (y < pos->drawEndY)
				{
					d = (y) * 256 - pos->size_y * 128 + pos->spriteHeight * 128;
					pos->texY = ((d * pos->txt->height[4]) / pos->spriteHeight) / 256;
					color = pos->txt->txt[4][pos->txt->width[4] * pos->texY + pos->texX];
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

	pos->texY = (int)pos->texPos & (pos->txt->height[texnum] - 1);
	pos->texPos += pos->step;
	color = (int)pos->txt->txt[texnum][pos->txt->height[texnum] * pos->texY + pos->texX];
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
	if (!(pos->txt = malloc(sizeof(t_txt))))
		return (ft_free_all(pos, "malloc t_txt"));
	if (!(pos->txt->voidtxt = (void**)malloc(sizeof(void*) * 5)))
		return (ft_free_all(pos, "malloc void**"));
	if (!(pos->txt->voidtxt[0] = (void*)mlx_xpm_file_to_image(pos->mlx_ptr, pos->linkN,
		&pos->txt->width[0], &pos->txt->height[0])))
		return (ft_free_all(pos, "xpm to ... N"));
	if (!(pos->txt->voidtxt[1] = (void*)mlx_xpm_file_to_image(pos->mlx_ptr, pos->linkS,
		&pos->txt->width[1], &pos->txt->height[1])))
		return (ft_free_all(pos, "xpm to ... S"));
	if (!(pos->txt->voidtxt[2] = (void*)mlx_xpm_file_to_image(pos->mlx_ptr, pos->linkE,
		&pos->txt->width[2], &pos->txt->height[2])))
		return (ft_free_all(pos, "xpm to ... E"));
	if (!(pos->txt->voidtxt[3] = (void*)mlx_xpm_file_to_image(pos->mlx_ptr, pos->linkW,
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
	double	cameraX;
	int		hit;
	int		y;
	int		color;
	int		n;
	int		i;

	//printf("Dir(%f, %f) Pos(%f, %f) Plane(%f, %f)\n", pos->dirX, pos->dirY, pos->posX, pos->posY, pos->planeX, pos->planeY);
	x = -1;
	while (++x < pos->size_x)
	{
		hit = 0;
		cameraX = 2 * (double)x / (double)pos->size_x - 1;
		pos->rayDirX = pos->dirX + pos->planeX * cameraX;
		pos->rayDirY = pos->dirY + pos->planeY * cameraX;
		pos->mapX = (int)pos->posX;
		pos->mapY = (int)pos->posY;
		pos->deltaDistX = fabs(1 / pos->rayDirX);
		pos->deltaDistY = fabs(1 / pos->rayDirY);
		if (pos->rayDirX < 0)
		{
			pos->stepX = -1;
			pos->sideDistX = (pos->posX - pos->mapX) * pos->deltaDistX;
		}
		else
		{
			pos->stepX = 1;
			pos->sideDistX = (pos->mapX + 1.0 - pos->posX) * pos->deltaDistX;
		}
		if (pos->rayDirY < 0)
		{
			pos->stepY = -1;
			pos->sideDistY = (pos->posY - pos->mapY) * pos->deltaDistY;
		}
		else
		{
			pos->stepY = 1;
			pos->sideDistY = (pos->mapY + 1.0 - pos->posY) * pos->deltaDistY;
		}
		while (hit == 0)
		{
			if (pos->sideDistX < pos->sideDistY)
			{
				pos->sideDistX += pos->deltaDistX;
				pos->mapX += pos->stepX;
				pos->side = 0;
			}
			else
			{
				pos->sideDistY += pos->deltaDistY;
				pos->mapY += pos->stepY;
				pos->side = 1;
			}
			if (pos->map[pos->mapY][pos->mapX] == '1')
				hit = 1;
		}
		if (pos->side == 0)
			pos->perpWallDist = ((double)pos->mapX - pos->posX + (1 - pos->stepX) / 2) / pos->rayDirX;
		else
			pos->perpWallDist = ((double)pos->mapY - pos->posY + (1 - pos->stepY) / 2) / pos->rayDirY;
		pos->lineHeight = (int)((double)pos->size_y / pos->perpWallDist);
		pos->drawStart = -pos->lineHeight / 2 + pos->size_y / 2;
		if (pos->drawStart < 0)
			pos->drawStart = 0;
		pos->drawEnd = pos->lineHeight / 2 + pos->size_y / 2;
		if (pos->drawEnd >= pos->size_y)
			pos->drawEnd = pos->size_y - 1;
		// wall
		if (pos->side == 0)
			pos->wallX = pos->posY + pos->perpWallDist * pos->rayDirY;
		else
			pos->wallX = pos->posX + pos->perpWallDist * pos->rayDirX;
		pos->wallX -= floor((pos->wallX));
		pos->texX = (int)(pos->wallX * pos->txt->width[0]);
		if(pos->side == 0 && pos->rayDirX > 0)
			pos->texX = pos->txt->width[0] - pos->texX - 1;
		if(pos->side == 1 && pos->rayDirY < 0)
			pos->texX = pos->txt->width[0] - pos->texX - 1;
		pos->step = 1.0 * (double)pos->txt->height[0] / (double)pos->lineHeight;
		pos->texPos = (pos->drawStart - pos->size_y / 2 + pos->lineHeight / 2) * pos->step;
		i = 0;
		n = x;
		while (i < pos->drawStart) // sol
		{
			pos->img_data[n] = pos->colorC;
			n += pos->size_x;
			i++;
		}
		while (i < pos->drawEnd) // wall
		{
			if (pos->side == 0 && pos->rayDirX < 0)
				pos->img_data[n] = texturing(pos, 3);
			else if (pos->side == 0 && pos->rayDirX > 0)
				pos->img_data[n] = texturing(pos, 2);
			else if (pos->side == 1 && pos->rayDirY < 0)
				pos->img_data[n] = texturing(pos, 0);
			else if (pos->side == 1 && pos->rayDirY > 0)
				pos->img_data[n] = texturing(pos, 1);
			n += pos->size_x;
			i++;
		}
		while (i < pos->size_y) // plafond
		{
			pos->img_data[n] = pos->colorF;
			n += pos->size_x;
			i++;
		}
		pos->ZBuffer[x] = pos->perpWallDist;
	}
	init_sprite(pos);
	mlx_put_image_to_window(pos->mlx_ptr, pos->win_ptr, pos->img_ptr, 0 ,0);
	return (0);
}

int		initkey(t_pos *pos)
{
	printf("test100\n");
	if (pos->key->key_w == 1) // W
	{
		if (pos->map[(int)pos->posY][(int)(pos->posX + pos->dirX * MoveSpeed + (pos->dirX < 0 ? -0.2 : 0.2))] != '1')
			pos->posX += pos->dirX * MoveSpeed;
		if (pos->map[(int)(pos->posY + pos->dirY * MoveSpeed + (pos->dirY < 0 ? -0.2 : 0.2))][(int)pos->posX] != '1')
			pos->posY += pos->dirY * MoveSpeed;
		pos->key->key_w = 0;
	}
	if (pos->key->key_d == 1) // D
	{
		if (pos->map[(int)pos->posY][(int)(pos->posX - pos->dirY * MoveSpeed + (-pos->dirY < 0 ? -0.2 : 0.2))] != '1')
			pos->posX += -pos->dirY * MoveSpeed;
		if (pos->map[(int)(pos->posY + pos->dirX * MoveSpeed + (pos->dirX < 0 ? -0.2 : 0.2))][(int)pos->posX] != '1')
			pos->posY += pos->dirX * MoveSpeed;
		pos->key->key_d = 0;
	}
	if (pos->key->key_s == 1) // S
	{
		if (pos->map[(int)pos->posY][(int)(pos->posX - pos->dirX * MoveSpeed + (-pos->dirX < 0 ? -0.2 : 0.2))] != '1')
			pos->posX -= pos->dirX * MoveSpeed;
		if (pos->map[(int)(pos->posY - pos->dirY * MoveSpeed + (-pos->dirY < 0 ? -0.2 : 0.2))][(int)pos->posX] != '1')
			pos->posY -= pos->dirY * MoveSpeed;
		pos->key->key_s = 0;
	}
	if (pos->key->key_a == 1) // A
	{
		if (pos->map[(int)pos->posY][(int)(pos->posX + pos->dirY * MoveSpeed + (pos->dirY < 0 ? -0.2 : 0.2))] != '1')
			pos->posX += pos->dirY * MoveSpeed;
		if (pos->map[(int)(pos->posY + pos->dirY * MoveSpeed + (-pos->dirX < 0 ? -0.2 : 0.2))][(int)pos->posX] != '1')
			pos->posY += -pos->dirX * MoveSpeed;
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

	printf("test504\n");
	pos->mlx_ptr = mlx_init();
	printf("test505\n");
	pos->win_ptr = mlx_new_window(pos->mlx_ptr, pos->size_x, pos->size_y, "NBA 1k83");
	pos->img_ptr = mlx_new_image(pos->mlx_ptr, pos->size_x, pos->size_y);
	pos->charimg_data = mlx_get_data_addr(pos->img_ptr, &i, &j, &n);
	pos->img_data = (int*)pos->charimg_data;
	init_tex(pos);
	printf("test1\n");
	pos->numSprite = count_sprite(pos);
	printf("test2\n");
	init_all_value(pos);
	printf("test3\n");
	keyinit(pos);
	printf("test4\n");
	algo(pos);
	printf("test5\n");
	return (0);
}

int		key(int key, void *structure)
{
	t_pos	*pos;

	printf("test404\n");
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
	printf("test6\n");
	mlx_hook(pos->win_ptr, 2, 0, key, pos);
	printf("test7\n");
	mlx_hook(pos->win_ptr, 3, 0, key, pos);
	printf("test8\n");
	mlx_hook(pos->win_ptr, 17, 0, finish, pos);
	printf("test9\n");
	mlx_loop_hook(pos->mlx_ptr, initkey, pos);
	printf("test10\n");
	mlx_loop(pos->mlx_ptr);
}

int		main(int argc, char **argv)
{
	t_pos	pos;

	if (argc < 2)
		return (0);
	//if (!(pos = (t_pos*)malloc(sizeof(t_pos*))))
	//	return (0);
	if (parser(argv, &pos) == -1)
		return (0);
	//printf("%d\n", ft_strncmp(argv[2], "--save", 6));
	printf("test\n");
	init(&pos);
	printf("test27\n");
	if (argc == 3)
		if (ft_strncmp(argv[2], "--save", 6) == 0)
			make_bmp(&pos);
	printf("test28\n");
	boucle(&pos);
	return (0);
}
