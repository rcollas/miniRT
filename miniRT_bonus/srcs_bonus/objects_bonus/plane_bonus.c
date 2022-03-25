/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efrancon <efrancon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 18:38:07 by efrancon          #+#    #+#             */
/*   Updated: 2022/03/25 11:27:56 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT_bonus.h"

_Bool	hit_plane(t_ray *ray, t_obj *obj, t_ray *hit)
{
	double	denominator;
	t_vec3	tmp;

	hit->dir = get_normalized_vec3(*obj->dir);
	normalize_vec3(&ray->dir);
	check_direction_normal(ray, obj, hit);
	denominator = dot_vec3(hit->dir, ray->dir);
	if (fabs(denominator) > 1e-6)
	{
		tmp = sub_vec3(*obj->origin, ray->origin);
		hit->dist = dot_vec3(tmp, hit->dir);
		hit->dist /= denominator;
		if (hit->dist > 0.001)
		{
			ray->dist = hit->dist;
			hit->origin = get_hit_point(*ray);
			return (TRUE);
		}
	}
	return (FALSE);
}
