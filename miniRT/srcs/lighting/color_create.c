/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_create.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efrancon <efrancon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 10:59:57 by efrancon          #+#    #+#             */
/*   Updated: 2022/03/24 10:59:58 by efrancon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	draw_pixel(
	t_image *image, unsigned long color, t_data *data)
{
	char	*dest;
	int		y;
	int		x;

	y = data->pixel_y;
	x = data->pixel_x;
	dest = image->addr + (y * image->line_len + x * image->bpp / 8);
	*(unsigned int *)dest = color;
}

unsigned long	create_trgb_struct(int transparency, t_vec3 *color)
{
	clamp_intensity(&color->coord[R]);
	clamp_intensity(&color->coord[G]);
	clamp_intensity(&color->coord[B]);
	color->coord[R] *= 255;
	color->coord[G] *= 255;
	color->coord[B] *= 255;
	return (transparency << 24 | (int)color->coord[R] << 16
		| (int)color->coord[G] << 8 | (int)color->coord[B]);
}

unsigned long	create_trgb(int transparency, int red, int green, int blue)
{
	clamp_color(&red);
	clamp_color(&green);
	clamp_color(&blue);
	return (transparency << 24 | red << 16 | green << 8 | blue);
}

unsigned long	create_rgb_struct(t_vec3 *color)
{
	clamp_intensity(&color->coord[R]);
	clamp_intensity(&color->coord[G]);
	clamp_intensity(&color->coord[B]);
	color->coord[R] *= 255;
	color->coord[G] *= 255;
	color->coord[B] *= 255;
	return ((int)color->coord[R] << 16
		| (int)color->coord[G] << 8
		| (int)color->coord[B]);
}

unsigned long	create_rgb(int red, int green, int blue)
{
	clamp_color(&red);
	clamp_color(&green);
	clamp_color(&blue);
	return (red << 16 | green << 8 | blue);
}
