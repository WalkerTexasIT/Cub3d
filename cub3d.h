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
# include <mlx.h>
# include <stdio.h>
/*# include <math.h>
# define mapWidth 24
# define mapHeight 24
# define screenWidth 640
# define screenHeight 480*/

typedef struct	s_ptr {
	void *mlx_ptr;
	void *win_ptr;
}				t_ptr;

/*typedef struct	s_pos {
	double posX;
	double posY;
	double dirX;
	double dirY;
}				t_pos;*/

#endif