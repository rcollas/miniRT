#include "miniRT.h"

_Bool	check_hit_object(
	t_ray *ray, t_obj *obj, t_ray *hit_min)
{
	t_ray	hit;

	if (obj->hit_object(ray, obj, &hit))
	{
		if (hit_min->dist > hit.dist)
		{
			hit_min->dist = hit.dist;
			hit_min->shine_factor = obj->shine_factor;
			copy_vec3(&hit_min->origin, hit.origin);
			copy_vec3(&hit_min->dir, hit.dir);
			copy_vec3(&hit_min->color, *obj->color);
		}
		return (TRUE);
	}
	return (FALSE);
}

void	init_var_hit(_Bool *hit_obj, t_ray *hit, t_vec3 *color)
{
	*hit_obj = FALSE;
	hit->dist = 1E99;
	hit->pixel_shadow = 1;
	hit->obj_ref = -1;
	*color = create_vec3(0, 0, 0);
}

void	detect_intersection(
	t_ray ray, t_obj *obj, unsigned long *color, t_data *data)
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
		if (check_hit_object(&ray, &obj[i], &hit))
		{
			hit_obj = TRUE;
			hit.obj_ref = i;
		}
		i++;
	}
	if (hit_obj)
	{
		if (is_in_shadow(obj, hit, data->scene->diffuse_light))
			hit.pixel_shadow = 0.5;
		rgb = get_light(data, hit, ray);
	}
	*color = create_rgb_struct(&rgb);
}

void	run_raytracing(
	t_mlx *mlx, t_scene *scene, t_data *data, _Bool path_tracing)
{
	unsigned long	pixel_color;
	t_ray			cam_ray;

	init_image(mlx, data);
	init_camera_ray(&cam_ray, data);
	data->cam_to_world_matrix = built_cam_to_world_matrix(scene->camera);
	data->pixel_y = -1;
	while (++data->pixel_y < HEIGHT)
	{
		data->pixel_x = -1;
		while (++data->pixel_x < WIDTH)
		{
			if (path_tracing)
				run_path_tracing(&cam_ray, data->obj, &pixel_color, data);
			else
				detect_intersection(cam_ray, data->obj, &pixel_color, data);
			draw_pixel(mlx->image, pixel_color, data);
		}
	}
	display_cam_param(data->scene->camera);
	mlx_put_image_to_window(mlx->ptr, mlx->window, mlx->image->img_ptr, 0, 0);
}
