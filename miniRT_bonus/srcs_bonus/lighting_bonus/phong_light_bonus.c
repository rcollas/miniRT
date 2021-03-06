/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phong_light_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efrancon <efrancon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 18:35:04 by efrancon          #+#    #+#             */
/*   Updated: 2022/03/25 14:03:21 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT_bonus.h"

t_vec3	get_diffuse_light(t_scene *scene, t_ray hit, t_vec3	light_dir)
{
	double	cos_theta;
	double	intensity;
	t_vec3	diffuse_light;

	normalize_vec3(&hit.dir);
	cos_theta = fmax(0.0, dot_vec3(hit.dir, light_dir));
	intensity = scene->diffuse_light->intensity * cos_theta;
	intensity *= hit.shadowing;
	clamp_intensity(&intensity);
	diffuse_light = mul_vec3_and_const(
			*scene->diffuse_light[hit.i].color, intensity);
	return (diffuse_light);
}

t_vec3	get_specular_light(
	t_scene *scene, t_ray hit, t_ray ray, t_vec3 light_dir)
{
	t_vec3	specular_light;
	double	intensity;
	t_vec3	reflected_ray;
	t_vec3	view_ray;
	double	cos_theta;

	specular_light = create_vec3(0, 0, 0);
	view_ray = sub_vec3(ray.origin, hit.origin);
	normalize_vec3(&view_ray);
	reflected_ray = mul_vec3_and_const(hit.dir,
			2 * dot_vec3(hit.dir, light_dir));
	reflected_ray = sub_vec3(reflected_ray, light_dir);
	cos_theta = dot_vec3(reflected_ray, view_ray);
	if (cos_theta > 0)
	{
		intensity = hit.obj->shine_factor * scene->diffuse_light->intensity
			* pow(fmax(0.0, cos_theta), SPECULAR_COEFF);
		intensity *= hit.shadowing;
		clamp_intensity(&intensity);
		specular_light = mul_vec3_and_const(
				*scene->diffuse_light[hit.i].color, intensity);
	}
	return (specular_light);
}

t_vec3	sum_phong_lights(t_scene *scene, t_ray hit, t_ray ray, t_data *data)
{
	t_vec3	light_dir;
	t_vec3	total_light;
	t_vec3	phong_light[2];
	int		i;

	total_light = create_vec3(0, 0, 0);
	i = -1;
	while (++i < scene->light_nb)
	{
		hit.i = i;
		if (!hit.obj->inside_object)
			hit.shadowing = compute_shadow(
					data->obj, &hit, &scene->diffuse_light[i]);
		light_dir = sub_vec3(*scene->diffuse_light[i].coord, hit.origin);
		normalize_vec3(&light_dir);
		phong_light[DIFFUSE] = get_diffuse_light(scene, hit, light_dir);
		phong_light[SPECULAR] = get_specular_light(scene, hit, ray, light_dir);
		total_light = add_vec3(total_light, phong_light[DIFFUSE]);
		total_light = add_vec3(total_light, phong_light[SPECULAR]);
	}
	return (total_light);
}
