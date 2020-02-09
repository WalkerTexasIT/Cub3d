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
	if (key == 125)
		ptr->y++;
	else if (key == 123)
		ptr->x--;
	else if (key == 124)
		ptr->x++;
	else if (key == 126)
		ptr->y--;
	else
		return (0);
	mlx_pixel_put(ptr->mlx_ptr, ptr->win_ptr, ptr->x, ptr->y, 255);
	return (0);
}

int		init(t_ptr *ptr)
{
	ptr->x = (ptr->size_x / 2);
	ptr->x = (ptr->size_y / 2);
	ptr->mlx_ptr = mlx_init();
	ptr->win_ptr = mlx_new_window(ptr->mlx_ptr, 640, 480, "CashGame");
	mlx_hook(ptr->win_ptr, 2, 0, print, &ptr);
	mlx_loop(ptr->mlx_ptr);
	return (0);
}

int		main(int argc, char **argv)
{
	t_ptr	map;

	if (argc < 2)
		return (0); 
	map.mlx_ptr = 0;
	map.win_ptr = 0;
	map.x = 0;
	map.y = 0;
	map.size_x = 0;
	map.size_y = 0;
	map.map = 0;
	parser(argv, &map);
	return (0);
}