/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracer_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efrancon <efrancon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 18:39:18 by efrancon          #+#    #+#             */
/*   Updated: 2022/03/25 14:03:21 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT_bonus.h"

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

t_vec3	compute_material(t_data *data, t_ray *hit, t_ray *ray)
{
	t_vec3	rgb;

	rgb = create_vec3(0, 0, 0);
	if (BONUS)
		handle_texture(hit);
	rgb = mul_vec3(get_light(data, *hit, *ray), hit->color);
	return (rgb);
}

void	detect_intersection(
	t_ray ray, unsigned long *color, t_data *data, t_thread *thread)
{
	_Bool	hit_obj;
	t_ray	hit;
	t_vec3	rgb;
	int		i;

	i = 0;
	init_var_hit(&hit_obj, &hit, &rgb);
	update_camera_ray(&ray, data, thread);
	while (i < data->obj_nb)
	{
		if (check_hit_object(&ray, &data->obj[i], &hit))
		{
			hit_obj = TRUE;
			data->obj_ref = i;
		}
		i++;
	}
	if (hit_obj)
		rgb = compute_material(data, &hit, &ray);
	*color = create_rgb_struct(&rgb);
}

void	run_raytracing(
	t_mlx *mlx, t_data *data, t_thread *thread)
{
	unsigned long	pixel_color;
	t_ray			cam_ray;
	int				ratio;

	(void)mlx;
	ratio = HEIGHT;
	if (THREADS > 1)
		ratio /= THREADS;
	init_camera_ray(&cam_ray, data);
	while (thread->pixel_y < thread->max_height)
	{
		thread->pixel_x = -1;
		while (++thread->pixel_x < WIDTH)
		{
			pixel_color = 0;
			if (data->path_tracing)
				run_path_tracing(&cam_ray, &pixel_color, data, thread);
			else
				detect_intersection(cam_ray, &pixel_color, data, thread);
			draw_pixel(mlx->image, pixel_color, thread);
		}
		display_loading(data, thread, ratio);
		thread->pixel_y++;
	}
	display_end_loading(data, thread);
}

void	run_minirt(t_data *data)
{
	t_mlx		*mlx;
	t_thread	main_thread;

	mlx = data->mlx;
	init_image(mlx, data);
	main_thread.pixel_y = 0;
	main_thread.max_height = HEIGHT;
	data->start_time = get_time();
	if (get_norm_vec3(*data->scene->camera->dir) && data->scene->camera->fov)
	{
		data->cam_to_world_matrix = built_cam_to_world_matrix(
				data->scene->camera);
		{
			if (data->multithreading && THREADS > 0)
				run_multithreading(data);
			else
				run_raytracing(mlx, data, &main_thread);
		}
	}
	display_cam_param(data->scene->camera, data);
	mlx_put_image_to_window(mlx->ptr, mlx->window, mlx->image->img_ptr, 0, 0);
}
