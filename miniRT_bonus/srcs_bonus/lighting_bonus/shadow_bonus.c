/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shadow_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efrancon <efrancon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 18:35:09 by efrancon          #+#    #+#             */
/*   Updated: 2022/03/24 18:35:10 by efrancon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT_bonus.h"

_Bool	trace_shadow_ray(
	t_ray *shadow_ray, t_obj *obj, t_diffuse_light *light)
{
	t_ray	hit;
	double	light_dist;
	int		i;

	hit.dist = INFINITY;
	i = 0;
	light_dist = get_norm_vec3(sub_vec3(*light->coord, shadow_ray->origin));
	while (i < obj->obj_nb)
	{
		if (obj[i].hit_object(shadow_ray, &obj[i], &hit)
			&& hit.dist < light_dist)
			return (TRUE);
		i++;
	}
	return (FALSE);
}

double	compute_shadow(
	t_obj *obj, t_ray *hit, t_diffuse_light *light)
{
	_Bool	in_shadow;
	t_ray	shadow_ray;

	shadow_ray.origin = add_vec3(
			hit->origin, mul_vec3_and_const(hit->dir, 1e-4));
	shadow_ray.dir = sub_vec3(*light->coord, shadow_ray.origin);
	normalize_vec3(&shadow_ray.dir);
	in_shadow = trace_shadow_ray(&shadow_ray, obj, light);
	if (in_shadow)
		return (0);
	return (1);
}
