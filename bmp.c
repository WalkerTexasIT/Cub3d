#include "cub3d.h"

static void	set_value(unsigned char *string, int i)
{
	string[0] = (unsigned char)(i);
	string[1] = (unsigned char)(i >> 8);
	string[2] = (unsigned char)(i >> 16);
	string[3] = (unsigned char)(i >> 24);
}

static int	bmp_header(t_pos *pos, int fd, int size)
{
	int				i;
	unsigned char	bmpheader[54];

	i = 0;
	while (i < 54)
		bmpheader[i++] = 0;
	bmpheader[0] = (unsigned char)('B');
	bmpheader[1] = (unsigned char)('M');
	set_value(bmpheader + 2, size);
	bmpheader[10] = (unsigned char)(54);
	bmpheader[14] = (unsigned char)(40);
	set_value(bmpheader + 18, pos->size_x);
	set_value(bmpheader + 22, pos->size_y);
	bmpheader[27] = (unsigned char)(1);
	bmpheader[28] = (unsigned char)(24);
	return (!(write(fd, bmpheader, 54) < 0));
}

static int	rgb_data(t_pos *pos, int x, int y)
{
	int		rgb;
	int		color;

	color = *(int*)(pos->charimg_data
			+ (4 * pos->size_x * (pos->size_y - 1 - y))
			+ (4 * x));
	rgb = (color & 0xFF0000) | (color & 0x00FF00) | (color & 0x0000FF);
	return (rgb);
}


static int	bmp_data(t_pos *pos, int fd, int n)
{
	const unsigned char		mall[3] = {0, 0, 0};
	int						i;
	int						j;
	int						rgb;

	i = -1;
	while (++i < pos->size_y)
	{
		j = -1;
		while (++j < pos->size_x)
		{
			rgb = rgb_data(pos, j, i);
			if ((write(fd, &rgb, 3) < 0))
				return (0);
			if (n > 0 && write(fd, &mall, n) < 0)
				return (0);
		}
	}
	return (1);
}

void		make_bmp(t_pos *pos)
{
	int		fd;
	int		size;
	int		i;

	i = (4 - (pos->size_x * 3) % 4) % 4;
	size = 54 + (3 * ((int)pos->size_x + i) * (int)pos->size_y);
	if ((fd = open("screenshot.bmp", O_WRONLY | O_CREAT
		| O_TRUNC | O_APPEND, 0666)) < 0)
		return (ft_free_all(pos, "fail open bmp fd"));
	if (!bmp_header(pos, fd, size))
		return (ft_free_all(pos, "fail bmp header"));
	if (!bmp_data(pos, fd, i))
		return (ft_free_all(pos, "fail bmp data write"));
	close(fd);
	ft_free_all(pos, "bmp finish");
}