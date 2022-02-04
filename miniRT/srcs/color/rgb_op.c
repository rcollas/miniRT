#include "miniRT.h"

t_vec3 init_color(double red, double green, double blue)
{
	t_rgb	new_color;

	new_color.r = red;
	new_color.g = green;
	new_color.b = blue;
	return (new_color);
}

void	copy_rgb(t_vec3 *dest, t_vec3 src)
{
	dest->r = src.r;
	dest->g = src.g;
	dest->b = src.b;
}

t_vec3 add_rgb(t_vec3 color_1, t_vec3 color_2)
{
	t_rgb	new_color;

	new_color.r = color_1.r + color_2.r;
	new_color.g = color_1.g + color_2.g;
	new_color.b = color_1.b + color_2.b;
	check_limit_color(&new_color);
	return (new_color);
}

t_vec3 mul_rgb(t_vec3 color_1, t_vec3 color_2)
{
	t_rgb	new_color;

	new_color.r = color_1.r * color_2.r;
	new_color.g = color_1.g * color_2.g;
	new_color.b = color_1.b * color_2.b;
	check_limit_color(&new_color);
	return (new_color);
}

t_vec3 mul_rgb_and_const(t_vec3 color, double k)
{
	t_rgb	new_color;

	new_color.r = color.r * k;
	new_color.g = color.g * k;
	new_color.b = color.b * k;
	check_limit_color(&new_color);
	return (new_color);
}
