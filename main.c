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
	int	x;
	int	y;

	x = 0;
	y = 0;
	if (key == 125)
		y++;
	else if (key == 123)
		x--;
	else if (key == 124)
		x++;
	else if (key == 126)
		y--;
	else
		return (0);
	mlx_pixel_put(ptr->mlx_ptr, ptr->win_ptr, x, y, 255);
	return (1);
}

int		main(void)
{
	t_ptr	ptr;

	ptr.mlx_ptr = mlx_init();
	ptr.win_ptr = mlx_new_window(ptr.mlx_ptr, 640, 480, "CashGame");
	mlx_hook(ptr.win_ptr, 2, 0, print, &ptr);
	mlx_loop(ptr.mlx_ptr);
	return (0);
}
