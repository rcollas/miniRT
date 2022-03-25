/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efrancon <efrancon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 11:07:01 by efrancon          #+#    #+#             */
/*   Updated: 2022/03/25 11:27:56 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

_Bool	check_hit_object(
	t_ray *ray, t_obj *obj, t_ray *hit_min)
{
	t_ray	hit;

	init_hit(&hit);
	if (obj->hit_object(ray, obj, &hit))
	{
		if (hit_min->dist > hit.dist)
		{
			hit_min->dist = hit.dist;
			copy_vec3(&hit_min->origin, hit.origin);
			copy_vec3(&hit_min->dir, hit.dir);
			copy_vec3(&hit_min->color, *obj->color);
			hit_min->obj = obj;
			hit_min->inside_object = hit.inside_object;
		}
		return (TRUE);
	}
	return (FALSE);
}

void	detect_intersection(
	t_ray ray, unsigned long *color, t_data *data)
{
	_Bool	hit_obj;
	t_ray	hit;
	t_vec3	rgb;
	int		i;

	i = 0;
	init_var_hit(&hit_obj, &hit, &rgb);
	update_camera_ray(&ray, data);
	while (i < data->obj_nb)
	{
		if (check_hit_object(&ray, &data->obj[i], &hit))
			hit_obj = TRUE;
		i++;
	}
	if (hit_obj)
		rgb = mul_vec3(get_light(data, hit), hit.color);
	*color = create_rgb_struct(&rgb);
}

void	run_raytracing(
	t_mlx *mlx, t_data *data)
{
	unsigned long	pixel_color;
	t_ray			cam_ray;

	init_camera_ray(&cam_ray, data);
	while (++data->pixel_y < HEIGHT)
	{
		data->pixel_x = -1;
		while (++data->pixel_x < WIDTH)
		{
			detect_intersection(cam_ray, &pixel_color, data);
			draw_pixel(mlx->image, pixel_color, data);
		}
	}
}

void	run_minirt(t_data *data)
{
	t_mlx		*mlx;

	mlx = data->mlx;
	init_image(mlx, data);
	data->pixel_y = -1;
	if (get_norm_vec3(*data->scene->camera->dir) && data->scene->camera->fov)
	{
		data->cam_to_world_matrix = built_cam_to_world_matrix(
				data->scene->camera);
		run_raytracing(mlx, data);
	}
	display_cam_param(data->scene->camera);
	mlx_put_image_to_window(mlx->ptr, mlx->window, mlx->image->img_ptr, 0, 0);
}
