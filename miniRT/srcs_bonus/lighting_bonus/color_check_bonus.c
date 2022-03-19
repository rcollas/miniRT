#include "miniRT_bonus.h"

void	clamp_intensity(double *intensity)
{
	if (*intensity > 1)
		*intensity = 1;
	if (*intensity < 0)
		*intensity = 0;
}

void	clamp_color(int *color)
{
	if (*color > 255)
		*color = 255;
	if (*color < 0)
		*color = 0;
}

void	check_limit_color(t_vec3 *color)
{
	clamp_intensity(&color->coord[R]);
	clamp_intensity(&color->coord[G]);
	clamp_intensity(&color->coord[B]);
}