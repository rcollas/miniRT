/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efrancon <efrancon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 18:43:14 by efrancon          #+#    #+#             */
/*   Updated: 2022/03/25 14:03:21 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT_bonus.h"

int	is_in_range(double min, double max, double value)
{
	return (value >= min && value <= max);
}

int	is_valid_rgb(t_vec3 *rgb)
{
	if (!rgb)
		return (FALSE);
	if (!is_in_range((double)0, (double)255, (double)rgb->coord[R]))
		return (FALSE);
	if (!is_in_range((double)0, (double)255, (double)rgb->coord[G]))
		return (FALSE);
	if (!is_in_range((double)0, (double)255, (double)rgb->coord[B]))
		return (FALSE);
	rgb->coord[R] /= 255.0;
	rgb->coord[G] /= 255.0;
	rgb->coord[B] /= 255.0;
	return (TRUE);
}

int	is_valid_vertex(t_vec3 *vertex)
{
	if (!vertex)
		return (FALSE);
	if (!is_in_range((double) -1, (double)1, (double)vertex->coord[X]))
		return (FALSE);
	if (!is_in_range((double) -1, (double)1, (double)vertex->coord[Y]))
		return (FALSE);
	if (!is_in_range((double) -1, (double)1, (double)vertex->coord[Z]))
		return (FALSE);
	return (TRUE);
}

int	check(void *obj, int type)
{
	if (type == AMBIENT_LIGHT)
		return (ambient_light_check((t_ambient_light *)obj));
	if (type == CAMERA)
		return (camera_check((t_camera *)obj));
	if (type == DIFFUSE_LIGHT)
		return (diffuse_light_check((t_diffuse_light *)obj));
	if (type == SPHERE || type == SKY)
		return (sphere_check((t_obj *)obj));
	if (type == PLANE)
		return (plane_check((t_obj *)obj));
	if (type == CYLINDER || type == CONE)
		return (cylinder_check((t_obj *)obj));
	if (type == DISK)
		return (disk_check((t_obj *)obj));
	if (type == SQUARE)
		return (square_check((t_obj *)obj));
	return (FAIL);
}
