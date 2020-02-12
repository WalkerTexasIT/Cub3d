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

int		print(int key, t_ptr *ptr)
{
	printf("%d\n", key);
	if (key == 125)
		ptr->y++;
	else if (key == 123)
		ptr->x--;
	else if (key == 124)
		ptr->x++;
	else if (key == 126)
		ptr->y--;
	else if (key == 53)
	{
		mlx_destroy_window(ptr->mlx_ptr, ptr->win_ptr);
		return (-1);
	}
	else
		return (0);
	mlx_pixel_put(ptr->mlx_ptr, ptr->win_ptr, ptr->x, ptr->y, 255);
	return (0);
}

int		algo(t_ptr *ptr, t_pos *pos)
{
	int		x;
	double	cameraX;

	pos->planeX = 0;
	pos->planeY = 0.66;
	x = -1;
	while (++x < ptr->size_x)
	{
		cameraX = 2 * (double)x / (double)ptr->size_x - 1;
		pos->rayDirX = pos->dirX + pos->planeX * cameraX;
		pos->rayDirY = pos->dirY + pos->planeY * cameraX;
		mapX = posY;
		mapY = posX;
		pos->deltaDistX = sqrt(1 + (pos->rayDirY * pos->rayDirY) / (pos->rayDirX * pos->rayDirX));
		pos->deltaDistY = sqrt(1 + (pos->rayDirX * pos->rayDirX) / (pos->rayDirY * pos->rayDirY));
		if (pos->rayDirX < 0)
		{
			pos->stepX = -1;
			pos->sideDistX = (pos->posX - (double)pos->mapX) * pos->deltaDistX;
		}
		else
		{
			pos->stepX = 1;
			pos->sideDistX = ((double)mapX)
		}
	}
}

int		init(t_ptr *ptr, t_pos *pos)
{
	ptr->x = (ptr->size_x / 2);
	ptr->x = (ptr->size_y / 2);
	ptr->mlx_ptr = mlx_init();
	ptr->win_ptr = mlx_new_window(ptr->mlx_ptr, 640, 480, "CashGame");
	if (mlx_hook(ptr->win_ptr, 2, 0, print, ptr) == -1)
		return (-1);
	mlx_loop(ptr->mlx_ptr);
	return (0);
}

int		main(int argc, char **argv)
{
	t_ptr	map;
	t_pos	pos;

	if (argc < 2)
		return (0);
	//parser(argv, &map, &pos);
	if (init(&map, &pos) == -1)
		return (0);
	return (0);
}