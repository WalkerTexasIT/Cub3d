#include "../inc/cub3d.h"

void	init_all_value(t_pos *pos)
{
	if (!(pos->spriteorder = (int*)malloc(sizeof(int) * pos->numsprite)))
		ft_free_all(pos, "malloc spriteorder");
	if (!(pos->spritedist = (double*)malloc(sizeof(double) * pos->numsprite)))
		ft_free_all(pos, "malloc spriteorder");
	pos->possprite = pos_sprite(pos);
	if (!(pos->zbuffer = (double*)malloc(sizeof(double) * pos->size_x)))
		ft_free_all(pos, "zbuffer malloc");
}

void	sprite_draw(t_pos *pos)
{
	int y;
	int d;
	int color;

	while (pos->stripe < pos->dex)
	{
		pos->tex_x = (int)(256 * (pos->stripe - (-pos->spritewidth / 2 +
				pos->ssx)) * pos->txt->width[4] / pos->spritewidth) / 256;
		if (pos->transy > 0 && pos->stripe > 0 && pos->stripe < pos->size_x
				&& pos->transy < pos->zbuffer[pos->stripe])
		{
			y = pos->dsy - 1;
			while (++y < pos->dey)
			{
				d = (y) * 256 - pos->size_y * 128 + pos->spriteheight * 128;
				pos->tex_y = ((d * pos->txt->height[4]) /
										pos->spriteheight) / 256;
				color = pos->txt->txt[4][pos->txt->width[4] *
										pos->tex_y + pos->tex_x];
				if ((color & 0x00FFFFFF) != 0)
					pos->img_data[(pos->size_x * y) + pos->stripe] = color;
			}
		}
		pos->stripe++;
	}
}

void	sprite_value(t_pos *pos, int i)
{
	pos->spritex = pos->possprite[pos->spriteorder[i]][0] - pos->posx;
	pos->spritey = pos->possprite[pos->spriteorder[i]][1] - pos->posy;
	pos->intDet = 1.0 / (pos->planex * pos->diry - pos->dirx * pos->planey);
	pos->transx = pos->intDet * (pos->diry * pos->spritex -
			pos->dirx * pos->spritey);
	pos->transy = pos->intDet * (-pos->planey * pos->spritex +
			pos->planex * pos->spritey);
	pos->ssx = (int)((pos->size_x / 2) * (1 + pos->transx / pos->transy));
	pos->spriteheight = abs((int)(pos->size_y / pos->transy));
	pos->dsy = -pos->spriteheight / 2 + pos->size_y / 2;
	pos->dsy = (pos->dsy < 0) ? 0 : pos->dsy;
	pos->dey = pos->spriteheight / 2 + pos->size_y / 2;
	pos->dey = (pos->dey >= pos->size_y) ? pos->size_y - 1 : pos->dey;
	pos->spritewidth = abs((int)(pos->size_y / pos->transy));
	pos->dsx = -pos->spritewidth / 2 + pos->ssx;
	pos->dsx = (pos->dsx < 0) ? 0 : pos->dsx;
	pos->dex = pos->spritewidth / 2 + pos->ssx;
	pos->dex = (pos->dex >= pos->size_x) ? pos->size_x - 1 : pos->dex;
	pos->stripe = pos->dsx;
}

void	sprite_ordist(t_pos *pos)
{
	int i;

	i = 0;
	while (i < pos->numsprite)
	{
		pos->spriteorder[i] = i;
		pos->spritedist[i] = ((pos->posx - pos->possprite[i][0]) *
			(pos->posx * pos->possprite[i][0]) + (pos->posy -
				pos->possprite[i][1]) * (pos->posy - pos->possprite[i][1]));
		i++;
	}
	if (pos->numsprite > 1)
		sort_sprite(pos);
}

void	init_sprite(t_pos *pos)
{
	int i;

	sprite_ordist(pos);
	i = 0;
	while (i < pos->numsprite)
	{
		sprite_value(pos, i);
		sprite_draw(pos);
		i++;
	}
}
