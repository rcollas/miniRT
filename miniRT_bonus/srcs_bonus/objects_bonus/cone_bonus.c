/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efrancon <efrancon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 18:37:44 by efrancon          #+#    #+#             */
/*   Updated: 2022/03/25 14:03:21 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT_bonus.h"

_Bool	hit_cone_caps(t_ray *ray, t_obj *obj, t_ray *hit)
{
	t_obj	cone_caps;
	t_ray	hit_caps;
	t_ray	ray_caps;

	cone_caps = *obj;
	copy_ray(&hit_caps, *hit);
	copy_ray(&ray_caps, *ray);
	cone_caps.origin->coord[X] = obj->origin->coord[X]
		+ obj->dir->coord[X] * obj->height;
	cone_caps.origin->coord[Y] = obj->origin->coord[Y]
		+ obj->dir->coord[Y] * obj->height;
	cone_caps.origin->coord[Z] = obj->origin->coord[Z]
		+ obj->dir->coord[Z] * obj->height;
	if (hit_disk(&ray_caps, &cone_caps, &hit_caps) && ray_caps.dist > 0.01
		&& ray_caps.dist < ray->dist)
	{
		copy_ray(ray, ray_caps);
		copy_ray(hit, hit_caps);
		return (TRUE);
	}
	return (FALSE);
}

_Bool	solve_quadratic_cone(
	double *coeff, double *closest_hit, t_ray *ray, t_obj *obj)
{
	double	delta;
	double	roots[2];

	delta = coeff[B] * coeff[B] - (4 * coeff[A] * coeff[C]);
	if (delta < 0)
		return (FALSE);
	roots[0] = (-coeff[B] - (sqrt(delta))) / (2 * coeff[A]);
	roots[1] = (-coeff[B] + (sqrt(delta))) / (2 * coeff[A]);
	if (roots[0] > 0 && check_cone_height(ray, obj, roots[0]))
		*closest_hit = roots[0];
	else if (roots[1] > 0 && check_cone_height(ray, obj, roots[1]))
		*closest_hit = roots[1];
	else
		return (FALSE);
	return (TRUE);
}

static void	compute_coeff_quation(double *coeff, t_ray *ray, t_obj *obj)
{
	t_vec3	ray_to_obj;
	double	angle;
	double	dot_product[2];

	angle = (obj->radius * obj->radius) / (obj->height * obj->height);
	ray_to_obj = sub_vec3(ray->origin, *obj->origin);
	dot_product[0] = dot_vec3(ray->dir, *obj->dir);
	dot_product[1] = dot_vec3(ray_to_obj, *obj->dir);
	coeff[A] = dot_vec3(ray->dir, ray->dir) - angle * dot_product[0]
		* dot_product[0] - dot_product[0] * dot_product[0];
	coeff[B] = 2 * (dot_vec3(ray->dir, ray_to_obj) - angle * dot_product[0]
			* dot_product[1] - dot_product[0] * dot_product[1]);
	coeff[C] = dot_vec3(ray_to_obj, ray_to_obj) - angle * dot_product[1]
		* dot_product[1] - dot_product[1] * dot_product[1];
}

_Bool	hit_cone(t_ray *ray, t_obj *obj, t_ray *hit)
{
	double	coeff[3];

	normalize_vec3(obj->dir);
	normalize_vec3(&ray->dir);
	compute_coeff_quation(coeff, ray, obj);
	if (solve_quadratic_cone(coeff, &ray->dist, ray, obj) && ray->dist > 0.01)
	{
		if (hit_cone_caps(ray, obj, hit))
			return (TRUE);
		hit->origin = get_hit_point(*ray);
		hit->dist = ray->dist;
		compute_normal_cone(ray, obj, hit);
		return (TRUE);
	}
	if (hit_cone_caps(ray, obj, hit))
		return (TRUE);
	return (FALSE);
}
