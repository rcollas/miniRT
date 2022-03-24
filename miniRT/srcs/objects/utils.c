/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efrancon <efrancon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 11:03:23 by efrancon          #+#    #+#             */
/*   Updated: 2022/03/24 11:03:24 by efrancon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	check_direction_normal(t_ray *ray, t_ray *hit)
{
	if (dot_vec3(hit->dir, ray->dir) > 0)
		hit->dir = mul_vec3_and_const(hit->dir, -1);
}

t_vec3	get_hit_point(t_ray ray)
{
	t_vec3	hit_point;

	hit_point = add_vec3(ray.origin, mul_vec3_and_const(ray.dir, ray.dist));
	return (hit_point);
}

void	copy_ray(t_ray *dest, t_ray src)
{
	copy_vec3(&dest->dir, src.dir);
	copy_vec3(&dest->origin, src.origin);
	copy_vec3(&dest->color, src.color);
	dest->dist = src.dist;
	dest->shadowing = src.shadowing;
	dest->obj = src.obj;
}
