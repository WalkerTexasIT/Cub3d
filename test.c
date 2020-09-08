#include <stdio.h>
#include <stdlib.h>

int			ft_strlen(const char *src)
{
	int n;

	n = 0;
	if (src == 0)
		return (0);
	while (src[n] != '\0')
		n++;
	return (n);
}

char		*ft_strnum(char *string, int n)
{
	char	*dest;
	int		len;
	int		i;

	len = ft_strlen(string);
	if (!(dest = (char*)malloc(sizeof(char) * (len - n + 1))))
		return (0);
	i = 0;
	while (string[n] != '\0')
		dest[i++] = string[n++];
	dest[i] = '\0';
	return (dest);
}

int		main(void)
{
	printf("%s\n", ft_strnum("NO ./path_of_north", 3));
	return (0);
}