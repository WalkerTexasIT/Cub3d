#include "../inc/cub3d.h"

void	set_path(t_pos *pos, char *line)
{
	if (line[0] == 'N' && line[1] == 'O')
		if (!(pos->linkn = ft_strnum(line, 3)))
			return (ft_free_all(pos, "erreur map"));
	if (line[0] == 'S' && line[1] == 'O')
		if (!(pos->links = ft_strnum(line, 3)))
			return (ft_free_all(pos, "erreur map"));
	if (line[0] == 'E' && line[1] == 'A')
		if (!(pos->linke = ft_strnum(line, 3)))
			return (ft_free_all(pos, "erreur map"));
	if (line[0] == 'W' && line[1] == 'E')
		if (!(pos->linkw = ft_strnum(line, 3)))
			return (ft_free_all(pos, "erreur map"));
	if (line[0] == 'S' && line[1] == ' ')
		if (!(pos->linksprite = ft_strnum(line, 2)))
			return (ft_free_all(pos, "erreur map"));
}

void	set_null_value(t_pos *pos)
{
	if (!(pos->txt = malloc(sizeof(t_txt))))
		return (ft_free_all(pos, "malloc t_txt"));
	pos->map = NULL;
	pos->txt->voidtxt = NULL;
	pos->txt->chartxt = NULL;
	pos->spriteorder = NULL;
	pos->linkn = NULL;
	pos->links = NULL;
	pos->linkw = NULL;
	pos->linke = NULL;
	pos->linksprite = NULL;
}

int		texturing(t_pos *pos, int texnum)
{
	int		color;

	pos->tex_y = (int)pos->texpos & (pos->txt->height[texnum] - 1);
	pos->texpos += pos->step;
	color = (int)pos->txt->txt[texnum][pos->txt->height[texnum]
		* pos->tex_y + pos->tex_x];
	return (color);
}

t_txt	*make_data_adress(t_txt *txt)
{
	int i;

	i = 0;
	if (!(txt->chartxt = (char**)malloc(sizeof(char*) * 5)))
		return (NULL);
	while (i < 5)
	{
		txt->chartxt[i] = mlx_get_data_addr(txt->voidtxt[i], &txt->bits[i],
			&txt->sl[i], &txt->end[i]);
		i++;
	}
	i = 0;
	if (!(txt->txt = (int**)malloc(sizeof(int*) * 5)))
		return (NULL);
	while (i < 5)
	{
		txt->txt[i] = (int*)txt->chartxt[i];
		i++;
	}
	return (txt);
}

void	init_tex(t_pos *pos)
{
	verif_xpm_file(pos);
	if (!(pos->txt->voidtxt = (void**)malloc(sizeof(void*) * 5)))
		return (ft_free_all(pos, "malloc void**"));
	if (!(pos->txt->voidtxt[0] = (void*)mlx_xpm_file_to_image(pos->mlx_ptr,
					pos->linkn, &pos->txt->width[0], &pos->txt->height[0])))
		return (ft_free_all(pos, "xpm to ... N"));
	if (!(pos->txt->voidtxt[1] = (void*)mlx_xpm_file_to_image(pos->mlx_ptr,
					pos->links, &pos->txt->width[1], &pos->txt->height[1])))
		return (ft_free_all(pos, "xpm to ... S"));
	if (!(pos->txt->voidtxt[2] = (void*)mlx_xpm_file_to_image(pos->mlx_ptr,
					pos->linke, &pos->txt->width[2], &pos->txt->height[2])))
		return (ft_free_all(pos, "xpm to ... E"));
	if (!(pos->txt->voidtxt[3] = (void*)mlx_xpm_file_to_image(pos->mlx_ptr,
					pos->linkw, &pos->txt->width[3], &pos->txt->height[3])))
		return (ft_free_all(pos, "xpm to ... W"));
	if (!(pos->txt->voidtxt[4] = (void*)mlx_xpm_file_to_image(pos->mlx_ptr,
				pos->linksprite, &pos->txt->width[4], &pos->txt->height[4])))
		return (ft_free_all(pos, "xpm to ... W"));
	if (make_data_adress(pos->txt) == NULL)
		return (ft_free_all(pos, "malloc in data adress"));
}
