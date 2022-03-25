/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   square_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efrancon <efrancon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 18:38:19 by efrancon          #+#    #+#             */
/*   Updated: 2022/03/25 11:27:56 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT_bonus.h"

_Bool	hit_square(t_ray *ray, t_obj *obj, t_ray *hit)
{
	t_vec3	x;
	t_vec3	y;
	t_vec3	origin_to_hit;
	double	dist_max;

	if (!hit_plane(ray, obj, hit))
		return (FALSE);
	if (obj->dir->coord[Y] == 1 || obj->dir->coord[Y] == -1)
		x = cross_vec3(create_vec3(1, 0, 0), *obj->dir);
	else
		x = cross_vec3(create_vec3(0, 1, 0), *obj->dir);
	normalize_vec3(&x);
	y = cross_vec3(x, *obj->dir);
	normalize_vec3(&y);
	dist_max = obj->height * 0.5;
	origin_to_hit = sub_vec3(hit->origin, *obj->origin);
	if (fabs(dot_vec3(origin_to_hit, x)) < dist_max
		&& fabs(dot_vec3(origin_to_hit, y)) < dist_max)
		return (TRUE);
	return (FALSE);
}
