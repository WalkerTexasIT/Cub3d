#include "../inc/cub3d.h"

void	dda_drawlimit(t_pos *pos)
{
	if (pos->side == 0)
		pos->perpwalldist = ((double)pos->mapx - pos->posx +
						(1 - pos->stepx) / 2) / pos->raydirx;
	else
		pos->perpwalldist = ((double)pos->mapy - pos->posy +
							(1 - pos->stepy) / 2) / pos->raydiry;
	pos->lineheight = (int)((double)pos->size_y / pos->perpwalldist);
	pos->drawstart = -pos->lineheight / 2 + pos->size_y / 2;
	if (pos->drawstart < 0)
		pos->drawstart = 0;
	pos->drawend = pos->lineheight / 2 + pos->size_y / 2;
	if (pos->drawend >= pos->size_y)
		pos->drawend = pos->size_y - 1;
	if (pos->side == 0)
		pos->wallx = pos->posy + pos->perpwalldist * pos->raydiry;
	else
		pos->wallx = pos->posx + pos->perpwalldist * pos->raydirx;
	pos->wallx -= floor((pos->wallx));
	pos->tex_x = (int)(pos->wallx * pos->txt->width[0]);
	if (pos->side == 0 && pos->raydirx > 0)
		pos->tex_x = pos->txt->width[0] - pos->tex_x - 1;
	if (pos->side == 1 && pos->raydiry < 0)
		pos->tex_x = pos->txt->width[0] - pos->tex_x - 1;
	pos->step = 1.0 * (double)pos->txt->height[0] / (double)pos->lineheight;
}

void	dda_hit(t_pos *pos)
{
	while (pos->hit == 0)
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
			pos->hit = 1;
	}
}

void	dda_sidedist(t_pos *pos)
{
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
}

void	dda_value(t_pos *pos)
{
	pos->hit = 0;
	pos->cam_x = 2 * (double)pos->x / (double)pos->size_x - 1;
	pos->raydirx = pos->dirx + pos->planex * pos->cam_x;
	pos->raydiry = pos->diry + pos->planey * pos->cam_x;
	pos->mapx = (int)pos->posx;
	pos->mapy = (int)pos->posy;
	pos->deltadistx = fabs(1 / pos->raydirx);
	pos->deltadisty = fabs(1 / pos->raydiry);
}

void	dda_while(t_pos *pos)
{
	pos->x = 0;
	while (pos->x < pos->size_x)
	{
		dda_value(pos);
		dda_sidedist(pos);
		dda_hit(pos);
		dda_drawlimit(pos);
		dda_draw(pos);
		pos->x++;
	}
	init_sprite(pos);
	mlx_put_image_to_window(pos->mlx_ptr, pos->win_ptr, pos->img_ptr, 0, 0);
}
