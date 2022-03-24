/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_tracing_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efrancon <efrancon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 18:39:10 by efrancon          #+#    #+#             */
/*   Updated: 2022/03/24 18:39:11 by efrancon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT_bonus.h"

t_vec3	get_random_ray_dir(t_ray result, t_vec3 *vec)
{
	t_vec3	tmp1;
	t_vec3	tmp2;
	t_vec3	random_ray_dir;

	tmp1 = mul_vec3_and_const(result.dir, vec[RANDOM_DIR_LOCAL].coord[Z]);
	tmp2 = add_vec3(
			mul_vec3_and_const(vec[TANGENT_1], vec[RANDOM_DIR_LOCAL].coord[X]),
			mul_vec3_and_const(vec[TANGENT_2], vec[RANDOM_DIR_LOCAL].coord[Y]));
	random_ray_dir = add_vec3(tmp1, tmp2);
	return (random_ray_dir);
}

void	get_random_ray(t_ray result, t_ray *random_ray)
{
	double	random_nb[2];
	t_vec3	vec[4];
	double	tmp;

	srand(ft_rand());
	random_nb[0] = frand() * 2 * M_PI;
	random_nb[1] = frand();
	tmp = sqrt(1 - random_nb[1]);
	vec[RANDOM_DIR_LOCAL].coord[X] = cos(random_nb[0]) * tmp;
	vec[RANDOM_DIR_LOCAL].coord[Y] = sin(random_nb[0]) * tmp;
	vec[RANDOM_DIR_LOCAL].coord[Z] = sqrt(random_nb[1]);
	vec[RANDOM].coord[X] = frand() - 0.5;
	vec[RANDOM].coord[Y] = frand() - 0.5;
	vec[RANDOM].coord[Z] = frand() - 0.5;
	vec[TANGENT_1] = cross_vec3(result.dir, vec[RANDOM]);
	normalize_vec3(&vec[TANGENT_1]);
	vec[TANGENT_2] = cross_vec3(vec[TANGENT_1], result.dir);
	random_ray->dir = get_random_ray_dir(result, vec);
	random_ray->origin = add_vec3(result.origin,
			mul_vec3_and_const(result.dir, 0.1));
	normalize_vec3(&random_ray->origin);
}

_Bool	check_all_objects(t_obj *obj, t_ray *ray, t_ray *hit_min)
{
	t_ray	hit;
	_Bool	hit_obj;
	int		i;

	init_var_hit(&hit_obj, hit_min, &hit_min->color);
	i = -1;
	while (++i < obj->obj_nb)
	{
		if (obj[i].hit_object(ray, &(obj[i]), &hit))
		{
			hit_obj = TRUE;
			if (hit_min->dist > hit.dist)
			{
				hit_min->dist = hit.dist;
				copy_vec3(&hit_min->origin, hit.origin);
				copy_vec3(&hit_min->dir, hit.dir);
				copy_vec3(&hit_min->color, *obj[i].color);
				hit_min->obj_ref = i;
			}
		}
	}
	return (hit_obj);
}

t_vec3	get_color_pixel(t_obj *obj, t_data *data, t_ray *ray, int rebound)
{
	_Bool	hit_obj;
	t_ray	hit;
	t_vec3	final_color;
	t_ray	random_ray[1];

	init_var_hit(&hit_obj, &hit, &final_color);
	hit_obj = check_all_objects(obj, ray, &hit);
	if (!rebound || (hit.shadowing == NO_SHADOW && rebound < REBOUND - 1))
		return (final_color);
	if (hit_obj)
	{
		get_random_ray(hit, random_ray);
		final_color = get_light(data, hit, *ray);
		final_color = add_vec3(final_color, mul_vec3_and_const(
					get_color_pixel(obj, data, random_ray, --rebound),
					PATH_TRACING_COEFF));
	}
	final_color = mul_vec3(final_color, hit.color);
	return (final_color);
}

void	run_path_tracing(
	t_ray *cam_ray, unsigned long *color, t_data *data, t_thread *thread)
{
	int		i;
	t_vec3	rgb;

	*color = 0;
	i = PASSES;
	data->lighting = CLASSIC_LIGHTING;
	update_camera_ray(cam_ray, data, thread);
	rgb = create_vec3(0, 0, 0);
	while (i--)
		rgb = add_vec3(rgb, get_color_pixel(data->obj, data, cam_ray, REBOUND));
	rgb = div_vec3_and_const(rgb, (double)PASSES);
	*color = create_rgb_struct(&rgb);
}
