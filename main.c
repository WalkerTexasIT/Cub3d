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

int		printline(int x, int start, int end, t_ptr *ptr)
{
	//printf("%d, %d, %d\n", x, start, end);
	while (start <= end)
	{
		mlx_pixel_put(ptr->mlx_ptr, ptr->win_ptr, x, start, 255);
		start++;
	}
	return (0);
}

int		algo(t_ptr *ptr, t_pos *pos)
{
	int		x;
	double	cameraX;
	int		hit;

	hit = 0;
	pos->planeX = 0;
	pos->planeY = 0.66;
	x = -1;
	while (++x < ptr->size_x)
	{
		cameraX = 2 * (double)x / (double)ptr->size_x - 1;
		pos->rayDirX = pos->dirX + pos->planeX * cameraX;
		pos->rayDirY = pos->dirY + pos->planeY * cameraX;
		pos->mapX = (int)pos->posY;
		pos->mapY = (int)pos->posX;
		pos->deltaDistX = fabs(1 / pos->rayDirX);
		pos->deltaDistY = fabs(1 / pos->rayDirY);
		if (pos->rayDirX < 0)
		{
			pos->stepX = -1;
			pos->sideDistX = (pos->posY - pos->mapX) * pos->deltaDistX;
		}
		else
		{
			pos->stepX = 1;
			pos->sideDistX = (pos->mapX + 1.0 - pos->posY) * pos->deltaDistX;
		}
		if (pos->rayDirY < 0)
		{
			pos->stepY = -1;
			pos->sideDistY = (pos->posX - pos->mapY) * pos->deltaDistY;
		}
		else
		{
			pos->stepY = 1;
			pos->sideDistY = (pos->mapY + 1.0 - pos->posX) * pos->deltaDistY;
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
			if (ptr->map[pos->mapX][pos->mapY] == '1')
				hit = 1;
		}
		if (pos->side == 0)
			pos->perpWallDist = ((double)pos->mapX - pos->posX + (1 - pos->stepX) / 2) / pos->rayDirX;
		else
			pos->perpWallDist = ((double)pos->mapY - pos->posY + (1 - pos->stepY) / 2) / pos->rayDirY;
		pos->lineHeight = (int)((double)ptr->size_y / pos->perpWallDist);
		if (x == 1)
			printf("%f\n", pos->perpWallDist);
		pos->drawStart = -pos->lineHeight / 2 + ptr->size_y / 2;
		if (pos->drawStart < 0)
			pos->drawStart = 0;
		pos->drawEnd = pos->lineHeight / 2 + ptr->size_y / 2;
		if (pos->drawEnd >= ptr->size_y)
			pos->drawEnd = ptr->size_y - 1;
		printline(x, pos->drawStart, pos->drawEnd, ptr);
	}
	return (0);
}

int		init(t_ptr *ptr, t_pos *pos)
{
	ptr->mlx_ptr = mlx_init();
	ptr->win_ptr = mlx_new_window(ptr->mlx_ptr, ptr->size_x, ptr->size_y, "CashGame");
	/*if (mlx_hook(ptr->win_ptr, 2, 0, print, ptr) == -1)
		return (-1);*/
	algo(ptr, pos);
	mlx_loop(ptr->mlx_ptr);
	return (0);
}

int		main(int argc, char **argv)
{
	t_ptr	map;
	t_pos	pos;

	if (argc < 2)
		return (0);
	parser(argv, &map, &pos);
	map.size_x = 1920;
	map.size_y = 1080;
	if (init(&map, &pos) == -1)
		return (0);
	return (0);
}