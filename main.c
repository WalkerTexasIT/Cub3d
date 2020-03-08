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

int		printline(int x, t_pos *pos)
{
	//printf("%d, %d, %d\n", x, start, end);
	while (pos->drawStart <= pos->drawEnd)
	{
		mlx_pixel_put(pos->mlx_ptr, pos->win_ptr, x, pos->drawStart, 255);
		pos->drawStart++;
	}
	return (0);
}

int		algo(t_pos *pos)
{
	int		x;
	double	cameraX;
	int		hit;

	pos->planeX = 0.66;
	pos->planeY = 0.0;
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
		printline(x, pos);
	}
	return (0);
}

int		initkey(int key, t_pos *pos)
{
	printf("%d\n", key);
	if (key == 13) // W
	{
		if (pos->map[(int)pos->posY][(int)(pos->posX + pos->dirX * MoveSpeed)] == '0')
			pos->posX += pos->dirX * MoveSpeed;
		if (pos->map[(int)(pos->posY + pos->dirY * MoveSpeed)][(int)pos->posX] == '0')
			pos->posY += pos->dirY * MoveSpeed;
	}
	if (key == 2) // D
	{
		if (pos->map[(int)pos->posY][(int)(pos->posX + -pos->dirY * MoveSpeed)] == '0')
			pos->posX += -pos->dirY * MoveSpeed;
		if (pos->map[(int)(pos->posY + pos->dirY * MoveSpeed)][(int)pos->posX] == '0')
			pos->posY += -pos->dirX * MoveSpeed;
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
	if (key == 53) // ESC
	{
		ft_free_map(pos);
		mlx_destroy_window(pos->mlx_ptr, pos->win_ptr);
		return (0);
	}
	mlx_clear_window(pos->mlx_ptr, pos->win_ptr);
	algo(pos);
	return (0);
}

int		init(t_ptr *ptr, t_pos *pos)
{
	pos->mlx_ptr = mlx_init();
	pos->win_ptr = mlx_new_window(pos->mlx_ptr, pos->size_x, pos->size_y, "CashGame");
	algo(pos);
	mlx_hook(pos->win_ptr, 2, 0, initkey, &*pos);
	mlx_loop(pos->mlx_ptr);
	return (0);
}

int		main(int argc, char **argv)
{
	t_ptr	map;
	t_pos	pos;

	if (argc < 2)
		return (0);
	parser(argv, &map, &pos);
	pos.size_x = 1920;
	pos.size_y = 1080;
	if (init(&map, &pos) == -1)
		return (0);
	return (0);
}