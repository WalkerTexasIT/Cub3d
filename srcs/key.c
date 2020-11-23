#include "../inc/cub3d.h"

int		initkeysecond(t_pos *pos)
{
	if (pos->key->key_a == 1)
	{
		if (pos->map[(int)pos->posy][(int)(pos->posx + pos->diry *
					MoveSpeed + (pos->diry < 0 ? -0.2 : 0.2))] != '1')
			pos->posx += pos->diry * MoveSpeed;
		if (pos->map[(int)(pos->posy + pos->diry * MoveSpeed +
			(-pos->dirx < 0 ? -0.2 : 0.2))][(int)pos->posx] != '1')
			pos->posy += -pos->dirx * MoveSpeed;
		pos->key->key_a = 0;
	}
	if (pos->key->key_right == 1)
		rot(pos, 'R');
	if (pos->key->key_left == 1)
		rot(pos, 'L');
	if (pos->win_ptr)
		mlx_clear_window(pos->mlx_ptr, pos->win_ptr);
	dda_while(pos);
	return (0);
}

void	initkeysec(t_pos *pos)
{
	if (pos->key->key_s == 1)
	{
		if (pos->map[(int)pos->posy][(int)(pos->posx - pos->dirx *
				MoveSpeed + (-pos->dirx < 0 ? -0.2 : 0.2))] != '1')
			pos->posx -= pos->dirx * MoveSpeed;
		if (pos->map[(int)(pos->posy - pos->diry * MoveSpeed +
			(-pos->diry < 0 ? -0.2 : 0.2))][(int)pos->posx] != '1')
			pos->posy -= pos->diry * MoveSpeed;
		pos->key->key_s = 0;
	}
}

int		initkey(t_pos *pos)
{
	if (pos->key->key_w == 1)
	{
		if (pos->map[(int)pos->posy][(int)(pos->posx + pos->dirx *
					MoveSpeed + (pos->dirx < 0 ? -0.2 : 0.2))] != '1')
			pos->posx += pos->dirx * MoveSpeed;
		if (pos->map[(int)(pos->posy + pos->diry * MoveSpeed +
			(pos->diry < 0 ? -0.2 : 0.2))][(int)pos->posx] != '1')
			pos->posy += pos->diry * MoveSpeed;
		pos->key->key_w = 0;
	}
	if (pos->key->key_d == 1)
	{
		if (pos->map[(int)pos->posy][(int)(pos->posx - pos->diry *
				MoveSpeed + (-pos->diry < 0 ? -0.2 : 0.2))] != '1')
			pos->posx += -pos->diry * MoveSpeed;
		if (pos->map[(int)(pos->posy + pos->dirx * MoveSpeed +
			(pos->dirx < 0 ? -0.2 : 0.2))][(int)pos->posx] != '1')
			pos->posy += pos->dirx * MoveSpeed;
		pos->key->key_d = 0;
	}
	initkeysec(pos);
	return (initkeysecond(pos));
}

void	keyinit(t_pos *pos)
{
	t_key	key;

	pos->key = &key;
	pos->key->key_w = 0;
	pos->key->key_s = 0;
	pos->key->key_a = 0;
	pos->key->key_d = 0;
	pos->key->key_left = 0;
	pos->key->key_right = 0;
}

int		key(int key, void *structure)
{
	t_pos	*pos;

	pos = (t_pos*)structure;
	if (key == 13)
		pos->key->key_w = 1;
	if (key == 1)
		pos->key->key_s = 1;
	if (key == 2)
		pos->key->key_d = 1;
	if (key == 0)
		pos->key->key_a = 1;
	if (key == 124)
		pos->key->key_right = 1;
	if (key == 123)
		pos->key->key_left = 1;
	if (key == 53)
		ft_free_all(pos, "");
	if (key == 17)
		ft_free_all(pos, "");
	return (0);
}
