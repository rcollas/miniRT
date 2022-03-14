#include "miniRT.h"

_Bool	check_hit_object(
	t_ray *ray, t_obj *obj, t_ray *hit_min, t_camera *camera)
{
	t_ray	hit;

	copy_vec3(&hit.cam_dir, *camera->dir);
	if (obj->hit_object(ray, obj, &hit))
	{
		if (hit_min->dist > hit.dist)
		{
			hit_min->dist = hit.dist;
			copy_vec3(&hit_min->origin, hit.origin);
			copy_vec3(&hit_min->dir, hit.dir);
			copy_vec3(&hit_min->color, *obj->color);
			hit_min->obj = obj;
		}
		return (TRUE);
	}
	return (FALSE);
}

void	init_var_hit(_Bool *hit_obj, t_ray *hit, t_vec3 *color)
{
	if (hit_obj)
		*hit_obj = FALSE;
	if (hit)
	{
		hit->dist = 1E99;
		hit->shadowing = NO_SHADOW;
		hit->obj_ref = -1;
	}
	if (color)
		*color = create_vec3(0, 0, 0);
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
		if (check_hit_object(&ray, &data->obj[i], &hit, data->scene->camera))
		{
			hit_obj = TRUE;
			data->obj_ref = i;
		}
		i++;
	}
	if (hit_obj)
	{
		if (BONUS)
			handle_texture(&hit);
		rgb = mul_vec3(get_light(data, hit, ray), hit.color);
	}
	*color = create_rgb_struct(&rgb);
}

void	run_raytracing(
	t_mlx *mlx, t_data *data, t_thread *thread)
{
	unsigned long	pixel_color;
	t_ray			cam_ray;
	int				ratio;

	ratio = HEIGHT / THREADS;
	init_camera_ray(&cam_ray, data);
	while (thread->pixel_y < thread->max_height)
	{
		thread->pixel_x = -1;
		while (++thread->pixel_x < WIDTH)
		{
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
	data->cam_to_world_matrix = built_cam_to_world_matrix(data->scene->camera);
	data->start_time = get_time();
	if (data->multithreading)
		run_multithreading(data);
	else
	{
		main_thread.pixel_y = 0;
		main_thread.max_height = HEIGHT;
		run_raytracing(mlx, data, &main_thread);
	}
	display_cam_param(data->scene->camera, data);
	mlx_put_image_to_window(mlx->ptr, mlx->window, mlx->image->img_ptr, 0, 0);
}
