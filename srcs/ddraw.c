#include "../inc/cub3d.h"

void	dda_drawsecond(t_pos *pos, int i, int n)
{
	while (i < pos->drawend)
	{
		if (pos->side == 0 && pos->raydirx < 0)
			pos->img_data[n] = texturing(pos, 3);
		else if (pos->side == 0 && pos->raydirx > 0)
			pos->img_data[n] = texturing(pos, 2);
		else if (pos->side == 1 && pos->raydiry < 0)
			pos->img_data[n] = texturing(pos, 0);
		else if (pos->side == 1 && pos->raydiry > 0)
			pos->img_data[n] = texturing(pos, 1);
		n += pos->size_x;
		i++;
	}
	while (i < pos->size_y)
	{
		pos->img_data[n] = pos->color_f;
		n += pos->size_x;
		i++;
	}
	pos->zbuffer[pos->x] = pos->perpwalldist;
}

void	dda_draw(t_pos *pos)
{
	int i;
	int n;

	i = 0;
	n = pos->x;
	pos->texpos = (pos->drawstart - pos->size_y
			/ 2 + pos->lineheight / 2) * pos->step;
	while (i < pos->drawstart)
	{
		pos->img_data[n] = pos->color_c;
		n += pos->size_x;
		i++;
	}
	dda_drawsecond(pos, i, n);
}
