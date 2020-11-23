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

#include "../inc/cub3d.h"

int		init(t_pos *pos)
{
	int i;
	int j;
	int n;

	pos->mlx_ptr = mlx_init();
	pos->win_ptr = mlx_new_window(pos->mlx_ptr, pos->size_x,
			pos->size_y, "NBA 1k83");
	pos->img_ptr = mlx_new_image(pos->mlx_ptr, pos->size_x, pos->size_y);
	pos->charimg_data = mlx_get_data_addr(pos->img_ptr, &i, &j, &n);
	pos->img_data = (int*)pos->charimg_data;
	init_tex(pos);
	pos->numsprite = count_sprite(pos);
	init_all_value(pos);
	keyinit(pos);
	dda_while(pos);
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

int		main(int argc, char **argv)
{
	t_pos	pos;

	if (argc < 2)
		return (0);
	set_null_value(&pos);
	if (parser(argv, &pos) == -1)
		return (0);
	init(&pos);
	if (argc == 3)
		if (ft_strncmp(argv[2], "--save", 6) == 0)
			make_bmp(&pos);
	boucle(&pos);
	return (0);
}
