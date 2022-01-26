#include "miniRT.h"

void	draw_pixel(t_image *image, int x, int y, int color)
{
	char			*dest;

	dest = image->addr + (y * image->line_len + x * image->bpp / 8);
	*(unsigned int *)dest = color;
}

int	create_trgb(int transparency, int red, int green, int blue)
{
	return (transparency << 24 | red << 16 | green << 8 | blue);
}

void	clamp_color(int *color)
{
	if (*color > 255)
		*color = 255;
	if (*color < 0)
		*color = 0;
}

void	check_limit_color(t_rgb *color)
{
	clamp_color(&color->r);
	clamp_color(&color->g);
	clamp_color(&color->b);
}
