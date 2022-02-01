#include "miniRT.h"

void	draw_pixel(t_image *image, int color, t_data *data)
{
	char	*dest;
	int		y;
	int		x;

	y = data->pixel_y;
	x = data->pixel_x;
	// y = HEIGHT - data->pixel_y - 1;
	// x = WIDTH - data->pixel_x - 1;
	// printf("y = %d | x = %d\n", x, y);
	dest = image->addr + (y * image->line_len + x * image->bpp / 8);
	*(unsigned int *)dest = color;
}

int	create_trgb_struct(int transparency, t_rgb *color)
{
	clamp_intensity(&color->r);
	clamp_intensity(&color->g);
	clamp_intensity(&color->b);
	color->r *= 255;
	color->g *= 255;
	color->b *= 255;
	return (transparency << 24 | (int)color->r << 16 | (int)color->g << 8 | (int)color->b);
}

int	create_trgb(int transparency, int red, int green, int blue)
{
	clamp_color(&red);
	clamp_color(&green);
	clamp_color(&blue);
	return (transparency << 24 | red << 16 | green << 8 | blue);
}
