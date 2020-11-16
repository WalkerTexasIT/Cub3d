#include "libft.h"

void		ft_bzero(void *src, size_t n)
{
	char *char_src;

	if (src == 0)
		return ;
	char_src = (char *)src;
	while (n != 0)
	{
		*char_src = 0;
		char_src++;
		n--;
	}
}
