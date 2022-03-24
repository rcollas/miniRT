/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efrancon <efrancon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 18:38:13 by efrancon          #+#    #+#             */
/*   Updated: 2022/03/24 18:38:14 by efrancon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT_bonus.h"

void	check_dir_normal_sphere(t_ray *ray, t_obj *obj, t_ray *hit)
{
	if (obj->type == SKY)
		check_direction_normal(ray, obj, hit);
	else if (dot_vec3(hit->dir, ray->dir) > 0.001)
	{
		hit->dir = mul_vec3_and_const(hit->dir, -1);
		hit->inside_object = TRUE;
	}
}

_Bool	hit_sphere(t_ray *ray, t_obj *obj, t_ray *hit)
{
	double	coeff[3];
	double	radius;
	double	roots[2];

	radius = obj->diameter * 0.5;
	coeff[A] = dot_vec3(ray->dir, ray->dir);
	coeff[B] = 2 * dot_vec3(ray->dir, sub_vec3(ray->origin, *obj->origin));
	coeff[C] = get_norm2_vec3(
			sub_vec3(ray->origin, *obj->origin)) - radius * radius;
	if (solve_quadratic_equation(coeff, roots, &ray->dist))
	{
		hit->origin = get_hit_point(*ray);
		hit->dist = ray->dist;
		hit->dir = get_normalized_vec3(sub_vec3(hit->origin, *obj->origin));
		check_dir_normal_sphere(ray, obj, hit);
		return (TRUE);
	}
	return (FALSE);
}
