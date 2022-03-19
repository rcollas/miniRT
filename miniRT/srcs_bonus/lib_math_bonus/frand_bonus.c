#include "miniRT_bonus.h"

unsigned int	ft_rand(void)
{
	int				fd;
	unsigned int	buff;
	unsigned int	*bit;

	fd = open("/dev/urandom", O_RDONLY);
	read(fd, &buff, sizeof(unsigned));
	bit = &buff;
	close(fd);
	return (*bit);
}

float	frand(void)
{
	float	float_rand;

	float_rand = (float)rand();
	while (float_rand > 1)
		float_rand /= 10;
	return (float_rand);
}
