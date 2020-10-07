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

int		**posSprite(t_pos *pos)
{
	int		i;
	int		a;
	int		b;
	int		posSprite[pos->numSprite][2];

	i = 0;
	a = 0;
	while (pos->map[a] != NULL)
	{
		b = 0;
		while (pos->map[a][b] != '\0')
		{
			if (pos->map[a][b] == '2')
			{
				posSprite[i][0] = b;
				posSprite[i][1] = a;
				i++;
			}
			b++;
		}
		a++;
	}
	return (posSprite);
}

int		countsprite(t_pos *pos)
{
	int n;
	int a;
	int b;

	n = 0;
	a = 0;
	while (pos->map[a] != NULL)
	{
		b = 0;
		while (pos->map[a][b] != '\0')
		{
			if (pos->map[a][b] == '2')
				n++;
			b++;
		}
		a++;
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
}

void	init_sprite(t_pos *pos)
{
	int i;

	i = 0;
	while (i < pos->numSprite)
	{
		pos->spriteOrder[i] = i;
		pos->spriteDistance[i] = ((pos->posX - pos->posSprite[i][0]) * (pos->posX * pos->posSprite[i][0]) + (pos->posY - pos->posSprite[i][1]) * (pos->posY - pos->posSprite[i][1]));
	}
	i = 0;
	while (i < pos->numSprite)
	{
		pos->spriteX = pos->posSprite[i][0] - pos->posX;
		pos->spriteY = pos->posSprite[i][1] - pos->posY;
		pos->intDet = 1.0 / (pos->planeX * pos->dirY - pos->dirX * pos->planeY);
		pos->transformX = pos->intDet
		pos->transformY =
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
	if (!(pos->txt->voidtxt = (void**)malloc(sizeof(void*) * 4)))
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
	if (!(pos->txt->voidtxt[4] = (void*)mlx_xpm_file_to_image(pos->mlx_ptr, pos->linkSprite,
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
		// sprite
		pos->numSprite = count_sprite(pos);
		init_sprite(pos);
	}
	mlx_put_image_to_window(pos->mlx_ptr, pos->win_ptr, pos->img_ptr, 0 ,0);
	return (0);
}

int		initkey(int key, t_pos *pos)
{
	//printf("%d\n", key);
	if (key == 13) // W
	{
		if (pos->map[(int)pos->posY][(int)(pos->posX + pos->dirX * MoveSpeed)] == '0')
			pos->posX += pos->dirX * MoveSpeed;
		if (pos->map[(int)(pos->posY + pos->dirY * MoveSpeed)][(int)pos->posX] == '0')
			pos->posY += pos->dirY * MoveSpeed;
	}
	if (key == 2) // D
	{
		if (pos->map[(int)pos->posY][(int)(pos->posX - pos->dirY * MoveSpeed)] == '0')
			pos->posX += -pos->dirY * MoveSpeed;
		if (pos->map[(int)(pos->posY + pos->dirX * MoveSpeed)][(int)pos->posX] == '0')
			pos->posY += pos->dirX * MoveSpeed;
	}
	if (key == 1) // S
	{
		if (pos->map[(int)pos->posY][(int)(pos->posX - pos->dirX * MoveSpeed)] == '0')
			pos->posX -= pos->dirX * MoveSpeed;
		if (pos->map[(int)(pos->posY - pos->dirY * MoveSpeed)][(int)pos->posX] == '0')
			pos->posY -= pos->dirY * MoveSpeed;
	}
	if (key == 0) // A
	{
		if (pos->map[(int)pos->posY][(int)(pos->posX + pos->dirY * MoveSpeed)] == '0')
			pos->posX += pos->dirY * MoveSpeed;
		if (pos->map[(int)(pos->posY + pos->dirY * MoveSpeed)][(int)pos->posX] == '0')
			pos->posY += -pos->dirX * MoveSpeed;
	}
	if (key == 124) // fleche droite
		rot(pos, 'R');
	if (key == 123) // fleche gauche
		rot(pos, 'L');
	if (key == 53) // ESC
	{
		ft_free_map(pos);
		mlx_destroy_window(pos->mlx_ptr, pos->win_ptr);
		exit(0);
	}
	mlx_clear_window(pos->mlx_ptr, pos->win_ptr);
	algo(pos);
	return (0);
}

int		init(t_pos *pos)
{
	int i;
	int j;
	int n;

	pos->mlx_ptr = mlx_init();
	pos->win_ptr = mlx_new_window(pos->mlx_ptr, pos->size_x, pos->size_y, "CashGame");
	pos->img_ptr = mlx_new_image(pos->mlx_ptr, pos->size_x, pos->size_y);
	pos->charimg_data = mlx_get_data_addr(pos->img_ptr, &i, &j, &n);
	pos->img_data = (int*)pos->charimg_data;
	init_tex(pos);
	pos->numSprite = count_sprite(pos);
	init_all_value(pos);
	algo(pos);
	if (mlx_hook(pos->win_ptr, 2, 0, initkey, &*pos) == -1)
		return (-1);
	mlx_loop(pos->mlx_ptr);
	return (0);
}

int		main(int argc, char **argv)
{
	t_pos	pos;

	if (argc < 2)
		return (0);
	if (parser(argv, &pos) == -1)
		return (0);
	//pos.size_x = 1080;
	//pos.size_y = 768;
	if (init(&pos) == -1)
		return (0);
	return (0);
}
